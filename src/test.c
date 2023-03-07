#include <stdio.h>
#include <string.h>
int main(void){
	char *thing;
	char c = 'c';
	char l = strlen(thing);
	thing[l] = c;
	thing[l+1] = '\0';
	printf("%s\n", thing);
	return 0;
}
