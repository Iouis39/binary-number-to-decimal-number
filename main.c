//
//  main.c
//
//  Created by Louis Grünberg on 10.04.22.
//

#include <stdio.h>

// define binary number
int bin[4] = {1, 1, 1, 1};

// counts current index in the array
unsigned int binNum;

// counts length of array
unsigned int binL;

// decimal number
int decNum;

int getPow(int base, int exp) {
    if (exp < 0)
        return -1;
    
    int result = 1;
    while(exp) {
        if(exp & 1)
            result *= base;
        exp >>= 1;
        base *= base;
    }
    
    return result;
}

// calculates the length of the array
void getLength(void) {
    binNum = sizeof(bin) / 4 ;
    binL = sizeof(bin) / 4;
}

// converts binary to decimal
int binaryToNum(void) {
    getLength();
    
    for (int i = 0; i < binL; i++) {
        binNum--;
        decNum += bin[i] * getPow(2, binNum);
    }
    
    printf("%d\n", decNum);
    
    return decNum;
}

int main() {
    binaryToNum();
    return 0;
}
