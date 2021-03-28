#include "err_deal.h"

int segment_error(int index, int lenth) {
    if (index > lenth) {
        printf("\nERROR:Segment error.\n");
        system("PAUSE");
        exit(1);
    }
    return 0;
}

int err_deal(int err, Token* token){
    printf("\n******___ERROR___******\n");
    switch (err) {
        case ERR_UNDETECTED_SYM:
            printf("\nline:%d\nCan't recognize symbol '%s'.\n",token->attribute->line, token->Ter_char);
            system("PAUSE");
            exit(1);
            break;
        case ERR_NUM_OUTLENTH:
            printf("\nline:%d\nToo long for number '%s'.\n",token->attribute->line, token->Ter_char);
            system("PAUSE");
            exit(1);
            break;
        case ERR_INPUT_OUTLENTH:
            printf("\nline:%d\nToo long for symbol '%s'.\n",token->attribute->line, token->Ter_char);
            system("PAUSE");
            exit(1);
            break;
        case ERR_ID_REDEFINITION:
            printf("\nline %d:\nRedefined of id '%s'.\n",token->attribute->line, token->Ter_char);
            system("PAUSE");
            exit(1);
            break;
        case ERR_MISSING_SEMI:
            printf("\nline %d:\nExpected ';' after '%s'.\n",token->attribute->line, token->Ter_char);
            system("PAUSE");
            exit(1);
            break;
        case ERR_ILLEGAL_ID:
            printf("\nline %d:\nIllegal id '%s'.\n",token->attribute->line, token->Ter_char);
            system("PAUSE");
            exit(1);
            break;
        case ERR_ID_UNDEFINITON:
            printf("\nline %d:\nUndefined of id '%s'.\n",token->attribute->line, token->Ter_char);
            system("PAUSE");
            exit(1);
            break;
        case ERR_WRITE_FORMAT:
            printf("\nline %d:\nfunction write is used mistakenly.\n", token->attribute->line);
            system("PAUSE");
            exit(1);
            break;
        case ERR_STATEMENT:
            printf("\nline %d:\nCan't recognize the statement.\n", token->attribute->line);
            system("PAUSE");
            exit(1);
            break;
        case ERR_DIFFERENT_TYPE:
            printf("\nline %d:\ndifferent type options of no avail.\n", token->attribute->line);
            system("PAUSE");
            exit(1);
            break;
        case ERR_MISSING_RIGHTPAREN:
            printf("\nline %d:\nCan't find a ')' matched '('.\n", token->attribute->line);
            system("PAUSE");
            exit(1);
            break;
    }
}
