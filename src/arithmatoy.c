#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

int VERBOSE = 0;

const char *get_all_digits() { return "0123456789abcdefghijklmnopqrstuvwxyz"; }
const size_t ALL_DIGIT_COUNT = 36;

void arithmatoy_free(char *number) { free(number); }

// Function to add two numbers
char *arithmatoy_add(unsigned int base, const char *lhs, const char *rhs) {
  size_t lhs_len = strlen(lhs);
  size_t rhs_len = strlen(rhs);
  char *result = (char*)calloc(lhs_len + 1, sizeof(char));
  int carry = 0;

  for (size_t i = 0; i < lhs_len; i++) {
    int lhs_digit = lhs[lhs_len - i - 1] - '0';
    int rhs_digit = (i < rhs_len) ? rhs[rhs_len - i - 1] - '0' : 0;
    int sum = carry + lhs_digit + rhs_digit;

    carry = sum/base;
    sum = sum%base;

    result[i] = sum + '0';
  }

  if (carry > 0) {
    result = realloc(result, lhs_len + 2);
    result[lhs_len] = carry + '0';
  }

  reverse(result);

  return result;
}

// Function to subtract two numbers
char *arithmatoy_sub(unsigned int base, const char *lhs, const char *rhs) {
  size_t lhs_len = strlen(lhs);
  size_t rhs_len = strlen(rhs);
  char *result = (char*)calloc(lhs_len + 1, sizeof(char));
  int carry = 0;

  for (size_t i = 0; i < lhs_len; i++) {
    int lhs_digit = lhs[lhs_len - i - 1] - '0';
    int rhs_digit = (i < rhs_len) ? rhs[rhs_len - i - 1] - '0' : 0;
    int diff = lhs_digit - rhs_digit - carry;

    if (diff < 0) {
      diff += base;
      carry = 1;
    } else {
      carry = 0;
    }

    result[i] = diff + '0';
  }

  if (carry != 0) {
    arithmatoy_free(result);
    return NULL;
  }

  reverse(result);

  return result;
}

Number* arithmatoy_mul(unsigned int base, const Number* lhs, const Number* rhs) {
    const char* all_digits = get_all_digits();
    int* res = calloc(lhs->len + rhs->len, sizeof(int));

    for (size_t i = 0; i < lhs->len; ++i) {
        for (size_t j = 0; j < rhs->len; ++j) {
            int digit_lhs = strchr(all_digits, tolower(lhs->number[i])) - all_digits;
            int digit_rhs = strchr(all_digits, tolower(rhs->number[j])) - all_digits;
            res[i + j] += digit_lhs * digit_rhs;
        }
    }

    for (size_t i = 0; i < lhs->len + rhs->len - 1; ++i) {
        res[i + 1] += res[i] / base;
        res[i] %= base;
    }

    char* res_str = calloc(lhs->len + rhs->len + 1, sizeof(char));
    size_t res_len = 0;

    for (size_t i = lhs->len + rhs->len; i-- > 0; ) {
        if (res_str[0] != '\0' || res[i] != 0)
            res_str[res_len++] = all_digits[res[i]];
    }

    res_str[res_len] = '\0';

    Number* result = create_number(res_str);

    free(res_str);
    free(res);

    return result;
}

unsigned int get_digit_value(char digit) {
  if (digit >= '0' && digit <= '9') {
    return digit - '0';
  }
  if (digit >= 'a' && digit <= 'z') {
    return 10 + (digit - 'a');
  }
  return -1;
}

char to_digit(unsigned int value) {
  if (value >= ALL_DIGIT_COUNT) {
    debug_abort("Invalid value for to_digit()");
    return 0;
  }
  return get_all_digits()[value];
}

char *reverse(char *str) {
  const size_t length = strlen(str);
  const size_t bound = length / 2;
  for (size_t i = 0; i < bound; ++i) {
    char tmp = str[i];
    const size_t mirror = length - i - 1;
    str[i] = str[mirror];
    str[mirror] = tmp;
  }
  return str;
}

const char *drop_leading_zeros(const char *number) {

  if (*number == '\0') {
    return number;
  }
  while (*number == '0') {
    ++number;
  }
  if (*number == '\0') {
    --number;
  }
  return number;
}

void debug_abort(const char *debug_msg) {
  fprintf(stderr, debug_msg);
  exit(EXIT_FAILURE);
}

