#include "utilsTest.h"

#include <stdlib.h>
#include <iomanip>
#include <iostream>

#ifndef __GNUC__
#include <Windows.h>
#endif//__GNUC__

namespace utils
{
	namespace test
	{
///////////////////////////////////////////////////////////////////////////////////////////////////
enum tConsoleColor {
	tConsoleColor_Black = 0,
	tConsoleColor_Blue = 1,
	tConsoleColor_Green = 2,
	tConsoleColor_Cyan = 3,
	tConsoleColor_Red = 4,
	tConsoleColor_Magenta = 5,
	tConsoleColor_Brown = 6,
	tConsoleColor_LightGray = 7,
	tConsoleColor_DarkGray = 8,
	tConsoleColor_LightBlue = 9,
	tConsoleColor_LightGreen = 10,
	tConsoleColor_LightCyan = 11,
	tConsoleColor_LightRed = 12,
	tConsoleColor_LightMagenta = 13,
	tConsoleColor_Yellow = 14,
	tConsoleColor_White = 15
};
///////////////////////////////////////////////////////////////////////////////////////////////////
void ASSERT(bool value)
{
	if (value)
	{
#ifndef __GNUC__
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		SetConsoleTextAttribute(hConsole, (WORD)((tConsoleColor_White << 4) | tConsoleColor_Black));
#endif//__GNUC__

		std::cout << "\n\n""ASSERT -> ERROR""\n\n" << std::endl;

#ifndef __GNUC__
		SetConsoleTextAttribute(hConsole, (WORD)((tConsoleColor_Black << 4) | tConsoleColor_LightGray));
#endif//__GNUC__

		system("pause");
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////
void RESULT(const char* msg, bool result)
{
#ifndef __GNUC__
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	//÷вет всего фона - белый. ÷вет всего текста - черный
	//system("color F0");
	//puts("Hello World!");
	//÷вет символов - желтый. ÷вет фона - темно-серый
	//SetConsoleTextAttribute(hConsole, (WORD)((DarkGray << 4) | Yellow));
#endif//__GNUC__

	std::cout << std::setw(70) << std::setfill('.') << std::setiosflags(std::ios::left) << msg;

	if (result)
	{
		std::cout << "OK";
	}
	else
	{
#ifndef __GNUC__
		SetConsoleTextAttribute(hConsole, (WORD)((tConsoleColor_Red << 4) | tConsoleColor_Yellow));
#endif//__GNUC__

		std::cout << "ERROR";

#ifndef __GNUC__
		SetConsoleTextAttribute(hConsole, (WORD)((tConsoleColor_Black << 4) | tConsoleColor_LightGray));
#endif//__GNUC__
	}

	std::cout << std::endl;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
void WARNING(const char* msg, bool show)
{
	if (show)
	{
#ifndef __GNUC__
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		SetConsoleTextAttribute(hConsole, (WORD)(tConsoleColor_LightRed));
#endif//__GNUC__

		std::cout<<"WARNING: " << msg;

#ifndef __GNUC__
		SetConsoleTextAttribute(hConsole, (WORD)((tConsoleColor_Black << 4) | tConsoleColor_LightGray));
#endif//__GNUC__

		std::cout << std::endl;
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////
	}
}