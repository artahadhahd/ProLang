#include <stdio.h>

#include "lexer.h"

int main(int argc, char const *argv[]){
	if (argc != 2){
		puts("Too many/No arguments passed");
		return -1;
	}
	RunLex(argv[1]);
	puts(""); // just to make things more easy to read
	return 0;
}
