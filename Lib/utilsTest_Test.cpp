#include "utilsTest.h"

#include <iostream>

namespace utils
{

void UnitTest_Test()
{
	using namespace test;

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
