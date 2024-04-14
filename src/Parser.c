#include "Parser.h"

struct Node* parse(struct Token* tokens){

    struct Node* root = (struct Node*) malloc(sizeof(struct Node));
    root->prev = NULL;
    root->type = 0;
    root->val.stmnt.type = 0;
    root->val.stmnt.args.declaration.name = NULL;
    root->val.stmnt.args.declaration.type = 0;
    root->val.stmnt.args.declaration.isThereAssignment = false;
    root->val.stmnt.args.declaration.assgnment.type = 0;

    struct Token* curr = tokens;
    struct Node* currNode = root;
    while(curr != NULL){
        switch(curr->type){
            case TYPE_KEYWORD:
                switch(curr->val.num){
                    case KW_IMPORT:
                        currNode->type = NTYPE_STATEMENT;

                }
                        
        }
        
        curr = curr->next;
    }

    return root;
}