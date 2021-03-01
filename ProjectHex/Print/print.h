#pragma once
#include <windows.h>
#include <cstdio>

enum console_color
{
	Black = 0,
	Blue,
	Green,
	Cyan,
	Red,
	Magenta,
	Brown,
	LightGray,
	DarkGray,
	LightBlue,
	LightGreen,
	LightCyan,
	LightRed,
	LightMagenta,
	Yellow,
	White,
};
class Print
{
public:
	static void color(const int forg_col);
	static void text(const char* text, const int color);
	static void error(const char* text);
	static void warning(const char* text);
	static void ok(const char* text);
};
