#include "PacketStar2_Common.h"
#include <iostream>

void PacketStar2()
{
	{
		tPacketStar2 Packet;

		//Packet.

		tVectorUInt8 PacketVector = Packet.ToVector();
	}

	{
		tVectorUInt8 Data{ 0x2A, 0x09, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0xB0, 0x8D };

		tPacketStar2 Packet;

		if (tPacketStar2::TryParse(Data, Packet))
		{
			std::cout << "tPacketStar2::TryParse() OK\n";
		}
	}

	{
		tVectorUInt8 Data{
			0x2A, 0x09, 0x00,
			0x2A, 0x09, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0xB0, 0x8D };

		tPacketStar2 Packet;

		if (tPacketStar2::Find(Data, Packet))
		{
			std::cout << "tPacketStar2::Find() OK\n";
		}
	}

	{
		tVectorUInt8 Data{
			0x2A, 0x09, 0x00,
			0x2A, 0x09, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0xB0, 0x8D,
			0x2A, 0x09, 0x00 };

		tPacketStar2 Packet;

		if (tPacketStar2::Find(Data, Packet))
		{
			std::cout << "tPacketStar2::Find() OK\n";
		}
	}
}