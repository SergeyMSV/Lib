namespace utils
{
	namespace packet_bntbx
	{
		namespace unit_test
		{
			void UnitTest_PacketBNTBX2();
		}
	}
}

void UnitTest_PacketBNTBX2_Msg0802();

int main()
{
	utils::packet_bntbx::unit_test::UnitTest_PacketBNTBX2();

	UnitTest_PacketBNTBX2_Msg0802();

	return 0;
}