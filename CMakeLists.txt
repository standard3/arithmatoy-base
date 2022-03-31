cmake_minimum_required(VERSION 3.22)

project(hello_world)

add_library(hello_world src/hello_world.c)
target_include_directories(hello_world PUBLIC src/include/)
file(GLOB_RECURSE INCLUDE_FILES "src/include/*.h")
set_target_properties(hello_world PROPERTIES PUBLIC_HEADER ${INCLUDE_FILES})

install(TARGETS hello_world
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  PUBLIC_HEADER DESTINATION include
)

if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME) AND BUILD_TESTING)
  enable_testing()

  add_executable(test_hello_world src/tests/test_hello_world.c)
  target_link_libraries(test_hello_world PRIVATE hello_world)

  find_package(cmocka CONFIG REQUIRED)
  target_link_libraries(test_hello_world PRIVATE cmocka::cmocka)

  install(TARGETS test_hello_world)

  add_test(NAME test_hello_world COMMAND test_hello_world)
endif()
