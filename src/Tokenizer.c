#include <Tokenizer.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>


char* keyTokens[] = {
"if",
"import",   
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
"TYPE_NEWLINE",
"TYPE_COMMENT",
"TYPE_MULTILINE_START",
"TYPE_MULTILINE_END"
};

bool keyword_check(struct Token* currToken,char* buffer){
    for (size_t i = 0; i < (sizeof(keyTokens) / sizeof(char*)); i++)
    {
	    if(!strcmp(keyTokens[i],buffer)){
            ((struct Token*)currToken->next)->type = TYPE_KEYWORD;
            ((struct Token*)currToken->next)->val.num =  i;
            return true;
        }
    }
    return false;
}
bool misc_check(struct Token* currToken,char* buffer,size_t i){
    bool val = false;
    if (buffer[i] == ';')
    {
        ((struct Token*)currToken->next)->type = TYPE_SEMI;
        ((struct Token*)currToken->next)->val.num = 1;

        val = true;
    }
    if (buffer[i] == '\n')
    {
        ((struct Token*)currToken->next)->type = TYPE_NEWLINE;
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
bool logic_check(struct Token* currToken,char* buffer,size_t i){
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
bool arith_check(struct Token* currToken,char* buffer,size_t* i){
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
        }else if(buffer[*i+1] == '/'){
            ((struct Token*)currToken->next)->type = TYPE_COMMENT;
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
bool open_and_close_check(struct Token* currToken,char* buffer,size_t i){
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

struct Token* tokenize(char* inbuf)
{

    char* buffer = inbuf;
    char *buffer2=malloc(1024);

    struct Token* currToken = malloc(sizeof(struct Token));
    currToken->next = malloc(sizeof(struct Token));
    currToken->prev = currToken;
    struct Token* firstToken = currToken->next; 
    struct Token* toFree = currToken;
    bool did_hit = false;

    while (strchr(buffer, ' ') || strchr(buffer, '\n'))
    {
        did_hit = false;
        char* nextSpace = strchr(buffer, ' ');
        if (nextSpace)
        {
            *nextSpace = '\0';
        }
        if(isdigit(buffer[0])){
            ((struct Token*)currToken->next)->type = TYPE_INT_LIT;
            ((struct Token*)currToken->next)->val.num =  atoi(buffer2);
            goto hit;
	    }

        if (!keyword_check(currToken, buffer))
        {
            size_t last_i = 0;
            size_t last_i2 = 0;
            for (size_t i = 0; i < strlen(buffer); i++)
            {
                buffer2[i] = buffer[i];
                buffer2[i + 1] = 0;
                
                if (open_and_close_check(currToken,buffer,i) ||
                        arith_check(currToken,buffer,&i) ||
                            logic_check(currToken,buffer,i) ||
                                misc_check(currToken,buffer,i))
                {
                    ((struct Token*)currToken->next)->prev = currToken;
                    currToken = currToken->next;
                    currToken->next = malloc(sizeof(struct Token));
                    last_i2 = last_i;
                    last_i = i;
                    did_hit = true;
                }
                if(last_i == i && last_i2 - last_i > 1 && !isdigit((buffer2 + last_i2)[0])){
                    char* copy_of_buffer = malloc(strlen(buffer2 + last_i2 + 1)+ 1);
                    memcpy(copy_of_buffer,buffer2 + last_i2 + 1,strlen(buffer2 + last_i2 + 1));
                    copy_of_buffer[strlen(buffer2 + last_i2 + 1)] = 0;

                    ((struct Token*)currToken->next)->type = TYPE_IDENT;
                    ((struct Token*)currToken->next)->val.str = copy_of_buffer;
                    currToken = currToken->next;
                    currToken->next = malloc(sizeof(struct Token));
                    did_hit = true;
                    continue;
                }
                
                if (keyword_check(currToken,buffer2))
                {
                    ((struct Token*)currToken->next)->prev = currToken;
                    currToken = currToken->next;
                    currToken->next = malloc(sizeof(struct Token));
                    last_i2 = last_i;
                    last_i = i;
                    //no need to do did_hit on this one
                }
            }
            if (last_i == 0)
            {
                char* copy_of_buffer = malloc(strlen(buffer)+ 1);
                memcpy(copy_of_buffer,buffer,strlen(buffer));
                copy_of_buffer[strlen(buffer)] = 0;

                ((struct Token*)currToken->next)->type = TYPE_IDENT;
                ((struct Token*)currToken->next)->val.str = copy_of_buffer;
            }
        }
        hit:
        if(!did_hit){
            ((struct Token*)currToken->next)->prev = currToken;
            currToken = currToken->next;
            currToken->next = malloc(sizeof(struct Token));
        }

        if (nextSpace)
        {
            buffer = nextSpace + 1;
        }
        else
        {
            buffer = buffer + strlen(buffer);
        }
    }
    free(buffer2);
    free(toFree);
    currToken->next = NULL;

return firstToken;
}