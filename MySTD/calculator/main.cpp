#include "head.h"

//���屣���ֱ�
char* reserve[10];

int in_put(char *txt, char *input, char *&write) {
    //��ȫ����
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
	char *txt = nullptr; //���ڴ���������ı�
	txt = (char*)malloc(sizeof(char) * MAX);
	init_reserve(reserve);//��ʼ�������ֱ�
    STACK id_table;//������ű�
    char *write_filename;
    char input[CHAR_MAX * 2 + 1];
    char output[MAX];
    int count = in_put(txt, input, write_filename);//�����û�����
	//��ʼ�ʷ�����
	Token* tokens[MAX];//��һ�����鱣�����ɵĴʷ���Ԫ����ָ��
	int start = 0;//��ʼɨ����±�
	int tokens_cnt = -1;//tokens����±� 
	int line = 1;//�﷨��Ԫ���к� 
	while (start <= count) {
		Token* new_token;
		//���ôʷ������������ɴʷ���Ԫ 
		if ((new_token = Token_scan(&start, txt, count, &line, &tokens_cnt)) == nullptr)
			break;
		//�ʷ��������󱨸� 
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



