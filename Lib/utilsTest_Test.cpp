#include "utilsTest.h"

#include <iostream>

namespace utils
{
	namespace test
	{
		namespace unit_test
		{

void UnitTest_Test()
{
	std::cout << "\n""UnitTest" << std::endl;

	WARNING("MEDVED");
	WARNING("PREVED", false);
	WARNING("PREVED-odnako", true);

	RESULT("Preved", true);
	RESULT("Medved", false);

	ASSERT(true);

	std::cout << std::endl;
}

		}
	}
}
