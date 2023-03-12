#include <stdio.h>
#include <stdlib.h>

#include "common.h"

// this struct is defined in common.h
struct filedata fd;

// Read file content to buffer for fast data reading
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
	if (buf) fread(buf, 1, fd.len, f);
	fclose(f);
	return buf;
}

size_t parse_comment(char *buf, size_t i)
{
	/* block comments */
	if (buf[++i] == '>') {
		while (buf[i] != '<') {
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
	while(buf[i] != '\n' && i < fd.len && buf[i] != '\0') {
		i++;
		fd.comments_char++;
	}
	return i;
E_EXIT_F:
	free(buf); // almost forgot about this one!
	printf("\n%s%s line %zu: %s\nError while parsing multline comments;" 
	"perhaps forgot a '<'?\n"
	"If this is not the case, check for null characters\n%s", 
		BLUE, fd.filename, fd.lines, RED, WHITE);
	exit(1);
}

void parse_assign(char *buf, size_t i) {
	while(i != 0 && buf[i] != '\n') {
		--i;
		if (buf[i] == ' ' || buf[i] == '\n') 
			continue;
	}
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
			parse_assign(buf, i);
		default:
			// printf("%c", buf[i]);
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
