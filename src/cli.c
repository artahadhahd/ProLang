#include <stdio.h>
#include <stdlib.h>

#include "lexer.h"

int main(int argc, char const *argv[]){
	if (argc != 2){
		puts("Too many/No arguments passed");
		exit(64);
	}
	ReadToBuffer(argv[1]);

	return 0;
}
