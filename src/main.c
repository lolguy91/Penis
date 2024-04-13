#include <stdio.h>
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
	
	
	struct Token* tokens = (struct Token*) tokenize(fp);
	while (tokens->next != 0){
		if(tokens->type == TYPE_KEYWORD){
			printf(" %s - %s\n",names[tokens->type],keyTokens[tokens->val.num]);	
		}else if(tokens->type == TYPE_IDENT){
			printf(" %s - \"%s\"\n",names[tokens->type],tokens->val.str);	
		}else{
			printf(" %s - %i\n",names[tokens->type],tokens->val.num);	
		}
		tokens = tokens->next;
	}
	printf("-%i--%i--\n",tokens->type,tokens->val);	

	//close the file
	fclose(fp);
	return 0;
}
