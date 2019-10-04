#include <iostream>
#include <string>
#include <utility>

#include <conio.h>
#include <time.h>

namespace utils
{
	namespace crypto
	{
		namespace RSA32
		{
			void UnitTest();
		}
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////
void main()
{
	utils::crypto::RSA32::UnitTest();

	system("pause");
}