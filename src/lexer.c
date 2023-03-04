#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "common.h"

// this struct is defined in common.h
struct filedata fd;

char *ReadToBuffer(char const *filename){
	char *buf = 0;
	FILE *f = fopen(filename, "rb");
	if (!f) {
		puts("Ooopsies! File not found");	
		exit(1);
	}
	fseek(f, 0, SEEK_END);
	fd.len = ftell(f);
	fseek(f, 0, SEEK_SET);
	
	buf = malloc(fd.len);
	if (buf) fread(buf, 1, fd.len, f);
	fclose(f);
	return buf;
}


char *lex(char *buf) {
	char *newbuf = 0;
	// newbuf = malloc(len - count(buf));
	size_t i = 0;
	size_t j = 0;
	while(i < fd.len) {
		switch (buf[i]){
			// ignore inline comments.
			case '#':
				while(buf[i] != 0xa) ++i;
			case 0xa:
				fd.lines++;
			case 0x9:
				i++;
				break;
			default:
				printf("%c", buf[i]);
				i++;
		}
	}
	printf("%d\n", fd.lines);
	free(buf);
	return newbuf;
}
void RunLex(const char *filename){
	lex(ReadToBuffer(filename));
}
