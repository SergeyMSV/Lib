#include "utilsCryptoRSA32.h"
#include "utilsTest.h"

#include <string.h>

#include <string>

#include <iostream>
#include <iomanip>

namespace utils
{
	namespace crypto
	{
		namespace RSA32
		{

std::vector<int> ToVector32(char* data, int dataSize)
{
	std::vector<int> Vector32;

	int Size = dataSize / 4;

	if ((dataSize % 4) > 0)
	{
		Size++;
	}

	int Index = 0;

	for (int i = 0; i < Size; ++i)
	{
		int Value = 0;

		Value |= (unsigned char)data[Index++];

		if (Index < dataSize)
		{
			Value |= (unsigned char)data[Index++] << 8;
		}

		if (Index < dataSize)
		{
			Value |= (unsigned char)data[Index++] << 16;
		}

		if (Index < dataSize)
		{
			Value |= (unsigned char)data[Index++] << 24;
		}

		Vector32.push_back(Value);
	}

	return Vector32;
}

std::string ToString(std::vector<int>& data)
{
	std::string Vector32;

	for (int i = 0; i < data.size(); ++i)
	{
		Vector32.push_back(data[i] & 0xFF);
		Vector32.push_back((data[i] >> 8) & 0xFF);
		Vector32.push_back((data[i] >> 16) & 0xFF);
		Vector32.push_back((data[i] >> 24) & 0xFF);
	}

	return Vector32;
}

void UnitTest()
{
	std::cout<<"\n\n""utils::crypto::RSA32::UnitTest"<<std::endl;

	char *DataArray = 0;
	std::vector<int> DataVector;

	char *PacketArray = 0;
	char *PayloadArray = 0;
	std::vector<char> PacketVector;
	std::vector<char> Payload;
	bool Result = false;

	//tPacket Packet;

	int PublicKeyN = 0x015ac7bb;//RSA KEY
	int PublicKeyE = 0x00009467;//RSA KEY

	//Test Parse: Just a packet

	char DataParse_1[] = "`1234567890-=qwertyuiop[]asdfghjkl;'zxcvbnm,./~!@##$%^^&*()_+QWERTYUIOPASDFGHJKLZXCVBNMöóêåíãøùçõúôûâàïğîëäæıÿ÷ñìèòüáşÉÖÓÊÅÍÃØÙÇÕÚÔÛÂÀÏĞÎËÄÆİß×ÑÌÈÒÜÁŞ";

	DataVector = ToVector32(DataParse_1, sizeof(DataParse_1));

	std::vector<int> EncryptedMsg = utils::crypto::RSA32::Encrypt(DataVector, PublicKeyE, PublicKeyN);

	std::vector<int> DecryptedMsg = utils::crypto::RSA32::Decrypt(EncryptedMsg, PublicKeyE, PublicKeyN);

	std::string DataParse_1_String = ToString(DecryptedMsg);

	std::cout << DataParse_1 << std::endl;
	std::cout << DataParse_1_String << std::endl;

	Result = DataVector == DecryptedMsg;

	utils::test::RESULT("Parse: Just a packet", Result);


	std::cout<<std::endl;
}

		}
	}
}
