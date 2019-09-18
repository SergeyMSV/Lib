#include "utilsPacketNMEA.h"

#include "utilsBase.h"
#include "utilsTest.h"

#include <string.h>

#include <iostream>
#include <iomanip>

namespace utils
{
	namespace unit_test
	{

void UnitTest_PacketNMEA()
{
	typedef utils::packet::tPacket<utils::packet_NMEA::tFormatNMEA, utils::packet_NMEA::tPayloadCommon> tPacketNMEA;

	//Test Parse CRC: Just a packet
	{
		std::string DataMsg("$GPGSV,3,1,10,23,38,230,44,29,71,156,47,07,29,116,41,08,09,081,36*7F\xd\xa");

		tVectorUInt8 Data(DataMsg.begin(), DataMsg.end());

		tPacketNMEA Packet;

		bool Result = tPacketNMEA::Find(Data, Packet);

		{
			tVectorUInt8 A = Packet.ToVector();

			tVectorUInt8 B(DataMsg.begin(), DataMsg.end());

			Result = Result &&
				A == B;
		}

		utils::test::RESULT("Parse CRC: Just a packet", Result);
	}

	////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////

	std::cout << "\n""UnitTest" << std::endl;

	//Test Parse CRC: Just a packet
	{
		char Data[] = "$GPGSV,3,1,10,23,38,230,44,29,71,156,47,07,29,116,41,08,09,081,36*7F\xd\xa";

		std::vector<char> DataVector(Data, Data + sizeof(Data) - 1);

		std::vector<char> PacketVector = utils::packet_NMEA::FindPacket(DataVector);

		DataVector = std::vector<char>(Data, Data + sizeof(Data) - 1);

		bool Result = PacketVector == DataVector;

		utils::test::RESULT("Parse CRC: Just a packet", Result);
	}

	//Test Parse CRC: Just a encapsulation packet
	{
		char Data[] = "!AIVDM,1,1,,1,1P000Oh1IT1svTP2r:43grwb05q4,0*01\xd\xa";

		std::vector<char> DataVector(Data, Data + sizeof(Data) - 1);

		std::vector<char> PacketVector = utils::packet_NMEA::FindPacket(DataVector);

		DataVector = std::vector<char>(Data, Data + sizeof(Data) - 1);

		bool Result = PacketVector == DataVector;

		utils::test::RESULT("Parse CRC: Just a encapsulation packet", Result);
	}

	//Test Parse CRC: Rubbish
	{
		char Data[] = { "GNGG$GNGG$GNGGA,221$GPGSV,3,1,10,23,38,230,44,29,71,156,47,07,29,116,41,08,09,081,36*7F\xd\xa,081,36*7F\xd\xa" };

		std::vector<char> DataVector(Data, Data + sizeof(Data) - 1);

		std::vector<char> PacketVector = utils::packet_NMEA::FindPacket(DataVector);

		char Data2[] = "$GPGSV,3,1,10,23,38,230,44,29,71,156,47,07,29,116,41,08,09,081,36*7F\xd\xa";

		DataVector = std::vector<char>(Data2, Data2 + sizeof(Data2) - 1);

		bool Result = PacketVector == DataVector;

		utils::test::RESULT("Parse CRC: Rubbish", Result);
	}

	//Test Parse CRC: Rubbish & encapsulation packet
	{
		char Data[] = { "!AIVDM!AIVDM!AIVDM!AIVDM!AIVDM,1,1,,1,1P000Oh1IT1svTP2r:43grwb05q4,0*01\xd\xa,081,36*7F\xd\xa" };

		std::vector<char> DataVector(Data, Data + sizeof(Data) - 1);

		std::vector<char> PacketVector = utils::packet_NMEA::FindPacket(DataVector);

		char Data2[] = "!AIVDM,1,1,,1,1P000Oh1IT1svTP2r:43grwb05q4,0*01\xd\xa";

		DataVector = std::vector<char>(Data2, Data2 + sizeof(Data2) - 1);

		bool Result = PacketVector == DataVector;

		utils::test::RESULT("Parse CRC: Rubbish & encapsulation packet", Result);
	}

	//Test Parse CRC: Wrong Packet + Right Packet
	{
		char Data[] = { "$GPGSV,3,1,10,23,38,230,44,29,21,156,47,07,29,116,41,08,09,081,36*7F\xd\xa$GNGGA,221325.000,,,,,0,0,,,M,,M,,*53\xd\xa" };

		std::vector<char> DataVector(Data, Data + sizeof(Data) - 1);

		std::vector<char> PacketVector = utils::packet_NMEA::FindPacket(DataVector);

		char Data2[] = "$GNGGA,221325.000,,,,,0,0,,,M,,M,,*53\xd\xa";

		DataVector = std::vector<char>(Data2, Data2 + sizeof(Data2) - 1);

		bool Result = PacketVector == DataVector;

		utils::test::RESULT("Parse CRC: Wrong Packet + Right Packet", Result);
	}

	//Test Parse CRC: GGA PayloadSize=84 that's more than stipulated in standard NMEA
	{
		char Data[] = { "$GPGGA,192758.000,5555.4159,N,03745.0626,E,1,08,01.0,00309.6,M,0014.4,M,000.0,0000*48\xd\xa" };

		std::vector<char> DataVector(Data, Data + sizeof(Data) - 1);

		std::vector<char> PacketVector = utils::packet_NMEA::FindPacket(DataVector);

		char Data2[] = "$GPGGA,192758.000,5555.4159,N,03745.0626,E,1,08,01.0,00309.6,M,0014.4,M,000.0,0000*48\xd\xa";

		DataVector = std::vector<char>(Data2, Data2 + sizeof(Data2) - 1);

		bool Result = PacketVector == DataVector;

		utils::test::RESULT("Parse CRC: GGA PayloadSize=84 (more than stipulated in NMEA)", Result);		
	}

	//Test Parse CRC: Find GGA 1
	{
		char Data[] = { "$GPGGA,090210.000,5539.564975,N,03732.411956,E,1,13,0.90,231.400,M,14.535,M,,*62\xd\xa" };

		std::vector<char> DataVector(Data, Data + sizeof(Data) - 1);

		std::vector<char> PacketVector = utils::packet_NMEA::FindPacket(DataVector);

		char Data2[] = "$GPGGA,090210.000,5539.564975,N,03732.411956,E,1,13,0.90,231.400,M,14.535,M,,*62\xd\xa";

		DataVector = std::vector<char>(Data2, Data2 + sizeof(Data2) - 1);

		bool Result = PacketVector == DataVector;

		utils::test::RESULT("Parse CRC: Find GGA 1", Result);
	}

	//Test Parse CRC: Find RMC 1
	{
		char Data[] = { "$GNRMC,090210.000,A,5539.564975,N,03732.411956,E,0.03,274.40,120517,,,A*71\xd\xa" };

		std::vector<char> DataVector(Data, Data + sizeof(Data) - 1);

		std::vector<char> PacketVector = utils::packet_NMEA::FindPacket(DataVector);

		char Data2[] = "$GNRMC,090210.000,A,5539.564975,N,03732.411956,E,0.03,274.40,120517,,,A*71\xd\xa";

		DataVector = std::vector<char>(Data2, Data2 + sizeof(Data2) - 1);

		bool Result = PacketVector == DataVector;

		utils::test::RESULT("Parse CRC: Find RMC 1", Result);
	}

	//Test Parse CRC: Parse RMC 1
	{
		char Data[] = { "$GNRMC,090210.000,A,5539.564975,N,03732.411956,E,0.03,274.40,120517,,,A*71\xd\xa" };

		std::vector<char> DataVector(Data, Data + sizeof(Data) - 1);

		std::vector<char> PacketVector = utils::packet_NMEA::FindPacket(DataVector);

		utils::packet_NMEA::tPacket Packet_Decoded;

		bool Result = utils::packet_NMEA::tPacket::TryParse(PacketVector, Packet_Decoded);

		Result = Result &&
			Packet_Decoded.Encapsulation == false &&
			Packet_Decoded.Address == "GNRMC" &&
			Packet_Decoded.Payload.size() == 12;

		utils::test::RESULT("Parse CRC: Parse RMC 1", Result);
	}

	//Test Parse CRC: Make MYRMC Empty
	{
		utils::packet_NMEA::tPacket Packet;

		Packet.Address = "MYRMC";

		std::vector<char> DataVector = Packet.ToVector();

		std::vector<char> PacketVector = utils::packet_NMEA::FindPacket(DataVector);

		utils::packet_NMEA::tPacket Packet_Decoded;

		bool Result = utils::packet_NMEA::tPacket::TryParse(PacketVector, Packet_Decoded);

		Result = Result &&
			Packet_Decoded.Encapsulation == false &&
			Packet_Decoded.Address == "MYRMC" &&
			Packet_Decoded.Payload.size() == 0;

		utils::test::RESULT("Parse CRC: Make MYRMC Empty", Result);
	}

	//Test Parse CRC: Make MYRMC 1
	{
		utils::packet_NMEA::tPacket Packet(1);

		Packet.Address = "MYRMC";

		Packet.Payload[0] = "Preved";

		std::vector<char> DataVector = Packet.ToVector();

		std::vector<char> PacketVector = utils::packet_NMEA::FindPacket(DataVector);

		utils::packet_NMEA::tPacket Packet_Decoded;

		bool Result = utils::packet_NMEA::tPacket::TryParse(PacketVector, Packet_Decoded);

		Result = Result &&
			Packet_Decoded.Encapsulation == false &&
			Packet_Decoded.Address == "MYRMC" &&
			Packet_Decoded.Payload.size() == 1 &&
			Packet_Decoded.Payload[0] == "Preved";

		utils::test::RESULT("Parse CRC: Make MYRMC 1", Result);
	}

	//Test Parse CRC: Make MYRMC 2
	{
		utils::packet_NMEA::tPacket Packet(2);

		Packet.Address = "MYRMC";

		Packet.Payload[0] = "Preved";
		Packet.Payload[1] = "Medved";

		std::vector<char> DataVector = Packet.ToVector();

		std::vector<char> PacketVector = utils::packet_NMEA::FindPacket(DataVector);

		utils::packet_NMEA::tPacket Packet_Decoded;

		bool Result = utils::packet_NMEA::tPacket::TryParse(PacketVector, Packet_Decoded);

		Result = Result &&
			Packet_Decoded.Encapsulation == false &&
			Packet_Decoded.Address == "MYRMC" &&
			Packet_Decoded.Payload.size() == 2 &&
			Packet_Decoded.Payload[0] == "Preved" &&
			Packet_Decoded.Payload[1] == "Medved";

		utils::test::RESULT("Parse CRC: Make MYRMC 2", Result);
	}

	//Test Parse CRC: Make MYRMC 3
	{
		utils::packet_NMEA::tPacket Packet;

		Packet.Address = "MYRMC";

		Packet.Payload.push_back("Preved");
		Packet.Payload.push_back("Medved");
		Packet.Payload.push_back("Odnako");

		std::vector<char> DataVector = Packet.ToVector();

		std::vector<char> PacketVector = utils::packet_NMEA::FindPacket(DataVector);

		utils::packet_NMEA::tPacket Packet_Decoded;

		bool Result = utils::packet_NMEA::tPacket::TryParse(PacketVector, Packet_Decoded);

		Result = Result &&
			Packet_Decoded.Encapsulation == false &&
			Packet_Decoded.Address == "MYRMC" &&
			Packet_Decoded.Payload.size() == 3 &&
			Packet_Decoded.Payload[0] == "Preved" &&
			Packet_Decoded.Payload[1] == "Medved" &&
			Packet_Decoded.Payload[2] == "Odnako";

		utils::test::RESULT("Parse CRC: Make MYRMC 3", Result);
	}

	//Test Parse CRC: Make MYRMC 3 encapsulation packet
	{
		utils::packet_NMEA::tPacket Packet;

		Packet.Encapsulation = true;

		Packet.Address = "MYRMC";

		Packet.Payload.push_back("Preved");
		Packet.Payload.push_back("Medved");
		Packet.Payload.push_back("Odnako");

		std::vector<char> DataVector = Packet.ToVector();

		std::vector<char> PacketVector = utils::packet_NMEA::FindPacket(DataVector);

		utils::packet_NMEA::tPacket Packet_Decoded;

		bool Result = utils::packet_NMEA::tPacket::TryParse(PacketVector, Packet_Decoded);

		Result = Result &&
			Packet_Decoded.Encapsulation == true &&
			Packet_Decoded.Address == "MYRMC" &&
			Packet_Decoded.Payload.size() == 3 &&
			Packet_Decoded.Payload[0] == "Preved" &&
			Packet_Decoded.Payload[1] == "Medved" &&
			Packet_Decoded.Payload[2] == "Odnako";

		utils::test::RESULT("Parse CRC: Make MYRMC 3 encapsulation packet", Result);
	}


	std::cout << std::endl;
}

	}
}
