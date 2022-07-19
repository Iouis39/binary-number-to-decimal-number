
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int convert(const char* input) {
    int result = 0;
    int i = 0;
    char c;
    // loop through chars in the input string
    while ((c=input[i++]) != 0) {
        // move existing bits 1 to left
        result <<= 1;
        if (c == '1') {
            // if the current char is "1" make the most right bit 1
            result |= 1;
        } else if (c != '0') {
            // otherwise it has to be a "0" or return error
            return -1;
        }
    }
    return result;
}

void test1() {
    char input[]= {"101\0"};
    int result = convert(input);
    assert(result == 5);
}

void test2() {
    char input[]= {"1\0"};
    int result = convert(input);
    assert(result == 1);
}

void test3() {
    char input[]= {"10\0"};
    int result = convert(input);
    assert(result == 2);
}

void test4() {
    char input[]= {"11\0"};
    int result = convert(input);
    assert(result == 3);
}

void test5() {
    char input[]= {"1010\0"};
    int result = convert(input);
    assert(result == 10);
}

void test6() {
    char input[]= {"1210\0"};
    int result = convert(input);
    assert(result == -1);
}

int main() {    

    test1();
    test2();
    test3();
    test4();
    test5();
    test6();

    return 0;
}


