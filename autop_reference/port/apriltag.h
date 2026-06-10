#ifndef AUTOP_REFERENCE_PORT_APRILTAG_H
#define AUTOP_REFERENCE_PORT_APRILTAG_H

enum apriltag_type_e {
    APRILTAG_NONE = 0,
    APRILTAG_MAYBE,
    APRILTAG_FOUND,
    APRILTAG_LEAVE,
    APRILTAG_NUM,
};

extern enum apriltag_type_e apriltag_type;
extern const char *apriltag_type_name[APRILTAG_NUM];

void check_apriltag(void);

#endif
