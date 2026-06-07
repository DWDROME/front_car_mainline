/*
* CD.cpp - 跨平台动态链接库实现
* 
* ============================================================================
* DLL动态链接库编写规则和使用方法
* ============================================================================
* 
* 【DLL编写规则】
* 1. 导出函数声明：
*    - 使用 DLL_EXPORT 宏定义导出函数
*    - 格式：DLL_EXPORT 返回类型 __stdcall 函数名(参数列表)
*    - 示例：DLL_EXPORT void __stdcall init_DLL()
* 
* 2. 调用约定：
*    - 统一使用 __stdcall 调用约定
*    - 确保与调用方（仿真软件）的调用约定一致
* 
* 3. 数据类型：
*    - 使用标准C++数据类型：uint8_t, int32_t, float等
*    - 避免使用C++特有类型（如string, vector等）
*    - 结构体使用C风格定义
* 
* 4. 内存管理：
*    - 避免动态内存分配（new/delete）
*    - 使用静态数组或栈内存
*    - 确保内存安全，避免内存泄漏
* 
* 5. 错误处理：
*    - 使用返回值或全局变量表示错误状态
*    - 避免抛出异常（C++异常在DLL边界可能有问题）
* 
* 6. 线程安全：
*    - 如果DLL可能被多线程调用，确保函数线程安全
*    - 使用适当的同步机制
* 
* 【接口函数说明】
* ============================================================================
* 
* 1. 初始化函数：
*    DLL_EXPORT void __stdcall init_DLL()
*    - 功能：DLL初始化，设置默认参数
*    - 调用时机：仿真软件启动时调用一次
*    - 作用：初始化全局变量、设置默认配置
* 
* 2. 图像处理函数：
*    DLL_EXPORT void __stdcall Camera_Deal(uint8* dst, Car_Data& CD)
*    - 功能：核心图像处理和控制逻辑
*    - 参数：dst - 图像数据数组，CD - 车辆数据结构体
*    - 调用时机：每帧图像处理时调用
*    - 作用：图像二值化、边界检测、路径规划、控制输出
* 
* 3. 参数修改函数：
*    DLL_EXPORT void __stdcall value_change(uint8 value_type, float value)
*    - 功能：实时修改算法参数
*    - 参数：value_type - 参数类型，value - 新参数值
*    - 调用时机：用户通过UI修改参数时
*    - 作用：动态调整算法行为
* 
* 4. 按钮响应函数：
*    DLL_EXPORT void __stdcall get_button_state(uint8 button_state)
*    - 功能：响应键盘按键事件
*    - 参数：button_state - 按键状态（1,2,3,4...）
*    - 调用时机：用户按下对应按键时
*    - 作用：触发特定功能（数据收集、参数调整等）
* 
* 5. 调试输出函数：
*    void printf(const char* format, ...)
*    - 功能：调试信息输出
*    - 参数：format - 格式化字符串，... - 可变参数
*    - 作用：在仿真软件界面显示调试信息
* 
* 【数据结构说明】
* ============================================================================
* 
* Car_Data 结构体（车辆数据交换）：
* - 输入数据：
*   * int32 LE, RE;    // 左右编码器数据
*   * float HA;        // 水平转角数据（陀螺仪）
* 
* - 输出数据：
*   * float SA;        // 舵机转角控制
*   * int32 LM, RM;    // 左右电机转速控制
*   * int32 BZ;        // 蜂鸣器控制
* 
* 【图像数据格式】
* ============================================================================
* 
* 图像数组规则：
* - 0: 黑色（背景）
* - 1: 白色（赛道）
* - 2: 红色（边界标记）
* - 3: 绿色（路径标记）
* - 4: 蓝色（特殊标记）
* - 5: 黄色（调试标记）
* - 9: 灰色（额外填充区域）
* 
* 【编译配置】
* ============================================================================
* 
* 1. 编译设置：
*    - 平台：x86 或 x64（与仿真软件一致）
*    - 运行时库：多线程DLL (/MD)
*    - 优化：根据需求选择（Debug/Release）
* 
* 2. 链接设置：
*    - 输出文件：CD.dll
*    - 模块定义文件：可选
*    - 导入库：自动生成CD.lib
* 
* 【使用流程】
* ============================================================================
* 
* 1. 仿真软件启动：
*    - 加载CD.dll
*    - 调用init_DLL()初始化
* 
* 2. 运行循环：
*    - 获取传感器数据
*    - 调用Camera_Deal()处理图像和控制
*    - 应用控制输出到车辆
* 
* 3. 用户交互：
*    - UI参数修改 → value_change()
*    - 按键操作 → get_button_state()
*    - 调试信息 → printf()显示
* 
* 【注意事项】
* ============================================================================
* 
* 1. 性能优化：
*    - 避免频繁的内存分配
*    - 使用查表法优化计算
*    - 合理使用内联函数
* 
* 2. 调试技巧：
*    - 使用printf输出关键变量
*    - 在图像上标记关键点
*    - 记录算法执行时间
* 
* 3. 兼容性：
*    - 确保数据类型大小一致
*    - 注意字节对齐问题
*    - 测试不同编译器版本
* 
* 4. 错误处理：
*    - 检查输入参数有效性
*    - 处理边界情况
*    - 提供错误恢复机制
* 
* ============================================================================
* 
* 作者：[Blight001]
* 创建日期：[2025-05-25]
* 最后修改：[2025-05-25]
* 版本：[1.0]
*/

#include <windows.h>
#include <cstdint> 
#include <cstdlib> 
#include <cstring> 
#include <cstdio>
#include <cstdarg>
#include <direct.h> // Windows 下创建目录
#include <io.h>     // 检查目录是否存在
//生成DLL时添加的宏定义
#ifdef _WIN32
#define DLL_EXPORT extern "C" __declspec(dllexport)
#endif

BOOL APIENTRY DllMain(HMODULE , DWORD ul_reason_for_call, LPVOID) 
{
    switch (ul_reason_for_call) 
    {
        case DLL_PROCESS_ATTACH:
        case DLL_PROCESS_DETACH:
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
            break;
    }
    return TRUE;
}
///////////////////////////////////////////////////////////
// 修改回调函数参数（只保留消息）
typedef void(__stdcall* DebugCallback)(const char* message);
DebugCallback s_debugCallback = nullptr;
DLL_EXPORT void __stdcall SetDebugCallback(DebugCallback callback) {s_debugCallback = callback;}
// 包装函数：将printf参数格式化为字符串并触发回调
void __stdcall CustomPrintf(const char* format, ...) {
    if (!s_debugCallback || !format) return;

    // 格式化可变参数
    char buffer[1024] = {0};  // 初始化为0
    va_list args;
    va_start(args, format);
    int len = vsnprintf(buffer, sizeof(buffer) - 1, format, args);  // 保留一个字节给null终止符
    va_end(args);

    // 确保字符串正确终止
    if (len >= 0 && len < sizeof(buffer)) {
        buffer[len] = '\0';
        // 触发回调
        s_debugCallback(buffer);
    }
}
// 宏替换：重定向printf到自定义回调
#define printf(format, ...) CustomPrintf(format, ##__VA_ARGS__)

#define system_delay_ms(time)  (Sleep(time*1))


///////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// 定义内容 ///////////////////////////////////////////////

#define uint8 uint8_t
#define int32 int32_t

#define UVC_WIDTH 160
#define UVC_HEIGHT 120

// 记忆数据大小
#define remember_data_size 3600
// 数据记忆结构体
struct remember_data 
{
    // 原始数据
    int     input_times = 0;
    int     encoder_left[remember_data_size] = {0};
    int     encoder_right[remember_data_size] = {0};
    float   angle[remember_data_size] = {0};

    // 数据分析
    int     element_number = 0;
    char    element_state[remember_data_size] = {0};
    float   element_angle[remember_data_size] = {0};
    float   element_angle_idealize[remember_data_size] = {0};
    float   element_distance[remember_data_size] = {0};
    int     track_point[2][remember_data_size] = {0};
    int     element_track_point[100][2][1000] = {0};
    int     element_kind[20]  = {30,60,90,120,150,180,270,360};

    // 数据逐帧调整策略
    float   adjust_servo_P[remember_data_size] = {0};
    float   adjust_servo_D[remember_data_size] = {0};
    float   adjust_speed[remember_data_size] = {0};
    float   adjust_delta_LRW[remember_data_size] = {0};
    float   adjust_basic_run_corner[remember_data_size] = {0};
    float   adjust_check_range[remember_data_size] = {0};

    // 数据元素调整策略             [0-速度   1-舵机P 2-舵机D  3-差速  4-铭感值 5-前瞻线 6-电机I]
    float   ED_small_forward[10]= {2.0      ,1.0    ,1.0    ,1.0    ,1.0    ,1.0    ,1.0    };
    float   ED_long_forward[10] = {10.0     ,1.0    ,1.0    ,1.0    ,1.0    ,1.0    ,1.0    };
    float   ED_angle_30[10]     = {1.0      ,0.9    ,1.5    ,0.5    ,1.0    ,0.4    ,1.0    };
    float   ED_angle_60[10]     = {1.0      ,0.8    ,1.5    ,0.5    ,1.5    ,0.45   ,1.0    };
    float   ED_angle_90[10]     = {1.0      ,1.2    ,1.5    ,1.5    ,0.5    ,0.5    ,1.0    };
    float   ED_angle_120[10]    = {1.0      ,1.2    ,1.5    ,1.5    ,0.5    ,0.55   ,1.0    };
    float   ED_angle_150[10]    = {1.0      ,1.2    ,1.5    ,1.5    ,0.5    ,0.6    ,1.0    };
    float   ED_angle_180[10]    = {2.0      ,1.2    ,1.5    ,1.5    ,0.5    ,0.65   ,1.0    };
    float   ED_angle_270[10]    = {3.0      ,1.2    ,1.5    ,2.0    ,1.2    ,0.7    ,1.0    };
    float   ED_element_ring[10] = {4.0      ,1.2    ,1.5    ,2.0    ,1.2    ,1.0    ,1.0    };
    float   ED_element_S[10]    = {1.0      ,1.1    ,1.0    ,2.0    ,0.0    ,0.2    ,1.0    };
    float   ED_element_s[10]    = {2.0      ,0.8    ,1.5    ,1.0    ,1.2    ,0.1    ,1.0    };
};

// 坐标点结构体
struct Point {
    int x;
    int y;
};

// 线段结果结构体
struct Result {
    float proportion;//白色区域比例
    int X;//白色区域中值X坐标
    int Y;//白色区域中值Y坐标
};

// 线两点位置结构体
struct LinePos {
    int sx, sy, ex, ey;
};

// 元素枚举
enum Element {
    Forward = 0,
    LeftRing = -1,
    RightRing = 1,
    Cross
};

// 车辆数据结构体
struct Car_Data {
    //获取数据
    //编码器数据
    int32 LE, RE; //[Left Encoder][Right Encoder]
    //水平转角数据
    float HA,PA,RA;   //[Horizontal Angle][Pitch Angle][Roll Angle]

    //控制数据
    //舵机转角数据
    float SA;   //[Servo Angle]
    //电机转速数据
    int LM, RM; //左电机[Left Motor]，右电机[Right Motor]
    //蜂鸣器数据
    int BZ;     //[Buzzer]
};


// PID控制器结构体
struct pid_cycle_struct{
    float p = 2.0f;                // 比例系数[比例控制根据当前误差大小进行调整，快速响应误差变化]
    float i = 0.0f;                // 积分系数[积分控制累计误差，消除稳态误差]
    float d = 1.5f;                // 微分系数[微分控制预测误差变化趋势，抑制振荡]
    float i_value_max = 100000.0f; // 积分最大值[防止积分饱和，避免积分项过大影响系统稳定性]
    float i_value_pro = 0.1f;      // 积分程度[控制积分项的积累速度，避免积分项过大]
    float out_max = 16.0f;          // 输出最大值[限制输出范围，防止过大的控制量]
    float p_value_last = 0.0f;     // 上一次的比例量[保存上一次的比例量，用于计算微分量]
    float i_value = 0.0f;          // 当前积分量[当前积分量，用于计算积分项]
    float out = 0.0f;              // PID输出值[PID控制器的输出值，用于控制执行器]
};

// 卡尔曼滤波器结构体
struct KalmanFilter{
    float q;        // 过程噪声协方差[过程噪声  描述了系统模型的不确定性。如果系统的动态变化非常快速或者不确定性较大，就需要增大  的值]
    float r;        // 测量噪声协方差[测量噪声  表示从传感器获得的数据的不确定性。如果传感器较为稳定且准确，应该减小  的值]
    float x;        // 估计值[在开始的时候，选择一个合理的初始值。如果你已知系统初始状态（如初始位置和速度），可以直接设置为该值。如果没有良好的初始信息，可以将其设为0或平均预期值。]
    float p;        // 估计误差协方差[初始的估计误差协方差 p 应该反映对初始状态的不确定性。如果对初始状态非常不确定，可以将 p设为一个较大的值，例如1000。这样做可以使卡尔曼滤波器更快地依赖于测量数据。如果对初始位置有较强信心，可以将 p设为较小的值，如1或10。]
    float k;        // 卡尔曼增益[卡尔曼增益 k 是衡量测量数据与预测数据之间权重的关键参数。如果 k 接近 1，则更相信测量数据；如果 k 接近 0，则更相信预测数据。]
};

// 定义π
#define M_PI 3.14159265358979323846

#define my_min(a, b) ((a) < (b) ? (a) : (b))

// 限幅函数
template<typename T>
inline T func_limit_ab(T value, T min_val, T max_val) {
    if (value < min_val) return min_val;
    if (value > max_val) return max_val;
    return value;
}

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// 控制算法 ///////////////////////////////////////////////

// 位置式PID控制
void pid_control(pid_cycle_struct *pid_cycle, float target, float real)
{
    float proportion_value = 0;         // 比例量
    float differential_value = 0;       // 微分量

    proportion_value = target - real;   // 比例量 = 目标值 - 实际值

    pid_cycle->i_value += (proportion_value * pid_cycle->i_value_pro);                                          // 积分量 = 积分量 + 比例量 * 积分程度
    pid_cycle->i_value = func_limit_ab(pid_cycle->i_value, -pid_cycle->i_value_max, pid_cycle->i_value_max);    // 积分量限幅

    differential_value = proportion_value - pid_cycle->p_value_last;                                            // 微分量 = 比例量 - 上一次比例量

    pid_cycle->out = (float)(pid_cycle->p * proportion_value + pid_cycle->i * pid_cycle->i_value + pid_cycle->d * differential_value); // PID综合

    pid_cycle->out = func_limit_ab(pid_cycle->out, -pid_cycle->out_max, pid_cycle->out_max);                    // PID输出限幅

    pid_cycle->p_value_last = proportion_value; // 保存比例量
}

// 卡尔曼滤波计算
float Kalman_Update(KalmanFilter* kf, float measurement) {
    // 预测阶段
    kf->p += kf->q;

    // 更新阶段
    kf->k = kf->p / (kf->p + kf->r);
    kf->x += kf->k * (measurement - kf->x);
    kf->p *= (1 - kf->k);

    return kf->x;
}


////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// 画面预处理函数 ///////////////////////////////////////////

// 图像二值化
void binarize_image_inplace(int thr, uint8_t* src, uint8_t* dst, int width, int height,int Top_fill)
{
    // 填充顶部无效像素
    for(int i = 0; i < Top_fill; i++)
    {
        for(int j = 0; j < width; j++)
        {
            src[i * width + j] = 0;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            dst[i * width + j] = (src[i * width + j] > thr) ? 1 : 0;
        }
    }
}

// 大津法（Otsu）计算图像二值化阈值
uint8 otsuThreshold(uint8 *image, uint8 width, uint8 height,uint8 add_value = 0) 
{
    #define GrayScale 256

    int pixelCount[GrayScale] = {0};    // 统计每个灰度级的像素数量
    float pixelPro[GrayScale] = {0};    // 每个灰度级的概率
    const int totalPixels = width * height;
    uint8 threshold = 0;
    float maxVariance = 0.0f;

    // 1. 统计每个灰度级的像素数量
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            uint8 grayValue = image[i * width + j];
            pixelCount[grayValue]++;
        }
    }

    // 2. 计算每个灰度级的概率和全局平均灰度
    float globalMean = 0.0f;
    for (int i = 0; i < GrayScale; i++) {
        pixelPro[i] = (float)pixelCount[i] / totalPixels;
        globalMean += i * pixelPro[i];
    }

    // 3. 遍历所有灰度级，寻找最佳阈值
    float w0 = 0.0f;      // 前景像素累计概率
    float mean0 = 0.0f;   // 前景像素平均灰度

    for (int t = 0; t < GrayScale; t++) {
        w0 += pixelPro[t];
        mean0 += t * pixelPro[t];

        if (w0 == 0 || w0 == 1) continue; // 避免除以0

        // 计算类间方差
        float mean1 = (globalMean - mean0) / (1 - w0); // 背景像素平均灰度
        float variance = w0 * (1 - w0) * pow(mean0 / w0 - mean1, 2);

        // 更新最佳阈值
        if (variance > maxVariance) {
            maxVariance = variance;
            threshold = (uint8)t;
        }
    }

    return threshold + add_value;
}

// 泛洪填充算法
void FloodFill(uint8_t* target_array, int width, int height, Result position)
{
    struct Segment {
        int x1, x2, y;
    };
    int startX = position.X;
    int startY = position.Y;  // 反转Y坐标

    // 找到有效点（边界点）
    bool out_point = false;
    for (int dx = -9; dx <= 9; dx += 1) {  // 搜索范围为1
        for (int dy = -18; dy <= 0; dy += 1) { // 搜索范围为1
            int nx = startX + dx;
            int ny = startY + dy;  // 搜索Y方向
            if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                if (target_array[ny * width + nx] != 0) {
                    startX = nx;  // 精确确定X坐标
                    startY = ny;  // 精确确定Y坐标
                    out_point = true;
                    break; // 找到有效点后退出循环
                }
            }
        }
        if (out_point) break;
    }
    if (!out_point)
    {
        printf("洪水填充无有效点\n");
        return;
    }

    // 初始化填充值为原值的7位
    const uint8_t fillValue = target_array[startY * width + startX] & 0x7F;

    // 栈存储边界点
    #define MAX_STACK 1024
    Segment stack[MAX_STACK];
    int stackTop = 0;

    // 填充开始，添加边界水平线
    int leftX = startX;
    while (leftX > 0 && (target_array[startY * width + (leftX - 1)] & 0x7F) == fillValue && !(target_array[startY * width + (leftX - 1)] & 0x80))
    {
        leftX--;
    }
    int rightX = startX;
    while (rightX < width - 1 && (target_array[startY * width + (rightX + 1)] & 0x7F) == fillValue && !(target_array[startY * width + (rightX + 1)] & 0x80))
    {
        rightX++;
    }

    // 填充开始，添加边界垂直线
    for (int x = leftX; x <= rightX; x++)
    {
        target_array[startY * width + x] |= 0x80;
    }
    stack[stackTop++] = Segment{ leftX, rightX, startY };

    // 遍历栈中的边界线
    while (stackTop > 0)
    {
        Segment seg = stack[--stackTop];
        int y = seg.y;
        int x1 = seg.x1;
        int x2 = seg.x2;

        // 遍历上边界
        if (y > 0)
        {
            int ny = y - 1;
            int x = x1;
            while (x <= x2)
            {
                // 找到有效像素
                while (x <= x2 && (target_array[ny * width + x] & 0x80 || (target_array[ny * width + x] & 0x7F) != fillValue))
                {
                    x++;
                }
                if (x > x2) break;

                // 精确确定边界
                int nx1 = x;
                while (x <= x2 && !(target_array[ny * width + x] & 0x80) && (target_array[ny * width + x] & 0x7F) == fillValue)
                {
                    x++;
                }
                int nx2 = x - 1;

                // 填充边界右侧
                while (nx1 > 0 && (target_array[ny * width + (nx1 - 1)] & 0x7F) == fillValue && !(target_array[ny * width + (nx1 - 1)] & 0x80))
                {
                    nx1--;
                    target_array[ny * width + nx1] |= 0x80;
                }
                while (nx2 < width - 1 && (target_array[ny * width + (nx2 + 1)] & 0x7F) == fillValue && !(target_array[ny * width + (nx2 + 1)] & 0x80))
                {
                    nx2++;
                    target_array[ny * width + nx2] |= 0x80;
                }

                // 填充边界垂直线
                for (int i = nx1; i <= nx2; i++) target_array[ny * width + i] |= 0x80;
                if (stackTop < MAX_STACK)
                {
                    stack[stackTop++] = Segment{ nx1, nx2, ny };
                }
                x = nx2 + 1;
            }
        }

        // 遍历下边界
        if (y < height - 1)
        {
            int ny = y + 1;
            int x = x1;
            while (x <= x2)
            {
                while (x <= x2 && (target_array[ny * width + x] & 0x80 || (target_array[ny * width + x] & 0x7F) != fillValue))
                {
                    x++;
                }
                if (x > x2) break;

                int nx1 = x;
                while (x <= x2 && !(target_array[ny * width + x] & 0x80) && (target_array[ny * width + x] & 0x7F) == fillValue)
                {
                    x++;
                }
                int nx2 = x - 1;

                while (nx1 > 0 && (target_array[ny * width + (nx1 - 1)] & 0x7F) == fillValue && !(target_array[ny * width + (nx1 - 1)] & 0x80))
                {
                    nx1--;
                    target_array[ny * width + nx1] |= 0x80;
                }
                while (nx2 < width - 1 && (target_array[ny * width + (nx2 + 1)] & 0x7F) == fillValue && !(target_array[ny * width + (nx2 + 1)] & 0x80))
                {
                    nx2++;
                    target_array[ny * width + nx2] |= 0x80;
                }

                for (int i = nx1; i <= nx2; i++) target_array[ny * width + i] |= 0x80;
                if (stackTop < MAX_STACK)
                {
                    stack[stackTop++] = Segment{ nx1, nx2, ny };
                }
                x = nx2 + 1;
            }
        }
    }

    for (int i = 0; i < width * height; i++)
    {
        if (target_array[i] & 0x80)
        {   // 有效点
            target_array[i] = fillValue;  // 恢复原值为0或1
        }
        else
        {   // 无效点
            // 获取原值的7位
            uint8_t original = target_array[i] & 0x7F;

            // 判断逻辑
            target_array[i] = (original <= 1) ? 0 : original;
        }
    }
    #undef MAX_STACK
}

// 获取连线白色像素点比例和中值坐标
Result get_line_blank(uint8_t* target_array, int width, int height, LinePos pos, uint8_t color,bool show_line = false,bool show_gray = true)
{
    Result error_result = { -1, -1, -1 };  // 修改为int类型

    if (!target_array || width <= 0 || height <= 0)
    {
        return error_result;
    }

    int sx = pos.sx;
    int sy = pos.sy;
    int ex = pos.ex;
    int ey = pos.ey;

    Point* linePoints = NULL;
    size_t pointCount = 0;
    size_t capacity = 0;

    int x0 = sx, y0 = sy;
    int x1 = ex, y1 = ey;

    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sxStep = (x0 < x1) ? 1 : -1;
    int syStep = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (1)
    {
        if (pointCount >= capacity)
        {
            capacity = (capacity == 0) ? 64 : capacity * 2;
            // 修复1：添加类型转换
            Point* new_points = (Point*)realloc(linePoints, capacity * sizeof(Point));
            if (!new_points)
            {
                free(linePoints);
                return error_result;
            }
            linePoints = new_points;
        }

        // 坐标检查保留
        if (x0 >= 0 && x0 < width && y0 >= 0 && y0 < height)
        {
            linePoints[pointCount++] = Point{ x0, y0 };
        }

        if (x0 == x1 && y0 == y1) break;

        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x0 += sxStep;
        }
        if (e2 < dx)
        {
            err += dx;
            y0 += syStep;
        }
    }

    if (pointCount == 0)
    {
        free(linePoints);
        return Result{ 0, -1, -1 };  // 修改为int类型
    }

    long long totalX = 0, totalY = 0;
    int whiteCount = 0;

    for (size_t i = 0; i < pointCount; i++)
    {
        int x = linePoints[i].x;
        int y = linePoints[i].y;

        if (x >= 0 && x < width && y >= 0 && y < height)
        {
            uint8_t* pixel = &target_array[y * width + x];
            if (*pixel != 0 && *pixel != 9 && *pixel != 6)
            {
                whiteCount++;
                totalX += x;
                totalY += y;
                if(show_line)
                    *pixel = color;
            }
            else if(show_line && show_gray)
            {
                *pixel = 9;
            }
        }
    }

    free(linePoints);

    if (whiteCount == 0)
    {
        return Result{ 0, -1, -1 };  // 修改为int类型
    }

    float ratio = (float)whiteCount / pointCount;
    int centerX = (int)(totalX / whiteCount);
    int centerY = (int)(totalY / whiteCount);

    target_array[centerY * width + centerX] = 2; // 标志中点

    return Result{ ratio, centerX, centerY };  // 将ratio转换为整数（乘以100保留两位小数）
}

// 剔除小黑区域
void RemoveSmallBlackRegions(uint8_t* target_array,int width,int height,int areaThreshold,uint8_t whiteValue = 1) 
{
    if (areaThreshold <= 0 || target_array == nullptr || width <= 0 || height <= 0)
        return;

    // 定义方向数组（4邻接）
    const int dx[4] = {0, -1, 1, 0};
    const int dy[4] = {-1, 0, 0, 1};

    // 分配访问标记数组
    bool* visited = (bool*)malloc(width * height * sizeof(bool));
    if (!visited) return;

    // 初始化访问标记数组
    for (int i = 0; i < width * height; ++i)
        visited[i] = false;

    // 分配队列和区域缓存
    int* queue = (int*)malloc(width * height * sizeof(int));
    int* region = (int*)malloc(width * height * sizeof(int));
    if (!queue || !region) {
        free(visited);
        if (queue) free(queue);
        return;
    }

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int index = y * width + x;

            if (target_array[index] == 0 && !visited[index]) {
                int q_start = 0, q_end = 0;
                int region_count = 0;

                // 起始点入队
                queue[q_end++] = index;
                visited[index] = true;
                region[region_count++] = index;

                while (q_start < q_end) {
                    int current_index = queue[q_start++];
                    int cx = current_index % width;
                    int cy = current_index / width;

                    for (int dir = 0; dir < 4; ++dir) {
                        int nx = cx + dx[dir];
                        int ny = cy + dy[dir];

                        if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                            int nindex = ny * width + nx;
                            if (target_array[nindex] == 0 && !visited[nindex]) {
                                visited[nindex] = true;
                                queue[q_end++] = nindex;
                                region[region_count++] = nindex;
                            }
                        }
                    }
                }

                // 判断区域面积是否小于阈值
                if (region_count < areaThreshold) {
                    for (int i = 0; i < region_count; ++i) {
                        target_array[region[i]] = whiteValue;
                    }
                }
            }
        }
    }

    // 释放内存
    free(visited);
    free(queue);
    free(region);
}

// 边缘腐蚀函数
void ApplyInnerBorder(uint8_t* target_array, int width, int height, int borderThickness, int border_color = 9)
{
    const int INF = 1000000; // 手动定义一个足够大的"无穷大"
    static bool original_mask[UVC_HEIGHT][UVC_WIDTH];
    static int distance_map[UVC_HEIGHT][UVC_WIDTH];

    if (borderThickness <= 0 || width > UVC_WIDTH || height > UVC_HEIGHT) return;

    // Step 1: 初始化掩码和距离图
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            original_mask[y][x] = (target_array[y * width + x] != 0 && target_array[y * width + x] != 9);
            distance_map[y][x] = original_mask[y][x] ? INF : 0;
        }
    }

    // Step 2: 第一遍扫描（左上到右下）
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (original_mask[y][x]) {
                if (y > 0) distance_map[y][x] = my_min(distance_map[y][x], distance_map[y - 1][x] + 1);
                if (x > 0) distance_map[y][x] = my_min(distance_map[y][x], distance_map[y][x - 1] + 1);
            }
        }
    }

    // Step 3: 第二遍扫描（右下到左上）
    for (int y = height - 1; y >= 0; --y) {
        for (int x = width - 1; x >= 0; --x) {
            if (original_mask[y][x]) {
                if (y < height - 1) distance_map[y][x] = my_min(distance_map[y][x], distance_map[y + 1][x] + 1);
                if (x < width - 1) distance_map[y][x] = my_min(distance_map[y][x], distance_map[y][x + 1] + 1);
            }
        }
    }

    // Step 4: 应用腐蚀并填充边框颜色
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if ((distance_map[y][x] <= borderThickness || x == width - 1) && target_array[y * width + x] != 0) {
                target_array[y * width + x] = border_color;
            }
        }
    }
}

// 透视变换
void ManualPerspectiveTransform(uint8_t* src_pixels, int src_width, int src_height, Point* src_points, Point* dst_points) 
{
    #define EPSILON 1e-6f
    // 步骤1：构建8x8线性方程组 
    float** A = (float**)malloc(8 * sizeof(float*));
    float* b = (float*)malloc(8 * sizeof(float));
    for (int i = 0; i < 8; i++) 
        A[i] = (float*)calloc(8, sizeof(float));

    for (int i = 0; i < 4; i++) {
        float src_x = src_points[i].x, src_y = src_points[i].y;
        float dst_x = dst_points[i].x, dst_y = dst_points[i].y;

        // X分量方程 
        int row_x = 2*i;
        A[row_x][0]=src_x; A[row_x][1]=src_y; A[row_x][2]=1.0f;
        A[row_x][6]=-src_x*dst_x; A[row_x][7]=-src_y*dst_x;
        b[row_x] = dst_x;

        // Y分量方程 
        int row_y = 2*i+1;
        A[row_y][3]=src_x; A[row_y][4]=src_y; A[row_y][5]=1.0f;
        A[row_y][6]=-src_x*dst_y; A[row_y][7]=-src_y*dst_y;
        b[row_y] = dst_y;
    }

    // 步骤2：高斯消元求解单应矩阵系数（内联实现）
    int n = 8;
    float** mat = (float**)malloc(n * sizeof(float*));
    float* vec = (float*)malloc(n * sizeof(float));
    for (int i=0; i<n; i++) {
        mat[i] = (float*)malloc(n * sizeof(float));
        memcpy(mat[i], A[i], n * sizeof(float));
        vec[i] = b[i];
    }

    // 高斯消元核心 
    for (int i=0; i<n; i++) {
        // 选主元
        int max_row = i;
        for (int j=i; j<n; j++) 
            if (fabs(mat[j][i]) > fabs(mat[max_row][i])) 
                max_row = j;

        // 行交换
        float* tmp_row = mat[i];
        mat[i] = mat[max_row];
        mat[max_row] = tmp_row;
        float tmp_val = vec[i];
        vec[i] = vec[max_row];
        vec[max_row] = tmp_val;

        // 奇异矩阵检查
        if (fabs(mat[i][i]) < EPSILON) {
            for (int k=0; k<n; k++) free(mat[k]);
            free(mat); free(vec);
            printf("Singular matrix detected\n");
            return;
        }

        // 归一化当前行
        float pivot = mat[i][i];
        for (int j=i; j<n; j++) mat[i][j] /= pivot;
        vec[i] /= pivot;

        // 下方行消元
        for (int j=i+1; j<n; j++) {
            float factor = mat[j][i];
            for (int k=i; k<n; k++) 
                mat[j][k] -= factor * mat[i][k];
            vec[j] -= factor * vec[i];
        }
    }

    // 回代求解
    float* H_coeffs = (float*)malloc(n * sizeof(float));
    for (int i=n-1; i>=0; i--) {
        H_coeffs[i] = vec[i];
        for (int j=i+1; j<n; j++) 
            H_coeffs[i] -= mat[i][j] * H_coeffs[j];
    }

    // 步骤3：构建3x3单应矩阵
    float H[9] = { 
        H_coeffs[0], H_coeffs[1], H_coeffs[2],
        H_coeffs[3], H_coeffs[4], H_coeffs[5],
        H_coeffs[6], H_coeffs[7], 1.0f 
    };

    // 步骤4：计算逆矩阵（内联实现）
    float det = H[0]*(H[4]*H[8]-H[5]*H[7]) 
            - H[1]*(H[3]*H[8]-H[5]*H[6]) 
            + H[2]*(H[3]*H[7]-H[4]*H[6]);
    if (fabs(det) < EPSILON) {
        printf("Non-invertible matrix\n");
        return;
    }
    float inv_det = 1.0f / det;
    float H_inv[9] = {
        (H[4]*H[8]-H[5]*H[7]) * inv_det,
        (H[2]*H[7]-H[1]*H[8]) * inv_det,
        (H[1]*H[5]-H[2]*H[4]) * inv_det,
        (H[5]*H[6]-H[3]*H[8]) * inv_det,
        (H[0]*H[8]-H[2]*H[6]) * inv_det,
        (H[2]*H[3]-H[0]*H[5]) * inv_det,
        (H[3]*H[7]-H[4]*H[6]) * inv_det,
        (H[1]*H[6]-H[0]*H[7]) * inv_det,
        (H[0]*H[4]-H[1]*H[3]) * inv_det 
    };

    // 步骤5：执行逆透视变换
    int dst_width = src_width, dst_height = src_height;
    uint8_t* dst_pixels = (uint8_t*)malloc(dst_width*dst_height);
    
    for (int y = 0; y < dst_height; y++) {
        for (int x = 0; x < dst_width; x++) {
            float denom = H_inv[6]*x + H_inv[7]*y + H_inv[8];
            if (fabs(denom) < EPSILON) {
                dst_pixels[y*dst_width+x] = 0;
                continue;
            }
            float src_x = (H_inv[0]*x + H_inv[1]*y + H_inv[2]) / denom;
            float src_y = (H_inv[3]*x + H_inv[4]*y + H_inv[5]) / denom;
            
            int x_src = (int)src_x, y_src = (int)src_y;
            if (x_src>=0 && x_src<src_width && y_src>=0 && y_src<src_height) 
                dst_pixels[y*dst_width+x] = src_pixels[y_src*src_width+x_src];
            else 
                dst_pixels[y*dst_width+x] = 0;
        }
    }

    // 步骤6：回写结果并清理资源 
    memcpy(src_pixels, dst_pixels, dst_width*dst_height);
    free(dst_pixels);
    for (int i=0; i<n; i++) { free(mat[i]); free(A[i]); }
    free(mat); free(vec); free(H_coeffs); free(A); free(b);

    // 透视变换使用方法
    // Point srcPoints[4] = {{0, (int)(UVC_HEIGHT*MPT_top_y)},{UVC_WIDTH, (int)(UVC_HEIGHT*MPT_top_y)},{UVC_WIDTH, UVC_HEIGHT},{0, UVC_HEIGHT}};
    // Point dstPoints[4] = {{0, 0},{UVC_WIDTH, 0},{(int)(UVC_WIDTH*MPT_button_x), UVC_HEIGHT},{(int)(UVC_WIDTH*(1 - MPT_button_x)), UVC_HEIGHT}};
    // ManualPerspectiveTransform((uint8*)AIB_array, UVC_WIDTH, UVC_HEIGHT, srcPoints, dstPoints);
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// 全部参数类 /////////////////////////////////////////////

bool cycle_run = false;

uint8 data_remember = 0; // 0: 不收集数据，1: 收集数据，2: 结束并分析数据，3：第二次准备收集数据，4: 第二次收集数据并优化算法

// 图像数据存储
uint8 BW_array[UVC_HEIGHT][UVC_WIDTH];              // 二值化和洪水填充后的黑白图像               
uint8 AIB_array[UVC_HEIGHT][UVC_WIDTH];             // 边缘腐蚀后的图像
uint8 pic_width    = UVC_WIDTH;                     // 图像宽度
uint8 pic_height   = UVC_HEIGHT;                    // 图像高度
uint8 pic_x_middle = UVC_WIDTH / 2;                 // 图像中心X
uint8 pic_y_middle = UVC_HEIGHT/ 2;                 // 图像中心Y
Result pic_scancol = {UVC_WIDTH / 2, UVC_HEIGHT-1}; // 图像底层行结果
float con_diff = 0.0f;                              // 舵机转角偏差
// 赛道边界检测相关变量
int   leftedge[UVC_HEIGHT];                 // 左边界数组
int   rightedge[UVC_HEIGHT];                // 右边界数组
int   middleline[UVC_HEIGHT];               // 中间线数组
int   middleline_valid[UVC_HEIGHT];         // 中间线有效数组
int   middleline_warn[UVC_HEIGHT];          // 中间线警告数组
int   middleline_invalid[UVC_HEIGHT];       // 中间线无效数组
Result cross_line_result;
uint8 end_row   =  60;
uint8 start_row =  UVC_HEIGHT - 10;
// 画面参数
int   add_Threshold = 25;           // 二值化阈值增加量【仿真-25|真实3】
int   path_thickness = 30;          // 边缘腐蚀层数 25
uint8 top_fill = 30;                // 画面上面填充的像素值 30
uint8 run_image_num = 0;            // 循迹画面序号 0-腐蚀图像，1-原黑白图像
// 控制参数
float now_speed    = 0.0f;          // 整体速度 13
float target_speed = 20.0f;         // 整体速度 13
float basic_run_corner = 0.02f;     // 舵机转角敏感度 0.05
float delta_LRW  = 0.5f;            // 后轮差速大小 0.2
float check_range = 0.9f;           // 循迹检查范围 0-1的范围，0.3f为前30%
pid_cycle_struct servo_PID = {1.9f,0.0f,1.0f};// 位置式PID控制
pid_cycle_struct motor_PID = {0.3f,2.0f,0.0f};// 位置式PID控制
// 斑马线参数
int   zebra_times = 0;              // 斑马线方向 0:无斑马线 1:斑马线 2:斑马线结束
int   zebra_check_y = 90;           // 斑马线检查行开始
int   start_run = 0;                // 斑马线开始运行计数
// 十字参数
int   cross_times = 0;              // 十字次数
int   find_line_lenth = 5;          // 十字左右判断线长度 5
// 圆环参数 
int   ring_times = 0;               // 圆环次数
int   ring_full = 0;                // 圆环方向 0:无圆环 1:左圆环 -1:右圆环
float ring_find_pos = 0.23f;        // 圆环左右判断线位置 0.25
int   ring_forward_line = 62;       // 圆环直线判断线位置 0.25
float ring_slope = 1.3f;            // 圆环填充斜率[改变入圆环角度]
float ringe_check_out_line=0.4f;    // 圆环出圆环目标检查行   0.4f[出圆环行数]
float ringe_DC_line = 1.5f;         // 圆环确认圆环目标检查行 2.3f[改变入圆环的提前-还是延时+]
// 坡道参数
int   roll_times = 0;
float ramp_angle = 8.0;            // 坡道目标转角度数 8.0
//初始化参数
float bef_target_speed = 0;
float bef_servo_P = 0;
float bef_servo_D = 0;
float bef_motor_I = 0;
float bef_delta_LRW = 0;
float bef_basic_run_corner = 0;
float bef_check_range = 0;

float bef_path_thickness = 0;
float bef_find_line_pos = 0;
//编码器延迟参数
float ED_K = 15000.0f;          // 编码器延迟系数 15000.0f
float ED_bef_encoder = 0;       // 编码器延迟前值 0
float ED_target_encoder = 0;    // 编码器延迟目标值 0
bool  ED_end = true;            // 编码器延迟结束 true:结束 false:未结束

void init_parameter();// 声明初始化
void set_ED(Car_Data& CD,float delay_dis);// 声明设置编码器延迟
float cal_line_degree(int *line, uint8_t SR, uint8_t ER);// 声明计算直线斜率
void optimization_deal(Car_Data& CD);// 声明优化处理
DLL_EXPORT void __stdcall save_remember_data_json(const char* filename);
DLL_EXPORT void __stdcall load_remember_data_json(const char* filename);

///////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////// 判断类函数 /////////////////////////////////////////////

// 判断斑马线
void check_zebra(Car_Data& CD)
{
    static int bef_color = 0;
    int diff_times = 0;
    int ml_invalid = 0;

    // 不运行时，不判断斑马线
    if(!cycle_run)
        return;

    //刚开始运行，不判断斑马线
    if(start_run < 300)
    {
        start_run++;
        return;
    }

    for(int y = start_row; y > end_row; y--)
    {
        if(middleline_invalid[y] != -1)
        {
            ml_invalid++;
        }
    }
    if(ml_invalid > 20)
    {
        cross_line_result = get_line_blank((uint8*)AIB_array, pic_width, pic_height, LinePos { 0, zebra_check_y, pic_width - 1, zebra_check_y }, 2,true);

        // 目标行中的所有颜色，原逻辑为白色，注释为循环一次
        for (int x = 0; x < UVC_WIDTH - 1; x++)
        {
            static int current_color;
            
            if(cross_line_result.Y > 0)
            {
                current_color = BW_array[cross_line_result.Y][x];
                AIB_array[cross_line_result.Y][x] = 4;
            }
            else
            {
                current_color = BW_array[0][x];
                AIB_array[0][x] = 4;
            }

            if(current_color != bef_color && (current_color == 0 || current_color == 1))
            {
                diff_times++;
                bef_color = current_color;
            }
        }

        // 判断逻辑
        if (diff_times >= 10 && zebra_times == 0  && roll_times == 0)
        {
            zebra_times++;
            printf("判断斑马线!!! %d\n", diff_times);
        }
    }
}

// 圆环斜率填充
void ring_slope_deal(uint8 *image,int width,int height, int ring_full ,float Ring_slope = ring_slope)
{
// 计算斜率：高度/半宽，确保从底部开始填充
float slope = (float)height / (float)(width * Ring_slope);
for (int i = 0; i < height; i++) {
    int from_bottom = height - 1 - i;
    
    for (int j = 0; j < width; j++) {
        if (ring_full == -1) { // 左圆环：从左下角开始向上填充
            float max_fill_height = slope * (width - j);
            if (from_bottom > max_fill_height) {
                image[i * width + j] = 9;
                continue;
            }
        }
        else if (ring_full == 1) { // 右圆环：从右下角开始向上填充
            float max_fill_height = slope * j;
            if (from_bottom > max_fill_height) {
                image[i * width + j] = 9;
                continue;
            }
        }
    }
}
}


// 判断圆环
Element check_ring(Car_Data& CD,int mode = 0)
{
    static int ring_monitor_y = 0;
    ring_monitor_y = (int)((pic_height - 1) * (1 - ring_find_pos));

    if(roll_times == 0)
    {
        // 判断圆环
        if(mode == 0)
        {
            Result RCR = get_line_blank((uint8*)AIB_array, pic_width, pic_height, LinePos { pic_width - 2  , ring_monitor_y - find_line_lenth, pic_width - 2 , ring_monitor_y }, 3,true);               //判断标志[圆+十]
            Result LCR = get_line_blank((uint8*)AIB_array, pic_width, pic_height, LinePos { 1              , ring_monitor_y - find_line_lenth, 1             , ring_monitor_y }, 3,true);               //判断标志[圆+十]
            
            Result middle_line_result = get_line_blank((uint8*)AIB_array, pic_width, pic_height, LinePos { 0, ring_forward_line, pic_width - 1, ring_forward_line }, 3);//寻找目标点
            get_line_blank((uint8*)AIB_array, pic_width, pic_height, LinePos { 0, ring_forward_line, pic_width - 1, ring_forward_line }, 3,true);//寻找目标点

            int CF = pic_x_middle - middle_line_result.X;

            //第一次判断
            if (abs(CF) < 30.0f && middle_line_result.X > 0 && middle_line_result.proportion > 0.1f)
            {
                if (RCR.proportion > 0.95f && LCR.proportion == 0.0f)//左黑右白
                {
                    // printf("左黑右白: %f\n",cal_line_degree(leftedge,start_row-10,end_row+20));
                    if(fabs(cal_line_degree(leftedge,start_row,end_row+10)) > 0.995f)
                    {
                        printf("发现右边分叉路! 差值:%d 中间点:%d 比例:%f\n",CF,middle_line_result.X,middle_line_result.proportion);
                        return RightRing;
                    }
                }
                if (LCR.proportion > 0.95f && RCR.proportion == 0.0f)//左白右黑
                {
                    // printf("左白右黑: %f\n",cal_line_degree(rightedge,start_row-10,end_row+20));
                    if(fabs(cal_line_degree(rightedge,start_row,end_row+10)) > 0.995f)
                    {
                        printf("发现左边分叉路! 差值:%d 中间点:%d 比例:%f\n",CF,middle_line_result.X,middle_line_result.proportion);
                        return LeftRing;
                    }
                }
            }
        }
        
        if(mode == 1 || mode == -1)
        {
            static int draw_close = 1;
            Result RCR = get_line_blank((uint8*)BW_array, pic_width, pic_height, LinePos { pic_width - 2 - draw_close , ring_monitor_y - find_line_lenth, pic_width - 2 - draw_close , ring_monitor_y }, 3,true);               //判断标志[圆+十]
                        get_line_blank((uint8*)AIB_array, pic_width, pic_height, LinePos { pic_width - 2 - draw_close , ring_monitor_y - find_line_lenth, pic_width - 2 - draw_close , ring_monitor_y }, 3,true); 
            Result LCR = get_line_blank((uint8*)BW_array, pic_width, pic_height, LinePos { 0 + draw_close             , ring_monitor_y - find_line_lenth, 0 + draw_close             , ring_monitor_y }, 3,true);               //判断标志[圆+十]
                        get_line_blank((uint8*)AIB_array, pic_width, pic_height, LinePos { 0 + draw_close             , ring_monitor_y - find_line_lenth, 0 + draw_close             , ring_monitor_y }, 3,true);  
            
            Result middle_line_result = get_line_blank((uint8*)AIB_array, pic_width, pic_height, LinePos { 0, ring_forward_line, pic_width - 1, ring_forward_line }, 3);//寻找目标点
            get_line_blank((uint8*)AIB_array, pic_width, pic_height, LinePos { 0, ring_forward_line, pic_width - 1, ring_forward_line }, 3,true);//寻找目标点

            int CF = pic_x_middle - middle_line_result.X;

            // 右圆环再次判断
            if (abs(CF) < 20.0f && middle_line_result.X != -1)
            {
                if(mode == 1)
                {
                    if (RCR.proportion > 0.3f && LCR.proportion == 0.0f)//左黑右白
                    {
                        if(fabs(cal_line_degree(leftedge,start_row-10,end_row+10)) > 0.999f)
                        {
                            printf("再次发现右圆环! 比例:%f\n",ring_find_pos);
                            return RightRing;
                        }
                        else
                        {
                            printf("边缘直线比例未达标:%f\n",ring_find_pos);
                        }
                    }
                    
                }

                // 左圆环再次判断
                if(mode == -1)
                {
                    if (LCR.proportion > 0.3f && RCR.proportion == 0.0f)//左白右黑
                    {
                        if(fabs(cal_line_degree(rightedge,start_row-10,end_row+10)) > 0.999f)
                        {
                            printf("再次发现左圆环! 比例:%f\n",ring_find_pos);
                            return LeftRing;
                        }
                        else
                        {
                            printf("边缘直线比例未达标:%f\n",ring_find_pos);
                        }
                    }
                }
            }
            else
            {
                printf("未走直线!\n");
            }
        }
    }

    return Forward;
}


// 判断元素
Element Element_Check(Car_Data& CD)
{
    static Element now_element = Forward;
    static Element bef_element = Forward;

    static float ring_bef_simulator = 0;        //圆旋转值
    
    ////////////////////////////////////////////////////十字判断////////////////////////////////////////////////////
    Result RCR = get_line_blank((uint8*)AIB_array, pic_width, pic_height, LinePos { pic_width - 2 - 1  , pic_height - 35, pic_width - 2 - 1 , pic_height - 30 }, 4,true);               //判断标志[十]
    Result LCR = get_line_blank((uint8*)AIB_array, pic_width, pic_height, LinePos { 0 + 2              , pic_height - 35, 0 + 2             , pic_height - 30 }, 4,true);               //判断标志[十]
    if (cross_times == 1)
    {
        if (ED_end)//远循环是否结束
        {
            cross_times = 0;
            ring_times = 0;
            printf("十字结束!\n");
        }

        now_element = Cross;
    }
    else if (LCR.proportion > 0.95f && RCR.proportion > 0.95f && ring_times < 2 && roll_times == 0)
    {
        set_ED(CD,1.0f); // 添加元素到编码器延时

        now_element = Cross;
        cross_times = 1;
        
        basic_run_corner = bef_basic_run_corner;
        path_thickness = bef_path_thickness;
        ring_find_pos = bef_find_line_pos;
        
        printf("十字开始!\n");
    }
    ////////////////////////////////////////////////////圆环判断////////////////////////////////////////////////////
    else if (ring_times == 5)//出圆环
    {
        if (ED_end)
        {
            ring_times = 0;
            basic_run_corner = bef_basic_run_corner;
            ring_find_pos = bef_find_line_pos;
            printf("圆环结束!\n");
        }
    }
    else if (ring_times == 4)//准备出圆环
    {
        if(ED_end)
        {
            ring_times++;
            ring_full = 0;
            run_image_num = 0;
            set_ED(CD,1.3f);
        }
    }
    else if (ring_times == 3)//准备出圆环
    {
        if (ED_end)
        {
            Result MR = get_line_blank((uint8*)BW_array, pic_width, pic_height, LinePos { 0, (int)(pic_height *(1-ringe_check_out_line) ), pic_width - 1, (int)(pic_height * (1-ringe_check_out_line)) }, 2,true);
                        get_line_blank((uint8*)AIB_array, pic_width, pic_height, LinePos { 0, (int)(pic_height *(1-ringe_check_out_line) ), pic_width - 1, (int)(pic_height * (1-ringe_check_out_line)) }, 2,true);

            if(MR.proportion > 0.99f)
            {
                set_ED(CD,0.4f);
                ring_times++;
                printf("准备出圆环! \n");
            }
        }
    }
    else if (ring_times == 2)//二次判断，进入圆环
    {
        if (ED_end || roll_times != 0)
        {
            ring_times = 0;
            ring_find_pos = bef_find_line_pos;
            printf("非圆环!\n");
        }
        else
        {
            now_element = check_ring(CD,bef_element);//再次判断是否存在圆环入口
                
            if(now_element == bef_element)
            {
                if(now_element == LeftRing)
                {
                    ring_full = -1;  // 左圆环
                    printf("进入左圆环!\n");
                }
                else if(now_element == RightRing)
                {
                    ring_full = 1;  // 右圆环
                    printf("进入右圆环!\n");
                }

                set_ED(CD,3.0f); // 添加元素到编码器延时
                ring_times++;
                basic_run_corner = 0.0f;
                run_image_num = 1;
                ring_bef_simulator = CD.HA;//获取当前陀螺仪数据
            }
        }
    }
    else if (ring_times == 1)//延时等待进圆环
    {
        if (ED_end)
        {
            ring_times++;
            set_ED(CD,1.5f); // 添加元素到编码器延时
            ring_find_pos = ring_find_pos * ringe_DC_line;
            printf("准备进入圆环!\n");
        }
        else 
        {
            if(bef_element == LeftRing && fabs(cal_line_degree(rightedge,start_row,end_row+10)) < 0.995f || bef_element == RightRing && fabs(cal_line_degree(leftedge,start_row,end_row+10)) < 0.995f)
            {
                ring_times = 4;
                printf("非圆环!\n");
            }
        }
    }
    else if (ring_times == 0)//判断到圆环，延时第一次判断准备进圆环
    {
        now_element = check_ring(CD);
        if(now_element == LeftRing || now_element == RightRing)
        {
            ring_times++;
            bef_element = now_element;
            set_ED(CD,0.8f); // 添加元素到编码器延时
        }
    }
    
    ///////////////////////////////////////////////// 坡道判断 /////////////////////////////////////////////////
    if      (CD.PA > ramp_angle && roll_times == 0)
    {
        roll_times++;
        set_ED(CD,2.5f); // 添加元素到编码器延时
        printf("判断坡道！%.2f\n",CD.PA);

        zebra_times = 0;
    }
    else if (roll_times == 1)
    {
        if(ED_end)
        {
            roll_times = 0;
            printf("坡道结束\n");
        }
    }

    ///////////////////////////////////////////////// 斑马线判断 /////////////////////////////////////////////////
    check_zebra(CD);//判断斑马线
    // 斑马线处理
    if      (zebra_times == 1)
    {
        set_ED(CD,1.0f);
        zebra_times++;
    }
    else if (zebra_times == 2)
    {
        if(ED_end)
        {
            printf("斑马线结束!\n");
            zebra_times ++;
            cycle_run = false;
            data_remember++;
            printf("数据处理模式: %d \n",data_remember);
        }
    }
    else if (zebra_times <= 100 && zebra_times != 0)
    {
        zebra_times ++;
        CD.SA = 0;
        CD.LM = 0;
        CD.RM = 0;
    }
    else if (zebra_times > 100)
    {
        zebra_times = 0;
        init_parameter();
        printf("再次发车!\n");
    }

    ///////////////////////////////////////////////// 没有变化返回前元素 /////////////////////////////////////////////////
    return now_element;
}


// 编码器延时
void set_ED(Car_Data& CD,float delay_dis)
{
    ED_target_encoder = delay_dis;
    ED_bef_encoder = ((CD.LE + CD.RE) / ED_K) / 2.0f;
    ED_end = false;
    CD.BZ = 1;
    // printf("编码器延时 开始:%.5f\n", ED_target_encoder);
}
bool encoder_delay(Car_Data& CD)
{
    if (((((CD.LE + CD.RE) / ED_K) / 2.0f) - ED_bef_encoder > ED_target_encoder) && ED_end == false)
    {
        // printf("编码器延时 结束:%.5f\n", ((CD.LE + CD.RE) / ED_K) / 2.0f - ED_bef_encoder);
        ED_end = true;
    }

    if (ED_end == true)
    {
        CD.BZ = 0;
        return true;
    }

    return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////// 控制类函数 /////////////////////////////////////////////
// 判断邻域是否有背景像素（优化为3x3邻域）
bool has_background_neighbor(uint8_t (*bin_image)[UVC_WIDTH], uint8_t y, uint8_t x) 
{
    for (int8_t dy = -1; dy <= 1; dy++) {
        for (int8_t dx = -1; dx <= 1; dx++) {
            if (x + dx >= 0 && x + dx < UVC_WIDTH && 
                y + dy >= 0 && y + dy < UVC_HEIGHT) {
                if (bin_image[y + dy][x + dx] == 0 || 
                    bin_image[y + dy][x + dx] == 9) {
                    return true;
                }
            }
        }
    }
    return false;
}

// 迷宫法追踪边界函数（优化版）
void detect_track_boundaries(uint8_t (*bin_image)[UVC_WIDTH]) 
{
    //////////////////////////////////////////////////////////////////////// 迷宫法获取赛道边界
    // 初始化左边界和右边界
    for (int i = 0; i < UVC_HEIGHT; i++) {
        leftedge[i] = -1;
        rightedge[i] = UVC_WIDTH;
    }

    // 定义8邻域搜索方向（调整优先级：优先向上/斜上）
    int8_t dx[] = {0, -1, 1, -1, 1, -1, 1, 0};    // 列偏移（x方向）
    int8_t dy[] = {-1, -1, -1, 0, 0, 1, 1, 1};    // 行偏移（y方向）：优先向上

    // 从图像底部开始追踪边界
    for (uint8_t i = start_row; i > end_row; i--) {
        // -------------------- 左边界初始扫描 --------------------
        if (leftedge[i] == -1) {  // 当前行无历史边界点
            uint8_t found = 0;
            for (uint8_t j = 4; j < UVC_WIDTH; j++) {  // 从列4开始扫描
                if (bin_image[i][j] == 1 && 
                    ((bin_image[i][j-1] == 0 || bin_image[i][j-1] == 9) && 
                    (bin_image[i][j-2] == 0 || bin_image[i][j-2] == 9))) {
                    leftedge[i] = j;          // 记录左边界列号
                    bin_image[i][j] = 4;      // 标记为蓝色
                    found = 1;
                    break;
                }
            }
            if (!found) {
                leftedge[i] = 0;              // 未找到则设置为最左边
                bin_image[i][0] = 4;          // 标记为蓝色
            }
        }

        // -------------------- 右边界初始扫描 --------------------
        if (rightedge[i] == UVC_WIDTH) {  // 当前行无历史边界点
            uint8_t found = 0;
            for (uint8_t j = UVC_WIDTH - 5; j > 0; j--) {  // 从列UVC_WIDTH-5开始扫描
                if (bin_image[i][j] == 1 && 
                    ((bin_image[i][j+1] == 0 || bin_image[i][j+1] == 9) && 
                    (bin_image[i][j+2] == 0 || bin_image[i][j+2] == 9))) {
                    rightedge[i] = j;         // 记录右边界列号
                    bin_image[i][j] = 2;      // 标记为红色
                    found = 1;
                    break;
                }
            }
            if (!found) {
                rightedge[i] = UVC_WIDTH - 1; // 未找到则设置为最右边
                bin_image[i][UVC_WIDTH - 1] = 2; // 标记为红色
            }
        }

        // -------------------- 迷宫法追踪上一行边界 --------------------
        // 左边界追踪
        if (leftedge[i] > 0) {  // 当前行有有效左边界点
            uint8_t found = 0;
            for (int dir = 0; dir < 8; dir++) {  // 按优先级搜索8邻域
                int8_t nx = leftedge[i] + dx[dir];
                int8_t ny = i + dy[dir];
                if (nx >= 0 && nx < UVC_WIDTH && ny >= 0 && ny < UVC_HEIGHT) {
                    if (bin_image[ny][nx] == 1 && has_background_neighbor(bin_image, ny, nx)) {
                        leftedge[ny] = nx;      // 记录上一行左边界点
                        bin_image[ny][nx] = 4;  // 标记为蓝色
                        found = 1;
                        break;
                    }
                }
            }
        }

        // 右边界追踪
        if (rightedge[i] < UVC_WIDTH - 1) {  // 当前行有有效右边界点
            uint8_t found = 0;
            for (int dir = 0; dir < 8; dir++) {
                int8_t nx = rightedge[i] + dx[dir];
                int8_t ny = i + dy[dir];
                if (nx >= 0 && nx < UVC_WIDTH && ny >= 0 && ny < UVC_HEIGHT) {
                    if (bin_image[ny][nx] == 1 && has_background_neighbor(bin_image, ny, nx)) {
                        rightedge[ny] = nx;     // 记录上一行右边界点
                        bin_image[ny][nx] = 2;  // 标记为红色
                        found = 1;
                        break;
                    }
                }
            }
        }
    }
}

// 赛道中线计算和绘制
float image_middle_and_bias(uint8 (*image)[UVC_WIDTH])
{
    static float add_enhance = 0.5f;
    static float add_enhance_2 = 0;

    memset(middleline, -1, sizeof(middleline));                      // 中线初始化为-1列
    memset(middleline_valid, -1, sizeof(middleline_valid));          // 中线有效初始化为-1列
    memset(middleline_warn, -1, sizeof(middleline_warn));            // 中线警告初始化为-1列
    memset(middleline_invalid, -1, sizeof(middleline_invalid));      // 中线无效初始化为-1列

    // 1. 计算每行中线位置
    for (uint8 i = start_row; i > end_row; i--) 
    {
        uint8 left_valid  = (leftedge[i] > 0);
        uint8 right_valid = (rightedge[i] < UVC_WIDTH - 1);
        
        if (left_valid && right_valid) 
        {
            // 情况1：两个边界都有效
            middleline[i] = (leftedge[i] + rightedge[i]) >> 1;
        }
        else if (left_valid) 
        {
            // 情况2：只有左边界有效 = 使用左边界 + 固定偏移
            int val = (leftedge[i] +  UVC_WIDTH-1) * (1-add_enhance) + add_enhance_2;
            if(val <= UVC_WIDTH-1)
                middleline[i] = val;  // 假设赛道宽度约60像素（左边界+右边界）/2
            else
                middleline[i] = UVC_WIDTH-1;
        }
        else if (right_valid) 
        {
            // 情况3：只有右边界有效 = 使用右边界 - 固定偏移
            int val = rightedge[i] * add_enhance - add_enhance_2;
            if(val >= 0)
                middleline[i] = val;  // 假设赛道宽度约60像素
            else
                middleline[i] = 0;
        }
        else 
        {
            // 情况4：两个边界都无效 - 使用上一行的中线值
            if (i < start_row) 
            {
                middleline[i] = middleline[i+1];  // 使用下一行的值（更靠近车辆）
            } 
            else 
            {
                middleline[i] = UVC_WIDTH / 2;    // 第一行使用图像中心
            }
        }
        
        // 边界保护
        if (middleline[i] >= UVC_WIDTH - 3) {
            middleline[i] = UVC_WIDTH - 3;
        } else if (middleline[i] <= 2) {
            middleline[i] = 2;
        }
    }

    // 5. 标记中线点（区分不同类型）
    for (uint8 i = start_row; i > end_row; i--) 
    {
        uint8 col = middleline[i];
        // 确定标记颜色
        uint8 left_valid  = (leftedge[i] > 2);
        uint8 right_valid = (rightedge[i] < UVC_WIDTH - 3);
        uint8 color;
        
        if (left_valid && right_valid) 
        {
            color = 3;  // 绿色：两个边界都有效
            middleline_valid[i] = col;
        }
        else if (left_valid || right_valid) 
        {
            color = 5;  // 黄色：一个边界有效（估计值）
            middleline_warn[i] = col;
        } 
        else 
        {
            color = 2;  // 红色：两个边界都无效（估计值）
            middleline_invalid[i] = col;
        }
        
        image[i][col] = color;
        if (i > 0) image[i-1][col] = color;
        if (i < UVC_HEIGHT-1) image[i+1][col] = color;
    }

    return 0;
}

// 直线程度计算
float cal_line_degree(int *line, uint8_t SR, uint8_t ER)
{
    Point valid_points[UVC_HEIGHT] = {0};  // 存储有效点
    uint8_t valid_count = 0;               // 有效点数量

    // 提取有效点（忽略值为 0 的点）
    for (uint8_t i = SR; i > ER; i--) 
    {
        if (line[i] != 0 || line[i] != UVC_WIDTH -1)  // 忽略为 0 的点
        {
            valid_points[valid_count].x = i;
            valid_points[valid_count].y = line[i];
            valid_count++;
        }
    }

    // 计算直线程度（Pearson 相关系数）
    float line_degree = 0.0f;
    if (valid_count >= 2)  // 至少需要 2 个有效点
    {
        float sum_x = 0.0f, sum_y = 0.0f;
        float sum_x2 = 0.0f, sum_y2 = 0.0f;
        float sum_xy = 0.0f;

        for (uint8_t n = 0; n < valid_count; n++) 
        {
            float x = valid_points[n].x;
            float y = valid_points[n].y;
            sum_x += x;
            sum_y += y;
            sum_x2 += x * x;
            sum_y2 += y * y;
            sum_xy += x * y;
        }

        float numerator = valid_count * sum_xy - sum_x * sum_y;
        float denominator_x = valid_count * sum_x2 - sum_x * sum_x;
        float denominator_y = valid_count * sum_y2 - sum_y * sum_y;
        float denominator = sqrt(denominator_x * denominator_y);

        if (denominator != 0)  // 避免除零
            line_degree = numerator / denominator;
    }

    return line_degree;
}

// 计算舵机转角偏差
double compute_y(double x, double b) {
    double a = 9.0 * b + 1.0;     // 映射 b ∈ [0,1] 到 a ∈ [1,10]

    if (x == 0.0) return 0.0;     // 特别处理 x = 0

    double abs_x = fabs(x);
    double sign_x = (x > 0.0) ? 1.0 : -1.0;  // 提取符号，避免除以零
    double numerator = pow(abs_x, a);        // |x|^a
    double denominator = pow(16.0, a - 1.0); // 15^(a-1)

    return sign_x * (numerator / denominator);
}

// 控制算法
float control_algorithm()
{
    float val = pic_x_middle;
    float all_degree_flag = 0;
    uint8 bef_effective_num = 0;
    uint8 effective_num = 0;
    //优先走两边都有效区域
    for(uint8 i = end_row; i < start_row; i++)//获取有效次数
        if(leftedge[i] > 0 && rightedge[i] < pic_width - 1)
            bef_effective_num++;

    for(uint8 i = end_row; i < start_row; i++)//范围获取有效次数
    {
        if(leftedge[i] > 0 && rightedge[i] < pic_width - 1)
        {
            if(effective_num <= (int)(bef_effective_num * check_range))
            {
                all_degree_flag += middleline[i];
                effective_num++;
            } 
        }
    }

    if(effective_num > 3)//有效数量大于3就走两边都有效区域
    {
        val = all_degree_flag / effective_num;
    }
    else//走两边无效区域过小
    {
        effective_num = 0;
        all_degree_flag = 0;
        bef_effective_num = 0;
        for(uint8 i = end_row; i < start_row; i++)//获取有效次数
            if(leftedge[i] > 0 || rightedge[i] < pic_width - 1)
                bef_effective_num++;

        for(uint8 i = end_row; i < start_row; i++)//范围获取有效次数
        {
            if(leftedge[i] > 0 || rightedge[i] < pic_width - 1)
            {
                if(effective_num < (int)((start_row - end_row) * check_range) + end_row)
                {
                    all_degree_flag += middleline[i];
                    effective_num++;
                }
            }
        }

        if(effective_num > 1)//有效数量大于1就走两边无效区域过小
        {
            val = all_degree_flag / effective_num;
        }
    }

    get_line_blank((uint8*)AIB_array, pic_width, pic_height, LinePos {(int)val,0,(int)val,5}, 4,true);
    return (val / pic_x_middle) - 1.0f;
}

// 画面变化处理
void image_diff_deal(Car_Data& CD,int follow_mode = run_image_num)
{
    uint8 follow_array[UVC_HEIGHT][UVC_WIDTH];              // 二值化和洪水填充后的黑白图像               
    if(follow_mode == 0)
    {
        memcpy(follow_array,AIB_array,sizeof(AIB_array));
    }
    else if(follow_mode == 1)
    {
        memcpy(follow_array,BW_array,sizeof(BW_array));
    }

    // 圆环填充
    ring_slope_deal((uint8*)follow_array, pic_width, pic_height, ring_full);

    // 边界检测
    detect_track_boundaries(follow_array);
    // 中线计算和绘制
    image_middle_and_bias(AIB_array);
    // 偏差计算
    con_diff = control_algorithm();
    // printf("con_diff = %f\n",con_diff);

    // 优化处理
    optimization_deal(CD);


    static float speed_change_dis = 0.2;
    if(now_speed < target_speed && cycle_run)
    {
        now_speed += speed_change_dis;
    }
    else if(now_speed > target_speed && cycle_run)
    {
        now_speed -= speed_change_dis;
    }
    ///////////////////////////////////////////////// 控制输出 /////////////////////////////////////////////////
    pid_control(&servo_PID, 0, compute_y(con_diff * 16,basic_run_corner));//计算舵机转角偏差
    pid_control(&motor_PID, now_speed, motor_PID.out);//计算舵机转角偏差

    CD.SA = servo_PID.out;

if(cycle_run)
{
    CD.LM = motor_PID.out * (1 + con_diff * delta_LRW);//设置左边电机转速
    CD.RM = motor_PID.out * (1 - con_diff * delta_LRW);//设置右边电机转速
}
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// 数据处理 /////////////////////////////////////////////
remember_data RD;                   // 记忆数据

int frame_num = 0;                              //运行帧率
float remember_data_dir_angle = 0.4f;           //判断方向最小角[越小度数越大]
float remember_data_check_angle = 25.0f;        //合并的最小角
float remember_data_check_distance = 7000.0f;   //合并的最小距离
float forward_tolerance = 0.9f;                 //直行容差距离
float turn_tolerance    = 0.8f;                 //转弯容差角度
float turn_judge_diff   = 0.30f;                //转弯判断角度
int   LF_check_distance = 15000;                //长距离直行判断距离

// 全局状态变量（可以封装进结构体）
int bef_encoder_left  = 0;
int bef_encoder_right = 0;
float bef_angle_deg   = 0.0f;
char  bef_direction  = 'S';       // 上一方向

float total_angle     = 0.0f;      // 当前方向累计角度
int   total_distance = 0;         // 当前方向累计距离
int   start_index = 0;            // 元素索引


void element_optimization_API(const char* element)
{
    /////////////////////////////// 特殊元素 ///////////////////////////////
    if(strcmp(element, "LF") == 0)//长距离直行
    {
        target_speed = bef_target_speed * RD.ED_long_forward[0];
        servo_PID.p = bef_servo_P * RD.ED_long_forward[1];
        servo_PID.d = bef_servo_D * RD.ED_long_forward[2];
        delta_LRW = bef_delta_LRW * RD.ED_long_forward[3];
        basic_run_corner = bef_basic_run_corner * RD.ED_long_forward[4];
        check_range = bef_check_range * RD.ED_long_forward[5];
        motor_PID.i = bef_motor_I * RD.ED_long_forward[6];
        printf("长距离直行调整\n");
        return;
    }
    if(strcmp(element, "NF") == 0)//短距离直行
    {
        target_speed = bef_target_speed * RD.ED_small_forward[0];
        servo_PID.p = bef_servo_P * RD.ED_small_forward[1];
        servo_PID.d = bef_servo_D * RD.ED_small_forward[2];
        delta_LRW = bef_delta_LRW * RD.ED_small_forward[3];
        basic_run_corner = bef_basic_run_corner * RD.ED_small_forward[4];
        check_range = bef_check_range * RD.ED_small_forward[5];
        motor_PID.i = bef_motor_I * RD.ED_small_forward[6];
        printf("短距离直行调整\n");
        return;
    }
    if(strcmp(element, "s") == 0)//小s
    {
        target_speed = bef_target_speed * RD.ED_element_s[0];
        servo_PID.p = bef_servo_P * RD.ED_element_s[1];
        servo_PID.d = bef_servo_D * RD.ED_element_s[2];
        delta_LRW = bef_delta_LRW * RD.ED_element_s[3];
        basic_run_corner = bef_basic_run_corner * RD.ED_element_s[4];
        check_range = bef_check_range * RD.ED_element_s[5];
        motor_PID.i = bef_motor_I * RD.ED_element_s[6];
        printf("小s调整\n");
        return;
    }
    if(strcmp(element, "S") == 0)//大S
    {
        target_speed = bef_target_speed * RD.ED_element_S[0];
        servo_PID.p = bef_servo_P * RD.ED_element_S[1];
        servo_PID.d = bef_servo_D * RD.ED_element_S[2];
        delta_LRW = bef_delta_LRW * RD.ED_element_S[3];
        basic_run_corner = bef_basic_run_corner * RD.ED_element_S[4];
        check_range = bef_check_range * RD.ED_element_S[5];
        motor_PID.i = bef_motor_I * RD.ED_element_S[6];
        printf("大S调整\n");
        return;
    }

    
    /////////////////////////////// 角度元素 ///////////////////////////////
    if(strcmp(element, "A30") == 0)//30°
    {
        target_speed = bef_target_speed * RD.ED_angle_30[0];
        servo_PID.p = bef_servo_P * RD.ED_angle_30[1];
        servo_PID.d = bef_servo_D * RD.ED_angle_30[2];
        delta_LRW = bef_delta_LRW * RD.ED_angle_30[3];
        basic_run_corner = bef_basic_run_corner * RD.ED_angle_30[4];
        check_range = bef_check_range * RD.ED_angle_30[5];
        motor_PID.i = bef_motor_I * RD.ED_angle_30[6];
        printf("30°调整\n");  
        return;
    }
    if(strcmp(element, "A60") == 0)//60°
    {
        target_speed = bef_target_speed * RD.ED_angle_60[0];
        servo_PID.p = bef_servo_P * RD.ED_angle_60[1];
        servo_PID.d = bef_servo_D * RD.ED_angle_60[2];
        delta_LRW = bef_delta_LRW * RD.ED_angle_60[3];
        basic_run_corner = bef_basic_run_corner * RD.ED_angle_60[4];
        check_range = bef_check_range * RD.ED_angle_60[5];
        motor_PID.i = bef_motor_I * RD.ED_angle_60[6];
        printf("60°调整\n");
        return;
    }
    if(strcmp(element, "A90") == 0)//90°
    {
        target_speed = bef_target_speed * RD.ED_angle_90[0];
        servo_PID.p = bef_servo_P * RD.ED_angle_90[1];
        servo_PID.d = bef_servo_D * RD.ED_angle_90[2];
        delta_LRW = bef_delta_LRW * RD.ED_angle_90[3];
        basic_run_corner = bef_basic_run_corner * RD.ED_angle_90[4];
        check_range = bef_check_range * RD.ED_angle_90[5];
        motor_PID.i = bef_motor_I * RD.ED_angle_90[6];
        printf("90°调整\n");
        return;
    }
    if(strcmp(element, "A120") == 0)//120°
    {
        target_speed = bef_target_speed * RD.ED_angle_120[0];
        servo_PID.p = bef_servo_P * RD.ED_angle_120[1];
        servo_PID.d = bef_servo_D * RD.ED_angle_120[2];
        delta_LRW = bef_delta_LRW * RD.ED_angle_120[3];
        basic_run_corner = bef_basic_run_corner * RD.ED_angle_120[4];
        check_range = bef_check_range * RD.ED_angle_120[5];
        motor_PID.i = bef_motor_I * RD.ED_angle_120[6];
        printf("120°调整\n");
        return;
    }
    if(strcmp(element, "A150") == 0)//150°
    {
        target_speed = bef_target_speed * RD.ED_angle_150[0];
        servo_PID.p = bef_servo_P * RD.ED_angle_150[1];
        servo_PID.d = bef_servo_D * RD.ED_angle_150[2];
        delta_LRW = bef_delta_LRW * RD.ED_angle_150[3];
        basic_run_corner = bef_basic_run_corner * RD.ED_angle_150[4];
        check_range = bef_check_range * RD.ED_angle_150[5];
        motor_PID.i = bef_motor_I * RD.ED_angle_150[6];
        printf("150°调整\n");
        return;
    }
    if(strcmp(element, "A180") == 0)//180°
    {
        target_speed = bef_target_speed * RD.ED_angle_180[0];
        servo_PID.p = bef_servo_P * RD.ED_angle_180[1];
        servo_PID.d = bef_servo_D * RD.ED_angle_180[2];
        delta_LRW = bef_delta_LRW * RD.ED_angle_180[3];
        basic_run_corner = bef_basic_run_corner * RD.ED_angle_180[4];
        check_range = bef_check_range * RD.ED_angle_180[5];
        motor_PID.i = bef_motor_I * RD.ED_angle_180[6];
        printf("180°调整\n");
        return;
    }
    if(strcmp(element, "A270") == 0)//270°
    {
        target_speed = bef_target_speed * RD.ED_angle_270[0];
        servo_PID.p = bef_servo_P * RD.ED_angle_270[1];
        servo_PID.d = bef_servo_D * RD.ED_angle_270[2];
        delta_LRW = bef_delta_LRW * RD.ED_angle_270[3];
        basic_run_corner = bef_basic_run_corner * RD.ED_angle_270[4];
        check_range = bef_check_range * RD.ED_angle_270[5];
        motor_PID.i = bef_motor_I * RD.ED_angle_270[6];
        printf("270°调整\n");
        return;
    }
    if(strcmp(element, "A360") == 0)//360°
    {
        target_speed = bef_target_speed * RD.ED_element_ring[0];
        servo_PID.p = bef_servo_P * RD.ED_element_ring[1];
        servo_PID.d = bef_servo_D * RD.ED_element_ring[2];
        delta_LRW = bef_delta_LRW * RD.ED_element_ring[3];
        basic_run_corner = bef_basic_run_corner * RD.ED_element_ring[4];
        check_range = bef_check_range * RD.ED_element_ring[5];
        motor_PID.i = bef_motor_I * RD.ED_element_ring[6];
        printf("360°调整\n");
        return;
    }
}


// 元素优化接口
void element_optimization_deal(char element,float distance,float angle,Car_Data& CD)
{
    static char bef_element = 'S';
    
    if(element == 'S')//短直
    {
        if(distance < LF_check_distance)
        {
            if(abs(int(RD.element_angle_idealize[start_index+1])) == 30)
            {
                element_optimization_API("s");
            }
            else if(abs(int(RD.element_angle_idealize[start_index+1])) >= 60)
            {
                element_optimization_API("S");
            }
            else
            {
                element_optimization_API("NF");
            }
        }
        else if(distance >= LF_check_distance)//长直
        {
            element_optimization_API("LF");
        }
        
    }
    else if (element == 'L' || element == 'R')
    {
        if(abs(int(angle)) == 30)
        {
            if(abs(int(RD.element_angle_idealize[start_index+2])) == 30 || abs(int(RD.element_angle_idealize[start_index-2])) == 30)
            {
                element_optimization_API("s");
            }
            else
            {
                element_optimization_API("A30");
            }

        }
        else if(abs(int(angle)) == 60)
        {
            if(abs(int(RD.element_angle_idealize[start_index+2])) >= 60 && RD.element_distance[start_index+1] < LF_check_distance)
            {
                element_optimization_API("S");
            }
            else
            {
                element_optimization_API("A60");
            }
        }
        else if(abs(int(angle)) == 90)
        {
            if(abs(int(RD.element_angle_idealize[start_index+2])) >= 60)
            {
                element_optimization_API("S");
            }
            else
            {
                element_optimization_API("A90");
            }
        }
        else if(abs(int(angle)) == 120)
        {
            if(abs(int(RD.element_angle_idealize[start_index+2])) >= 60)
            {
                element_optimization_API("S");
            }
            else
            {
                element_optimization_API("A120");
            }
        }
        else if(abs(int(angle)) == 150)
        {
            element_optimization_API("A150");
        }
        else if(abs(int(angle)) == 180)
        {
            element_optimization_API("A180");
        }
        else if(abs(int(angle)) == 270)
        {
            element_optimization_API("A270");
        }
        else if(abs(int(angle)) == 360)
        {
            element_optimization_API("A360");
        }
    }

    bef_element = element;
}

// 回忆数据分析处理
void data_analysis_deal()
{
    printf("数据分析处理\n");

    ////////////////////////////////////// 处理角度和编码器数据变成坐标 //////////////////////////////////////
    for (int i = 0; i < RD.input_times; i++)
    {
        if(RD.angle[i] != NULL && RD.encoder_left[i] != NULL && RD.encoder_right[i] != NULL)
        {
            static int bef_encoder_left = 0;
            static int bef_encoder_right = 0;
            static int delta_d = 0;
            static int delta_x = 0;
            static int delta_y = 0;

            delta_d = (RD.encoder_left[i]  - bef_encoder_left) + (RD.encoder_right[i] - bef_encoder_right) / 2;
            delta_x += delta_d * cos(RD.angle[i]* M_PI / 180.0);
            delta_y += delta_d * sin(RD.angle[i]* M_PI / 180.0);

            RD.track_point[0][i] = delta_x;
            RD.track_point[1][i] = delta_y;

            // printf("point[%d] = %d, %d\n", i, point[0][i], point[1][i]);

            bef_encoder_left = RD.encoder_left[i];
            bef_encoder_right = RD.encoder_right[i];
        }
    }

    ////////////////////////////////////// 轨迹数据采集与优化合并 //////////////////////////////////////
    float check_point_extent = 1.0f;                     // 判断最大角度阈值
    char now_direction = 'S';                            // 当前方向
    int new_element_number = 0;                          // 优化后轨迹段数量
    int bef_encoder_left = 0, bef_encoder_right = 0;     // 编码器历史值
    double bef_angle_deg = 0;                            // 角度历史值
    double total_angle = 0;                              // 累计角度
    float total_distance = 0;                            // 累计距离
    char bef_direction = 'S';                            // 历史方向

    // 轨迹点计算变量
    int delta_x = 0, delta_y = 0;
    int save_element_num = 0;
    int bef_element_num = 0;

    for (int i = 1; i < RD.input_times - 1; i++) 
    {
        // 1. 基础数据计算
        double angle_deg = RD.angle[i] - bef_angle_deg;  // 角度变化量
        float motor_delta_d = ((RD.encoder_left[i] + RD.encoder_right[i]) - (bef_encoder_left + bef_encoder_right)) / 2.0f;  // 距离变化量

        // 2. 方向判断
        if (total_distance > remember_data_check_distance)
        {
            if (angle_deg < -remember_data_dir_angle) now_direction = 'L';
            else if (angle_deg > remember_data_dir_angle) now_direction = 'R';
            else now_direction = 'S';
        }

        // 3. 轨迹段状态管理
        if (now_direction == bef_direction) 
        {
            // 同向累加
            total_angle += angle_deg;
            total_distance += motor_delta_d;
        }
        else
        {
            // 方向改变时处理上一段轨迹
            if (bef_direction != 'S' || total_distance > 0)  // 避免初始空段
            {
                // 3.1 小角度过滤与合并
                if ((bef_direction == 'L' || bef_direction == 'R') && fabs(total_angle) < remember_data_check_angle  || (total_distance < remember_data_check_distance)) 
                {
                    if (new_element_number > 0)  // 合并到上一段
                    {
                        RD.element_angle[new_element_number - 1] += total_angle;
                        RD.element_distance[new_element_number - 1] += total_distance;
                    }
                }
                else  // 保留有效段
                {
                    // 3.2 方向一致性合并
                    if (new_element_number > 0 && RD.element_state[new_element_number - 1] == bef_direction)
                    {
                        RD.element_angle[new_element_number - 1] += total_angle;
                        RD.element_distance[new_element_number - 1] += total_distance;
                    }
                    else  // 新增轨迹段
                    {
                        RD.element_state[new_element_number] = bef_direction;
                        RD.element_angle[new_element_number] = total_angle;
                        RD.element_distance[new_element_number] = total_distance;
                        new_element_number++;
                    }
                }
            }
            // 重置状态
            bef_direction = now_direction;
            total_angle = angle_deg;
            total_distance = motor_delta_d;
        }

        // 4. 轨迹点记录
        int delta_d = (RD.encoder_left[i] - bef_encoder_left + RD.encoder_right[i] - bef_encoder_right) / 2;
        delta_x += delta_d * cos(RD.angle[i] * M_PI / 180.0);
        delta_y += delta_d * sin(RD.angle[i] * M_PI / 180.0);

        if (bef_element_num != new_element_number)
        {
            save_element_num = 0;
            bef_element_num = new_element_number;
        }
        else
        {
            save_element_num++;
        }
        RD.element_track_point[new_element_number][0][save_element_num] = delta_x;
        RD.element_track_point[new_element_number][1][save_element_num] = delta_y;

        // 更新历史数据
        bef_angle_deg = RD.angle[i];
        bef_encoder_left = RD.encoder_left[i];
        bef_encoder_right = RD.encoder_right[i];
    }

    // 处理最后一段轨迹
    if (bef_direction != 'S' || total_distance > 0)
    {
        if ((bef_direction == 'L' || bef_direction == 'R') && fabs(total_angle) < remember_data_check_angle  || (total_distance < remember_data_check_distance))
        {
            if (new_element_number > 0)
            {
                RD.element_angle[new_element_number - 1] += total_angle;
                RD.element_distance[new_element_number - 1] += total_distance;
            }
        }
        else
        {
            if (new_element_number > 0 && RD.element_state[new_element_number - 1] == bef_direction)
            {
                RD.element_angle[new_element_number - 1] += total_angle;
                RD.element_distance[new_element_number - 1] += total_distance;
            }
            else
            {
                RD.element_state[new_element_number] = bef_direction;
                RD.element_angle[new_element_number] = total_angle;
                RD.element_distance[new_element_number] = total_distance;
                new_element_number++;
            }
        }
    }

    RD.element_number = new_element_number;  // 更新最终轨迹段数量


    
    ////////////////////////////////////// 新增的角度估计与标准化逻辑开始 //////////////////////////////////////
    // 角度标准化与理想角度估计（支持多种理想角度）
    for (int i = 0; i < RD.element_number; i++) {
        float actual_angle = RD.element_angle[i];
        int ideal_angle = 0;
        int min_diff = 10000;
        if (RD.element_state[i] == 'L') {
            // 匹配最接近的正理想角度
            for (int k = 0; k < 8; k++) {
                int diff = abs((int)fabs(actual_angle) - RD.element_kind[k]);
                if (diff < min_diff) {
                    min_diff = diff;
                    ideal_angle = RD.element_kind[k];
                }
            }
            RD.element_angle_idealize[i] = (float)ideal_angle; // 直接赋值为标准化角度
        } else if (RD.element_state[i] == 'R') {
            // 匹配最接近的负理想角度
            for (int k = 0; k < 8; k++) {
                int diff = abs((int)fabs(actual_angle) - RD.element_kind[k]);
                if (diff < min_diff) {
                    min_diff = diff;
                    ideal_angle = -RD.element_kind[k];
                }
            }
            RD.element_angle_idealize[i] = (float)ideal_angle; // 直接赋值为标准化角度
        } else {
            RD.element_angle_idealize[i] = 0.0f;
        }
    }

    ////////////////////////////////////// 提取和规划数据 //////////////////////////////////////
    for(int i = 0; i < RD.element_number; i++)
    {
        if(RD.element_state[i] == 'L')
        {
            printf("数据: %d, 左拐 %.1f°, 距离 %.1f\n", i, RD.element_angle_idealize[i], RD.element_distance[i]/1000.0f);
        }
        else if(RD.element_state[i] == 'R')
        {
            printf("数据: %d, 右拐 %.1f°, 距离 %.1f\n", i, RD.element_angle_idealize[i], RD.element_distance[i]/1000.0f);
        }
        else
        {
            printf("数据: %d, 直线 %.1f°, 距离 %.1f\n", i, RD.element_angle_idealize[i], RD.element_distance[i]/1000.0f);
        }
    }
}

// 实时数据分析函数
int realtime_analysis(Car_Data& CD)
{
    if(frame_num == 0)
    {
        bef_angle_deg = RD.angle[frame_num];
        bef_encoder_left = RD.encoder_left[frame_num];
        bef_encoder_right = RD.encoder_right[frame_num];
    }

    if (RD.element_state[start_index] == 'S')//直线处理
    {
        if(total_distance > RD.element_distance[start_index] * forward_tolerance)
        {
            if(RD.element_state[start_index+1] == 'L' && con_diff < -turn_judge_diff)
            {
                start_index++;
                total_distance = 0.0f;
                printf("直行完成！左转弯\n\n\n");
            }
            else if(RD.element_state[start_index+1] == 'R' && con_diff > turn_judge_diff)
            {
                start_index++;
                total_distance = 0.0f;
                printf("直行完成！右转弯\n\n\n");
            }
        }

        if(total_distance > RD.element_distance[start_index])
        {
            start_index++;
            total_distance = 0.0f;
            printf("强制直行完成\n\n\n");
        }
        
        total_distance += ((RD.encoder_left[frame_num] - bef_encoder_left) + (RD.encoder_right[frame_num] - bef_encoder_right))/2.0f;
        // printf("直行！目距: %.2f, 当距: %.2f, 当度:%.2f°\n", RD.element_distance[start_index]/1000.0f,total_distance/1000.0f, fabs(con_diff));
    }
    else//转弯处理
    {
        if(fabs(total_angle) > fabs(RD.element_angle[start_index] * turn_tolerance) || total_distance > RD.element_distance[start_index] * forward_tolerance)
        {
            if(RD.element_state[start_index] == 'L')
            {
                if( con_diff > -turn_judge_diff )
                {
                    start_index++;
                    total_angle = 0.0f;
                    total_distance = 0.0f;
                    printf("左转弯完成！\n\n\n");
                }
            }
            else if(RD.element_state[start_index] == 'R')
            {
                if( con_diff < turn_judge_diff )
                {
                    start_index++;
                    total_angle = 0.0f;
                    total_distance = 0.0f;
                    printf("右转弯完成！\n\n\n");
                }
            }
            
        }

        if(fabs(total_angle) > fabs(RD.element_angle_idealize[start_index]) || total_distance > RD.element_distance[start_index])
        {
            start_index++;
            total_angle = 0.0f;
            total_distance = 0.0f;
            printf("强制转弯完成！\n\n\n");
        }

        total_angle += RD.angle[frame_num] - bef_angle_deg;
        total_distance += ((RD.encoder_left[frame_num] - bef_encoder_left) + (RD.encoder_right[frame_num] - bef_encoder_right))/2.0f;
        
        if(RD.element_state[start_index] == 'L')
        {
            // printf("左转！目角: %.2f°, 当角: %.2f°\n", RD.element_angle_idealize[start_index], total_angle);
        }
        else if(RD.element_state[start_index] == 'R')
        {
            // printf("右转！目角: %.2f°, 当角: %.2f°\n", RD.element_angle_idealize[start_index], total_angle);
        }
    }
    
    
    element_optimization_deal(RD.element_state[start_index], RD.element_distance[start_index], RD.element_angle_idealize[start_index],CD);
    bef_angle_deg = RD.angle[frame_num];
    bef_encoder_left = RD.encoder_left[frame_num];
    bef_encoder_right = RD.encoder_right[frame_num];
    
    return 0;
}

// 获取数据并实时分析
void optimization_deal(Car_Data& CD)
{

    if (RD.input_times < remember_data_size - 1 && data_remember == 1)//数据收集
    {
        RD.encoder_left[RD.input_times]  = CD.LE;
        RD.encoder_right[RD.input_times] = CD.RE;
        RD.angle[RD.input_times]         = CD.HA;

        RD.input_times++;
        return;
    }

    if (RD.input_times == remember_data_size - 1 || data_remember == 2)//数据收集结束
    {
        data_analysis_deal();

        save_remember_data_json("data/data.json");//保存数据

        data_remember = 3;

        total_angle = 0.0f;
        total_distance = 0.0f;

        printf("数据收集结束\n");
        return;
    }

    if(data_remember == 4)//优化处理
    {
        RD.encoder_left[frame_num]  = CD.LE;
        RD.encoder_right[frame_num] = CD.RE;
        RD.angle[frame_num]         = CD.HA;

        // printf("优化处理...当前帧数:%d\n",frame_num);

        // 实时分析
        realtime_analysis(CD);

        frame_num++;
        return;
    }
}


///////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////// 参数初始化函数 ///////////////////////////////////////////
void init_parameter()
{
    bef_target_speed = target_speed;

    bef_servo_P = bef_servo_P == 0 ? servo_PID.p : bef_servo_P;
    servo_PID.p = bef_servo_P;
    bef_servo_D = bef_servo_D == 0 ? servo_PID.d : bef_servo_D;
    servo_PID.d = bef_servo_D;
    bef_motor_I = bef_motor_I == 0 ? motor_PID.i : bef_motor_I;
    motor_PID.i = bef_motor_I;
    bef_delta_LRW = bef_delta_LRW == 0 ? delta_LRW : bef_delta_LRW;
    delta_LRW = bef_delta_LRW;
    bef_check_range = bef_check_range == 0 ? check_range : bef_check_range;
    check_range = bef_check_range;
    bef_basic_run_corner = bef_basic_run_corner == 0 ? basic_run_corner : bef_basic_run_corner;
    basic_run_corner = bef_basic_run_corner;

    bef_path_thickness = bef_path_thickness == 0 ? path_thickness : bef_path_thickness;
    path_thickness = bef_path_thickness;
    bef_find_line_pos = bef_find_line_pos == 0 ? ring_find_pos : bef_find_line_pos;
    ring_find_pos = bef_find_line_pos;
    
    con_diff = 0;                   // 舵机转角偏差
    ring_times = 0;                 // 圆环次数
    cross_times = 0;                // 十字次数
    ED_bef_encoder = 0;             // 编码器延迟前值 0
    ED_target_encoder = 0;          // 编码器延迟目标值 0
    ED_end = true;                  // 编码器延迟结束 true:结束 false:未结束
    run_image_num = 0;              // 运行图像次数 0:腐蚀循迹 1:非腐蚀循迹
    ring_full = 0;                  // 圆环方向 0:无圆环 1:左圆环 -1:右圆环
    start_run = 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////// 外部调用函数 ///////////////////////////////////////////




//初始化全局变量
DLL_EXPORT void init_DLL()
{
    init_parameter();

    frame_num = 0;//帧重置
    start_index = 0;
    now_speed = 0.0f;

    printf("Dll 加载成功！\n");
}

// 图像处理
DLL_EXPORT void Camera_Deal(uint8* dst, Car_Data& CD)
{
    // 二值化
    binarize_image_inplace(otsuThreshold(dst, pic_width, pic_height,add_Threshold), dst, (uint8*)BW_array, pic_width, pic_height,top_fill);

    // 泛洪填充
    FloodFill((uint8*)BW_array, pic_width, pic_height, get_line_blank((uint8*)BW_array, pic_width, pic_height, LinePos {0, pic_height - 1, pic_width - 1, pic_height - 1 }, 3));

    // 复制到AIB_array
    memcpy(AIB_array, BW_array, pic_width * pic_height);

    // 剔除小黑区域
    RemoveSmallBlackRegions((uint8*)AIB_array, pic_width, pic_height, 25, 1);

    // 边界腐蚀
    ApplyInnerBorder((uint8*)AIB_array, pic_width, pic_height, path_thickness);

    // 控制逻辑
    image_diff_deal(CD);

    // 判断元素
    Element_Check(CD);

    
    // 编码器延迟
    encoder_delay(CD);

    // 复制到dst
    memcpy(dst, AIB_array, pic_width * pic_height);
}












// 按钮状态处理
DLL_EXPORT void get_button_state(uint8 button_state)
{
    if(button_state == 1)
    {
        if(data_remember == 0)
        {
            data_remember = 1;
            printf("开始收集数据\n");
        }
        else if(data_remember == 1)
        {
            data_remember = 2;
            printf("结束并分析数据\n");
        }
        return;
    }
    if(button_state == 2)
    {
        data_remember = 0;
        memset(&RD, 0, sizeof(RD));
        printf("重置优化处理\n");
        return;
    }
    if(button_state == 3)
    {
        data_remember = 3;
        printf("开始优化处理\n");
        return;
    }
    if(button_state == 4)
    {
        load_remember_data_json("data/data.json");
        printf("导入数据!\n");
        for(int i = 0; i < RD.element_number; i++)
        {
            if(RD.element_state[i] == 'L')
            {
                printf("数据: %d, 左拐 %.1f°, 距离 %.1f\n", i, RD.element_angle_idealize[i], RD.element_distance[i]/1000.0f);
            }
            else if(RD.element_state[i] == 'R')
            {
                printf("数据: %d, 右拐 %.1f°, 距离 %.1f\n", i, RD.element_angle_idealize[i], RD.element_distance[i]/1000.0f);
            }
            else
            {
                printf("数据: %d, 直线 %.1f°, 距离 %.1f\n", i, RD.element_angle_idealize[i], RD.element_distance[i]/1000.0f);
            }
        }
        return;
    }
}

// UI参数修改处理
DLL_EXPORT void value_change(uint8 value_type, float value)
{
    if(value_type == 1)
    {
        printf("修改微分系数:%.5f\n",value);
        return;
    }
    if(value_type == 2)
    {
        basic_run_corner = value;
        bef_basic_run_corner = basic_run_corner;
        printf("修改敏感度:%.5f\n", value);
        return;
    }
    if(value_type == 3)
    {
        path_thickness = (int)value;
        bef_path_thickness = path_thickness;
        printf("修改腐蚀层数:%.5f\n", value);
        return;
    }
    if(value_type == 4)
    {
        printf("修改阈值:%.5f\n", value);
        return;
    }
    if(value_type == 5)
    {
        target_speed = value;
        printf("修改速度:%.5f\n", value);
        return;
    }
    if(value_type == 6)
    {
        delta_LRW = value;
        printf("修改左右轮差值:%.5f\n", value);
        return;
    }
    if(value_type == 7)
    {
        cycle_run = value == 1 ? true : false;
        printf("是否运行:%.5f\n", value);
        if(cycle_run)
        {
            if(data_remember == 0)
                data_remember++;
            else if(data_remember == 3)
                data_remember++;
            printf("开始运行\n");
        }
        else
        {
            if(data_remember == 1)
                data_remember++;
            printf("停止运行\n");
        }
        return;
    }
}








DLL_EXPORT void __stdcall load_remember_data_json(const char* filename) 
{
    FILE* fp = fopen(filename, "r");
    if (!fp) { printf("无法打开文件: %s\n", filename); return; }
    
    char* buffer = NULL;
    long length = 0;
    fseek(fp, 0, SEEK_END);
    length = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    buffer = (char*)malloc(length + 1);
    if (!buffer) { fclose(fp); printf("内存分配失败\n"); return; }
    fread(buffer, 1, length, fp);
    buffer[length] = '\0';
    fclose(fp);

    // // 解析input_times
    // char* p = strstr(buffer, "\"input_times\"");
    // if (p) sscanf(p, " \"input_times\" : %d", &RD.input_times);

    // // 解析encoder_left
    // p = strstr(buffer, "\"encoder_left\"");
    // if (p) {
    //     char* arr_start = strchr(p, '[');
    //     char* arr_end = strchr(arr_start, ']');
    //     if (arr_start && arr_end) {
    //         char arr_buf[4096] = {0};
    //         strncpy(arr_buf, arr_start + 1, arr_end - arr_start - 1);
    //         char* token = strtok(arr_buf, ",");
    //         int i = 0;
    //         while (token && i < remember_data_size) {
    //             RD.encoder_left[i++] = atoi(token);
    //             token = strtok(NULL, ",");
    //         }
    //     }
    // }
    // // 解析encoder_right
    // p = strstr(buffer, "\"encoder_right\"");
    // if (p) {
    //     char* arr_start = strchr(p, '[');
    //     char* arr_end = strchr(arr_start, ']');
    //     if (arr_start && arr_end) {
    //         char arr_buf[4096] = {0};
    //         strncpy(arr_buf, arr_start + 1, arr_end - arr_start - 1);
    //         char* token = strtok(arr_buf, ",");
    //         int i = 0;
    //         while (token && i < remember_data_size) {
    //             RD.encoder_right[i++] = atoi(token);
    //             token = strtok(NULL, ",");
    //         }
    //     }
    // }
    // // 解析angle
    // p = strstr(buffer, "\"angle\"");
    // if (p) {
    //     char* arr_start = strchr(p, '[');
    //     char* arr_end = strchr(arr_start, ']');
    //     if (arr_start && arr_end) {
    //         char arr_buf[4096] = {0};
    //         strncpy(arr_buf, arr_start + 1, arr_end - arr_start - 1);
    //         char* token = strtok(arr_buf, ",");
    //         int i = 0;
    //         while (token && i < remember_data_size) {
    //             RD.angle[i++] = (float)atof(token);
    //             token = strtok(NULL, ",");
    //         }
    //     }
    // }
    // // 解析track_point二维数组
    // p = strstr(buffer, "\"track_point\"");
    // if (p) {
    //     char* arr_start = strchr(p, '['); // 第一个[
    //     if (arr_start) arr_start = strchr(arr_start + 1, '['); // 第二个[
    //     for (int row = 0; row < 2 && arr_start; row++) {
    //         char* arr_end = strchr(arr_start, ']');
    //         if (arr_end) {
    //             char arr_buf[4096] = {0};
    //             strncpy(arr_buf, arr_start + 1, arr_end - arr_start - 1);
    //             char* token = strtok(arr_buf, ",");
    //             int col = 0;
    //             while (token && col < remember_data_size) {
    //                 RD.track_point[row][col++] = atoi(token);
    //                 token = strtok(NULL, ",");
    //             }
    //             arr_start = strchr(arr_end + 1, '['); // 下一个[
    //         }
    //     }
    // }
    // 解析element_number
    char* p = strstr(buffer, "\"element_number\"");
    if (p) sscanf(p, " \"element_number\" : %d", &RD.element_number);

    // 解析element_state
    p = strstr(buffer, "\"element_state\"");
    if (p) {
        char* arr_start = strchr(p, '[');
        char* arr_end = strchr(arr_start, ']');
        if (arr_start && arr_end) {
            char arr_buf[4096] = {0};
            strncpy(arr_buf, arr_start + 1, arr_end - arr_start - 1);
            char* token = strtok(arr_buf, ",");
            int i = 0;
            while (token && i < remember_data_size) {
                // 跳过引号
                while (*token == ' ' || *token == '\"') token++;
                RD.element_state[i++] = *token;
                token = strtok(NULL, ",");
            }
        }
    }
    // 解析element_angle
    p = strstr(buffer, "\"element_angle\"");
    if (p) {
        char* arr_start = strchr(p, '[');
        char* arr_end = strchr(arr_start, ']');
        if (arr_start && arr_end) {
            char arr_buf[4096] = {0};
            strncpy(arr_buf, arr_start + 1, arr_end - arr_start - 1);
            char* token = strtok(arr_buf, ",");
            int i = 0;
            while (token && i < remember_data_size) {
                RD.element_angle[i++] = (float)atof(token);
                token = strtok(NULL, ",");
            }
        }
    }
    // 解析element_distance
    p = strstr(buffer, "\"element_distance\"");
    if (p) {
        char* arr_start = strchr(p, '[');
        char* arr_end = strchr(arr_start, ']');
        if (arr_start && arr_end) {
            char arr_buf[4096] = {0};
            strncpy(arr_buf, arr_start + 1, arr_end - arr_start - 1);
            char* token = strtok(arr_buf, ",");
            int i = 0;
            while (token && i < remember_data_size) {
                RD.element_distance[i++] = (float)atof(token);
                token = strtok(NULL, ",");
            }
        }
    }
    // 解析element_angle_idealize
    p = strstr(buffer, "\"element_angle_idealize\"");
    if (p) {
        char* arr_start = strchr(p, '[');
        char* arr_end = strchr(arr_start, ']');
        if (arr_start && arr_end) {
            char arr_buf[4096] = {0};
            strncpy(arr_buf, arr_start + 1, arr_end - arr_start - 1);
            char* token = strtok(arr_buf, ",");
            int i = 0;
            while (token && i < remember_data_size) {
                RD.element_angle_idealize[i++] = (float)atof(token);
                token = strtok(NULL, ",");
            }
        }
    }
    // 解析element_track_point 三维数组 [element_number][2][input_times]
    p = strstr(buffer, "\"element_track_point\"");
    if (p) {
        char* arr_start = strchr(p, '['); // 第一个[
        if (arr_start) arr_start++; // 跳过第一个[
        for (int elem = 0; elem < RD.element_number; elem++) {
            // 找到每个element的开头 [
            while (*arr_start && *arr_start != '[') arr_start++;
            if (!*arr_start) break;
            arr_start++; // 进入element的[
            for (int xy = 0; xy < 2; xy++) {
                // 找到每个x/y的开头 [
                while (*arr_start && *arr_start != '[') arr_start++;
                if (!*arr_start) break;
                arr_start++; // 进入x/y的[
                char* arr_end = strchr(arr_start, ']');
                if (arr_end) {
                    char arr_buf[8192] = {0};
                    strncpy(arr_buf, arr_start, arr_end - arr_start);
                    arr_buf[arr_end - arr_start] = '\0';
                    char* token = strtok(arr_buf, ",");
                    int k = 0;
                    while (token && k < remember_data_size) {
                        RD.element_track_point[elem][xy][k++] = atoi(token);
                        token = strtok(NULL, ",");
                    }
                    arr_start = arr_end + 1; // 跳到下一个
                }
            }
            // 跳到下一个element的开头
            while (*arr_start && *arr_start != ']') arr_start++;
            if (*arr_start) arr_start++;
        }
    }
    free(buffer);
    printf("记忆数据已导入: %s\n", filename);
}



DLL_EXPORT void __stdcall save_remember_data_json(const char* filename) {
    // 自动创建一级目录
    char path[256] = {0};
    strcpy(path, filename);
    char* last_slash = strrchr(path, '\\');
    if (!last_slash) last_slash = strrchr(path, '/');
    if (last_slash) {
        *last_slash = '\0';
        if (_access(path, 0) == -1) {
            _mkdir(path); // 创建目录
        }
    }

    FILE* fp = fopen(filename, "w");
    if (!fp) { printf("无法打开或创建文件: %s\n", filename); return; }

    fprintf(fp, "{\n");
    fprintf(fp, "  \"input_times\": %d,\n", RD.input_times);

    // 数组写法
    #define WRITE_INT_ARRAY(name, arr, n) \
        fprintf(fp, "  \"" #name "\": ["); \
        for (int i = 0; i < n; ++i) { \
            fprintf(fp, "%d%s", arr[i], (i < n-1) ? "," : ""); \
        } \
        fprintf(fp, "],\n");

    #define WRITE_FLOAT_ARRAY(name, arr, n) \
        fprintf(fp, "  \"" #name "\": ["); \
        for (int i = 0; i < n; ++i) { \
            fprintf(fp, "%.6f%s", arr[i], (i < n-1) ? "," : ""); \
        } \
        fprintf(fp, "],\n");

    #define WRITE_CHAR_ARRAY(name, arr, n) \
        fprintf(fp, "  \"" #name "\": ["); \
        for (int i = 0; i < n; ++i) { \
            fprintf(fp, "\"%c\"%s", arr[i], (i < n-1) ? "," : ""); \
        } \
        fprintf(fp, "],\n");

    WRITE_INT_ARRAY(encoder_left, RD.encoder_left, RD.input_times)
    WRITE_INT_ARRAY(encoder_right, RD.encoder_right, RD.input_times)
    WRITE_FLOAT_ARRAY(angle, RD.angle, RD.input_times)

    // 新增：保存track_point二维数组
    fprintf(fp, "  \"track_point\": [\n");
    for (int row = 0; row < 2; ++row) {
        fprintf(fp, "    [");
        for (int col = 0; col < RD.input_times; ++col) {
            fprintf(fp, "%d%s", RD.track_point[row][col], (col < RD.input_times - 1) ? "," : "");
        }
        fprintf(fp, "]%s\n", (row < 1) ? "," : "");
    }
    fprintf(fp, "  ],\n");

    fprintf(fp, "  \"element_number\": %d,\n", RD.element_number);
    WRITE_CHAR_ARRAY(element_state, RD.element_state, RD.element_number)
    WRITE_FLOAT_ARRAY(element_angle, RD.element_angle, RD.element_number)
    WRITE_FLOAT_ARRAY(element_distance, RD.element_distance, RD.element_number)
    WRITE_FLOAT_ARRAY(element_angle_idealize, RD.element_angle_idealize, RD.element_number)

    WRITE_FLOAT_ARRAY(adjust_servo_P, RD.adjust_servo_P, RD.input_times)
    WRITE_FLOAT_ARRAY(adjust_servo_D, RD.adjust_servo_D, RD.input_times)
    WRITE_FLOAT_ARRAY(adjust_speed, RD.adjust_speed, RD.input_times)
    WRITE_FLOAT_ARRAY(adjust_delta_LRW, RD.adjust_delta_LRW, RD.input_times)
    // 新增：保存element_track_point三维数组 [element_number][2][input_times]
    fprintf(fp, "  \"element_track_point\": [\n");
    for (int elem = 0; elem < RD.element_number; ++elem) {
        fprintf(fp, "    [\n");
        for (int xy = 0; xy < 2; ++xy) {
            fprintf(fp, "      [");
            for (int k = 0; k < RD.input_times; ++k) {
                fprintf(fp, "%d%s", RD.element_track_point[elem][xy][k], (k < RD.input_times - 1) ? "," : "");
            }
            fprintf(fp, "]%s\n", (xy < 1) ? "," : "");
        }
        fprintf(fp, "    ]%s\n", (elem < RD.element_number - 1) ? "," : "");
    }
    fprintf(fp, "  ],\n");
    // 最后一个字段不加逗号
    fprintf(fp, "  \"adjust_basic_run_corner\": [");
    for (int i = 0; i < RD.input_times; ++i)
        fprintf(fp, "%.6f%s", RD.adjust_basic_run_corner[i], (i < RD.input_times-1) ? "," : "");
    fprintf(fp, "]\n}\n");

    fclose(fp);
    printf("记忆数据已保存到: %s\n", filename);
}












///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////END/////////////////////////////////////////////

































