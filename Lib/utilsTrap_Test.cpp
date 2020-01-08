#include "utilsTrap.h"
#include "utilsTest.h"

#include <iostream>

namespace utils
{
	namespace unit_test
	{

void UnitTest_Trap()
{
	std::cout<<"\n\n""utils::trap::tTrap"<<std::endl;

	using namespace trap;

	//Test: The same
	{
		static const char Msg[] = "\xd\xa""CLOSED\xd\xa";

		tTrap<Msg, sizeof(Msg) - 1> Trap;

		char Data[] = "\xd\xa""CLOSED\xd\xa";

		std::vector<char> DataVector(Data, Data + sizeof(Data));

		bool Result = Trap.Try(DataVector);

		utils::test::RESULT("The same", Result);
	}

	//Test: Reverse
	{
		static const char Msg[] = "\xa\xd""DESOLC\xa\xd";

		tTrap<Msg, sizeof(Msg) - 1, true> Trap;

		char Data[] = "\xd\xa""CLOSED\xd\xa";

		std::vector<char> DataVector(Data, Data + sizeof(Data));

		bool Result = Trap.Try(DataVector);

		utils::test::RESULT("Reverse", Result);
	}

	//Test: 0x0D + the same
	{
		static const char Msg[] = "\xd\xa""CLOSED\xd\xa";

		tTrap<Msg, sizeof(Msg) - 1> Trap;

		char Data[] = "\xd\xd\xa""CLOSED\xd\xa";

		std::vector<char> DataVector(Data, Data + sizeof(Data));

		bool Result = Trap.Try(DataVector);

		utils::test::RESULT("0x0D + the same", Result);
	}

	//Test: 0x0D + 0x0D + the same
	{
		static const char Msg[] = "\xd\xa""CLOSED\xd\xa";

		tTrap<Msg, sizeof(Msg) - 1> Trap;

		char Data[] = "\xd\xd\xd\xa""CLOSED\xd\xa";

		std::vector<char> DataVector(Data, Data + sizeof(Data));

		bool Result = Trap.Try(DataVector);

		utils::test::RESULT("0x0D + 0x0D + the same", Result);
	}


	//Test: No first 0x0D
	{
		static const char Msg[] = "\xd\xa""CLOSED\xd\xa";

		tTrap<Msg, sizeof(Msg) - 1> Trap;

		char Data[] = "\xa""CLOSED\xd\xa";

		std::vector<char> DataVector(Data, Data + sizeof(Data));

		bool Result = !Trap.Try(DataVector);

		utils::test::RESULT("no first 0x0D", Result);
	}

	//Test: 0x0D + 0x0D + the same + rubbush
	{
		static const char Msg[] = "\xd\xa""CLOSED\xd\xa";

		tTrap<Msg, sizeof(Msg) - 1> Trap;

		char Data[] = "\xd\xd\xd\xa""CLOSED\xd\xa""CLOX";

		std::vector<char> DataVector(Data, Data + sizeof(Data));

		bool Result = Trap.Try(DataVector);

		utils::test::RESULT("0x0D + 0x0D + the same + rubbush", Result);
	}

	//Test: 0x0D + 0x0D + rubbish + the same + rubbush
	{
		static const char Msg[] = "\xd\xa""CLOSED\xd\xa";

		tTrap<Msg, sizeof(Msg) - 1> Trap;

		char Data[] = "\xd\xd\xd\xa""CLO""\xd\xa""CLOSED\xd\xa""CLOX";

		std::vector<char> DataVector(Data, Data + sizeof(Data));

		bool Result = Trap.Try(DataVector);

		utils::test::RESULT("0x0D + 0x0D + rubbish + the same + rubbush", Result);
	}


	std::cout << std::endl;
}

	}
}