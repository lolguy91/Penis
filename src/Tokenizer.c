#include <Tokenizer.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>


char* keyTokens[] = {
"if",
"else",
"while",
"for",
"return",
"break",
"continue",
"u8",
"u16",
"u32",
"bool",
"float"
};
char* names[] = {
"TYPE_INVALID",
"TYPE_KEYWORD",
"TYPE_INT_LIT",
"TYPE_SEMI",
"TYPE_OPEN",
"TYPE_CLOSE",
"TYPE_IDENT",
"TYPE_EQUALS",
"TYPE_ADD",
"TYPE_SUB",
"TYPE_MUL",
"TYPE_DIV",
"TYPE_MOD",
"TYPE_AND",
"TYPE_OR",
"TYPE_NOT",
"TYPE_NOPE",
"TYPE_SEPARATOR",
"TYPE_DECIMAL_POINT",
"TYPE_COMMENT",
"TYPE_MULTILINE_START",
"TYPE_MULTILINE_END"
};

bool keyword_check(struct Token* currToken,char* buffer){
    for (int i = 0; i < (sizeof(keyTokens) / sizeof(char*)); i++)
    {
	    if(!strcmp(keyTokens[i],buffer)){
            ((struct Token*)currToken->next)->type = TYPE_KEYWORD;
            ((struct Token*)currToken->next)->val.num =  i;
            return true;
        }
    }
    return false;
}
bool misc_check(struct Token* currToken,char* buffer,int i){
    bool val = false;
    if (buffer[i] == ';')
    {
        ((struct Token*)currToken->next)->type = TYPE_SEMI;
        ((struct Token*)currToken->next)->val.num = 1;

        val = true;
    }
    if (buffer[i] == '=')
    {
        ((struct Token*)currToken->next)->type = TYPE_EQUALS;
        ((struct Token*)currToken->next)->val.num = 1;
        val = true;
    }
    if (buffer[i] == ',')
    {
        ((struct Token*)currToken->next)->type = TYPE_SEPARATOR;
        ((struct Token*)currToken->next)->val.num = 1;
        val = true;
    }
    if (buffer[i] == '.')
    {
        ((struct Token*)currToken->next)->type = TYPE_DECIMAL_POINT;
        ((struct Token*)currToken->next)->val.num = 1;
        val = true;
    }
    return val;
}
bool logic_check(struct Token* currToken,char* buffer,int i){
    bool val = false;
    if (buffer[i] == '&')
    {
        ((struct Token*)currToken->next)->type = TYPE_AND;
        ((struct Token*)currToken->next)->val.num = 1;

        val = true;
    }
    if (buffer[i] == '|')
    {
        ((struct Token*)currToken->next)->type = TYPE_OR;
        ((struct Token*)currToken->next)->val.num = 1;
        val = true;
    }
    if (buffer[i] == '~')
    {
        ((struct Token*)currToken->next)->type = TYPE_NOT;
        ((struct Token*)currToken->next)->val.num = 1;
        val = true;
    }
    if (buffer[i] == '!')
    {
        ((struct Token*)currToken->next)->type = TYPE_NOPE;
        ((struct Token*)currToken->next)->val.num = 1;
        val = true;
    }
    return val;
}
bool arith_check(struct Token* currToken,char* buffer,int* i){
    bool val = false;
    if (buffer[*i] == '+')
    {
        ((struct Token*)currToken->next)->type = TYPE_ADD;
        ((struct Token*)currToken->next)->val.num = 1;

        val = true;
    }
    if (buffer[*i] == '-')
    {
        ((struct Token*)currToken->next)->type = TYPE_SUB;
        ((struct Token*)currToken->next)->val.num = 1;
        val = true;
    }
    if (buffer[*i] == '*')
    {
        if(buffer[*i+1] == '/'){
            ((struct Token*)currToken->next)->type = TYPE_MULTILINE_END;
            ((struct Token*)currToken->next)->val.num = 1;
            (*i)++;
            val = true;
        }else{
            ((struct Token*)currToken->next)->type = TYPE_MUL;
            ((struct Token*)currToken->next)->val.num = 1;
            val = true;
        }
    }
    if (buffer[*i] == '/')
    {
        if (buffer[*i + 1] == '*')
        {
            ((struct Token*)currToken->next)->type = TYPE_MULTILINE_START;
            ((struct Token*)currToken->next)->val.num = 1;
            (*i)++;
            val = true;
        }else{
            ((struct Token*)currToken->next)->type = TYPE_DIV;
            ((struct Token*)currToken->next)->val.num = 1;
            val = true;
        }
    }
    if (buffer[*i] == '%')
    {
        ((struct Token*)currToken->next)->type = TYPE_MOD;
        ((struct Token*)currToken->next)->val.num = 1;
        val = true;
    }
    return val;
}
bool open_and_close_check(struct Token* currToken,char* buffer,int i){
    bool val = false;
    if (buffer[i] == '(')
    {
        ((struct Token*)currToken->next)->type = TYPE_OPEN;
        ((struct Token*)currToken->next)->val.num = 1;

        val = true;
    }
    if (buffer[i] == '{')
    {
        ((struct Token*)currToken->next)->type = TYPE_OPEN;
        ((struct Token*)currToken->next)->val.num =  2;
        val = true;
    }
    if (buffer[i] == '[')
    {
        ((struct Token*)currToken->next)->type = TYPE_OPEN;
        ((struct Token*)currToken->next)->val.num =  3;
        val = true;
    }
    if (buffer[i] == ')')
    {
        ((struct Token*)currToken->next)->type = TYPE_CLOSE;
        ((struct Token*)currToken->next)->val.num = 1;
        val = true;
    }
    if (buffer[i] == '}')
    {
        ((struct Token*)currToken->next)->type = TYPE_CLOSE;
        ((struct Token*)currToken->next)->val.num =  2;
        val = true;
    }
    if (buffer[i] == ']')
    {
        ((struct Token*)currToken->next)->type = TYPE_CLOSE;
        ((struct Token*)currToken->next)->val.num =  3;
        val = true;
    }
    return val;
}

struct Token* tokenize(FILE* fp)
{
    //create the string buffers
    char *buffer=malloc(1024);
    char *buffer2=malloc(1024);

    int fscanout = fscanf(fp,"%s",buffer);
    struct Token* currToken = malloc(sizeof(struct Token));
    currToken->next = malloc(sizeof(struct Token));
    currToken->prev = currToken;
    struct Token* firstToken = currToken->next;
    bool dummy_pervention = false;

    while(fscanout != -1){
        dummy_pervention = false;
        if(!keyword_check(currToken,buffer)){
            int imod = 0;
            for (size_t i = 0; i < strlen(buffer); i++)
            {
                buffer2[i + imod] = buffer[i];
                buffer2[i + imod + 1] = 0;

                if(isdigit(buffer[i]) && !isdigit(buffer[i+1])){
                    ((struct Token*)currToken->next)->type = TYPE_INT_LIT;
                    ((struct Token*)currToken->next)->val.num =  atoi(buffer2);

                    ((struct Token*)currToken->next)->prev = currToken;
                    currToken = currToken->next;
                    currToken->next = malloc(sizeof(struct Token));
                    dummy_pervention = true;
                    imod -= strlen(buffer2);
	            }

                if (keyword_check(currToken,buffer2))
                {
                    ((struct Token*)currToken->next)->prev = currToken;
                    currToken = currToken->next;
                    currToken->next = malloc(sizeof(struct Token));
                    dummy_pervention = true;
                    imod -= strlen(buffer2);
                }
                
                if (open_and_close_check(currToken,buffer,i) ||
                        arith_check(currToken,buffer,&i) ||
                            logic_check(currToken,buffer,i) ||
                                misc_check(currToken,buffer,i))
                {
                    ((struct Token*)currToken->next)->prev = currToken;
                    currToken = currToken->next;
                    currToken->next = malloc(sizeof(struct Token));
                    dummy_pervention = true;
                    imod--;
                }
            }
            if(imod == 0){
                char* copy_of_buffer = malloc(strlen(buffer)+ 1);
                memcpy(copy_of_buffer,buffer,strlen(buffer));
                copy_of_buffer[strlen(buffer)] = 0;

                ((struct Token*)currToken->next)->type = TYPE_IDENT;
                ((struct Token*)currToken->next)->val.str = copy_of_buffer;

            }
        }
        if(!dummy_pervention){
            ((struct Token*)currToken->next)->prev = currToken;
            currToken = currToken->next;
            currToken->next = malloc(sizeof(struct Token));
        }

        fscanout = fscanf(fp,"%s",buffer);
    }

return firstToken;
}