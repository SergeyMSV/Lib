#include "utilsPacketNMEA.h"
#include "utilsBase.h"
#include "utilsCRC.h"

namespace utils
{
	namespace packet_NMEA
	{

const int PacketSizeMax = 91;//Actually GGA can contain fields LAT and LON of 11 and 12 bytes respectively, therfore GGA will be $GPGGA,192800.000,5555.415900,N,03745.062600,E,1,07,01.9,00310.5,M,0014.4,M,000.0,0000*47 (88 + 3("$",<CR>,<LF>) = 91)
//const int PacketSizeMax = 85;
///////////////////////////////////////////////////////////////////////////////////////////////////
bool VerifyPacketFormat(std::vector<char>& packet)
{
	if (packet.size() >= ContainerSize && (*packet.begin() == '$' || *packet.begin() == '!') && *(packet.end() - 5) == '*' && *(packet.end() - 2) == 0x0D && *(packet.end() - 1) == 0x0A)
	{
		for (size_t i = 1; i < packet.size() - 5; ++i)
		{
			char Byte = packet[i];

			if ((Byte >= 0x20 && Byte < 0x7E && Byte != 0x0D && Byte != 0x0A && Byte != '$' && Byte != '*' && Byte != '!' && Byte != '\\' && Byte != '^') != true)
			{
				return false;
			}
		}

		return true;
	}

	return false;
}

bool VerifyPacket(std::vector<char>& packet)
{
	if (VerifyPacketFormat(packet))
	{
		unsigned char CRC = utils::crc::CRC08_NMEA(&packet[1], packet.size() - 6);//*xx\xd\xa

		char StrCRC[3];
		StrCRC[0] = *(packet.end() - 4);
		StrCRC[1] = *(packet.end() - 3);
		StrCRC[2] = 0;

		unsigned char CRCReceived = (unsigned char)strtoul(StrCRC, 0, 16);

		return CRC == CRCReceived;
	}

	return false;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<char> FindPacket(std::vector<char>& receivedData)
{
	std::vector<char> Packet;

	unsigned int ReceivedStxPos = 0;
	unsigned int ReceivedEtxPos = 0;

	while (1)
	{
		while (ReceivedStxPos < receivedData.size() && receivedData[ReceivedStxPos] != '$' && receivedData[ReceivedStxPos] != '!')
		{
			ReceivedStxPos++;
		}

		if (ReceivedStxPos >= receivedData.size())
		{
			break;
		}

		if (receivedData.size() - ReceivedStxPos >= ContainerSize)
		{
			ReceivedEtxPos = ReceivedStxPos;

			while (ReceivedEtxPos < receivedData.size() && receivedData[ReceivedEtxPos] != '*')
			{
				ReceivedEtxPos++;
			}

			if (ReceivedEtxPos + 4 >= receivedData.size() || ReceivedStxPos >= ReceivedEtxPos)//*xx\xa\xd
			{
				break;
			}

			unsigned int PacketSize = ReceivedEtxPos - ReceivedStxPos + 5;//- [ETX + CRC + 0x0D + 0x0A] (*xx\xd\xa)

			if (PacketSize <= PacketSizeMax && receivedData.size() - ReceivedStxPos >= PacketSize)
			{
				Packet = std::vector<char>(receivedData.begin() + ReceivedStxPos, receivedData.begin() + ReceivedStxPos + PacketSize);

				if (VerifyPacket(Packet))
				{
					receivedData.erase(receivedData.begin(), receivedData.begin() + ReceivedStxPos + PacketSize);

					break;
				}
				else
				{
					Packet = std::vector<char>();

					ReceivedStxPos++;
				}
			}
			else
			{
				ReceivedStxPos++;
			}
		}
		else
		{
			break;
		}
	}

	return Packet;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
tPacket::tPacket()
{
	Encapsulation = false;

	Payload = std::vector<std::string>(0);
}

tPacket::tPacket(int payloadItemQty, bool encapsulation)
{
	Encapsulation = encapsulation;

	Payload = std::vector<std::string>(payloadItemQty);
}

tPacket::tPacket(std::string address, int payloadItemQty, bool encapsulation)
{
	Encapsulation = encapsulation;

	Address = address;

	Payload = std::vector<std::string>(payloadItemQty);
}

tPacket::tPacket(std::string address, std::vector<std::string>& payload, bool encapsulation)
{
	Encapsulation = encapsulation;

	Address = address;

	Payload = payload;
}

bool tPacket::TryParse(std::vector<char>& receivedPacket, tPacket& packet)
{
	if (receivedPacket.size() >= ContainerSize)
	{
		int ItemsQty = 0;

		for (size_t i = 0; i < receivedPacket.size(); ++i)
		{
			if (receivedPacket[i] == ',')
			{
				ItemsQty++;
			}
		}

		packet = tPacket(ItemsQty);

		packet.Encapsulation = *receivedPacket.begin() == '!';

		std::vector<char>::iterator receivedPacketIterator = receivedPacket.begin() + 1;

		std::vector<char> LocalVector;

		for (; receivedPacketIterator != receivedPacket.end(); receivedPacketIterator++)
		{
			if (*receivedPacketIterator == '*' || *receivedPacketIterator == 0x0D || *receivedPacketIterator == 0x0A)
			{
				break;
			}

			if (*receivedPacketIterator != ',')
			{
				packet.Address.push_back(*receivedPacketIterator);
			}
			else
			{
				receivedPacketIterator++;

				break;
			}
		}

		for (int i = 0; i < ItemsQty; ++i)
		{
			for (; receivedPacketIterator != receivedPacket.end(); receivedPacketIterator++)
			{
				if (*receivedPacketIterator == '*' || *receivedPacketIterator == 0x0D || *receivedPacketIterator == 0x0A)
				{
					break;
				}

				if (*receivedPacketIterator != ',')
				{
					packet.Payload[i].push_back(*receivedPacketIterator);
				}
				else
				{
					receivedPacketIterator++;

					break;
				}
			}
		}

		return true;
	}

	return false;
}

std::vector<char> tPacket::ToVector()
{
	size_t PayloadSize = 0;

	for (size_t i = 0; i < Payload.size(); ++i)
	{
		PayloadSize += Payload[i].size() + 1;
	}

	std::vector<char> Packet;

	Packet.reserve(ContainerSize + Address.size() + PayloadSize);

	Packet.push_back(Encapsulation ? '!' : '$');

	Packet.insert(Packet.end(), Address.begin(), Address.end());

	for (size_t i = 0; i < Payload.size(); ++i)
	{
		Packet.push_back(',');

		Packet.insert(Packet.end(), Payload[i].begin(), Payload[i].end());
	}

	unsigned char CRC = utils::crc::CRC08_NMEA(Packet.begin() + 1, Packet.end());

	Packet.push_back('*');	

	char StrCRC[5];
	sprintf_s(StrCRC, "%02X", CRC);

	Packet.push_back(StrCRC[0]);
	Packet.push_back(StrCRC[1]);

	Packet.push_back(0x0D);
	Packet.push_back(0x0A);

	return Packet;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
	}
}