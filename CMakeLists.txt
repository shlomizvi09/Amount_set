cmake_minimum_required(VERSION 3.15)
project(amount_set C)

set(CMAKE_C_STANDARD 99)

add_executable(amount_set amount_set_tests.c amount_set_main.c
        amount_set_tests.h amount_set.c amount_set.h test_utilities.h)