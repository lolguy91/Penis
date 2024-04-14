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
"struct",
"break",
"continue",
"u8",
"u16",
"u32",
"i8",
"i16",
"i32",
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

    size_t i = 0;
    size_t j = 0;
    while (buffer[i] != '\0')
    {
        did_hit = false;
        if (buffer[i] == ' ' || buffer[i] == '\t')
        {  
            if (j != 0  && j <= 1024){
                char* buf2copy = (char*)malloc(j + 1);
                memcpy(buf2copy, buffer2, j);
                buf2copy[j] = '\0';
                ((struct Token*)currToken->next)->type = TYPE_IDENT;
                ((struct Token*)currToken->next)->val.str = buf2copy;
                j = 0;
                did_hit = true;
                goto end;
            }
            j = 0;
            i++;
            continue;
        }

        // dont add spaces
        if(j > 1024){
            j = 0;
        }
        buffer2[j] = buffer[i];
        buffer2[j + 1] = '\0';
        j++;

        if(keyword_check(currToken,buffer2)){
            j = 0;
            did_hit = true;
            goto end;   
        }

        // detect decimal numbers
        if (isdigit(buffer[i]) && !isdigit(buffer[i + 1])){
            char* first = buffer + i;

            //magic
            for (; isdigit(*first); first--);
            first++;

            ((struct Token*)currToken->next)->type = TYPE_INT_LIT;
            ((struct Token*)currToken->next)->val.num = atoi(first);
            j = 0;
            did_hit = true;
            goto end;
        }

        switch(buffer[i])
        {
            case ';':
                ((struct Token*)currToken->next)->type = TYPE_SEMI;
                ((struct Token*)currToken->next)->val.num = 0;
                did_hit = true;
                j--;
                goto end;
            case '(':
                ((struct Token*)currToken->next)->type = TYPE_OPEN;
                ((struct Token*)currToken->next)->val.num = 0;
                did_hit = true;
                j--;
                goto end;
            case '{':
                ((struct Token*)currToken->next)->type = TYPE_OPEN;
                ((struct Token*)currToken->next)->val.num = 1;
                did_hit = true;
                j--;
                goto end;
            case '[':
                ((struct Token*)currToken->next)->type = TYPE_OPEN;
                ((struct Token*)currToken->next)->val.num = 2;
                did_hit = true;
                j--;
                goto end;
            case ')':
                ((struct Token*)currToken->next)->type = TYPE_CLOSE;
                ((struct Token*)currToken->next)->val.num = 0;
                did_hit = true;
                j--;
                goto end;
            case '}':
                ((struct Token*)currToken->next)->type = TYPE_CLOSE;
                ((struct Token*)currToken->next)->val.num = 1;
                did_hit = true;
                j--;
                goto end;
            case ']':
                ((struct Token*)currToken->next)->type = TYPE_CLOSE;
                ((struct Token*)currToken->next)->val.num = 2;
                did_hit = true;
                j--;
                goto end;
            case '+':
                ((struct Token*)currToken->next)->type = TYPE_ADD;
                ((struct Token*)currToken->next)->val.num = 0;
                did_hit = true;
                j--;
                goto end;
            case '-':
                ((struct Token*)currToken->next)->type = TYPE_SUB;
                ((struct Token*)currToken->next)->val.num = 0;
                did_hit = true;
                j--;
                goto end;
            case '*':
                if(buffer[i+1] == '/'){
                    ((struct Token*)currToken->next)->type = TYPE_MULTILINE_END;
                    ((struct Token*)currToken->next)->val.num = 0;
                    i++;
                    j-=2;
                    did_hit = true;
                    goto end;
                }
                ((struct Token*)currToken->next)->type = TYPE_MUL;
                ((struct Token*)currToken->next)->val.num = 0;
                did_hit = true;
                j--;
                goto end;
            case '/':
                if(buffer[i+1] == '/'){
                    ((struct Token*)currToken->next)->type = TYPE_COMMENT;
                    ((struct Token*)currToken->next)->val.num = 0;
                    i++;
                    j-=2;
                    did_hit = true;
                    goto end;
                } else if (buffer[i+1] == '*'){
                    ((struct Token*)currToken->next)->type = TYPE_MULTILINE_START;
                    ((struct Token*)currToken->next)->val.num = 0;
                    i++;
                    j-=2;
                    did_hit = true;
                    goto end;
                }
                ((struct Token*)currToken->next)->type = TYPE_DIV;
                ((struct Token*)currToken->next)->val.num = 0;
                did_hit = true;
                j--;
                goto end;
            case '%':
                ((struct Token*)currToken->next)->type = TYPE_MOD;
                ((struct Token*)currToken->next)->val.num = 0;
                did_hit = true;
                j--;
                goto end;
            case '&':
                ((struct Token*)currToken->next)->type = TYPE_AND;
                ((struct Token*)currToken->next)->val.num = 0;
                did_hit = true;
                j--;
                goto end;
            case '|':
                ((struct Token*)currToken->next)->type = TYPE_OR;
                ((struct Token*)currToken->next)->val.num = 0;
                did_hit = true;
                j--;
                goto end;
            case '!':
                ((struct Token*)currToken->next)->type = TYPE_NOT;
                ((struct Token*)currToken->next)->val.num = 0;
                did_hit = true;
                j--;
                goto end;
            case '=':
                ((struct Token*)currToken->next)->type = TYPE_EQUALS;
                ((struct Token*)currToken->next)->val.num = 0;
                did_hit = true;
                j--;
                goto end;
            case '.':
                ((struct Token*)currToken->next)->type = TYPE_DECIMAL_POINT;
                ((struct Token*)currToken->next)->val.num = 0;
                did_hit = true;
                j--;
                goto end;
            case '\n':
                ((struct Token*)currToken->next)->type = TYPE_NEWLINE;
                ((struct Token*)currToken->next)->val.num = 0;
                did_hit = true;
                if(buffer[i] != '\0'){
                    j = 0;
                }
                goto end;
        }
        end:
        if(did_hit){
            ((struct Token*)currToken->next)->prev = currToken;
            currToken = currToken->next;
            currToken->next = malloc(sizeof(struct Token));
        }
        i++;
    }
    free(buffer2);
    free(toFree);
    free(currToken->next);
    currToken->next = NULL;
    
return firstToken;
}