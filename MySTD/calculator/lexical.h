//
// Created by ASUS on 2021/3/26.
//

#ifndef CALCULATOR_LEXICAL_H
#define CALCULATOR_LEXICAL_H
#include "strt.h"
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <cstdio>
//声明保留字表
extern char* reserve[10];
//初始化保留字表

int init_reserve(char **reserve);
Token* Token_scan(int* start, char *txt, int len, int* line, int* tokens_cnt);
int print_tokens(Token **tokens, int count);
#endif //CALCULATOR_LEXICAL_H
