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
	fd.filename = filename;
	fseek(f, 0, SEEK_END);
	fd.len = ftell(f);
	fseek(f, 0, SEEK_SET);

	buf = malloc(fd.len);
	if (buf) fread(buf, 1, fd.len, f);
	fclose(f);
	return buf;
}

size_t parse_comment(char *buf, size_t i) {
	if (buf[++i] == '>') {
		while (buf[i] != '<') {
			if (buf[i] == '\0') {
				free(buf); // almost forgot about this one!
				printf("\n%s%s line %d: %s\nError while parsing multline comments; perhaps forgot a '<'?\nIf this is not the case, check for null characters\n%s", 
					BLUE, fd.filename, fd.lines, RED, WHITE);
				exit(1);
			}
			if (buf[i] == 0xa) {
				fd.lines++;
			}
			i++;
			fd.comments_char++;
		}
		i++;
	}
	while(buf[i] != 0xa && i < fd.len ) {
		i++;
		fd.comments_char++;
	}
	return i;
}

char *lex(char *buf) {
	size_t i = 0;
	// size_t j = 0;
	while(i < fd.len) {
		switch (buf[i]){
		case '#':
			i = parse_comment(buf, i);
			fd.comments_char++;
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
	// this is how many characters with actual code inside them.
	// printf("%d\n", fd.len - fd.comments_char-fd.comments_line-1);
	// printf("%s\n", newbuf);
	free(buf);
	return "true";
}

void RunLex(char const *filename) {
	lex(ReadToBuffer(filename));
}
