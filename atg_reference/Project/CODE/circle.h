#ifndef CIRCLE_H
#define CIRCLE_H

enum circle_type_e {
    CIRCLE_NONE = 0,                            // 闂堢偛娓鹃悳顖浤佸锟�
    CIRCLE_LEFT_BEGIN, CIRCLE_RIGHT_BEGIN,      // 閸﹀棛骞嗗锟芥慨瀣剁礉鐠囧棗鍩嗛崚鏉垮礋娓氼湌鐟欐帞鍋ｉ崣锔跨娓氀囨毐閻╂挳浜鹃妴锟�
    CIRCLE_LEFT_IN, CIRCLE_RIGHT_IN,            // 閸﹀棛骞嗘潻娑樺弳閿涘苯宓嗙挧鏉垮煂娑擄拷娓氀呮纯闁搫绱濇稉锟芥笟褍娓鹃悳顖滄畱娴ｅ秶鐤嗛妴锟�
    CIRCLE_LEFT_RUNNING, CIRCLE_RIGHT_RUNNING,  // 閸﹀棛骞嗛崘鍛村劥閵嗭拷
    CIRCLE_LEFT_OUT, CIRCLE_RIGHT_OUT,          // 閸戝棗顦崙鍝勬妇閻滎垽绱濋崡瀹犵槕閸掝偄鍩岄崙铏瑰箚婢跺嫮娈慙鐟欐帞鍋ｉ妴锟�
    CIRCLE_LEFT_END, CIRCLE_RIGHT_END,          // 閸﹀棛骞嗙紒鎾存将閿涘苯宓嗛崘宥嗩偧鐠ф澘鍩岄崡鏇氭櫠閻╂挳浜鹃惃鍕秴缂冾喓锟斤拷
    CIRCLE_NUM,                                 //
};


extern const char *circle_type_name[CIRCLE_NUM];

extern enum circle_type_e circle_type;

extern int none_left_line , none_right_line ;

extern int have_left_line, have_right_line;

extern int is_large_circle,is_small_circle;

extern int circle_in_length , circle_in_distance;

extern int circle_count;

extern int round_cirlce_left_num,round_cirlce_right_num;

void check_circle();

void reset_circle_entry_votes();

void run_circle();

void draw_circle();

#endif // CIRCLE_H
