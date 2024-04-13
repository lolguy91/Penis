
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
#define TYPE_MULTILINE_START  20
#define TYPE_MULTILINE_END    21


struct Token{
    void* prev;

    char type;
    union {
        int num;
        char* str;
    } val;

    void* next;
};

struct Token* tokenize(FILE* fp);
void initTokenizer();
extern char* keyTokens[];
extern char* names[];

#endif // __TOKENIZER_H__
