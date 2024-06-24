#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

int VERBOSE = 0;

const char *get_all_digits() { return "0123456789abcdefghijklmnopqrstuvwxyz"; }
const size_t ALL_DIGIT_COUNT = 36;

void arithmatoy_free(char *number) { free(number); }

char *init_buffer(const size_t len) {
  char *result = (char *)calloc(len + 1, sizeof(char));
  result[len] = '\0';
  return result;
}

char *arithmatoy_add(unsigned int base, const char *lhs, const char *rhs) {
  if (VERBOSE) {
    fprintf(stderr, "add: entering function\n");
  }

  // Check for invalid inputs
  if (lhs == NULL || rhs == NULL || base >= ALL_DIGIT_COUNT) {
    return NULL;
  }

  // Drop leading zeros
  lhs = drop_leading_zeros(lhs);
  rhs = drop_leading_zeros(rhs);

  const size_t lhs_length = strlen(lhs);
  const size_t rhs_length = strlen(rhs);
  const size_t max_length = lhs_length > rhs_length ? lhs_length : rhs_length;
  char *result = init_buffer(max_length);

  unsigned int carry = 0;

  // Add the digits from right to left
  for (size_t i = 0; i < max_length; ++i) {
    const unsigned int lhs_digit =
        i < lhs_length ? get_digit_value(lhs[lhs_length - i - 1]) : 0;

    const unsigned int rhs_digit =
        i < rhs_length ? get_digit_value(rhs[rhs_length - i - 1]) : 0;

    const unsigned int sum = lhs_digit + rhs_digit + carry;

    // Compute the carry and the sum
    carry = sum / base;

    // Store the result
    result[max_length - i] = to_digit(sum % base);
  }

  // Store the last carry
  result[0] = to_digit(carry);

  return drop_leading_zeros(result);
}

char *arithmatoy_sub(unsigned int base, const char *lhs, const char *rhs) {
  if (VERBOSE) {
    fprintf(stderr, "sub: entering function\n");
  }

  // Check for invalid inputs
  if (lhs == NULL || rhs == NULL || base >= ALL_DIGIT_COUNT) {
    return NULL;
  }

  // Drop leading zeros
  lhs = drop_leading_zeros(lhs);
  rhs = drop_leading_zeros(rhs);

  const size_t lhs_length = strlen(lhs);
  const size_t rhs_length = strlen(rhs);
  const size_t max_length = lhs_length > rhs_length ? lhs_length : rhs_length;

  // Check if the result will be negative
  if (lhs_length < rhs_length ||
      (lhs_length == rhs_length && strcmp(lhs, rhs) < 0)) {
    return NULL;
  }

  char *result = init_buffer(max_length);

  unsigned int carry = 0;

  // Subtract the digits from right to left
  for (size_t i = 0; i < max_length; ++i) {
    const unsigned int lhs_digit =
        i < lhs_length ? get_digit_value(lhs[lhs_length - i - 1]) : 0;

    const unsigned int rhs_digit =
        i < rhs_length ? get_digit_value(rhs[rhs_length - i - 1]) : 0;

    const unsigned int sum = lhs_digit - rhs_digit + carry;

    // Compute the carry and the sum
    carry = sum / base;

    // Store the result
    result[max_length - i] = to_digit(sum % base);
  }

  // Store the last carry
  result[0] = to_digit(carry);

  return drop_leading_zeros(result);
}

char *arithmatoy_mul(unsigned int base, const char *lhs, const char *rhs) {
  if (VERBOSE) {
    fprintf(stderr, "mul: entering function\n");
  }

  // Check for invalid inputs
  if (lhs == NULL || rhs == NULL || base >= ALL_DIGIT_COUNT) {
    return NULL;
  }

  // Drop leading zeros
  lhs = drop_leading_zeros(lhs);
  rhs = drop_leading_zeros(rhs);

  const size_t lhs_length = strlen(lhs);
  const size_t rhs_length = strlen(rhs);
  const size_t max_length = lhs_length + rhs_length;

  char *result = init_buffer(max_length);

  // Initialize the result with zeros
  for (size_t i = 0; i < max_length; ++i) {
    result[i] = '0';
  }

  // Multiply each digit of lhs with each digit of rhs
  for (size_t i = 0; i < lhs_length; ++i) {
    for (size_t j = 0; j < rhs_length; ++j) {
      // Multiply the digits
      const unsigned int lhs_digit = get_digit_value(lhs[lhs_length - i - 1]);
      const unsigned int rhs_digit = get_digit_value(rhs[rhs_length - j - 1]);
      const unsigned int mul = lhs_digit * rhs_digit;

      // Compute the carry and the sum
      unsigned int carry = mul / base;
      unsigned int sum = mul % base;

      // Compute the position of the result
      size_t k = i + j;

      // Add the result to the current position
      while (sum > 0) {
        sum += get_digit_value(result[max_length - k - 1]);
        carry += sum / base;
        result[max_length - k - 1] = to_digit(sum % base);
        sum = carry;
        carry = 0;
        ++k;
      }
    }
  }

  return drop_leading_zeros(result);
}

unsigned int get_digit_value(char digit) {
  // Convert a digit from get_all_digits() to its integer value
  if (digit >= '0' && digit <= '9') {
    return digit - '0';
  }
  if (digit >= 'a' && digit <= 'z') {
    return 10 + (digit - 'a');
  }
  return -1;
}

char to_digit(unsigned int value) {
  // Convert an integer value to a digit from get_all_digits()
  if (value >= ALL_DIGIT_COUNT) {
    debug_abort("Invalid value for to_digit()");
    return 0;
  }
  return get_all_digits()[value];
}

char *reverse(char *str) {
  // Reverse a string in place, return the pointer for convenience
  // Might be helpful if you fill your char* buffer from left to right
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

char *drop_leading_zeros(const char *number) {
  // If the number has leading zeros, return a pointer past these zeros
  // Might be helpful to avoid computing a result with leading zeros
  if (*number == '\0') {
    return (char *)number;
  }
  while (*number == '0') {
    ++number;
  }
  if (*number == '\0') {
    --number;
  }
  return (char *)number;
}

void debug_abort(const char *debug_msg) {
  // Print a message and exit
  fprintf(stderr, debug_msg);
  exit(EXIT_FAILURE);
}
