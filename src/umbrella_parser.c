#include <parser.h>
#include <ptree.h>
#include <stdlib.h>
#include "parser.h"

int main(int argc, char **argv){
	if(argc < 2){
		puts("Too few arguments.  Please specify the file to parse.");
		return 1;
	}
	FILE *file = fopen(argv[1], "r");
	if(!file){
		printf("Failed to open file \"%s\"!\n", argv[1]);
		return 2;
	}
	PRA_Ptree *t = PRA_parseFile(file, start);
	if(!t){
		puts("Parsing unsuccessful.");
		fclose(file);
		return 3;
	}
	puts("It worked! Output:");
	PRA_printPtree(t, 0);
	PRA_deletePtree(t);
	free(t);
	fclose(file);
}

