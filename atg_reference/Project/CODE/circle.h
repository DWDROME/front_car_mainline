#ifndef CIRCLE_H
#define CIRCLE_H

enum circle_type_e {
    CIRCLE_NONE = 0,                            // 闂堢偛娓鹃悳顖浤佸锟�
    CIRCLE_LEFT_BEGIN, CIRCLE_RIGHT_BEGIN,      // 閸﹀棛骞嗗锟芥慨瀣剁礉鐠囧棗鍩嗛崚鏉垮礋娓氼湌鐟欐帞鍋ｉ崣锔跨娓氀囨毐閻╂挳浜鹃妴锟�
    CIRCLE_LEFT_RUNNING, CIRCLE_RIGHT_RUNNING,  // 閸﹀棛骞嗛崘鍛村劥閵嗭拷
    CIRCLE_LEFT_OUT, CIRCLE_RIGHT_OUT,          // 閸戝棗顦崙鍝勬妇閻滎垽绱濋崡瀹犵槕閸掝偄鍩岄崙铏瑰箚婢跺嫮娈慙鐟欐帞鍋ｉ妴锟�
    CIRCLE_NUM,                                 //
};

enum circle_ref_mode_e {
    CIRCLE_REF_NONE = 0,
    CIRCLE_REF_BEGIN_AB,
    CIRCLE_REF_IN_C,
};

typedef struct circle_anchor_point_s {
    int found;
    int id;
    int raw_x;
    int raw_y;
} circle_anchor_point_t;

extern const char *circle_type_name[CIRCLE_NUM];

extern enum circle_type_e circle_type;

extern enum circle_ref_mode_e circle_ref_mode;

extern circle_anchor_point_t circle_A_point;
extern circle_anchor_point_t circle_B_point;
extern circle_anchor_point_t circle_C_point;

extern int none_left_line , none_right_line ;

extern int have_left_line, have_right_line;

extern int circle_count;

extern int round_cirlce_left_num,round_cirlce_right_num;

void check_circle();
int circle_entry_candidate_pending(void);

void reset_circle_entry_votes();

void suppress_circle_entry_frames(int frames);

void suppress_circle_reentry_after_exit(void);

void clear_circle_entry_suppression(void);

void reset_circle_begin_flags();

void reset_circle_geometry_state(void);

void update_circle_heading(float yaw_rate_rad_s, int period_ms, int valid);
int circle_heading_enter_ready(void);

int circle_cal_log_enabled(void);

void run_circle();

void draw_circle();

#endif // CIRCLE_H
