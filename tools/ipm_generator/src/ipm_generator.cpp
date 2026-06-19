#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#include <algorithm>
#include <array>
#include <cerrno>
#include <cmath>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>

namespace {

constexpr int kInputWidth = 640;
constexpr int kInputHeight = 360;
constexpr int kRawWidth = 160;
constexpr int kRawHeight = 120;
constexpr int kIpmWidth = 160;
constexpr int kIpmHeight = 120;
constexpr int kValidRowThreshold = 40;
constexpr double kEpsilon = 1e-9;
constexpr double kMinQuadrilateralArea = 1.0;
constexpr double kMaxHomographyReprojectionError = 0.25;
constexpr float kAtgRoadWidthMeters = 0.45f;
constexpr float kAtgPixelPerMeter = 116.0f;
constexpr float kTargetCenterX = static_cast<float>(kIpmWidth) * 0.5f;
constexpr float kTargetHalfRoadWidth = kAtgRoadWidthMeters * kAtgPixelPerMeter * 0.5f;

const std::array<cv::Point2f, 4> kDefaultTarget = {
    cv::Point2f(kTargetCenterX - kTargetHalfRoadWidth, 70.0f),  // left-bottom
    cv::Point2f(kTargetCenterX + kTargetHalfRoadWidth, 70.0f),  // right-bottom
    cv::Point2f(kTargetCenterX - kTargetHalfRoadWidth, 30.0f),  // left-top
    cv::Point2f(kTargetCenterX + kTargetHalfRoadWidth, 30.0f),  // right-top
};

struct Options {
    std::filesystem::path input_path;
    std::filesystem::path output_dir = "output";
    std::vector<cv::Point2f> points;
    bool no_window = false;
};

struct TableData {
    std::vector<float> raw_to_ipm_x;
    std::vector<float> raw_to_ipm_y;
    std::vector<int> undist_to_raw_x;
    std::vector<int> undist_to_raw_y;
};

struct PickState {
    cv::Mat image;
    std::vector<cv::Point2f> points;
    cv::Point cursor{-1, -1};
    bool has_cursor = false;
};

struct TunedTarget {
    std::array<cv::Point2f, 4> points;
    float shift_y;
};

void print_usage(const char *argv0)
{
    std::cerr
        << "Usage:\n"
        << "  " << argv0 << " --input <640x360_gray.png> [--out <dir>]\n"
        << "  " << argv0 << " --input <image> --points x1,y1,x2,y2,x3,y3,x4,y4 [--out <dir>] [--no-window]\n\n"
        << "Point order: left-bottom, right-bottom, left-top, right-top.\n";
}

std::vector<std::string> split(const std::string &text, char delim)
{
    std::vector<std::string> out;
    std::stringstream ss(text);
    std::string item;
    while(std::getline(ss, item, delim)) {
        out.push_back(item);
    }
    return out;
}

std::string trim(const std::string &text)
{
    const char *space = " \t\r\n";
    const size_t begin = text.find_first_not_of(space);
    if(begin == std::string::npos) {
        return "";
    }
    const size_t end = text.find_last_not_of(space);
    return text.substr(begin, end - begin + 1);
}

float parse_float_strict(const std::string &raw)
{
    const std::string text = trim(raw);
    if(text.empty()) {
        throw std::runtime_error("--points contains an empty value");
    }

    errno = 0;
    char *end = nullptr;
    const float value = std::strtof(text.c_str(), &end);
    if(end == text.c_str() || *end != '\0' || errno == ERANGE) {
        throw std::runtime_error("invalid --points numeric value: " + raw);
    }
    return value;
}

std::vector<cv::Point2f> parse_points(const std::string &arg)
{
    if(std::count(arg.begin(), arg.end(), ',') != 7) {
        throw std::runtime_error("--points expects 8 comma-separated numbers");
    }

    const std::vector<std::string> parts = split(arg, ',');
    if(parts.size() != 8) {
        throw std::runtime_error("--points expects 8 comma-separated numbers");
    }

    std::vector<cv::Point2f> points;
    points.reserve(4);
    for(size_t i = 0; i < parts.size(); i += 2) {
        const float x = parse_float_strict(parts[i]);
        const float y = parse_float_strict(parts[i + 1]);
        points.emplace_back(x, y);
    }
    return points;
}

Options parse_args(int argc, char **argv)
{
    Options options;
    for(int i = 1; i < argc; ++i) {
        const std::string arg = argv[i];
        if(arg == "--input" && i + 1 < argc) {
            options.input_path = argv[++i];
        } else if(arg == "--out" && i + 1 < argc) {
            options.output_dir = argv[++i];
        } else if(arg == "--points" && i + 1 < argc) {
            options.points = parse_points(argv[++i]);
        } else if(arg == "--no-window") {
            options.no_window = true;
        } else if(arg == "--help" || arg == "-h") {
            print_usage(argv[0]);
            std::exit(0);
        } else {
            throw std::runtime_error("unknown or incomplete argument: " + arg);
        }
    }

    if(options.input_path.empty()) {
        throw std::runtime_error("--input is required");
    }
    if(options.no_window && options.points.empty()) {
        throw std::runtime_error("--no-window requires --points");
    }
    if(!options.points.empty() && options.points.size() != 4) {
        throw std::runtime_error("exactly four points are required");
    }
    return options;
}

cv::Mat read_gray_image(const std::filesystem::path &path)
{
    cv::Mat image = cv::imread(path.string(), cv::IMREAD_GRAYSCALE);
    if(image.empty()) {
        throw std::runtime_error("failed to read image: " + path.string());
    }
    if(image.cols != kInputWidth || image.rows != kInputHeight) {
        std::ostringstream oss;
        oss << "expected 640x360 input, got " << image.cols << "x" << image.rows;
        throw std::runtime_error(oss.str());
    }
    return image;
}

std::array<cv::Point2f, 4> scale_points_to_runtime(const std::vector<cv::Point2f> &points)
{
    std::array<cv::Point2f, 4> scaled{};
    const float sx = static_cast<float>(kRawWidth) / static_cast<float>(kInputWidth);
    const float sy = static_cast<float>(kRawHeight) / static_cast<float>(kInputHeight);
    for(size_t i = 0; i < scaled.size(); ++i) {
        scaled[i] = cv::Point2f(points[i].x * sx, points[i].y * sy);
    }
    return scaled;
}

void validate_input_points(const std::vector<cv::Point2f> &points)
{
    if(points.size() != 4) {
        throw std::runtime_error("exactly four points are required");
    }

    for(size_t i = 0; i < points.size(); ++i) {
        const cv::Point2f &pt = points[i];
        if(!std::isfinite(pt.x) || !std::isfinite(pt.y) ||
           pt.x < 0.0f || pt.x >= static_cast<float>(kInputWidth) ||
           pt.y < 0.0f || pt.y >= static_cast<float>(kInputHeight)) {
            std::ostringstream oss;
            oss << "point " << (i + 1) << " is outside 640x360 input bounds: "
                << pt.x << "," << pt.y;
            throw std::runtime_error(oss.str());
        }
    }
}

void draw_selection(cv::Mat &view, const std::vector<cv::Point2f> &points)
{
    static const char *labels[] = {"LB", "RB", "LT", "RT"};
    for(size_t i = 0; i < points.size(); ++i) {
        cv::circle(view, points[i], 5, cv::Scalar(0, 255, 255), cv::FILLED);
        cv::putText(view, labels[i], points[i] + cv::Point2f(7.0f, -7.0f),
                    cv::FONT_HERSHEY_SIMPLEX, 0.55, cv::Scalar(0, 255, 255), 1, cv::LINE_AA);
    }

    if(points.size() >= 2) {
        cv::line(view, points[0], points[1], cv::Scalar(0, 220, 0), 2, cv::LINE_AA);
    }
    if(points.size() >= 3) {
        cv::line(view, points[0], points[2], cv::Scalar(0, 220, 0), 2, cv::LINE_AA);
    }
    if(points.size() == 4) {
        cv::line(view, points[1], points[3], cv::Scalar(0, 220, 0), 2, cv::LINE_AA);
        cv::line(view, points[2], points[3], cv::Scalar(0, 220, 0), 2, cv::LINE_AA);
    }
}

void mouse_callback(int event, int x, int y, int, void *userdata)
{
    auto *state = static_cast<PickState *>(userdata);
    if(event == cv::EVENT_MOUSEMOVE) {
        state->cursor = cv::Point(x, y);
        state->has_cursor = true;
        return;
    }
    if(event != cv::EVENT_LBUTTONDOWN) {
        return;
    }
    if(state->points.size() < 4) {
        state->points.emplace_back(static_cast<float>(x), static_cast<float>(y));
    }
}

// 底层参考层：图像竖直中线(辅助左右对称) + 鼠标十字准线 + 坐标。
void draw_guides(cv::Mat &view, const PickState &state)
{
    cv::line(view, cv::Point(kInputWidth / 2, 0), cv::Point(kInputWidth / 2, kInputHeight - 1),
             cv::Scalar(110, 110, 110), 1, cv::LINE_AA);

    if(!state.has_cursor) {
        return;
    }
    const cv::Point c = state.cursor;
    if(c.x < 0 || c.x >= kInputWidth || c.y < 0 || c.y >= kInputHeight) {
        return;
    }
    cv::line(view, cv::Point(0, c.y), cv::Point(kInputWidth - 1, c.y),
             cv::Scalar(0, 180, 255), 1, cv::LINE_AA);
    cv::line(view, cv::Point(c.x, 0), cv::Point(c.x, kInputHeight - 1),
             cv::Scalar(0, 180, 255), 1, cv::LINE_AA);
}

// 局部放大镜：鼠标周围区域放大到鼠标对侧角，中心红十字对应当前精确像素。
// 只在还没标满 4 点时显示(标点过程辅助)。
void draw_magnifier(cv::Mat &view, const PickState &state)
{
    if(state.points.size() >= 4 || !state.has_cursor) {
        return;
    }
    const cv::Point c = state.cursor;
    if(c.x < 0 || c.x >= kInputWidth || c.y < 0 || c.y >= kInputHeight) {
        return;
    }

    const int src_half = 18;
    const int zoom = 6;
    const int x0 = std::clamp(c.x - src_half, 0, kInputWidth - 1);
    const int y0 = std::clamp(c.y - src_half, 0, kInputHeight - 1);
    const int x1 = std::clamp(c.x + src_half, 0, kInputWidth - 1);
    const int y1 = std::clamp(c.y + src_half, 0, kInputHeight - 1);
    if(x1 - x0 < 4 || y1 - y0 < 4) {
        return;
    }

    cv::Mat patch = state.image(cv::Rect(x0, y0, x1 - x0, y1 - y0)).clone();
    cv::Mat mag;
    cv::resize(patch, mag, cv::Size((x1 - x0) * zoom, (y1 - y0) * zoom), 0, 0, cv::INTER_NEAREST);
    const int mcx = (c.x - x0) * zoom;
    const int mcy = (c.y - y0) * zoom;
    cv::line(mag, cv::Point(mcx - 9, mcy), cv::Point(mcx + 9, mcy), cv::Scalar(0, 0, 255), 1);
    cv::line(mag, cv::Point(mcx, mcy - 9), cv::Point(mcx, mcy + 9), cv::Scalar(0, 0, 255), 1);

    // 放大镜放鼠标对侧角，避免遮挡正在标的区域。
    int px = (c.x < kInputWidth / 2) ? (kInputWidth - mag.cols - 10) : 10;
    int py = (c.y < kInputHeight / 2) ? (kInputHeight - mag.rows - 10) : 84;
    px = std::clamp(px, 0, kInputWidth - mag.cols);
    py = std::clamp(py, 0, kInputHeight - mag.rows);
    mag.copyTo(view(cv::Rect(px, py, mag.cols, mag.rows)));
    cv::rectangle(view, cv::Rect(px, py, mag.cols, mag.rows), cv::Scalar(0, 180, 255), 1);

    std::ostringstream oss;
    oss << "(" << c.x << "," << c.y << ")";
    cv::putText(view, oss.str(), cv::Point(px, std::max(12, py - 4)),
                cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 180, 255), 1, cv::LINE_AA);
}

// 4 点齐后的即时验收：用标的四点把当前图 warp 成矩形预览。
// 标得好则赛道左右边线会贴合两条红色竖直参考线；歪/弯说明四点要微调。
// 这是纯标点质量预览(输入图域)，不依赖运行时 raw/IPM 坐标，不写任何文件。
void draw_preview(cv::Mat &view, const PickState &state)
{
    if(state.points.size() != 4) {
        return;
    }

    const int pw = 180;
    const int ph = 240;
    const float lx = pw * 0.32f;
    const float rx = pw * 0.68f;
    const std::vector<cv::Point2f> src = {state.points[0], state.points[1],
                                          state.points[2], state.points[3]};
    const std::vector<cv::Point2f> dst = {
        cv::Point2f(lx, ph * 0.95f),  // LB
        cv::Point2f(rx, ph * 0.95f),  // RB
        cv::Point2f(lx, ph * 0.05f),  // LT
        cv::Point2f(rx, ph * 0.05f),  // RT
    };

    cv::Mat homography = cv::getPerspectiveTransform(src, dst);
    cv::Mat preview;
    cv::warpPerspective(state.image, preview, homography, cv::Size(pw, ph));
    cv::line(preview, cv::Point(static_cast<int>(lx), 0), cv::Point(static_cast<int>(lx), ph - 1),
             cv::Scalar(0, 0, 255), 1, cv::LINE_AA);
    cv::line(preview, cv::Point(static_cast<int>(rx), 0), cv::Point(static_cast<int>(rx), ph - 1),
             cv::Scalar(0, 0, 255), 1, cv::LINE_AA);

    const int px = std::clamp(kInputWidth - pw - 10, 0, kInputWidth - pw);
    const int py = std::clamp(kInputHeight - ph - 10, 0, kInputHeight - ph);
    preview.copyTo(view(cv::Rect(px, py, pw, ph)));
    cv::rectangle(view, cv::Rect(px, py, pw, ph), cv::Scalar(0, 0, 255), 1);
    cv::putText(view, "preview: road edges hug red lines = good", cv::Point(px, std::max(12, py - 4)),
                cv::FONT_HERSHEY_SIMPLEX, 0.42, cv::Scalar(0, 0, 255), 1, cv::LINE_AA);
}

std::vector<cv::Point2f> pick_points_interactive(const cv::Mat &gray)
{
    PickState state;
    cv::cvtColor(gray, state.image, cv::COLOR_GRAY2BGR);

    const std::string window_name = "IPM point picker";
    cv::namedWindow(window_name, cv::WINDOW_NORMAL);
    cv::resizeWindow(window_name, kInputWidth, kInputHeight);
    cv::setMouseCallback(window_name, mouse_callback, &state);

    std::cerr << "Click four points in order: left-bottom, right-bottom, left-top, right-top.\n"
              << "Keys: u=undo, r=reset, enter/space=accept after 4 points, esc=abort.\n";

    for(;;) {
        cv::Mat view = state.image.clone();
        draw_guides(view, state);
        draw_selection(view, state.points);
        draw_magnifier(view, state);
        draw_preview(view, state);
        cv::putText(view, "Order: LB -> RB -> LT -> RT", cv::Point(14, 26),
                    cv::FONT_HERSHEY_SIMPLEX, 0.65, cv::Scalar(0, 255, 255), 2, cv::LINE_AA);
        cv::putText(view, "u undo | r reset | enter accept | esc abort", cv::Point(14, 52),
                    cv::FONT_HERSHEY_SIMPLEX, 0.55, cv::Scalar(0, 255, 255), 1, cv::LINE_AA);
        cv::imshow(window_name, view);

        const int key = cv::waitKey(30);
        if(key == 27) {
            cv::destroyWindow(window_name);
            throw std::runtime_error("point picking aborted");
        }
        if(key == 'u' || key == 'U') {
            if(!state.points.empty()) {
                state.points.pop_back();
            }
        } else if(key == 'r' || key == 'R') {
            state.points.clear();
        } else if((key == 13 || key == 10 || key == ' ') && state.points.size() == 4) {
            break;
        }
    }

    cv::destroyWindow(window_name);
    return state.points;
}

TunedTarget shifted_target(float dy)
{
    std::array<cv::Point2f, 4> target = kDefaultTarget;
    float min_y = target.front().y;
    float max_y = target.front().y;
    for(const cv::Point2f &pt : target) {
        min_y = std::min(min_y, pt.y);
        max_y = std::max(max_y, pt.y);
    }

    const float clamped_dy = std::clamp(dy, -min_y, static_cast<float>(kIpmHeight - 1) - max_y);
    for(cv::Point2f &pt : target) {
        pt.y += clamped_dy;
    }
    return {target, clamped_dy};
}

double ordered_quadrilateral_area(const std::array<cv::Point2f, 4> &points)
{
    const std::array<size_t, 4> polygon_order = {0, 1, 3, 2};
    double twice_area = 0.0;
    for(size_t i = 0; i < polygon_order.size(); ++i) {
        const cv::Point2f &a = points[polygon_order[i]];
        const cv::Point2f &b = points[polygon_order[(i + 1) % polygon_order.size()]];
        twice_area += static_cast<double>(a.x) * static_cast<double>(b.y) -
                      static_cast<double>(b.x) * static_cast<double>(a.y);
    }
    return std::abs(twice_area) * 0.5;
}

void validate_quadrilateral(const std::array<cv::Point2f, 4> &points, const std::string &name)
{
    for(const cv::Point2f &pt : points) {
        if(!std::isfinite(pt.x) || !std::isfinite(pt.y)) {
            throw std::runtime_error(name + " contain non-finite coordinates");
        }
    }

    if(ordered_quadrilateral_area(points) < kMinQuadrilateralArea) {
        throw std::runtime_error(name + " do not form a valid quadrilateral");
    }
}

bool project_point(const cv::Mat &h, double x, double y, double &out_x, double &out_y)
{
    const double h00 = h.at<double>(0, 0);
    const double h01 = h.at<double>(0, 1);
    const double h02 = h.at<double>(0, 2);
    const double h10 = h.at<double>(1, 0);
    const double h11 = h.at<double>(1, 1);
    const double h12 = h.at<double>(1, 2);
    const double h20 = h.at<double>(2, 0);
    const double h21 = h.at<double>(2, 1);
    const double h22 = h.at<double>(2, 2);

    const double denom = h20 * x + h21 * y + h22;
    if(std::abs(denom) < kEpsilon) {
        return false;
    }
    out_x = (h00 * x + h01 * y + h02) / denom;
    out_y = (h10 * x + h11 * y + h12) / denom;
    return std::isfinite(out_x) && std::isfinite(out_y);
}

void validate_homography_projection(const cv::Mat &h,
                                    const std::array<cv::Point2f, 4> &src,
                                    const std::array<cv::Point2f, 4> &dst)
{
    for(size_t i = 0; i < src.size(); ++i) {
        double x = 0.0;
        double y = 0.0;
        if(!project_point(h, src[i].x, src[i].y, x, y)) {
            throw std::runtime_error("failed to compute a valid homography");
        }

        const double error = std::hypot(x - static_cast<double>(dst[i].x),
                                        y - static_cast<double>(dst[i].y));
        if(error > kMaxHomographyReprojectionError) {
            throw std::runtime_error("homography reprojection check failed");
        }
    }
}

cv::Mat find_homography_checked(const std::array<cv::Point2f, 4> &src,
                                const std::array<cv::Point2f, 4> &dst)
{
    validate_quadrilateral(src, "source points");
    validate_quadrilateral(dst, "target points");

    cv::Mat h = cv::getPerspectiveTransform(src.data(), dst.data());
    if(h.empty() || h.type() != CV_64F || !cv::checkRange(h) ||
       std::abs(cv::determinant(h)) < kEpsilon) {
        throw std::runtime_error("failed to compute a valid homography");
    }
    validate_homography_projection(h, src, dst);
    return h;
}

cv::Mat warp_to_ipm(const cv::Mat &runtime_gray, const cv::Mat &raw_to_ipm)
{
    cv::Mat ipm;
    cv::warpPerspective(runtime_gray, ipm, raw_to_ipm, cv::Size(kIpmWidth, kIpmHeight),
                        cv::INTER_NEAREST, cv::BORDER_CONSTANT, cv::Scalar(255));
    return ipm;
}

cv::Mat warp_valid_mask(const cv::Size &runtime_size, const cv::Mat &raw_to_ipm)
{
    cv::Mat source_mask(runtime_size, CV_8UC1, cv::Scalar(255));
    cv::Mat ipm_mask;
    cv::warpPerspective(source_mask, ipm_mask, raw_to_ipm, cv::Size(kIpmWidth, kIpmHeight),
                        cv::INTER_NEAREST, cv::BORDER_CONSTANT, cv::Scalar(0));
    return ipm_mask;
}

int find_effective_top_row(const cv::Mat &ipm_valid_mask)
{
    for(int y = kIpmHeight - 1; y >= 0; --y) {
        int valid_count = 0;
        for(int x = 0; x < kIpmWidth; ++x) {
            if(ipm_valid_mask.at<uint8_t>(y, x) != 0) {
                ++valid_count;
            }
        }
        if(valid_count > kValidRowThreshold) {
            return y + 1;
        }
    }
    return kIpmHeight;
}

float compute_tuning_shift(const cv::Mat &initial_valid_mask)
{
    const int effective_top = find_effective_top_row(initial_valid_mask);
    const int shift = kIpmHeight - effective_top;
    return static_cast<float>(shift);
}

cv::Mat annotate_original(const cv::Mat &gray, const std::vector<cv::Point2f> &points)
{
    cv::Mat annotated;
    cv::cvtColor(gray, annotated, cv::COLOR_GRAY2BGR);
    draw_selection(annotated, points);
    return annotated;
}

void write_matrix_text(const std::filesystem::path &path, const cv::Mat &matrix)
{
    std::ofstream out(path);
    if(!out) {
        throw std::runtime_error("failed to write " + path.string());
    }
    out << std::fixed << std::setprecision(10);
    for(int r = 0; r < 3; ++r) {
        for(int c = 0; c < 3; ++c) {
            if(c > 0) {
                out << ' ';
            }
            out << matrix.at<double>(r, c);
        }
        out << '\n';
    }
}

void write_metadata(const std::filesystem::path &path,
                    const std::vector<cv::Point2f> &input_points,
                    const std::array<cv::Point2f, 4> &runtime_points,
                    const std::array<cv::Point2f, 4> &target_initial,
                    const std::array<cv::Point2f, 4> &target_tuned,
                    float tune_shift)
{
    std::ofstream out(path);
    if(!out) {
        throw std::runtime_error("failed to write " + path.string());
    }
    out << std::fixed << std::setprecision(6);
    out << "{\n";
    out << "  \"input_size\": [640, 360],\n";
    out << "  \"runtime_size\": [160, 120],\n";
    out << "  \"point_order\": [\"left-bottom\", \"right-bottom\", \"left-top\", \"right-top\"],\n";
    out << "  \"input_points\": [\n";
    for(size_t i = 0; i < input_points.size(); ++i) {
        out << "    [" << input_points[i].x << ", " << input_points[i].y << "]"
            << (i + 1 == input_points.size() ? "\n" : ",\n");
    }
    out << "  ],\n";
    out << "  \"runtime_points\": [\n";
    for(size_t i = 0; i < runtime_points.size(); ++i) {
        out << "    [" << runtime_points[i].x << ", " << runtime_points[i].y << "]"
            << (i + 1 == runtime_points.size() ? "\n" : ",\n");
    }
    out << "  ],\n";
    out << "  \"target_initial\": [\n";
    for(size_t i = 0; i < target_initial.size(); ++i) {
        out << "    [" << target_initial[i].x << ", " << target_initial[i].y << "]"
            << (i + 1 == target_initial.size() ? "\n" : ",\n");
    }
    out << "  ],\n";
    out << "  \"target_tuned\": [\n";
    for(size_t i = 0; i < target_tuned.size(); ++i) {
        out << "    [" << target_tuned[i].x << ", " << target_tuned[i].y << "]"
            << (i + 1 == target_tuned.size() ? "\n" : ",\n");
    }
    out << "  ],\n";
    out << "  \"tune_shift_y\": " << tune_shift << "\n";
    out << "}\n";
}

TableData generate_tables(const cv::Mat &raw_to_ipm)
{
    TableData table;
    table.raw_to_ipm_x.assign(kRawWidth * kRawHeight, -1.0f);
    table.raw_to_ipm_y.assign(kRawWidth * kRawHeight, -1.0f);
    table.undist_to_raw_x.assign(kRawWidth * kRawHeight, -1);
    table.undist_to_raw_y.assign(kRawWidth * kRawHeight, -1);

    for(int y = 0; y < kRawHeight; ++y) {
        for(int x = 0; x < kRawWidth; ++x) {
            const int idx = y * kRawWidth + x;
            table.undist_to_raw_x[idx] = x;
            table.undist_to_raw_y[idx] = y;

            double ix = -1.0;
            double iy = -1.0;
            if(project_point(raw_to_ipm, x, y, ix, iy) &&
               ix >= 0.0 && ix < static_cast<double>(kIpmWidth) &&
               iy >= 0.0 && iy < static_cast<double>(kIpmHeight)) {
                table.raw_to_ipm_x[idx] = static_cast<float>(ix);
                table.raw_to_ipm_y[idx] = static_cast<float>(iy);
            }
        }
    }

    return table;
}

void write_reference_array_2d(std::ofstream &out,
                              const std::string &type,
                              const std::string &name,
                              const std::vector<float> &data,
                              int precision)
{
    out << "AT_SDRAM_SECTION_ALIGN_INIT(" << type << ' ' << name
        << "[MT9V03X_CSI_H][MT9V03X_CSI_W], 64) = {\n";
    for(int y = 0; y < kRawHeight; ++y) {
        out << "    {";
        for(int x = 0; x < kRawWidth; ++x) {
            if(x > 0) {
                out << ", ";
            }
            out << std::fixed << std::setprecision(precision) << data[y * kRawWidth + x];
        }
        out << (y + 1 == kRawHeight ? "}\n" : "},\n");
    }
    out << "};\n\n";
}

void write_reference_array_2d(std::ofstream &out,
                              const std::string &type,
                              const std::string &name,
                              const std::vector<int> &data)
{
    out << "AT_SDRAM_SECTION_ALIGN_INIT(" << type << ' ' << name
        << "[MT9V03X_CSI_H][MT9V03X_CSI_W], 64) = {\n";
    for(int y = 0; y < kRawHeight; ++y) {
        out << "    {";
        for(int x = 0; x < kRawWidth; ++x) {
            if(x > 0) {
                out << ", ";
            }
            out << data[y * kRawWidth + x];
        }
        out << (y + 1 == kRawHeight ? "}\n" : "},\n");
    }
    out << "};\n\n";
}

void write_matrix_c(std::ofstream &out, const std::string &name, const cv::Mat &matrix)
{
    out << "AT_DTCM_SECTION_ALIGN_INIT(float " << name << "[3][3], 8) = {";
    for(int r = 0; r < 3; ++r) {
        out << (r == 0 ? "{" : "                                                {");
        for(int c = 0; c < 3; ++c) {
            if(c > 0) {
                out << ", ";
            }
            out << std::scientific << std::setprecision(8)
                << static_cast<float>(matrix.at<double>(r, c)) << "f";
        }
        out << (r == 2 ? "}}" : "},\n");
    }
    out << ";\n";
}

void write_camera_param_c(const std::filesystem::path &path,
                          const TableData &table,
                          const cv::Mat &raw_to_ipm,
                          const cv::Mat &ipm_to_raw)
{
    std::ofstream out(path);
    if(!out) {
        throw std::runtime_error("failed to write " + path.string());
    }
    out << "#include \"camera_param.h\"\n";
    out << "#include \"common.h\"\n\n";
    out << "// Generated by ipm_generator from a 640x360 grayscale calibration image.\n";
    out << "// Runtime coordinate contract: raw/IPM are both 160x120; negative mapx/mapy values mean no valid mapping.\n";
    out << "// No lens distortion is modeled here, so invx/invy are identity undistorted-raw -> raw tables.\n\n";

    out << "AT_DTCM_SECTION_ALIGN_INIT(float K[3][3], 8) = {{1.0f, 0.0f, 0.0f},\n";
    out << "                                                {0.0f, 1.0f, 0.0f},\n";
    out << "                                                {0.0f, 0.0f, 1.0f}};\n";
    out << "AT_DTCM_SECTION_ALIGN_INIT(float D[4], 8) = {0.0f, 0.0f, 0.0f, 0.0f};\n";
    write_matrix_c(out, "H", ipm_to_raw);
    write_matrix_c(out, "H_inv", raw_to_ipm);
    out << "\n";
    out << "bool map_inv(float pt0[2], int pt1[2])\n";
    out << "{\n";
    out << "    if(pt0 == NULL || pt1 == NULL)\n";
    out << "    {\n";
    out << "        return false;\n";
    out << "    }\n\n";
    out << "    const float den = H[2][0] * pt0[0] + H[2][1] * pt0[1] + H[2][2];\n";
    out << "    if(den == 0.0f)\n";
    out << "    {\n";
    out << "        return false;\n";
    out << "    }\n\n";
    out << "    const int rx = (int)(0.5f + (H[0][0] * pt0[0] + H[0][1] * pt0[1] + H[0][2]) / den);\n";
    out << "    const int ry = (int)(0.5f + (H[1][0] * pt0[0] + H[1][1] * pt0[1] + H[1][2]) / den);\n";
    out << "    if(rx < 0 || rx >= MT9V03X_CSI_W || ry < 0 || ry >= MT9V03X_CSI_H)\n";
    out << "    {\n";
    out << "        return false;\n";
    out << "    }\n\n";
    out << "    const int ix = invx[ry][rx];\n";
    out << "    const int iy = invy[ry][rx];\n";
    out << "    if(ix < 0 || ix >= MT9V03X_CSI_W || iy < 0 || iy >= MT9V03X_CSI_H)\n";
    out << "    {\n";
    out << "        return false;\n";
    out << "    }\n\n";
    out << "    pt1[0] = ix;\n";
    out << "    pt1[1] = iy;\n";
    out << "    return true;\n";
    out << "}\n\n";

    out << "// raw -> IPM x: mapx[raw_y][raw_x] = IPM column, <0 means outside view.\n";
    write_reference_array_2d(out, "float", "mapx", table.raw_to_ipm_x, 5);
    out << "// raw -> IPM y: mapy[raw_y][raw_x] = IPM row, <0 means outside view.\n";
    write_reference_array_2d(out, "float", "mapy", table.raw_to_ipm_y, 5);
    out << "// undistorted raw -> raw x, identity for the current no-distortion model.\n";
    write_reference_array_2d(out, "int", "invx", table.undist_to_raw_x);
    out << "// undistorted raw -> raw y, identity for the current no-distortion model.\n";
    write_reference_array_2d(out, "int", "invy", table.undist_to_raw_y);
}

void ensure_write_image(const std::filesystem::path &path, const cv::Mat &image)
{
    if(!cv::imwrite(path.string(), image)) {
        throw std::runtime_error("failed to write image: " + path.string());
    }
}

void run(const Options &options)
{
    const cv::Mat input_gray = read_gray_image(options.input_path);
    std::vector<cv::Point2f> input_points = options.points;
    if(input_points.empty()) {
        input_points = pick_points_interactive(input_gray);
    }

    validate_input_points(input_points);

    cv::Mat runtime_gray;
    cv::resize(input_gray, runtime_gray, cv::Size(kRawWidth, kRawHeight), 0.0, 0.0, cv::INTER_AREA);

    const std::array<cv::Point2f, 4> runtime_points = scale_points_to_runtime(input_points);
    const cv::Mat initial_h = find_homography_checked(runtime_points, kDefaultTarget);
    const cv::Mat initial_ipm = warp_to_ipm(runtime_gray, initial_h);
    const cv::Mat initial_valid_mask = warp_valid_mask(runtime_gray.size(), initial_h);

    const TunedTarget tuned_target = shifted_target(compute_tuning_shift(initial_valid_mask));
    const cv::Mat tuned_h = find_homography_checked(runtime_points, tuned_target.points);
    const cv::Mat tuned_h_inv = tuned_h.inv();
    const cv::Mat tuned_ipm = warp_to_ipm(runtime_gray, tuned_h);
    const TableData tables = generate_tables(tuned_h);

    std::filesystem::create_directories(options.output_dir);
    ensure_write_image(options.output_dir / "preview_original_points.png",
                       annotate_original(input_gray, input_points));
    ensure_write_image(options.output_dir / "preview_ipm_initial.png", initial_ipm);
    ensure_write_image(options.output_dir / "preview_ipm_tuned.png", tuned_ipm);
    write_matrix_text(options.output_dir / "ipm_matrix_initial.txt", initial_h);
    write_matrix_text(options.output_dir / "ipm_matrix_tuned.txt", tuned_h);
    write_metadata(options.output_dir / "selected_points.json", input_points, runtime_points,
                   kDefaultTarget, tuned_target.points, tuned_target.shift_y);
    write_camera_param_c(options.output_dir / "camera_param.c", tables, tuned_h, tuned_h_inv);

    std::cout << "IPM generation complete.\n";
    std::cout << "Output: " << options.output_dir << "\n";
    std::cout << "Tune shift y: " << tuned_target.shift_y << "\n";
}

} // namespace

int main(int argc, char **argv)
{
    try {
        const Options options = parse_args(argc, argv);
        run(options);
    } catch(const std::exception &ex) {
        std::cerr << "error: " << ex.what() << "\n\n";
        print_usage(argv[0]);
        return 1;
    }
    return 0;
}
