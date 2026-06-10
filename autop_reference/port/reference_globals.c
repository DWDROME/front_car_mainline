#include "headfile.h"
#include "main.h"
#include "camera_param.h"
#include "flash_param.h"

enum garage_type_e {
    GARAGE_NONE = 0,
    GARAGE_OUT_LEFT, GARAGE_OUT_RIGHT,
    GARAGE_FOUND_LEFT, GARAGE_FOUND_RIGHT,
    GARAGE_IN_LEFT, GARAGE_IN_RIGHT,
    GARAGE_PASS_LEFT, GARAGE_PASS_RIGHT,
    GARAGE_STOP,
    GARAGE_NUM,
};

enum yroad_type_e {
    YROAD_NONE = 0,
    YROAD_FOUND,
    YROAD_NEAR,
    YROAD_LEFT_RUN, YROAD_RIGHT_RUN,
    YROAD_LEFT_OUT, YROAD_RIGHT_OUT,
    YROAD_NUM,
};

enum apriltag_type_e {
    APRILTAG_NONE = 0,
    APRILTAG_MAYBE,
    APRILTAG_FOUND,
    APRILTAG_LEAVE,
    APRILTAG_NUM,
};

typedef struct openart_param_t {
    uint8_t rx_buffer[10];
    int fa_type;
    int openart_result;
    int64_t aprilencoder;
    int64_t aprilwaitencoder;
} openart_param_t;

float angle;

image_t img_raw = DEF_IMAGE(NULL, MT9V03X_CSI_W, MT9V03X_CSI_H);
static uint8_t img_thres_data[MT9V03X_CSI_H][MT9V03X_CSI_W];
image_t img_thres = DEF_IMAGE((uint8_t *)img_thres_data, MT9V03X_CSI_W, MT9V03X_CSI_H);
static uint8_t img_line_data[MT9V03X_CSI_H][MT9V03X_CSI_W];
image_t img_line = DEF_IMAGE((uint8_t *)img_line_data, MT9V03X_CSI_W, MT9V03X_CSI_H);

bool line_show_sample = false;
bool line_show_blur = false;
bool track_left = false;

int ipts0[POINTS_MAX_LEN][2];
int ipts1[POINTS_MAX_LEN][2];
int ipts0_num, ipts1_num;

float rpts0[POINTS_MAX_LEN][2];
float rpts1[POINTS_MAX_LEN][2];
int rpts0_num, rpts1_num;

float rpts0b[POINTS_MAX_LEN][2];
float rpts1b[POINTS_MAX_LEN][2];
int rpts0b_num, rpts1b_num;

float rpts0s[POINTS_MAX_LEN][2];
float rpts1s[POINTS_MAX_LEN][2];
int rpts0s_num, rpts1s_num;

float rpts0a[POINTS_MAX_LEN];
float rpts1a[POINTS_MAX_LEN];
int rpts0a_num, rpts1a_num;

float rpts0an[POINTS_MAX_LEN];
float rpts1an[POINTS_MAX_LEN];
int rpts0an_num, rpts1an_num;

float rptsc0[POINTS_MAX_LEN][2];
float rptsc1[POINTS_MAX_LEN][2];
int rptsc0_num, rptsc1_num;

float (*rpts)[2];
int rpts_num;

float rptsn[POINTS_MAX_LEN][2];
int rptsn_num;

int Ypt0_rpts0s_id, Ypt1_rpts1s_id;
bool Ypt0_found, Ypt1_found;

int Lpt0_rpts0s_id, Lpt1_rpts1s_id;
bool Lpt0_found, Lpt1_found;

bool is_straight0, is_straight1;

enum track_type_e track_type = TRACK_RIGHT;

enum garage_type_e garage_type = GARAGE_NONE;
const char *garage_type_name[GARAGE_NUM] = {
    "GARAGE_NONE",
    "GARAGE_OUT_LEFT", "GARAGE_OUT_RIGHT",
    "GARAGE_FOUND_LEFT", "GARAGE_FOUND_RIGHT",
    "GARAGE_IN_LEFT", "GARAGE_IN_RIGHT",
    "GARAGE_PASS_LEFT", "GARAGE_PASS_RIGHT",
    "GARAGE_STOP",
};

enum yroad_type_e yroad_type = YROAD_NONE;
const char *yroad_type_name[YROAD_NUM] = {
    "YROAD_NONE",
    "YROAD_FOUND",
    "YROAD_NEAR",
    "YROAD_LEFT_RUN", "YROAD_RIGHT_RUN",
    "YROAD_LEFT_OUT", "YROAD_RIGHT_OUT",
};

enum apriltag_type_e apriltag_type = APRILTAG_NONE;
int apriltag_time = 0;
const char *apriltag_type_name[APRILTAG_NUM] = {
    "APRILTAG_NONE",
    "APRILTAG_MAYBE",
    "APRILTAG_FOUND",
    "APRILTAG_LEAVE",
};

openart_param_t openart = {0};
int enable_adc = 0;

int64_t g_autop_reference_encoder_total = 0;

int64_t get_total_encoder(void)
{
    return g_autop_reference_encoder_total;
}

void check_garage(void)
{
}

void run_garage(void)
{
}

void draw_garage(void)
{
}

void check_yroad(void)
{
}

void run_yroad(void)
{
}

void draw_yroad(void)
{
}

void check_apriltag(void)
{
}

void openart_send(void)
{
}

void openart_mini(void)
{
}

void check_openart(void)
{
}
