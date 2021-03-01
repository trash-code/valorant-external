#include <windows.h>
#include "print.h"

void Print::color(const int forg_col)
{
	const auto h_std_out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(h_std_out, &csbi))
	{
		const WORD w_color = (csbi.wAttributes & 0xF0) + (forg_col & 0x0F);
		SetConsoleTextAttribute(h_std_out, w_color);
	}
}

void Print::text(const char* text, const int colour)
{
	color(colour);
	printf(static_cast<const char*>(text));
	color(White);
}

void Print::error(const char* text)
{
	color(Red);
	printf(static_cast<const char*>(text));
	color(White);
}

void Print::warning(const char* text)
{
	color(Yellow);
	printf(static_cast<const char*>(text));
	color(White);
}

void Print::ok(const char* text)
{
	color(Green);
	printf(static_cast<const char*>(text));
	color(White);
}