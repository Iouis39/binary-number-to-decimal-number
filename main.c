//
//  main.c
//
//  Created by Louis Grünberg on 10.04.22.
//

#include <stdio.h>
#include <assert.h>

int getPow(int base, int exp) {
    if (exp < 0) {
        return -1;
    }
    
    int result = 1;
    while(exp) {
        if(exp & 1) {
            result *= base;
        }
        exp >>= 1;
        base *= base;
    }
    
    return result;
}


// you don't need a comment if the method is well named
// also make it a real function:
//     with input parameter - we need the actual binary array and the number of elements as you cannot calc that at runtime
//     and a result as the functions return value
int convertBinaryToDecimal(int input[], int numberOfInputElements) {

    int result = 0;
    
    for (int i = 0; i < numberOfInputElements; i++) {
        int exp = numberOfInputElements - i - 1;
        result += input[i] * getPow(2, exp);
    }
        
    return result;
}


void test15() {
    int binNum[] = {1, 1, 1, 1};
    
    int decNum = convertBinaryToDecimal(binNum, sizeof(binNum)/sizeof(binNum[0]));

    assert(decNum == 15);
}

void test1() {
    int binNum[] = {0, 0, 0, 1};
    
    int decNum = convertBinaryToDecimal(binNum, sizeof(binNum)/sizeof(binNum[0]));

    assert(decNum == 1);
}

void test2() {
    int binNum[] = {0, 0, 0, 0, 1, 0};
    
    int decNum = convertBinaryToDecimal(binNum, sizeof(binNum)/sizeof(binNum[0]));

    assert(decNum == 2);
}

void test3() {
    int binNum[] = {1, 1};
    
    int decNum = convertBinaryToDecimal(binNum, sizeof(binNum)/sizeof(binNum[0]));

    assert(decNum == 3);
}

int main() {
    
    test1();
    test1();
    test2();
    test3();

    return 0;
}

