#include "precompiled.h"

#include <stdarg.h>
#include <stdio.h>
#include <fcntl.h>
#include <fstream>


#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <windows.h>
#include <Windows.h>
#include <io.h>

#define _CRT_SECURE_NO_WARNINGS
#define IOSTREAM_OUTPUT 1
#define VISUAL_STUDIO_OUTPUT 2
#define OPTION_OUTPUT VISUAL_STUDIO_OUTPUT
#endif

#pragma warning( push )
#pragma warning( disable : 4244 ) 
#pragma warning( disable : 4101 ) 

// maximum mumber of lines the output console should have
static const WORD MAX_CONSOLE_LINES = 500;
static bool start = false;

#if defined(OPTION_OUTPUT) && OPTION_OUTPUT==IOSTREAM_OUTPUT
void RedirectIOToConsole() {
	int hConHandle;
	long long lStdHandle;
	CONSOLE_SCREEN_BUFFER_INFO coninfo;
	FILE *fp;

	// allocate a console for this app
	AllocConsole();

	// redirect unbuffered STDOUT to the console
	lStdHandle = (long long)GetStdHandle(STD_OUTPUT_HANDLE);
	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
	fp = _fdopen(hConHandle, "w");
	*stdout = *fp;
	setvbuf(stdout, NULL, _IONBF, 0);


	// redirect unbuffered STDERR to the console
	lStdHandle = (long long)GetStdHandle(STD_ERROR_HANDLE);
	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
	fp = _fdopen(hConHandle, "w");
	*stderr = *fp;
	setvbuf(stderr, NULL, _IONBF, 0);
}
#endif

void log(const char file[], int line, const char* format, ...) {
	static char tmp_string[4096];
	static char tmp_string2[4096];
	static va_list  ap;

	// Construct the string from variable arguments
	va_start(ap, format);
	vsprintf_s(tmp_string, format, ap);
	va_end(ap);
	sprintf_s(tmp_string2, "\n%s(%d) : %s", file, line, tmp_string);


#if defined(OPTION_OUTPUT)
#if OPTION_OUTPUT==IOSTREAM_OUTPUT
	//using simple console, redirect output
	if (start == false) {
		start = true;
		RedirectIOToConsole();
	}

#else
	//using visual studio
	#ifdef UNICODE
		wchar_t    wbuf[4096];
		size_t ret = 0;
		mbstowcs_s(&ret, wbuf, tmp_string2, 4096);
		OutputDebugString(wbuf);
	#else
		OutputDebugString(tmp_string2);
	#endif
#endif
#endif

	//using simple console with windows or unix
#if (defined(OPTION_OUTPUT) && OPTION_OUTPUT==IOSTREAM_OUTPUT) || !defined(OPTION_OUTPUT)
	std::clog << tmp_string2;
#endif

}

#pragma warning( pop )
