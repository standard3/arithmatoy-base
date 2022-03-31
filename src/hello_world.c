#include <stddef.h>
#include <stdlib.h>
#include <string.h>

char *get_hello_world(char const *who) {
  const char *prefix = "Hello World ";
  const size_t who_offset = strlen(prefix);
  const char *suffix = " !";
  const size_t who_length = who ? strlen(who) : 0;
  const size_t suffix_offset = who_offset + who_length;
  char *const buffer = (char *)malloc(suffix_offset + strlen(suffix) + 1);
  strcpy(buffer, prefix);
  if (who_length > 0) {
    strcpy(buffer + who_offset, who);
    strcpy(buffer + suffix_offset, suffix);
  } else {
    strcpy(buffer + suffix_offset, suffix + 1); // Don't add extra ' '
  }
  return buffer;
}

void free_hello_world(char *str) { free(str); }
