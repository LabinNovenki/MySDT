#include "lexical.h"

int init_reserve(char ** reserve){
    reserve[0] = "int";
    reserve[1] = "float";
    reserve[2] = "write";
}

Token* Token_scan(int* start, char *txt, int len, int* line, int* tokens_cnt){
    /*
    start:开始扫描的下标
    txt:代扫描的文本
    line:返回词法单元的行号
    count:返回词法单元的逻辑标号
    tokens_cnt:记录词法单元个数
    return 扫描出的词法单元
    */
    char ch;
    while (*start < len && txt[*start] != '#') {
        ch = txt[*start];
        //检测到空白字符
        if (ch == ' ' || ch == '\t') {
            (*start) ++;
            continue;
        }
        else if (ch == '\n') {
            (*start) ++;
            (*line) ++;
            continue;
        }
            //检测到字母
        else if ( isalpha(ch) ) {
            Token* new_token = (Token*)malloc(sizeof(Token));
            new_token->attribute = (Atrbt*)malloc(sizeof(Atrbt));
            char *str = (char*)malloc(sizeof(char) * CHAR_LEN);
            int count = 0;
            //开始读入字符
            while ( txt[*start] != ' ' && txt[*start] != '\t'
                    && txt[*start] != '\n' && txt[*start] != ';'
                    && isalnum(txt[*start]) && *start < len) {
//				printf("ch = %c\n", txt[*start]);
                str[count] = txt[*start];
                (*start) ++;
                count ++;
                //若识别长度过长
                if (count >= CHAR_LEN) {
                    str[count] = '\0';
                    new_token->Ter_char = str;
                    new_token->attribute->line = (*line);
                    new_token->Ter = ERR_INPUT_OUTLENTH;
                    return new_token;
                }
            }
            if (txt[*start] == '\n')
                (*line) ++ ;
            str[count] = '\0';
            //构建词法单元
            new_token->Ter_char = str;
            new_token->attribute->line = (*line);
            int is_reserve = 0;
            for (int i  = 0; i < RESERVE; i ++) {
                //如果是保留字
//				printf("\nstr = %s, reserve[%d] = %s\n", str, i, reserve[i]);
                if (strcmp(str, reserve[i]) == 0) {
                    new_token->attribute->name = NULL;
                    new_token->Ter = i;
                    is_reserve = 1;
                    break;
                }
            }
            //如果是标识符
            if (is_reserve == 0) {
                new_token->attribute->name = str;
                new_token->Ter = ID;
            }

            (*tokens_cnt) ++;
            return new_token;
        }
            //检测到数字
        else if (isdigit(ch)) {
            Token* new_token = (Token*)malloc(sizeof(Token));
            new_token->attribute = (Atrbt*)malloc(sizeof(Atrbt));
            char *str = (char*)malloc(sizeof(char) * CHAR_LEN);
            int count = 0;
            while ( txt[*start] != ' ' && txt[*start] != '\t'
                    && txt[*start] != '\n' && txt[*start] != ';'
                    && (isdigit(txt[*start]) || txt[*start] == '.') && *start < len) {
//				printf("ch = %c\n", txt[*start]);
                str[count] = txt[*start];
                (*start) ++;
                count ++;
                //数字长度过长，无法读取
                if (count >= CHAR_LEN) {
                    str[count] = '\0';
                    new_token->Ter_char = str;
                    new_token->attribute->line = (*line);
                    new_token->Ter = ERR_NUM_OUTLENTH;
                    return new_token;
                }
            }
            if (txt[*start] == '\n')
                (*line) ++ ;
            str[count] = '\0';
            //构建词法单元
            new_token->Ter_char = str;
            new_token->Ter = NUMBER;
            new_token->attribute->line = (*line);
            new_token->attribute->name = nullptr;
            (*tokens_cnt) ++;

            return new_token;

        }
            //检测到符号
        else if (ch >= '(' && ch <= '/' || ch == ';' || ch == '=') {
            Token* new_token = (Token*)malloc(sizeof(Token));
            new_token->attribute = (Atrbt*)malloc(sizeof(Atrbt));
            char *str = (char*)malloc(sizeof(char) * 2);
            str[0] = ch;
            str[1] = '\0';
            new_token->Ter_char = str;
            new_token->attribute->line = (*line);
            new_token->attribute->name = nullptr;
            switch(ch){
                case '(':
                    new_token->Ter = LEFT_PAREN;
                    break;
                case ')':
                    new_token->Ter = RIGHT_PAREN;
                    break;
                case '+':
                    new_token->Ter = OP_PLUS;
                    break;
                case '-':
                    new_token->Ter = OP_SUB;
                    break;
                case '*':
                    new_token->Ter = OP_MUL;
                    break;
                case '/':
                    new_token->Ter = OP_DIV;
                    break;
                case '=':
                    new_token->Ter = OP_ASSIGN;
                    break;
                case ';':
                    new_token->Ter = SEMI;
                default:
                    break;

            }
            (*start) ++;
            (*tokens_cnt) ++;
            return new_token;
        }
            //检测到未知字符
        else {
            Token* new_token = (Token*)malloc(sizeof(Token));
            new_token->attribute = (Atrbt*)malloc(sizeof(Atrbt));
            new_token->Ter_char = &ch;
            new_token->attribute->name = NULL;
            new_token->attribute->line = (*line);
            new_token->Ter = ERR_UNDETECTED_SYM;
            return new_token;
        }
        (*start) ++;
    }
    return nullptr;
}

int print_tokens(Token **tokens, int count){
    //for debugging
    printf("\ntokens:\n");
    for (int i = 0; i <= count; i ++) {
        printf("<%d, %s, %s, %d>\n", tokens[i]->Ter, tokens[i]->Ter_char,
               tokens[i]->attribute->name, tokens[i]->attribute->line);
    }
}