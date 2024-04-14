#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <Tokenizer.h>

int main(int argc, char *argv[]){
	FILE *fp;
	if (argc!=2){
	    printf("Usage: %s filename\n",argv[0]);
	    return 1;
	}

	fp=fopen(argv[1],"r");
	if (fp==NULL){
	    printf("File not found\n");
	}
	
	int length = 0;
	while (fgetc(fp) != EOF){
		length++;
	}
	rewind(fp);
	char* contents = (char*) malloc(length+1);
	fread(contents,1,length,fp);
	contents[length] = '\0';
	
	struct Token* tokens = (struct Token*) tokenize(contents);
	struct Token* curr = tokens;
	while (true){
		if(curr->type > 22 || curr->type < 0){
			printf(" invalid type\n");
			goto end;
		}
		if(curr->type == TYPE_KEYWORD){
			printf(" %s - %s\n",names[curr->type],keyTokens[curr->val.num]);	
		}else if(curr->type == TYPE_IDENT){
			printf(" %s - \"%s\"\n",names[curr->type],curr->val.str);	
		}else{
			printf(" %s - %i\n",names[curr->type],curr->val.num);	
		}
		end:
		if (curr->next == NULL)
			break;
		curr = curr->next;
	}
	printf("-%i--%i--\n",curr->type,curr->val.num);	

	// free stuff
	free(contents);
	curr = tokens;
	while (curr != NULL){
		struct Token* next = curr->next;
		if (curr->type == TYPE_IDENT)
			free(curr->val.str);
		free(curr);
		curr = next;
	}

	//close the file
	fclose(fp);
	return 0;
}
