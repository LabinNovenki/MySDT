//
// Created by ASUS on 2021/3/26.
//

#ifndef CALCULATOR_ID_TABLE_H
#define CALCULATOR_ID_TABLE_H
#include "stack.h"
#include "strt.h"
#include <cstring>
#include <cstdlib>
#include "stack.h"

int add_id_table(STACK *id_table, char *name, int type, int i, float f);
int is_rep(STACK* id_table, char* name);
int is_exist(STACK *id_table, char* name);
int update_id(STACK *id_table, int index, int type, int i, float f);

#endif //CALCULATOR_ID_TABLE_H
