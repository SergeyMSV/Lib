#include "utilsPacketNMEA.h"

#include "utilsBase.h"
#include "utilsTest.h"

#include <iostream>
#include <iomanip>

namespace utils
{

void UnitTest_PacketNMEAPayload()
{
	std::cout << "\n""utils::packet::tPacketNMEA Payload\n";
/*
	typedef utils::packet::tPacket<utils::packet_NMEA::tFormatNMEA, utils::packet_NMEA::tPayloadCommon> tPacketNMEA;

	UnitTest_PacketNMEA_Find<tPacketNMEA>("Parse CRC: Just a packet",
		"$GPGSV,3,1,10,23,38,230,44,29,71,156,47,07,29,116,41,08,09,081,36*7F\xd\xa",
		"$GPGSV,3,1,10,23,38,230,44,29,71,156,47,07,29,116,41,08,09,081,36*7F\xd\xa");

	UnitTest_PacketNMEA_Find<tPacketNMEA>("Parse CRC: Rubbish",
		"GNGG$GNGG$GNGGA,221$GPGSV,3,1,10,23,38,230,44,29,71,156,47,07,29,116,41,08,09,081,36*7F\xd\xa,081,36*7F\xd\xa",
		"$GPGSV,3,1,10,23,38,230,44,29,71,156,47,07,29,116,41,08,09,081,36*7F\xd\xa");

	UnitTest_PacketNMEA_Find<tPacketNMEA>("Parse CRC: Wrong Packet + Right Packet",
		"$GPGSV,3,1,10,23,38,230,44,29,21,156,47,07,29,116,41,08,09,081,36*7F\xd\xa$GNGGA,221325.000,,,,,0,0,,,M,,M,,*53\xd\xa",
		"$GNGGA,221325.000,,,,,0,0,,,M,,M,,*53\xd\xa");

	UnitTest_PacketNMEA_Find<tPacketNMEA>("Parse CRC: GGA PayloadSize=84 (more than stipulated in NMEA)",
		"$GPGGA,192758.000,5555.4159,N,03745.0626,E,1,08,01.0,00309.6,M,0014.4,M,000.0,0000*48\xd\xa",
		"$GPGGA,192758.000,5555.4159,N,03745.0626,E,1,08,01.0,00309.6,M,0014.4,M,000.0,0000*48\xd\xa");

	UnitTest_PacketNMEA_Find<tPacketNMEA>("Parse CRC: Find GGA 1",
		"$GPGGA,090210.000,5539.564975,N,03732.411956,E,1,13,0.90,231.400,M,14.535,M,,*62\xd\xa",
		"$GPGGA,090210.000,5539.564975,N,03732.411956,E,1,13,0.90,231.400,M,14.535,M,,*62\xd\xa");

	UnitTest_PacketNMEA_Find<tPacketNMEA>("Parse CRC: Find RMC 1",
		"$GNRMC,090210.000,A,5539.564975,N,03732.411956,E,0.03,274.40,120517,,,A*71\xd\xa",
		"$GNRMC,090210.000,A,5539.564975,N,03732.411956,E,0.03,274.40,120517,,,A*71\xd\xa");

	UnitTest_PacketNMEA_Parse<tPacketNMEA>("Parse CRC: Parse RMC 1",
		"$GNRMC,090210.000,A,5539.564975,N,03732.411956,E,0.03,274.40,120517,,,A*71\xd\xa",
		{ "GNRMC", "090210.000", "A", "5539.564975", "N", "03732.411956", "E", "0.03", "274.40", "120517", "", "", "A" });

	UnitTest_PacketNMEA_Make<tPacketNMEA>("Parse CRC: Make GNRMC",
		{ "GNRMC", "090210.000", "A", "5539.564975", "N", "03732.411956", "E", "0.03", "274.40", "120517", "", "", "A" });

	UnitTest_PacketNMEA_Make<tPacketNMEA>("Parse CRC: Make MYRMC Empty",
		{ "MYRMC" });

	UnitTest_PacketNMEA_Make<tPacketNMEA>("Parse CRC: Make MYRMC 1",
		{ "MYRMC", "Preved" });

	UnitTest_PacketNMEA_Make<tPacketNMEA>("Parse CRC: Make MYRMC 2",
		{ "MYRMC", "Preved", "Medved" });

	UnitTest_PacketNMEA_Make<tPacketNMEA>("Parse CRC: Make MYRMC 2",
		{ "MYRMC", "Preved", "Medved", "Odnako" });

	std::cout << "\n""tPacketNMEABin\n";

	typedef utils::packet::tPacket<utils::packet_NMEA::tFormatNMEABin, utils::packet_NMEA::tPayloadCommon> tPacketNMEABin;

	UnitTest_PacketNMEA_Parse<tPacketNMEABin>("Parse CRC: Just a encapsulation packet",
		"!AIVDM,1,1,,1,1P000Oh1IT1svTP2r:43grwb05q4,0*01\xd\xa",
		{ "AIVDM", "1", "1", "", "1", "1P000Oh1IT1svTP2r:43grwb05q4", "0" });

	//CRC matches by chance
	//UnitTest_PacketNMEA_Parse<tPacketNMEABin>("Parse CRC: Rubbish & encapsulation packet",
	//	"!AIVDM!AIVDM!AIVDM!AIVDM!AIVDM,1,1,,1,1P000Oh1IT1svTP2r:43grwb05q4,0*01\xd\xa,081,36*7F\xd\xa",
	//	{ "AIVDM", "1", "1", "", "1", "1P000Oh1IT1svTP2r:43grwb05q4", "0" });

	//Added '5' into the header
	UnitTest_PacketNMEA_Parse<tPacketNMEABin>("Parse CRC: Rubbish & encapsulation packet",
		"!AIVDM!AIVDM!AIV5DM!AIVDM!AIVDM,1,1,,1,1P000Oh1IT1svTP2r:43grwb05q4,0*01\xd\xa,081,36*7F\xd\xa",
		{ "AIVDM", "1", "1", "", "1", "1P000Oh1IT1svTP2r:43grwb05q4", "0" });

	UnitTest_PacketNMEA_Make<tPacketNMEABin>("Parse CRC: Make MYRMC 3 encapsulation packet",
		{ "MYRMC", "Preved", "Medved", "Odnako" });
		*/


	std::cout << std::endl;
}

}
