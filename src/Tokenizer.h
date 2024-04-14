
#ifndef __TOKENIZER_H__
#define __TOKENIZER_H__
#include <stdio.h>
#include <ctype.h>

#define TYPE_INVALID          0
#define TYPE_KEYWORD          1
#define TYPE_INT_LIT          2
#define TYPE_SEMI             3
#define TYPE_OPEN             4
#define TYPE_CLOSE            5
#define TYPE_IDENT            6
#define TYPE_EQUALS           7
#define TYPE_ADD              8
#define TYPE_SUB              9
#define TYPE_MUL              10
#define TYPE_DIV              11
#define TYPE_MOD              12
#define TYPE_AND              13
#define TYPE_OR               14
#define TYPE_NOT              15
#define TYPE_NOPE             16
#define TYPE_SEPARATOR        17
#define TYPE_DECIMAL_POINT    18
#define TYPE_NEWLINE          19
#define TYPE_COMMENT          20
#define TYPE_MULTILINE_START  21
#define TYPE_MULTILINE_END    22

#define KW_IF                 0
#define KW_IMPORT             1
#define KW_ELSE               2
#define KW_WHILE              3
#define KW_FOR                4
#define KW_RETURN             5
#define KW_STRUCT             6
#define KW_BREAK              7
#define KW_CONTINUE           8
#define KW_U8                 9
#define KW_U16                10
#define KW_U32                11
#define KW_I8                 12
#define KW_I16                13
#define KW_I32                14
#define KW_BOOL               15
#define KW_FLOAT              16

struct Token{
    void* prev;

    unsigned char type;
    union {
        int num;
        char* str;
    } val;

    void* next;
};

struct Token* tokenize(char *buffer);
void initTokenizer();
extern char* keyTokens[];
extern char* names[];

#endif // __TOKENIZER_H__
