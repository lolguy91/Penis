#ifndef PARSER_H
#define PARSER_H
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <Tokenizer.h>

#define NTYPE_STATEMENT 0
#define     STYPE_DECLARATION 1
#define     STYPE_ASSIGNMENT 2
#define NTYPE_EXPRESSION 3

struct Expression{
    
};

struct Statement  {
            char type;
            union {
                struct declaration {
                    char* name;
                    char type;
                    bool isThereAssignment;
                    struct Expression assgnment;
                }
            } args;
};

struct Node{
    void* prev;
    char type;
    union {
        struct Statement stmnt;
        struct Expression expr;
    } val;
    void* next;
};

struct Node* parse(struct Token* tokens);

#endif