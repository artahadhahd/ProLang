#pragma once
// for feature use lol
#if defined(__linux__)
	#define PLATFORM 'l'
#elif define(_WIN32)
	#define PLATFORM 'w'
#endif
#ifndef PLATFORM
	#define PLATFROM 'u'
#endif

const char *ReadToBuffer(const char *filename);

