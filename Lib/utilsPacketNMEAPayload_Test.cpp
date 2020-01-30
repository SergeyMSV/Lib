#include "utilsPacketNMEAPayload.h"

#include "utilsBase.h"
#include "utilsTest.h"

#include <iostream>
#include <iomanip>
//#include <tuple>

namespace utils
{

//template <class T>
//void UnitTest_PacketNMEAPayload_Test()
//{
//	T Val;
//	std::cout << Val.ToString() << '\n';
//}
//
//template <class T, class TArg>
//void UnitTest_PacketNMEAPayload_Test(TArg arg)
//{
//	T Val(arg);
//	std::cout << Val.ToString() << '\n';
//}

void UnitTest_PacketNMEAPayload()
{
	std::cout << "\n""utils::packet_NMEA::Payload\n";

	using namespace utils::packet_NMEA;

	typedef utils::packet::tPacket<utils::packet_NMEA::tFormatNMEA, utils::packet_NMEA::tPayloadCommon> tPacketNMEA;
	tPacketNMEA lalal;

	tVectorUInt8 Vect = lalal.ToVector();
	std::string Raw("$GNRMC,090210.000,A,5539.564975,N,03732.411956,E,0.03,274.40,120517,,,A*71\xd\xa");
	tVectorUInt8 DataVector(Raw.begin(), Raw.end());

	tPacketNMEA Packet;

	bool Result = tPacketNMEA::Find(DataVector, Packet);

	utils::packet_NMEA::tPayloadCommon::value_type PacketData = Packet.GetPayload();

	typedef tPayloadRMC<13, 10, 11, 12> tMsgRMC;

	tMsgRMC Val(PacketData);

	if (Val.GNSS.Value != tMsgRMC::gnss_type::tGNSS_State::UNKNOWN)//Parsed!!
	{
		utils::packet_NMEA::tPayloadCommon::value_type PacketData1 = Val.GetPayload();

		tPacketNMEA Packet2(PacketData1);

		tVectorUInt8 RawPacket = Packet2.ToVector();

		std::cout << "Preved: " << std::string(RawPacket.cbegin(), RawPacket.cend());//C++14
	}



	//typedef tLongitude<12> tLongitude12;
	//UnitTest_PacketNMEAPayload_Test<tLongitude12>();
	//UnitTest_PacketNMEAPayload_Test<tLongitude12>("03732.411956");
	//UnitTest_PacketNMEAPayload_Test<tLongitude12>(231.4567834);


	std::cout << std::endl;
}

}
