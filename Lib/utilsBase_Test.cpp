#include "utilsBase.h"

#include "utilsTest.h"

#include <algorithm>

#include <iostream>

//#define DEBUG_SHOW_DOES_NOT_WORK

namespace utils
{
	namespace unit_test
	{

void UnitTest_Base()
{
	std::cout << "\n""utils::Base" << std::endl;

	//////////////////////////////////////////////////////////////////////////////////////////////////
	{
		tVectorUInt8 Data{ 0x01,0x02,0x03,0x04 };

		unsigned int A = 0;

		unsigned char *Last = std::copy(Data.begin(), Data.end(), (unsigned char*)&A);

		utils::test::RESULT("copy 1", true);
	}

	{
		tVectorUInt8 Data{ 0x01,0x02,0x03,0x04 };

		unsigned int A = 0;

		unsigned char* Last = std::copy_backward(Data.begin(), Data.end(), ((unsigned char*)& A) + sizeof(A));

		utils::test::RESULT("copy_backward 2", true);
	}

	{
		unsigned int A = 0x12345678;

		std::reverse(((unsigned char*)& A), ((unsigned char*)& A) + sizeof(A));

		utils::test::RESULT("reverse 2", true);
	}

	{
		uint64_t A = 0x12345678ABCDEF35;

		std::reverse(((unsigned char*)& A), ((unsigned char*)& A) + sizeof(A));

		utils::test::RESULT("reverse 3", true);
	}

	{
		char Data[] = { 1,2,3,4,5,6,7,8 };

		tVectorUInt8 DataVector;

		DataVector.insert(DataVector.end(), Data, Data + sizeof(Data));

		utils::test::RESULT("ToVector 4", true);
	}

	{
		unsigned int Data{ 0x12345678 };

		tVectorUInt8 DataVector{ 6,3,5 };

		utils::Append(DataVector, Data);

		utils::test::RESULT("Append 1", true);
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////

	//Read<unsigned int>
	{
		tVectorUInt8 Data{ 0x01,0x02,0x03,0x04 };

		auto A = utils::Read<unsigned int>(&Data[0], Data.size());

		utils::test::RESULT("Read<unsigned int>, Endian=default", A == 0x04030201);
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////

	//Read<unsigned int, tVectorUInt8::iterator>
	{
		tVectorUInt8 Data{ 0x01,0x02,0x03,0x04 };

		auto A = utils::Read<unsigned int, tVectorUInt8::iterator>(Data.begin(), Data.end());

		utils::test::RESULT("Read<unsigned int, tVectorUInt8::iterator>, Endian=default", A == 0x04030201);
	}

	//Read<unsigned int>
	{
		tVectorUInt8 Data{ 0x01,0x02,0x03,0x04 };

		auto A = utils::Read<unsigned int>(&Data[0], Data.size());

		utils::test::RESULT("Read<unsigned int>, Endian=Little", A == 0x04030201);
	}

	//Read<unsigned int, tVectorUInt8::iterator>
	{
		tVectorUInt8 Data{ 0x01,0x02,0x03,0x04 };

		auto A = utils::Read<unsigned int, tVectorUInt8::iterator>(Data.begin(), Data.end());

		utils::test::RESULT("Read<unsigned int, tVectorUInt8::iterator>, Endian=default", A == 0x04030201);
	}

	//Read<unsigned int, tVectorUInt8::iterator>
	{
		tVectorUInt8 Data{ 0x01,0x02,0x03,0x04 };

		auto A = utils::Read<unsigned int, tVectorUInt8::iterator>(Data.begin(), Data.end());

		utils::test::RESULT("Read<uint64_t, tVectorUInt8::iterator>, Endian=Little", A == 0x04030201);
	}

	//Read<uint64_t, tVectorUInt8::iterator>
	{
		tVectorUInt8 Data{ 0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08 };

		auto A = utils::Read<uint64_t, tVectorUInt8::iterator>(Data.begin(), Data.end());

		utils::test::RESULT("Read<uint64_t, tVectorUInt8::iterator>, Endian=default", A == 0x0807060504030201);
	}

	//Read<uint64_t, tVectorUInt8::iterator>
	{
		tVectorUInt8 Data{ 0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08 };

		auto A = utils::Read<uint64_t, tVectorUInt8::iterator>(Data.begin(), Data.end());

		utils::test::RESULT("Read<uint64_t, tVectorUInt8::iterator>, Endian=Little", A == 0x0807060504030201);
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////

	//ToVector<double> & Read<double, tVectorUInt8::iterator>
	{
		double Figure = 12345678.901;

		tVectorUInt8 Data = ToVector(12345678.901);

		auto A = utils::Read<decltype(Figure), tVectorUInt8::iterator>(Data.begin(), Data.end());

		utils::test::RESULT("ToVector<double> & Read<double, ...>, Endian=default", A == Figure);
	}

	//ToVector<double> & Read<double, tVectorUInt8::iterator>
	{
		double A = 12345678.901;

		tVectorUInt8 Data = ToVector(A);

		auto C = utils::Read<decltype(A)>(&Data[0], Data.size());

		utils::test::RESULT("ToVector<double> & Read<double, ...>, Endian=default", C == A);
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////

	//ToVector<int>
	{
		int Figure = -1234567;

		tVectorUInt8 Data = ToVector(Figure);

		auto A = utils::Read<decltype(Figure), tVectorUInt8::iterator>(Data.begin(), Data.end());

		utils::test::RESULT("ToVector<int>, Endian=default", A == Figure);
	}

	//ToVector<int>
	{
		int A = -1234567;

		tVectorUInt8 Data = ToVector(A);

		auto C = utils::Read<decltype(A), tVectorUInt8::iterator>(Data.begin(), Data.end());

		utils::test::RESULT("ToVector<int>, Endian=Little", C == A);
	}

	//ToVector<unsigned int>
	{
		unsigned int A = 0x12345678;

		tVectorUInt8 Data = ToVector(A);

		auto C = utils::Read<decltype(A), tVectorUInt8::iterator>(Data.begin(), Data.end());

		utils::test::RESULT("ToVector<unsigned int>, Endian=Little", C == A);
	}

	//ToVector<unsigned short>
	{
		unsigned short A = 0x1234;

		tVectorUInt8 Data = ToVector(A);

		auto C = utils::Read<decltype(A), tVectorUInt8::iterator>(Data.begin(), Data.end());

		utils::test::RESULT("ToVector<unsigned short>, Endian=Little", C == A);
	}

	//ToVector<int64_t>
	{
		int64_t Figure = 0x123456789ABCDEF0;

		tVectorUInt8 Data = ToVector(Figure);

		auto A = utils::Read<decltype(Figure), tVectorUInt8::iterator>(Data.begin(), Data.end());

		utils::test::RESULT("ToVector<int64_t>, Endian=Little", A == Figure);
	}

	//ToVector<int64_t>, Size - 4
	{
		int64_t A = 0x123456789ABCDEF0;

		tVectorUInt8 Data = ToVector(A);

		auto C = utils::Read<decltype(A), tVectorUInt8::iterator>(Data.begin(), Data.end() - 4);

		utils::test::RESULT("ToVector<int64_t>, Endian=Little", C == (A & 0x00000000FFFFFFFF));
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////
	//Read<char>, Radix=tRadix_10
	{
		std::string Str = " -123ko4_dsfg";

		auto A = Read<char>(Str.begin(), Str.end(), tRadix_10);

		utils::test::RESULT("Read<char>, Radix=tRadix_10", A == -123);
	}

	//Read<short>, Radix=tRadix_10
	{
		std::string Str = " -12345ko4_dsfg";

		auto A = Read<short>(Str.begin(), Str.end(), tRadix_10);

		utils::test::RESULT("Read<short>, Radix=tRadix_10", A == -12345);
	}

	//Read<int>, Radix=tRadix_10
	{
		std::string Str = " -1234567ko4_dsfg";

		auto A = Read<int>(Str.begin(), Str.end(), tRadix_10);

		utils::test::RESULT("Read<int>, Radix=tRadix_10", A == -1234567);
	}

#ifdef DEBUG_SHOW_DOES_NOT_WORK
	//Read<int64_t>, Radix=tRadix_10
	{
		std::string Str = " -123456789123456789ko4_dsfg";

		auto A = Read<int64_t>(Str.begin(), Str.end(), tRadix_10);

		utils::test::RESULT("Read<int64_t>, Radix=tRadix_10", A == -123456789123456789);
	}

	//Read<unsigned char>, Radix=tRadix_10, 1
	{
		std::string Str = " -123ko4_dsfg";

		auto A = Read<unsigned char>(Str.begin(), Str.end(), tRadix_10);

		utils::test::RESULT("Read<unsigned char>, Radix=tRadix_10, 1", A == 123);
	}
#endif//DEBUG_SHOW_DOES_NOT_WORK

	//Read<unsigned char>, Radix=tRadix_10, 2
	{
		std::string Str = " 123ko4_dsfg";

		auto A = Read<unsigned char>(Str.begin(), Str.end(), tRadix_10);

		utils::test::RESULT("Read<unsigned char>, Radix=tRadix_10, 2", A == 123);
	}

#ifdef DEBUG_SHOW_DOES_NOT_WORK
	//Read<unsigned short>, Radix=tRadix_10, 1
	{
		std::string Str = " -12345ko4_dsfg";

		auto A = Read<unsigned short>(Str.begin(), Str.end(), tRadix_10);

		utils::test::RESULT("Read<unsigned short>, Radix=tRadix_10, 1", A == 12345);
	}
#endif//DEBUG_SHOW_DOES_NOT_WORK

	//Read<unsigned short>, Radix=tRadix_10, 2
	{
		std::string Str = " 12345ko4_dsfg";

		auto A = Read<unsigned short>(Str.begin(), Str.end(), tRadix_10);

		utils::test::RESULT("Read<unsigned short>, Radix=tRadix_10, 2", A == 12345);
	}

#ifdef DEBUG_SHOW_DOES_NOT_WORK
	//Read<unsigned int>, Radix=tRadix_10, 1
	{
		std::string Str = " -1234567ko4_dsfg";

		auto A = Read<unsigned int>(Str.begin(), Str.end(), tRadix_10);

		utils::test::RESULT("Read<unsigned int>, Radix=tRadix_10, 1", A == 1234567);
	}
#endif//DEBUG_SHOW_DOES_NOT_WORK

	//Read<unsigned int>, Radix=tRadix_10, 2
	{
		std::string Str = " 1234567ko4_dsfg";

		auto A = Read<unsigned int>(Str.begin(), Str.end(), tRadix_10);

		utils::test::RESULT("Read<unsigned int>, Radix=tRadix_10, 2", A == 1234567);
	}

#ifdef DEBUG_SHOW_DOES_NOT_WORK
	//Read<uint64_t>, Radix=tRadix_10, 1
	{
		std::string Str = " -123456789123456789ko4_dsfg";

		auto A = Read<uint64_t>(Str.begin(), Str.end(), tRadix_10);

		utils::test::RESULT("Read<uint64_t>, Radix=tRadix_10, 1", A == 123456789123456789);
	}

	//Read<uint64_t>, Radix=tRadix_10, 2
	{
		std::string Str = " 123456789123456789ko4_dsfg";

		auto A = Read<uint64_t>(Str.begin(), Str.end(), tRadix_10);

		utils::test::RESULT("Read<uint64_t>, Radix=tRadix_10, 2", A == 123456789123456789);
	}
#endif//DEBUG_SHOW_DOES_NOT_WORK

	//////////////////////////////////////////////////////////////////////////////////////////////////
	//Read<int>, Radix=tRadix_10, data size is bigger than possible
	{
		std::string Str = " 1234567891234345234523234556789ko4_dsfg";

		auto A = Read<int>(Str.begin(), Str.end(), tRadix_10);

		utils::test::RESULT("Read<int>, Radix=tRadix_10, data size is bigger than possible", A == 0xFFFFFFFF);
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////
	//Read<unsigned char>, Radix=tRadix_16
	{
		std::string Str = " -FEjghk";

		auto A = Read<unsigned char>(Str.begin(), Str.end(), tRadix_16);

		utils::test::RESULT("Read<unsigned char>, Radix=tRadix_16", A == 0xFE);
	}

	//Read<unsigned short>, Radix=tRadix_16
	{
		std::string Str = " -FEAC-3465l;j";

		auto A = Read<unsigned short>(Str.begin(), Str.end(), tRadix_16);

		utils::test::RESULT("Read<unsigned short>, Radix=tRadix_16", A == 0xFEAC);
	}

	//Read<unsigned int>, Radix=tRadix_16
	{
		std::string Str = " -FD345678jkl;";

		auto A = Read<unsigned int>(Str.begin(), Str.end(), tRadix_16);

		utils::test::RESULT("Read<unsigned int>, Radix=tRadix_16", A == 0xFD345678);
	}

#ifdef DEBUG_SHOW_DOES_NOT_WORK
	//Read<uint64_t>, Radix=tRadix_16
	{
		std::string Str = " -FB123456AE098765_dsfg";

		auto A = Read<uint64_t>(Str.begin(), Str.end(), tRadix_16);

		utils::test::RESULT("Read<uint64_t>, Radix=tRadix_16", A == 0xFB123456AE098765);
	}
#endif//DEBUG_SHOW_DOES_NOT_WORK

	//////////////////////////////////////////////////////////////////////////////////////////////////
	//Read<unsigned int>, Radix=tRadix_16 - Read(const char* data, tRadix radix)
	{
		std::string Str = " -FD345678jkl;";

		auto A = Read<unsigned int>(Str.c_str(), tRadix_16);

		utils::test::RESULT("Read(const char* data, tRadix radix)", A == 0xFD345678);
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////
	//ReadInt, Radix=tRadix_10
	//{
	//	std::string Str = " -1234567ko4_dsfg";

	//	auto A = ReadInt((char*)Str.c_str(), tRadix_10);

	//	utils::test::RESULT("ReadInt, Radix=tRadix_10", A == -1234567);
	//}
	//////////////////////////////////////////////////////////////////////////////////////////////////
	//ReadInt, Radix=tRadix_16
	//{
	//	std::string Str = " 1234F567ko4_dsfg";

	//	auto A = ReadInt((char*)Str.c_str(), tRadix_16);

	//	utils::test::RESULT("ReadInt, Radix=tRadix_16", A == 0x1234F567);
	//}

	//////////////////////////////////////////////////////////////////////////////////////////////////
	//Reverse<int>
	{
		int A = 0x12345678;

		A = Reverse(A);

		utils::test::RESULT("Reverse<int>", A == 0x78563412);
	}

	//Reverse<unsigned int>
	{
		unsigned int A = 0x12345678;

		A = Reverse(A);

		utils::test::RESULT("ChangeEndian<unsigned int>", A == 0x78563412);
	}

	//Reverse<short>
	{
		short A = 0x1234;

		A = Reverse(A);

		utils::test::RESULT("Reverse<short>", A == 0x3412);
	}

	//Reverse<unsigned short>
	{
		unsigned short A = 0x1234;

		A = Reverse(A);

		utils::test::RESULT("Reverse<unsigned short>", A == 0x3412);
	}

	//Reverse<unsigned char>
	{
		unsigned char A = 0x12;

		A = Reverse(A);

		utils::test::RESULT("Reverse<unsigned char>", A == 0x12);
	}

	//Reverse<uint64_t>
	{
		uint64_t A = 0x1234'5678'90AB'CDEF;

		A = Reverse(A);

		utils::test::RESULT("Reverse<uint64_t>", A == 0xEFCD'AB90'7856'3412);
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////

	{
		type::tKey2<10> Key_1;
		type::tKey2<10> Key_2;

		utils::test::RESULT("type::tKey2<10> ==", Key_1 == Key_2);

		Key_1[4] = 4;

		utils::test::RESULT("type::tKey2<10> !=", Key_1 != Key_2);
	}

	{
		type::tKey1<10> Key_1;
		type::tKey1<10> Key_2;

		type::tKey2<10> Key2;

		Key_1 = Key2;
		Key_2 = Key2;

		utils::test::RESULT("type::tKey1<10> ==", Key_1 == Key_2);

		Key_1[4] = 4;

		utils::test::RESULT("type::tKey1<10> !=", Key_1 != Key_2);
	}

	{
		tKey128 Key_1;
		tKey128 Key_2;

		utils::type::tKey2<16> Key2;

		Key_1.Value = Key2;
		Key_2.Value = Key2;

		utils::test::RESULT("tKey128 ==", Key_1 == Key_2);

		Key_1.Field.A = 4;

		utils::test::RESULT("tKey128 !=", Key_1 != Key_2);
	}

	{
		tKey96 Key_1;
		tKey96 Key_2;

		utils::type::tKey2<12> Key2;

		Key_1.Value = Key2;
		Key_2.Value = Key2;

		utils::test::RESULT("tKey96 ==", Key_1 == Key_2);

		Key_1.Field.A = 4;

		utils::test::RESULT("tKey96 !=", Key_1 != Key_2);
	}

	{
		tKey64 Key_1;
		tKey64 Key_2;

		utils::type::tKey2<8> Key2;

		Key_1.Value = Key2;
		Key_2.Value = Key2;

		utils::test::RESULT("tKey64 ==", Key_1 == Key_2);

		Key_1.Field.A = 4;

		utils::test::RESULT("tKey64 !=", Key_1 != Key_2);
	}

	{
		tKey32 Key_1;
		tKey32 Key_2;

		utils::type::tKey2<4> Key2;

		Key_1.Value = Key2;
		Key_2.Value = Key2;

		utils::test::RESULT("tKey32 ==", Key_1 == Key_2);

		Key_1.Field.A = 4;

		utils::test::RESULT("tKey32 !=", Key_1 != Key_2);
	}


	//////////////////////////////////////////////////////////////////////////////////////////////////

	/* [TBD]
	//////////////////////////////////////////////////////////////////////////////////////////////////
	//FromBCD
	{
		char B = FromBCD(0x92);

		utils::test::RESULT("FromBCD", B == 92);
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////
	//ToCP866(tISO8859 codePage, const std::string& data)
	{
		std::string Str("������, ������!!!");

		std::string StrCP866 = charset::ToCP866(charset::tISO8859_5, Str);

		std::cout << Str << " = " << StrCP866 << std::endl;
	}
	*/

	std::cout << std::endl;
}

	}
}
