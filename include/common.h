struct filedata {
	char const *filename;
	size_t len;
	size_t lines;
	size_t comments_char;
	size_t comments_line;
};

// colors
#define WHITE "\x1B[37;1m"
#define RED "\x1B[31;1m"
#define GREEN "\x1B[32;1m"
#define YELLOW "\x1B[33;1m"
#define BLUE "\x1B[34;1m"
