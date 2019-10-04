namespace utils
{
	namespace unit_test
	{
		void UnitTest_Base();
		void UnitTest_CRC();
		void UnitTest_CryptoAES();
		void UnitTest_Key();
		void UnitTest_PacketBNTBX2();
		void UnitTest_PacketNMEA();
		void UnitTest_PacketStar();
		void UnitTest_PacketStar2();
		void UnitTest_Test();
	}
}

int main()
{
	using namespace utils::unit_test;

	UnitTest_Base();
	UnitTest_CRC();
	UnitTest_CryptoAES();
	UnitTest_Key();
	UnitTest_PacketBNTBX2();
	UnitTest_PacketNMEA();
	UnitTest_PacketStar();
	UnitTest_PacketStar2();
	//UnitTest_Test();

	return 0;
}