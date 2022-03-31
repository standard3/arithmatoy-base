#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>

#include <cmocka.h>

#include "hello_world.h"

static void test_hello_world_with_NULL_string(void **state) {
  char *const str = get_hello_world(NULL);
  assert_string_equal(str, "Hello World !");
}

static void test_hello_world_with_empty_string(void **state) {
  char *const str = get_hello_world("");
  assert_string_equal(str, "Hello World !");
}

static void test_hello_world_with_my_name(void **state) {
  char *const str = get_hello_world("Laurent");
  assert_string_equal(str, "Hello World Laurent !");
}

int main() {
  struct CMUnitTest const tests[] = {
      cmocka_unit_test(test_hello_world_with_NULL_string),
      cmocka_unit_test(test_hello_world_with_empty_string),
      cmocka_unit_test(test_hello_world_with_my_name),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
