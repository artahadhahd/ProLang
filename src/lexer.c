#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// We need to open the file, and read it to memory.
const char *ReadToBuffer(const char *filename){
	char *buf = 0;
	unsigned int len; // Characters inside the file
	FILE *f = fopen(filename, "rb");
	if (!f) {
		puts("Ooopsies! File not found");	
		exit(1);
	}
	fseek(f, 0, SEEK_END);
	len = ftell(f);
	printf("%d\n", len);
	fseek(f, 0, SEEK_SET);
	
	buf = malloc(len);
	if (buf) fread(buf, 1, len, f);
	fclose(f);
	
	return buf;
}

