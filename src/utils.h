#pragma once

#include <stddef.h>
#include <string.h>

extern int VERBOSE;

const char *get_all_digits();
extern const size_t ALL_DIGIT_COUNT;

unsigned int get_digit_value(char base);

char to_digit(unsigned int value);

char *reverse(char *str);

char *drop_leading_zeros(const char *number);

void debug_abort(const char *debug_msg);
