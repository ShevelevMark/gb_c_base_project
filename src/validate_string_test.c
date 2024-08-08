#include <read.h>
#include <stdbool.h>
#include <stdio.h>

int main() {
    // TEST 1
    {
        char const *str = "";
        bool const expected = false;
        bool const actual = validate_string(str);
        printf("TEST 01 {input:%s|%s}\n", str, actual == expected ? "OK" : "FAIL");  
    }

    // TEST 2
    {
        char const *str = "2020; 1; 2; 3;21;-32";
        bool const expected = true;
        bool const actual = validate_string(str);
        printf("TEST 02 {input:%s|%s}\n", str, actual == expected ? "OK" : "FAIL"); 
    }

    // TEST 3
    {
        char const *str = "2020; 1; 2; 3;21;-32;";
        bool const expected = false;
        bool const actual = validate_string(str);
        printf("TEST 03 {input:%s|%s}\n", str, actual == expected ? "OK" : "FAIL");
    }

    // TEST 4
    {
        char const *str = "2020; 1; 2; 3;21;32";
        bool const expected = true;
        bool const actual = validate_string(str);
        printf("TEST 04 {input:%s|%s}\n", str, actual == expected ? "OK" : "FAIL");
    }

    // TEST 5
    {
        char const *str = "2020; 1; 2; 3;21; -32";
        bool const expected = false;
        bool const actual = validate_string(str);
        printf("TEST 05 {input:%s|%s}\n", str, actual == expected ? "OK" : "FAIL");
    }

    // TEST 6
    {
        char const *str = "2020;1; 2; 3;21;32";
        bool const expected = false;
        bool const actual = validate_string(str);
        printf("TEST 06 {input:%s|%s}\n", str, actual == expected ? "OK" : "FAIL");
    }

    // TEST 7
    {
        char const *str = "2020;01; 2; 3;21;32";
        bool const expected = true;
        bool const actual = validate_string(str);
        printf("TEST 07 {input:%s|%s}\n", str, actual == expected ? "OK" : "FAIL");
    }

    // TEST 8
    {
        char const *str = "12020;01; 2; 3;21;32";
        bool const expected = false;
        bool const actual = validate_string(str);
        printf("TEST 08 {input:%s|%s}\n", str, actual == expected ? "OK" : "FAIL");
    }

    // TEST 9
    {
        char const *str = "220;01; 2; 3;21;32";
        bool const expected = false;
        bool const actual = validate_string(str);
        printf("TEST 09 {input:%s|%s}\n", str, actual == expected ? "OK" : "FAIL");
    }

    // TEST 10
    {
        char const *str = "2021;01;16;01;05;-xx";
        bool const expected = false;
        bool const actual = validate_string(str);
        printf("TEST 10 {input:%s|%s}\n", str, actual == expected ? "OK" : "FAIL");
    }

    // TEST 11
    {
        char const *str = "2021;;16;01;05;10";
        bool const expected = false;
        bool const actual = validate_string(str);
        printf("TEST 11 {input:%s|%s}\n", str, actual == expected ? "OK" : "FAIL");
    }

    // TEST 12
    {
        char const *str = "2021;16;01;05;10";
        bool const expected = false;
        bool const actual = validate_string(str);
        printf("TEST 12 {input:%s|%s}\n", str, actual == expected ? "OK" : "FAIL");
    }

    // TEST 13
    {
        char const *str = "2021;02;16;01;;05;10";
        bool const expected = false;
        bool const actual = validate_string(str);
        printf("TEST 13 {input:%s|%s}\n", str, actual == expected ? "OK" : "FAIL");
    }

    // TEST 14
    {
        char const *str = "2021;0x;16;01;;05;10";
        bool const expected = false;
        bool const actual = validate_string(str);
        printf("TEST 14 {input:%s|%s}\n", str, actual == expected ? "OK" : "FAIL");
    }
     

    return 0;
}