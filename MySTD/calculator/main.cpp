#include "head.h"

//定义保留字表
char* reserve[10];

int in_put(char *txt, char *input, char *&write) {
    //安全输入
    char *read_filename;
    FILE *fp1;
    fgets(input, CHAR_MAX * 2 + 1, stdin);
    read_filename = strtok(input, " ");
    write = strtok(nullptr, "\n");
    if ( (fp1 = fopen(read_filename, "r")) == nullptr) {
        printf("ERROR:\nfail to open the file \"%s\".", read_filename);
        return 1;
    }
    char ch;
    int count = 0;
    while ((ch = fgetc(fp1)) != '#' && !feof(fp1)) {
        txt[count] = ch;
        count ++;
    }
    txt[count] = '\0';
    fclose(fp1);
    return count;
}

int out_put(char *output, char *filename){
    char input[CHAR_MAX];
    FILE*fp;
    fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("fail to open file \"%s\"\n", filename);
    }
    fprintf(fp, "%s", output);
    fclose(fp);
    return 0;
}

int main(){
	char *txt = nullptr; //用于储存输入的文本
	txt = (char*)malloc(sizeof(char) * MAX);
	init_reserve(reserve);//初始化保留字表
    STACK id_table;//定义符号表
    char *write_filename;
    char input[CHAR_MAX * 2 + 1];
    char output[MAX];
    int count = in_put(txt, input, write_filename);//调用用户输入
	//开始词法分析
	Token* tokens[MAX];//用一个数组保存生成的词法单元序列指针
	int start = 0;//开始扫描的下标
	int tokens_cnt = -1;//tokens最大下标 
	int line = 1;//语法单元的行号 
	while (start <= count) {
		Token* new_token;
		//调用词法分析函数生成词法单元 
		if ((new_token = Token_scan(&start, txt, count, &line, &tokens_cnt)) == nullptr)
			break;
		//词法分析错误报告 
		if (new_token->Ter < 0) {
		    err_deal(new_token->Ter, new_token);
			system("PAUSE");
			return 1;
		}
		tokens[tokens_cnt] = new_token;
//		printf("\nnew = %d, %s\n", new_token->Ter, new_token->Ter_char);
	}
	
//	printf("start = %d\ntokens_cnt:%d\nline:%d\n",start, tokens_cnt, line);
//    print_tokens(tokens, tokens_cnt);
//    printf("\nlenth = %d\n", tokens_cnt);
    int index = 0;
    while(index <= tokens_cnt) {
        Token *new_token;
        new_token = stmt(&id_table, index, tokens, tokens_cnt, output);
        if (new_token == nullptr) {
            break;
        }
        if (new_token->Ter < 0) {
            err_deal(new_token->Ter, new_token);
        }
    }
//  printf("term = %d\n", term(index, tokens, tokens_cnt));
//  printf("stmt = %d\n", stmt(&id_table, index, tokens, tokens_cnt));
//	int res = reverse_polish(index, tokens_cnt, tokens);
//	printf("\nres = %d\n", res);

    out_put(output, write_filename);
    printf("\ncompile successfully.");
    system("PAUSE");
	return 0;
}



