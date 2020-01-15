#include "utilsLog.h"
#include "utilsTest.h"

#include <iostream>

class tLogger : public utils::tLog
{
protected:
	virtual void WriteLog(const std::string& msg, bool timestamp, bool showAlways) override final
	{
		std::cout << "[LOG " << " timestamp=" << timestamp << " showAlways=" << showAlways << " ]" << msg  << std::endl;
	}
};

namespace utils
{
	namespace unit_test
	{

void UnitTest_tLog()
{
	std::cout << "\n""utils::tLog" << std::endl;

	bool Result = false;

	//Test 1
	{
		tLogger Log;

		Log.Write("Write");
		Log.WriteLine("WriteLine");
		Log.WriteLineArg(true, "WriteLineArg %d", 123);
		Log.WriteErrLine("WriteErrLine");
		Log.WriteHex("WriteHex", { 0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F });
		Log.WriteInfoBlock("WriteInfoBlock");
		Log.WriteInfoLine("WriteInfoLine");
		Log.WriteInfoLineArg(true, "WriteInfoLineArg %d", 456);

		//Result = true;

		//utils::test::RESULT("Test 1", Result);
	}

	//Test 1
	/*{
		{
			tMutex Mtx;

			{
				tMutexLockGuard MtxLockGuard(&Mtx);
			}

			{
				tMutexLockGuard MtxLockGuard(&Mtx);
			}
		}

		Result = true;

		utils::test::RESULT("Test 1", Result);
	}*/


	std::cout << std::endl;
}

	}
}
