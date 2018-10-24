#pragma once
#ifndef LOG_H
#define LOG_H

/// <summary>
/// Deal with the difference between linux/unix and windows in the output of std::cout
/// Can choose between showing through the terminal or using the output of visual studio
/// </summary>
#define LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);


void log(const char file[], int line, const char* format, ...);


#endif // !LOG_H
