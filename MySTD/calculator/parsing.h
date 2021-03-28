//
// Created by ASUS on 2021/3/26.
//

#ifndef CALCULATOR_PARSING_H
#define CALCULATOR_PARSING_H
#include "strt.h"
#include <cstdio>
#include "stack.h"
#include "math_.h"
#include <cstdlib>
#include "id_table.h"
#include "err_deal.h"

Token *stmt(STACK* id_table, int &index, Token **tokens, int lenth, char *output);
int F(int &index, Token **tokens, int lenth);
Item *reverse_polish(STACK* id_table, int start_term, int end, Token **tokens);
int term(int &index, Token **tokens, int lenth);
int R(int &index, Token **tokens, int lenth);
int type(int lookahead, Token **tokens);

#endif //CALCULATOR_PARSING_H
