#include "utilsLog.h"

#include <cstdio>

#ifdef LIB_UTILS_LOG

namespace utils
{

void tLog::Write(const std::string& msg, tLogColour textColour, bool timestamp)
{
#ifdef LIB_UTILS_LOG_COLOUR

	std::string Str = "\x1b[";

	switch (textColour)
	{
	case tLogColour::Black: Str += "30"; break;
	case tLogColour::Red: Str += "31"; break;
	case tLogColour::Green: Str += "32"; break;
	case tLogColour::Yellow: Str += "33"; break;
	case tLogColour::Blue: Str += "34"; break;
	case tLogColour::Magenta: Str += "35"; break;
	case tLogColour::Cyan: Str += "36"; break;
	case tLogColour::White: Str += "37"; break;
	//case tLogColour::Default: Str += "39"; break;
	case tLogColour::LightGray: Str += "90"; break;
	case tLogColour::LightRed: Str += "91"; break;
	case tLogColour::LightGreen: Str += "92"; break;
	case tLogColour::LightYellow: Str += "93"; break;
	case tLogColour::LightBlue: Str += "94"; break;
	case tLogColour::LightMagenta: Str += "95"; break;
	case tLogColour::LightCyan: Str += "96"; break;
	case tLogColour::LightWhite: Str += "97"; break;
	default: Str += "39"; break;
	}

	Str += "m" + msg + "\x1b[0m";

	WriteLog(Str, timestamp, false);

#else//LIB_UTILS_LOG_COLOUR
	WriteLog(msg, timestamp, false);
#endif//LIB_UTILS_LOG_COLOUR
}

void tLog::WriteLine(const std::string& msg, tLogColour textColour, bool timestamp)
{
#ifdef LIB_UTILS_LOG_COLOUR
	Write(msg + '\n', textColour, timestamp);
#else//LIB_UTILS_LOG_COLOUR
	WriteLog(msg + '\n', timestamp, false);
#endif//LIB_UTILS_LOG_COLOUR
}

void tLog::Write(const std::string& msg, bool timestamp)
{
	WriteLog(msg, timestamp, false);
}

void tLog::WriteLine(const std::string& msg, bool timestamp)
{
	WriteLog(msg + '\n', timestamp, false);
}

void tLog::WriteLineArg(bool timestamp, const char* format, ...)
{
	char Buffer[160];

	std::va_list Args;

	va_start(Args, format);

	std::vsprintf(Buffer, format, Args);

	std::string Str(Buffer);

	va_end(Args);

	WriteLog(Str + '\n', timestamp, false);
}

void tLog::WriteErrLine(const std::string& msg, bool timestamp)
{
#ifdef LIB_UTILS_LOG_COLOUR
	WriteLog(std::string("\x1b[31mER:") + msg + "\x1b[0m" "\n", timestamp, true);
#else//LIB_UTILS_LOG_COLOUR
	WriteLog(std::string("ER:") + msg + '\n', timestamp, true);
#endif//LIB_UTILS_LOG_COLOUR
}

void tLog::WriteHex(const std::string& msg, const std::vector<char>& data, bool timestamp)
{
	std::string Str = msg + '\n';

	char Figure[5];

	std::string Substr;

	for (unsigned int i = 0; i < data.size(); ++i)
	{
		std::sprintf(Figure, "%02X ", (unsigned char)data[i]);
		Str += Figure;

		if (data[i] <= 0x20 || data[i] == 0x25)
		{
			Substr += '.';
		}
		else
		{
			Substr += data[i];
		}

		if (((i + 1) % 16) == 0)
		{
			Str += "  " + Substr;

			Substr.clear();

			if (i != data.size())
			{
				Str += '\n';
			}
		}
		else if (((i + 1) % 8) == 0)
		{
			Str += "  ";
		}
	}

	int FullStringsEnd = Str.find_last_of('\n');

	int Filled = Str.size() - FullStringsEnd;
	int Empty = 53 - Filled;

	for (int i = 0; i < Empty; ++i)
	{
		Str += ' ';
	}

	Str += Substr;

	WriteLog(Str + '\n', timestamp, false);
}

void tLog::WriteInfoBlock(const std::string& msg)
{
	WriteLog(msg, false, true);
}

void tLog::WriteInfoLine(const std::string& msg, bool timestamp)
{
	WriteLog(msg + '\n', timestamp, true);
}

void tLog::WriteInfoLineArg(bool timestamp, const char* format, ...)
{
	char Buffer[160];

	std::va_list Args;

	va_start(Args, format);

	std::vsprintf(Buffer, format, Args);

	std::string Str(Buffer);

	va_end(Args);

	WriteLog(Str + '\n', timestamp, true);
}

}

#endif//LIB_UTILS_LOG
