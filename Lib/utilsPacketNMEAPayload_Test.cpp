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

	tPayloadRMC<13, 10, 11, 12> Val(PacketData);

	utils::packet_NMEA::tPayloadCommon::value_type PacketData1 = Val.GetPayload();

	//UnitTest_PacketNMEAPayload_Test<tDate>();
	//UnitTest_PacketNMEAPayload_Test<tDate>("120517");
	////std::tuple<tUInt8, tUInt8, tUInt8> Args = std::make_tuple( 17, 4, 19 );
	////UnitTest_PacketNMEAPayload_Test<tDate>(Args);
	//{
	//	tDate Val(17, 4, 19);

	//	std::cout << Val.ToString() << '\n';
	//}
	//
	//typedef tTime<6> tTime6;
	//UnitTest_PacketNMEAPayload_Test<tTime6>();
	//UnitTest_PacketNMEAPayload_Test<tTime6>("192758");
	//{
	//	tTime6 Val(17, 4, 19);

	//	std::cout << Val.ToString() << '\n';
	//}

	//typedef tTime<10> tTime10;
	//UnitTest_PacketNMEAPayload_Test<tTime10>();
	//UnitTest_PacketNMEAPayload_Test<tTime10>("192758.345");
	//{
	//	tTime10 Val(17, 4, 19.524);

	//	std::cout << Val.ToString() << '\n';
	//}

	//typedef tLatitude<9> tLatitude9;
	//UnitTest_PacketNMEAPayload_Test<tLatitude9>();
	//UnitTest_PacketNMEAPayload_Test<tLatitude9>("5539.5649");
	//UnitTest_PacketNMEAPayload_Test<tLatitude9>(31.45678);

	//typedef tLatitude<11> tLatitude11;
	//UnitTest_PacketNMEAPayload_Test<tLatitude11>();
	//UnitTest_PacketNMEAPayload_Test<tLatitude11>("5539.564975");
	//UnitTest_PacketNMEAPayload_Test<tLatitude11>(31.4567834);

	//typedef tLongitude<10> tLongitude10;
	//UnitTest_PacketNMEAPayload_Test<tLongitude10>();
	//UnitTest_PacketNMEAPayload_Test<tLongitude10>("03732.4119");
	//UnitTest_PacketNMEAPayload_Test<tLongitude10>(31.45678);

	//typedef tLongitude<12> tLongitude12;
	//UnitTest_PacketNMEAPayload_Test<tLongitude12>();
	//UnitTest_PacketNMEAPayload_Test<tLongitude12>("03732.411956");
	//UnitTest_PacketNMEAPayload_Test<tLongitude12>(231.4567834);

	std::cout << std::endl;
}

}
