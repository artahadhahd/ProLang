#pragma once
#if 0
// for feature use lol
#if defined(__linux__)
	#define PLATFORM 'l'
#elif define(_WIN32)
	#define PLATFORM 'w'
#endif
#ifndef PLATFORM
	#define PLATFROM 'u'
#endif
#endif


// const char *ReadToBuffer(const char *filename);
void RunLex(char const *filename);

