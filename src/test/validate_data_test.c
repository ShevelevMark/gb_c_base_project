#include <read.h>
#include <stdio.h>
#include <stdbool.h>

#define TEST(N, input, expected) \
{ int data[6]; \
 char const *str = input; \
 bool const expt = expected; \
 bool const actual = validate_data(str, data + 0, data + 1, data + 2, data + 3, data + 4, data + 5); \
 printf("TEST %2d: %s\n", N, expt == actual ? "OK" : "FAIL"); }

#define TEST_DATA(N, input, year, month, day, hour, minute, temperature) \
{ int data[6]; \
 char const *str = input; \
 bool const validate_res = validate_data(str, data + 0, data + 1, data + 2, data + 3, data + 4, data + 5); \
 bool const actual = validate_res && data[0] == year && data[1] == month && data[2] == day && data[3] == hour && data[4] == minute && data[5] == temperature; \
 printf("TEST %2d: %s\n", N, actual ? "OK" : "FAIL"); }

int validate_data_test(void) {
    TEST(1, "3001; 1; 2; 3; 4; 5", false)
    TEST(2, "1899; 1; 2; 3; 4; 5", false)
    TEST(3, "3000; 1; 2; 3; 4; 5", true)
    TEST(5, "1900; 1; 2; 3; 4; 5", true)
    TEST_DATA(6, "2999; 1; 2; 3; 4; 5", 2999, 1, 2, 3, 4, 5)
    TEST(7, "2999; 1; 2; 3; 4;-5", true)
    TEST_DATA(8, "2999; 1; 2; 3; 4;-5", 2999, 1, 2, 3, 4, -5)
    TEST(9, "2020;13;28; 1; 2;-99", false)
    TEST(10, "2020;12;28; 1; 2;-99", true)
    TEST_DATA(11, "2020;12;28; 1; 2;-99", 2020, 12, 28, 1, 2, -99)
    return 0;
}

int main() {
    validate_data_test();
    return 0;
}