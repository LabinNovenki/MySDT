#include "math_.h"


int is_int(char *str) {
    int ch = 0;
    if (str[0] == '0' && str[1] != '\0') {
        return 0;
    }
    while (str[ch] != '\0') {
        if (!isdigit(str[ch])) {
            return 0;
        }
        ch ++;
    }
    return 1;
}

int is_float(char *str){
    int ch = 0, count = 0;
    if (str[0] == 0 && isdigit(str[1])) {
        return 0;
    }
    if (str[0] == '.') {
        return 0;
    }
    while (str[ch] != '\0') {
        if (!isdigit(str[ch]) && str[ch] != '.') {
            return 0;
        }
        if (str[ch] == '.') {
            count ++;
        }
        ch ++;
    }
    if (count != 1) {
        return 0;
    }
    return 1;
}

int cal_2_int(int op1, int op2, char ch){
    switch (ch) {
        case '+': return op1 + op2;
        case '-': return op1 - op2;
        case '*': return op1 * op2;
        case '/': return op1 / op2;
        default: return 0;
    }
}

float cal_2_float(float op1, float op2, char ch){
    switch (ch) {
        case '+': return op1 + op2;
        case '-': return op1 - op2;
        case '*': return op1 * op2;
        case '/': return op1 / op2;
        default: return 0;
    }
}



