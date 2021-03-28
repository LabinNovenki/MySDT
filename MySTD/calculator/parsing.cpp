#include "parsing.h"

int type(int lookahead, Token **tokens){
    if (tokens[lookahead]->Ter == INT) {
        return INT;
    }
    else if (tokens[lookahead]->Ter == FLOAT) {
        return FLOAT;
    }

    return -1;
}

int R(int &index, Token **tokens, int lenth){
    //消除非终结符号term左递归的辅助函数
//	printf("R():index = %d\n", index);
    if (index > lenth || tokens[index]->Ter == SEMI || tokens[index]->Ter == RIGHT_PAREN) {
        return 1;
    }

    if (tokens[index]->Ter == OP_MUL || tokens[index]->Ter == OP_DIV
        || tokens[index]->Ter == OP_PLUS || tokens[index]->Ter == OP_SUB) {
        index ++;
//		printf("index = %d, lenth = %d\n", index, lenth);
        if (index <= lenth && F(index, tokens, lenth) >= 0) {
            if ( R(index, tokens, lenth) >= 0) {
//				printf("R = %d\n", 1);
                return index;
            }
        }
    }
//    printf("R = %d\n", -1);
    return -1;
}

int F(int &index, Token **tokens, int lenth) {
    if (index <= lenth && tokens[index]->Ter == NUMBER || tokens[index]->Ter == ID) {
        index ++;
        return 1;
    }
    else if (index <= lenth && tokens[index]->Ter == LEFT_PAREN) {
        index ++;
        if (F(index, tokens, lenth) >= 0) {
            if (R(index, tokens, lenth) >= 0) {
                if (index <= lenth && tokens[index]->Ter == RIGHT_PAREN) {
                    index ++;
                    return 1;
                }
                else {
                    //缺右括号
                    return -1;
                }
            }
        }
    }
    //语句非法
    return -1;
}

int term(int &index, Token **tokens, int lenth){
//	printf("term():scanning = %s, index = %d\n", tokens[index]->Ter_char, index);
    if (index > lenth || tokens[index]->Ter == SEMI) {
        return -1;
    }
    if (F(index, tokens, lenth)) {
        if( R(index, tokens, lenth) >= 0) {
            return index;
        }
    }
    //表达式非法
    return -1;
}

Item* reverse_polish(STACK *id_table, int start_term, int end, Token **tokens) {
//    printf("resvese_polish():\n");
    STACK st1, st2;
    int index = start_term;
    while (index < end) {
//        printf("\nscanning: %s:\n", tokens[index]->Ter_char);
        //扫描到数字或标识符
        if (tokens[index]->Ter == NUMBER) {
            if (is_int(tokens[index]->Ter_char)) {
                int num = atoi(tokens[index]->Ter_char);
                Item *pit = (Item*)malloc(sizeof (Item));
                pit->type = INT;
                pit->i = num;
                push(&st2, (void *) pit);
            } else if (is_float(tokens[index]->Ter_char)) {
                float num = atof(tokens[index]->Ter_char);
                Item *pit = (Item*)malloc(sizeof (Item));
                pit->type = FLOAT;
                pit->f = num;
                push(&st2, (void *) pit);
            }
        }
        if (tokens[index]->Ter == ID) {
            int i;
            if ((i = is_exist(id_table, tokens[index]->Ter_char)) == -1) {
                //未定义的变量
                err_deal(ERR_ID_UNDEFINITON, tokens[index]);
            }
            if ((((Item *) id_table->st[i])->type) == INT) {
                int num = ((Item *) id_table->st[i])->i;
                Item *pit = (Item*)malloc(sizeof (Item));
                pit->type = INT;
                pit->i = num;
                push(&st2, (void *) pit);
            } else if ((((Item *) id_table->st[i])->type) == FLOAT) {
                float num = ((Item *) id_table->st[i])->f;
                Item *pit = (Item*)malloc(sizeof (Item));
                pit->type = FLOAT;
                pit->f = num;
                push(&st2, (void *) pit);
            } else {
                //未识别的变量类型
                printf("\nSegment fault.\n");
                system("PAUSE");
                exit(1);
            }
        }
        //扫描到'*'或'/'
        if (tokens[index]->Ter == OP_MUL || tokens[index]->Ter == OP_DIV) {
            //出栈栈顶元素直到栈空或栈顶元素为‘+’或‘-’或栈顶为左括号
            while ( st1.top > -1 && *((char *) st1.st[st1.top]) != '('
                   && *((char *) st1.st[st1.top]) != '+' && *((char *) st1.st[st1.top]) != '-') {
                void *pchar = pop(&st1);
                void *op2 = pop(&st2);
                void *op1 = pop(&st2);
                if (((Item *) op2)->type == ((Item *) op1)->type) {
                    if (((Item *) op2)->type == INT) {
                        int num = cal_2_int(((Item *) op1)->i, ((Item *) op2)->i, *(char *) pchar);
                        Item *pit = (Item*)malloc(sizeof (Item));
                        pit->type = INT;
                        pit->i = num;
                        push(&st2, (void *) pit);
                    } else if (((Item *) op2)->type == FLOAT) {
                        float num = cal_2_float(((Item *) op1)->f, ((Item *) op2)->f, *(char *) pchar);
                        Item *pit = (Item*)malloc(sizeof (Item));
                        pit->type = FLOAT;
                        pit->f = num;
                        push(&st2, (void *) pit);
                    }
                } else if (((Item *) op2)->type == INT && ((Item *) op1)->type == FLOAT){
                    //操作数类型不匹配
                    float num = cal_2_float(((Item *) op1)->f, ((float)((Item *) op2)->i), *(char *) pchar);
                    Item *pit = (Item*)malloc(sizeof (Item));
                    pit->type = FLOAT;
                    pit->f = num;
                    push(&st2, (void *) pit);
                }
                else if (((Item *) op2)->type == FLOAT && ((Item *) op1)->type == INT){
                    float num = cal_2_float((float)(((Item *) op1)->i), ((Item *) op2)->f, *(char *) pchar);
                    Item *pit = (Item*)malloc(sizeof (Item));
                    pit->type = FLOAT;
                    pit->f = num;
                    push(&st2, (void *) pit);
                }
            }
            push(&st1, (void*)tokens[index]->Ter_char);
        }
        //扫描到'+'或'-'
        if (tokens[index]->Ter == OP_SUB || tokens[index]->Ter == OP_PLUS) {
            //出栈直到栈空或遇到左括号
            while (st1.top > -1 && *((char *) st1.st[st1.top]) != '(' ) {
                void *pchar = pop(&st1);
                void *op2 = pop(&st2);
                void *op1 = pop(&st2);
//                printf("\ntype1:%d, type2:%d\n", ((Item *) op2)->type, ((Item *) op1)->type);
                if (((Item *) op2)->type == ((Item *) op1)->type) {
                    if (((Item *) op2)->type == INT) {
                        int num = cal_2_int(((Item *) op1)->i, ((Item *) op2)->i, *(char *) pchar);
                        Item *pit = (Item*)malloc(sizeof (Item));
                        pit->type = INT;
                        pit->i = num;
                        push(&st2, (void *) pit);
                    } else if (((Item *) op2)->type == FLOAT) {
                        float num = cal_2_float(((Item *) op1)->f, ((Item *) op2)->f, *(char *) pchar);
                        Item *pit = (Item*)malloc(sizeof (Item));
                        pit->type = FLOAT;
                        pit->f = num;
                        push(&st2, (void *) pit);
                    }
                } else if (((Item *) op2)->type == INT && ((Item *) op1)->type == FLOAT){
                    //操作数类型不匹配
                    float num = cal_2_float(((Item *) op1)->f, ((float)((Item *) op2)->i), *(char *) pchar);
                    Item *pit = (Item*)malloc(sizeof (Item));
                    pit->type = FLOAT;
                    pit->f = num;
                    push(&st2, (void *) pit);
                }
                else if (((Item *) op2)->type == FLOAT && ((Item *) op1)->type == INT){
                    float num = cal_2_float((float)(((Item *) op1)->i), ((Item *) op2)->f, *(char *) pchar);
                    Item *pit = (Item*)malloc(sizeof (Item));
                    pit->type = FLOAT;
                    pit->f = num;
                    push(&st2, (void *) pit);
                }
            }
            push(&st1, (void*)tokens[index]->Ter_char);
        }
        //扫描到'('
        if (tokens[index]->Ter == LEFT_PAREN) {
            push(&st1, (void*)tokens[index]->Ter_char);
        }
        //扫描到')'
        if (tokens[index]->Ter == RIGHT_PAREN) {
            while (st1.top > -1 && *((char *) st1.st[st1.top]) != '(' ) {
                void *pchar = pop(&st1);
                void *op2 = pop(&st2);
                void *op1 = pop(&st2);
//                printf("\ntype1:%d, type2:%d\n", ((Item *) op2)->type, ((Item *) op1)->type);
                if (((Item *) op2)->type == ((Item *) op1)->type) {
                    if (((Item *) op2)->type == INT) {
                        int num = cal_2_int(((Item *) op1)->i, ((Item *) op2)->i, *(char *) pchar);
                        Item *pit = (Item*)malloc(sizeof (Item));
                        pit->type = INT;
                        pit->i = num;
                        push(&st2, (void *) pit);
                    } else if (((Item *) op2)->type == FLOAT) {
                        float num = cal_2_float(((Item *) op1)->f, ((Item *) op2)->f, *(char *) pchar);
                        Item *pit = (Item*)malloc(sizeof (Item));
                        pit->type = FLOAT;
                        pit->f = num;
                        push(&st2, (void *) pit);
                    }
                } else if (((Item *) op2)->type == INT && ((Item *) op1)->type == FLOAT){
                    //操作数类型不匹配
                    float num = cal_2_float(((Item *) op1)->f, ((float)((Item *) op2)->i), *(char *) pchar);
                    Item *pit = (Item*)malloc(sizeof (Item));
                    pit->type = FLOAT;
                    pit->f = num;
                    push(&st2, (void *) pit);
                }
                else if (((Item *) op2)->type == FLOAT && ((Item *) op1)->type == INT){
                    float num = cal_2_float((float)(((Item *) op1)->i), ((Item *) op2)->f, *(char *) pchar);
                    Item *pit = (Item*)malloc(sizeof (Item));
                    pit->type = FLOAT;
                    pit->f = num;
                    push(&st2, (void *) pit);
                }
            }
            if (st1.top <= -1) {
                printf("Segment Fault..\n");
                exit(1);
            }
            else {
                pop(&st1);
            }
        }
        index++;
    }
    if (st1.top != -1) {
//        printf("\nstill not empty:");
        //如果扫描完后符号栈依然不为空
        while (st1.top != -1) {
            void *pchar = pop(&st1);
//            printf("\npop:%s", (char*)pchar);
            void *op2 = pop(&st2);
            void *op1 = pop(&st2);
//            printf("\ntype1:%d, type2:%d\n", ((Item *) op2)->type, ((Item *) op1)->type);
            if (((Item *) op2)->type == ((Item *) op1)->type) {
                if (((Item *) op2)->type == INT) {
//                    printf("op1:%d, op2:%d\n", ((Item *) op1)->i, ((Item *) op2)->i);
                    int num = cal_2_int(((Item *) op1)->i, ((Item *) op2)->i, *(char *) pchar);
                    Item *pit = (Item*)malloc(sizeof (Item));
                    pit->type = INT;
                    pit->i = num;
                    push(&st2, (void *) pit);
                } else if (((Item *) op2)->type == FLOAT) {
                    float num = cal_2_float(((Item *) op1)->f, ((Item *) op2)->f, *(char *) pchar);
                    Item *pit = (Item*)malloc(sizeof (Item));
                    pit->type = FLOAT;
                    pit->f = num;
                    push(&st2, (void *) pit);
                }
            } else if (((Item *) op2)->type == INT && ((Item *) op1)->type == FLOAT){
                //操作数类型不匹配
                float num = cal_2_float(((Item *) op1)->f, ((float)((Item *) op2)->i), *(char *) pchar);
                Item *pit = (Item*)malloc(sizeof (Item));
                pit->type = FLOAT;
                pit->f = num;
                push(&st2, (void *) pit);
            }
            else if (((Item *) op2)->type == FLOAT && ((Item *) op1)->type == INT){
                float num = cal_2_float((float)(((Item *) op1)->i), ((Item *) op2)->f, *(char *) pchar);
                Item *pit = (Item*)malloc(sizeof (Item));
                pit->type = FLOAT;
                pit->f = num;
                push(&st2, (void *) pit);
            }
        }
    }
    void *res = st2.st[st2.top];
    return (Item*)res;
}

Token * stmt(STACK *id_table, int &index, Token **tokens, int lenth, char *output){
    if (index > lenth) {
        return nullptr;
    }
    //定义变量的语句
    if  ((type(index, tokens) ) >= 0) {
        int type = index;
        index ++;
        if (index <= lenth && tokens[index]->Ter == ID) {
            int id = index;
            index ++;
            if (index <= lenth && tokens[index]->Ter == SEMI) {
                index ++;
                //检测变量是否已存在
                if (is_rep(id_table, tokens[id]->Ter_char)) {
                    tokens[id]->Ter = ERR_ID_REDEFINITION;
                    return tokens[id];
                }
                //变量定义语句合法
                add_id_table(id_table, tokens[id]->Ter_char, tokens[type]->Ter, 0, 0);
                return tokens[index - 1];
            }
            else {
                //缺分号
                tokens[index - 1]->Ter = ERR_MISSING_SEMI;
                return tokens[index - 1];
            }
        }
        else {
            //第二个词法单元不是标识符
            segment_error(index, lenth);
            tokens[index - 1]->Ter = ERR_ILLEGAL_ID;
            return tokens[index - 1];
        }
    }

    //write语句
    if (tokens[index]->Ter == WRITE) {
        index ++;
        if (index <= lenth && tokens[index]->Ter == LEFT_PAREN) {
            index ++;
            if (index <= lenth && tokens[index]->Ter == ID) {
                int id = index;
                int a;
                if ( (a = is_exist(id_table, tokens[id]->Ter_char) ) < 0) {
                    //变量未定义
                    tokens[id]->Ter = ERR_ID_UNDEFINITON;
                    return tokens[id];
                }
                index ++;
                if (index <= lenth && tokens[index]->Ter == RIGHT_PAREN) {
                    index ++;
                    if (index <= lenth && tokens[index]->Ter == SEMI) {
                        if (((Item*)id_table->st[a])->type == FLOAT) {
                            sprintf(output, "\n%s = %f\n", ((Item*)id_table->st[a])->name,
                                    ((Item*)id_table->st[a])->f);
                        }
                        else {
                            sprintf(output, "\n%s = %d\n", ((Item*)id_table->st[a])->name,
                                    ((Item*)id_table->st[a])->i);
                        }
                        index ++;
                        return tokens[index - 1];
                    }
                }
                else {
                    //write缺少右括号
                    segment_error(index, lenth);
                    tokens[index]->Ter = ERR_WRITE_FORMAT;
                    return tokens[index];
                }
            }
            else {
                //write左括号后不是标识符
                segment_error(index, lenth);
                tokens[index]->Ter = ERR_WRITE_FORMAT;
                return tokens[index];
            }
        }
        else {
            //write后面缺左括号
            segment_error(index, lenth);
            tokens[index]->Ter = ERR_WRITE_FORMAT;
            return tokens[index];
        }
    }

    //赋值语句
    if (tokens[index]->Ter == ID) {
        int id = index;
        int table_index = is_exist(id_table, tokens[index]->Ter_char);
        if (table_index < 0) {
            //变量未定义
            tokens[id]->Ter = ERR_ID_UNDEFINITON;
            return tokens[id];
        }
        index ++;
        if (tokens[index]->Ter == OP_ASSIGN) {
            index ++;
            int term_start = index;
            if (term(index, tokens, lenth) >= 0) {
                Item *res = reverse_polish(id_table, term_start, index, tokens);
//                printf("\n%d %f\n", res->i, res->f);
                if (((Item*)id_table->st[table_index])->type == INT && res->type == FLOAT) {
                    err_deal(ERR_DIFFERENT_TYPE, tokens[id]);
                }
                else if (((Item*)id_table->st[table_index])->type == FLOAT && res->type == INT) {
                    update_id(id_table, table_index, FLOAT, res->i, (float)(res->i));
                }
                else {
                    update_id(id_table, table_index, res->type, res->i, res->f);
                }
                if (tokens[index]->Ter == SEMI) {
                    index ++;
                    return tokens[index - 1];
                }
                else {
                    //缺分号
                    tokens[index - 1]->Ter = ERR_MISSING_SEMI;
                    return tokens[index - 1];
                }
            }
        }
        else {
            //缺赋值符号
            segment_error(index, lenth);
            tokens[index]->Ter = ERR_STATEMENT;
            return tokens[index];
        }
    }
    segment_error(index, lenth);
    tokens[index]->Ter = ERR_STATEMENT;
    return tokens[index];
}

