#ifndef _STRT_H
#define _STRT_H

#define MAX 1000
#define RESERVE 3 //�����ָ���
#define CHAR_LEN 20

enum Terminal{
    INT, FLOAT, WRITE, ID, RELOP, NUMBER,
    OP_PLUS, OP_SUB, OP_MUL, OP_DIV, OP_ASSIGN,
    LEFT_PAREN, RIGHT_PAREN, SEMI
};
enum Nonterminal{
    TYPE, TERM, STMT
};

enum Err_num{
    ERR_UNDETECTED_SYM = -1,
    ERR_INPUT_OUTLENTH = -2,
    ERR_NUM_OUTLENTH = -3,
    ERR_ID_REDEFINITION = -4,
    ERR_MISSING_SEMI = -5,
    ERR_ILLEGAL_ID = -6,
    ERR_ID_UNDEFINITON = -7,
    ERR_WRITE_FORMAT = -8,
    ERR_STATEMENT = -9,
    ERR_DIFFERENT_TYPE = -10,
    ERR_MISSING_RIGHTPAREN = -11
};

//���ű����
typedef struct ITEM{
    char *name;
    int type;
    int i;
    float f;
}Item;

//�ʷ���Ԫ����
typedef struct Attribute{
	char *name;//���ʷ���ԪΪ��ʶ��ʱ��nameΪָ���ʶ�������ַ�����ָ�룻���ʷ���ԪΪ���Ż����֣�name = NULL
	int line;//�ʷ���Ԫ���к�
}Atrbt;

//�ʷ���Ԫ��ʵ�� 
typedef struct TOKEN{
	int Ter;
	char* Ter_char;
	Atrbt* attribute;
}Token;

#endif
