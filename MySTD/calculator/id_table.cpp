#include "id_table.h"


//生成符号表项
int add_id_table(STACK* id_table, char *name, int type, int i, float f){
    Item* pitem = (Item*)malloc(sizeof(Item));
    pitem->name = name;
    pitem->type = type;
    pitem->i = i;
    pitem->f = f;
    push(id_table, (void*)pitem);
}

//检测符号表有无重复
int is_rep(STACK* id_table, char* name){
    for (int i = 0; i <= id_table->top; i ++) {
        if (strcmp(name, ((Item*)id_table->st[i])->name) == 0) {
            return 1;
        }
    }
    return 0;
}

//检测某变量是否在符号表内，若存在返回下标,否则返回-1
int is_exist(STACK *id_table, char* name){
    for (int i = 0; i <= id_table->top; i ++) {
        if (strcmp(name, ((Item*)id_table->st[i])->name) == 0) {
            return i;
        }
    }
    return -1;
}

//更新符号表
int update_id(STACK *id_table, int index, int type, int i, float f){
    if ((((Item*)id_table->st[index])->type) == INT) {
        ((Item*)id_table->st[index])->i = i;
    }
    else if ((((Item*)id_table->st[index])->type) == FLOAT) {
        ((Item*)id_table->st[index])->f = f;
    }
    else {
        //无法识别的变量类型
        return -1;
    }
}



