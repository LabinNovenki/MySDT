//
// Created by ASUS on 2021/3/26.
//
#ifndef CALCULATOR_MATH__H
#define CALCULATOR_MATH__H
#include <cstdio>
#include <cctype>
int is_int(char *str);
int is_float(char *str);
int cal_2_int(int op1, int op2, char ch);
float cal_2_float(float op1, float op2, char ch);
#endif //CALCULATOR_MATH__H
