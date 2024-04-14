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
#define     ETYPE_CONSTANT 4
#define     ETYPE_UNARY 5
#define     ETYPE_BINARY 6
#define     ETYPE_TRINARY 7
#define     ETYPE_IDENTIFIER 8


#define DTYPE_U8 0
#define DTYPE_U16 1
#define DTYPE_U32 2
#define DTYPE_I8 3
#define DTYPE_I16 4
#define DTYPE_I32 5
#define DTYPE_BOOL 6
#define DTYPE_FLOAT 7


struct Expression {
    char type;
    union {
        struct {
            char type;
            union {
                char* string;
                char uint8;
                short uint16;
                int uint32;
                float float32;
                bool boolean;       
            } data;
        } constant;
        struct {
            char type;
            struct Expression* left;
            struct Expression* right;
        } binary;
        struct {
            char type;
            struct Expression* left;
            struct Expression* right;
            struct Expression* right2;
        } trinary;
        struct {
            int ID;
        } identifier;
    };
};

struct Statement  {
            char type;
            union {
                struct{
                    char* name;
                    char type;
                    bool isThereAssignment;
                    struct Expression assgnment;
                } declaration;
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