//
//  main.c
//
//  Created by Louis Grünberg on 10.04.22.
//

#include <stdio.h>

int calcPower(int base, int exp) {
    if(exp < 0) {
      return -1;
    }
    int result = 1;
    while (exp--) {
      result *= base;
    }
    return result;
}

int convertBinaryToDecimal(int input[], int numberOfInputElements, int* result) {
    *result = 0;
    
    for (int i = 0; i < numberOfInputElements; i++) {
        int exp = numberOfInputElements - i - 1;
        *result += input[i] * calcPower(2, exp);
    }
    
    return 0;
}

void test1(void) {
    int binNum[] = {1, 1, 1, 1};
    int decNum;
    
    convertBinaryToDecimal(binNum, sizeof(binNum)/sizeof(binNum[0]), &decNum);
    
    printf("%d\n", decNum);
}

void test2(void) {
    int binNum[] = {0, 0, 0, 0, 1, 0};
    int decNum;

    convertBinaryToDecimal(binNum, sizeof(binNum)/sizeof(binNum[0]), &decNum);

    printf("%d\n", decNum);
}

void test3(void) {
    int binNum[] = {1, 1};
    int decNum;

    convertBinaryToDecimal(binNum, sizeof(binNum)/sizeof(binNum[0]), &decNum);

    printf("%d\n", decNum);
}

int main() {
    
    test1();
    test2();
    test3();

    return 0;
}
