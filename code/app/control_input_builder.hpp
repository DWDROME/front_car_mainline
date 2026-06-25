#pragma once

#include <cstdint>

#include "types.hpp"

int64_t atg_distance_counts_from_encoder_delta(const control_feedback_t &fb);
int cross_half_relay_limit_frames(int period_ms);
void apply_cross_half_relay(control_input_t *input, int line_found);
control_input_t control_input_from_current_frame(const runtime_t *rt, int line_found);
