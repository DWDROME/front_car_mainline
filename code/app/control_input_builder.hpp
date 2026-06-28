#pragma once

#include <cstdint>

#include "types.hpp"

control_input_t control_input_from_current_frame(const runtime_t *rt, int line_found);
