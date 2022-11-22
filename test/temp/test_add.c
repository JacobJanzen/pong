#include "test_add.h"

#include <assert.h>

#include "../../include/temp.h"

void test_add_one() {
    int expected_result = 2;
    int input = 1;

    assert(expected_result == add_one(input));
}

void test_add_two() {
    int expected_result = 3;
    int input = 1;

    assert(expected_result == add_two(input));
}
