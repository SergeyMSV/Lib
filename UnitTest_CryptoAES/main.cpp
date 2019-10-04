#include <iostream>
#include <string>
#include <utility>

#include <conio.h>
#include <time.h>

namespace utils
{
	namespace crypto
	{
		namespace AES
		{
			void UnitTest();
		}
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////
void main()
{
	utils::crypto::AES::UnitTest();

	system("pause");
}