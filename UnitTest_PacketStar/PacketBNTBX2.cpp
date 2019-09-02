#include "PacketBNTBX2_Common.h"
#include "PacketBNTBX2_Msg0802.h"
#include <iostream>

void PacketBNTBX2()
{
	{
		tPacketBNTBX2 Packet;

		tMsgBNTBX0802Rsp Msg(0x25);

		Packet.SetMsg<tMsgBNTBX0802Rsp>(Msg);

		tVectorUInt8 PacketVector = Packet.ToVector();

		tPacketBNTBX2 Packet_Decoded;

		if (tPacketBNTBX2::TryParse(PacketVector, Packet_Decoded))
		{
			std::cout << "tPacketBNTBX2::TryParse() OK\n";
		}
		else
		{
			std::cout << "tPacketBNTBX2::TryParse() ER\n";
		}
	}

	{
		tVectorUInt8 Data{ 0x5F, 0x66, 0x00, 0x00, 0x00, 0x08, 0x02, 0x01, 0x00, 0x00, 0xAA, 0x62 };

		tPacketBNTBX2 Packet;

		if (tPacketBNTBX2::TryParse(Data, Packet))
		{
			std::cout << "tPacketBNTBX2::TryParse() OK\n";

			switch (Packet.GetMsgID())
			{
			case tPacketBNTBX2::tMsgID_08:
			{
				switch (Packet.GetMsgVER())
				{
				case 0x02:
				{
					try
					{
						tMsgBNTBX0802Rsp Msg = Packet.GetMsg<tMsgBNTBX0802Rsp>();

						std::cout << "tPacketBNTBX2::GetMsg<tPayloadBNTBX0802>() OK\n";
					}
					catch (std::exception ex)
					{
						std::cout << "tPacketBNTBX2::GetMsg<tPayloadBNTBX0802>() ER: " << ex.what() << '\n';
					}

					break;
				}
				}

				break;
			}
			}
		}
	}

	{
		tVectorUInt8 Data{ 
			0x00, 0x08, 0x5F, 0x5F, //Rubbish
			0x5F, 0x66, 0x00, 0x00, 0x00, 0x08, 0x02, 0x01, 0x00, 0x00, 0xAA, 0x62 };

		tPacketBNTBX2 Packet;

		if (tPacketBNTBX2::Find(Data, Packet))
		{
			std::cout << "tPacketBNTBX2::Find() OK\n";
		}
	}

	{
		tVectorUInt8 Data{
			0x00, 0x08, 0x5F, 0x5F, //Rubbish
			0x5F, 0x66, 0x00, 0x00, 0x00, 0x08, 0x02, 0x01, 0x00, 0x00, 0xAA, 0x62,
			0x00, 0x08, 0x5F, 0x5F };

		tPacketBNTBX2 Packet;

		if (tPacketBNTBX2::Find(Data, Packet))
		{
			std::cout << "tPacketBNTBX2::Find() OK\n";
		}
	}
}