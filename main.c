
#include <stdio.h>
#include <stdlib.h>

// this can be optimized, but for now it does its job
int calcPower(int base, int exp) {
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

// this signature was defined and had to be used for this exercise
int convertBinaryToDecimal(int input[], int numberOfInputElements, int* result) {

    *result = 0;
    
    for (int i = 0; i < numberOfInputElements; i++) {
        int exp = numberOfInputElements - i - 1;
        *result += input[i] * calcPower(2, exp);
    }
        
    return 0;
}

// converts the input from the console to the defined interface
int stringToIntArr(char* string, int size, int** intArrayResult) {
    *intArrayResult = malloc(sizeof(int)*size);
    int i = 0;
    while (string[i] != 0) {
        if (string[i] == '0') {
            (*intArrayResult)[i] = 0;
        } else if (string[i] == '1') {
            (*intArrayResult)[i] = 1;
        } else {
            return -1;
        }        
        i++;
    }
    return i == size ? 0 : -1;
}

// needed as getline returns CR/NL
void remove_CR_NL(char** line, ssize_t * lineSize) {
    int i = 0;
    while ((*line)[i] != 0) {
        if ((*line)[i] == '\r' || (*line)[i] == '\n') {
            (*line)[i] = 0;
            (*lineSize)--;
        }
        i++;
    }
}

// reading a string from console in a safe way
ssize_t readInputFromConsole(char** line) {
    printf("Enter a binary value: ");
    *line = NULL;
    size_t len = 0;
    ssize_t lineSize = 0;
    lineSize = getline(line, &len, stdin);
    remove_CR_NL(line, &lineSize);
    return lineSize;
}

int main() {    
    ssize_t size;
    do {        
        char* string;
        size = readInputFromConsole(&string);
        if (size > 0) {
            int* binNum;
            int err = stringToIntArr(string, size, &binNum);
            if (err != 0) {
                printf("Invalid input.\n");
            } else {
                int decNum;
                err = convertBinaryToDecimal(binNum, size, &decNum);
                if (err != 0) {
                    printf("Conversion failed.\n");
                } else {
                    printf("Decimal value: %d\n", decNum);
                }
            }
            free(binNum);
        }
        free(string);
    } while (size > 0);

    return 0;
}


