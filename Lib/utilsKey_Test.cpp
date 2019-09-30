#include "utilsKey.h"

#include "utilsTest.h"

#include <algorithm>

#include <iostream>

//#define DEBUG_SHOW_DOES_NOT_WORK

namespace utils
{
	namespace unit_test
	{

void UnitTest_Key()
{
	std::cout << "\n""utils::Key" << std::endl;

	//////////////////////////////////////////////////////////////////////////////////////////////////

	{
		tKey128 Key_1;
		tKey128 Key_2;

		type::tKey2<4> Key2;

		Key_1.Value = Key2;
		Key_2.Value = Key2;

		utils::test::RESULT("tKey128 ==", Key_1 == Key_2);

		Key_1.Field.A = 4;

		utils::test::RESULT("tKey128 !=", Key_1 != Key_2);
	}

	{
		tKey96 Key_1;
		tKey96 Key_2;

		type::tKey2<3> Key2;

		Key_1.Value = Key2;
		Key_2.Value = Key2;

		utils::test::RESULT("tKey96 ==", Key_1 == Key_2);

		Key_1.Field.A = 4;

		utils::test::RESULT("tKey96 !=", Key_1 != Key_2);
	}

	{
		tKey64 Key_1;
		tKey64 Key_2;

		type::tKey2<2> Key2;

		Key_1.Value = Key2;
		Key_2.Value = Key2;

		utils::test::RESULT("tKey64 ==", Key_1 == Key_2);

		Key_1.Field.A = 4;

		utils::test::RESULT("tKey64 !=", Key_1 != Key_2);
	}

	{
		tKey32 Key_1;
		tKey32 Key_2;

		type::tKey2<1> Key2;

		Key_1.Value = Key2;
		Key_2.Value = Key2;

		utils::test::RESULT("tKey32 ==", Key_1 == Key_2);

		Key_1.Field.A = 4;

		utils::test::RESULT("tKey32 !=", Key_1 != Key_2);
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////

	{
		tKey128 Key;
		Key.Field.A = 0x01;
		Key.Field.B = 0x02;
		Key.Field.C = 0x03;
		Key.Field.D = 0x04;

		std::string Str = ToString(Key);

		utils::test::RESULT("tKey128 !=", Str == "00000004-00000003-00000002-00000001");
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////


	std::cout << std::endl;
}

	}
}
