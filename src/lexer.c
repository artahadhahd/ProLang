#include <stdio.h>
#include <stdlib.h>

#include "common.h"

// this struct is defined in common.h
struct filedata fd;

// Read file content to buffer for faser I/O
char *ReadToBuffer(char const *filename)
{
	char *buf = 0;
	FILE *f = fopen(filename, "rb");
	if (!f) {
		printf("File '%s' not found\n", filename);
		exit(1);
	}
	fd.filename = filename;
	fseek(f, 0, SEEK_END);
	fd.len = ftell(f);
	fseek(f, 0, SEEK_SET);

	buf = malloc(fd.len);
	if (buf) 
		fread(buf, 1, fd.len, f);
	fclose(f);
	return buf;
}

// the program skips over comments with this function.
size_t parse_comment(char *buf, size_t i)
{
	/* block comments */
	if (buf[++i] == '>') {
		while (buf[i] != '<') {
			// this is for when comment is not terminated or there is a null character in the comment.
			if (buf[i] == '\0')
				goto E_EXIT_F;
			if (buf[i] == '\n')
				fd.lines++;
			i++;
			fd.comments_char++;
		}
		i++;
	}
	// inline comments 
	else {
		while(buf[i] != '\n' && i < fd.len && buf[i] != '\0') {
			i++;
			fd.comments_char++;
		}
	}
	return --i;
E_EXIT_F:
	free(buf);
	// colors are all defined in common.h (ANSI escape codes)
	printf("\n%s%s line %zu: %s\n"
	"Error while parsing multline comments;" 
	"perhaps forgot a '<'?\n"
	"If this is not the case, check for null characters in your code\n%s", 
		BLUE, fd.filename, ++fd.lines, RED, WHITE);
	exit(1);
}

// TODO: Fix the logic here.
char *parse_assign(char *buf, size_t i)
{
	while (buf[i] != '\n') {
		i--;
		if (buf[i] == ' ' || buf[i] == '\t') 
			continue;
		if (i == 1) /* if something is defined on the top of the file, then it will go out of bounds. */
			return &buf[--i];
		return &buf[i];
	}
	return "0";
}
char *lex(char *buf)
{
	size_t i = 0;
	while(i < fd.len) {
		switch (buf[i]){
		case '#':
			i = parse_comment(buf, i);
			fd.comments_char++;
		case '\n':
			fd.lines++;
		case '\t':
			i++;
			break;
		case '=':
		 	printf("%s\n", parse_assign(buf, i));
		default:
			printf("%c", buf[i]);
			i++;
		}
	}
	// printf("%d\n", fd.len - fd.comments_char-fd.comments_line-1);
	free(buf);
	return "true";
}

void RunLex(char const *filename)
{
	lex(ReadToBuffer(filename));
}
