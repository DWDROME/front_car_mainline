#pragma once

#include "types.hpp"

void tracking_reset(runtime_t *rt);
int tracking_process_frame(runtime_t *rt);
int track_line_found(const runtime_t *rt);

int seed_pair_accepted(const seed_pair_t *sd, int state);
int midline_has_forward_lookahead(const midline_t *midline, int aim_distance, int ref_y);
