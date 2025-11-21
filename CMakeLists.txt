cmake_minimum_required(VERSION 3.14)
project(lab5)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Основная программа
add_executable(main src/main.cpp src/CustomAllocator.cpp)
target_include_directories(main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.0
  TLS_VERIFY false
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Тесты
add_executable(tests tests/tests.cpp src/CustomAllocator.cpp)
target_link_libraries(tests GTest::gtest_main)
target_include_directories(tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

enable_testing()
add_test(NAME lab5_tests COMMAND tests)