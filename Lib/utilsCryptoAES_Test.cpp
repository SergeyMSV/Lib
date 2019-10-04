#include "utilsCryptoAES.h"
#include "utilsConverter.h"
#include "utilsTest.h"

#include <string.h>

#include <iostream>
#include <iomanip>

namespace utils
{
	namespace crypto
	{
		namespace AES
		{

void Dump(char *msg, unsigned char *data, int len)
{
	printf("%8.8s: ", msg);

	for (int i = 0; i < len; i++)
	{
		printf(" %2.2x", data[i]);
	}

	printf("\n");
}

tAES_CYPHER_ERR Encrypt_ecb(tAES_CYPHER mode, unsigned char *data, int len, unsigned char *key);
tAES_CYPHER_ERR Decrypt_ecb(tAES_CYPHER mode, unsigned char *data, int len, unsigned char *key);

void aes_cypher_128_test()
{
#if 1
	unsigned char buf[] = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff };
	unsigned char key[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };
#else
	unsigned char buf[] = { 0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d, 0x31, 0x31, 0x98, 0xa2, 0xe0, 0x37, 0x07, 0x34 };
	unsigned char key[] = { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c };
#endif

	printf("\ntAES_CYPHER_128 encrypt test case:\n");
	printf("Input:\n");
	Dump("data", buf, sizeof(buf));
	Dump("key ", key, sizeof(key));
	Encrypt_ecb(tAES_CYPHER_128, buf, sizeof(buf), key);

	printf("\ntAES_CYPHER_128 decrypt test case:\n");
	printf("Input:\n");
	Dump("data", buf, sizeof(buf));
	Dump("key ", key, sizeof(key));
	Decrypt_ecb(tAES_CYPHER_128, buf, sizeof(buf), key);

	printf("Output:\n");
	Dump("data", buf, sizeof(buf));
}

void aes_cypher_192_test()
{
	unsigned char buf[] = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff };
	unsigned char key[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17 };

	printf("\ntAES_CYPHER_192 encrypt test case:\n");
	printf("Input:\n");
	Dump("data", buf, sizeof(buf));
	Dump("key ", key, sizeof(key));
	Encrypt_ecb(tAES_CYPHER_192, buf, sizeof(buf), key);

	printf("\ntAES_CYPHER_192 decrypt test case:\n");
	printf("Input:\n");
	Dump("data", buf, sizeof(buf));
	Dump("key ", key, sizeof(key));
	Decrypt_ecb(tAES_CYPHER_192, buf, sizeof(buf), key);

	printf("Output:\n");
	Dump("data", buf, sizeof(buf));
}

void aes_cypher_256_test()
{
	unsigned char buf[] = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff };
	unsigned char key[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f };
	
	printf("\ntAES_CYPHER_256 encrypt test case:\n");
	printf("Input:\n");
	Dump("data", buf, sizeof(buf));
	Dump("key ", key, sizeof(key));
	Encrypt_ecb(tAES_CYPHER_256, buf, sizeof(buf), key);

	printf("\ntAES_CYPHER_256 decrypt test case:\n");
	printf("Input:\n");
	Dump("data", buf, sizeof(buf));
	Dump("key ", key, sizeof(key));
	Decrypt_ecb(tAES_CYPHER_256, buf, sizeof(buf), key);

	printf("Output:\n");
	Dump("data", buf, sizeof(buf));
}

void UnitTest()
{
	std::cout << "\n\n""utils::crypto::AES::UnitTest" << std::endl;

#ifdef LIB_UTILS_CRYPTO_AES_PPRINTF_LOG
	aes_cypher_128_test();
	aes_cypher_192_test();
	aes_cypher_256_test();
#endif//LIB_UTILS_CRYPTO_AES_PPRINTF_LOG

	bool Result = false;


	//Test ECB: AES_128
	{
		char Data[] = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff };
		char Key[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };
		char DataENCRYPTED[] = { 0x69, 0xc4, 0xe0, 0xd8, 0x6a, 0x7b, 0x04, 0x30, 0xd8, 0xcd, 0xb7, 0x80, 0x70, 0xb4, 0xc5, 0x5a };

		std::vector<char> DataVector(Data, Data + sizeof(Data));

		std::vector<char> KeyVector(Key, Key + sizeof(Key));

		std::vector<char> DataENCRYPTEDVector(DataENCRYPTED, DataENCRYPTED + sizeof(DataENCRYPTED));

		std::vector<char> DataVectorEncrypted = DataVector;

		Result = EncryptECB(utils::crypto::AES::tAES_CYPHER_128, DataVectorEncrypted, KeyVector) == tAES_CYPHER_ERR_None;

		std::vector<char> DataVectorDecrypted = DataVectorEncrypted;

		Result = Result && DecryptECB(utils::crypto::AES::tAES_CYPHER_128, DataVectorDecrypted, KeyVector) == tAES_CYPHER_ERR_None;

		Result = Result && DataVector == DataVectorDecrypted && DataVector != DataVectorEncrypted && DataENCRYPTEDVector == DataVectorEncrypted;

		utils::test::RESULT("ECB: AES_128", Result);
	}

	//Test ECB: AES_192
	{
		char Data[] = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff };
		char Key[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17 };
		char DataENCRYPTED[] = { 0xdd, 0xa9, 0x7c, 0xa4, 0x86, 0x4c, 0xdf, 0xe0, 0x6e, 0xaf, 0x70, 0xa0, 0xec, 0x0d, 0x71, 0x91 };

		std::vector<char> DataVector(Data, Data + sizeof(Data));

		std::vector<char> KeyVector(Key, Key + sizeof(Key));

		std::vector<char> DataENCRYPTEDVector(DataENCRYPTED, DataENCRYPTED + sizeof(DataENCRYPTED));

		std::vector<char> DataVectorEncrypted = DataVector;

		Result = EncryptECB(utils::crypto::AES::tAES_CYPHER_192, DataVectorEncrypted, KeyVector) == tAES_CYPHER_ERR_None;

		std::vector<char> DataVectorDecrypted = DataVectorEncrypted;

		Result = Result && DecryptECB(utils::crypto::AES::tAES_CYPHER_192, DataVectorDecrypted, KeyVector) == tAES_CYPHER_ERR_None;

		Result = Result && DataVector == DataVectorDecrypted && DataVector != DataVectorEncrypted && DataENCRYPTEDVector == DataVectorEncrypted;

		utils::test::RESULT("ECB: AES_192", Result);
	}

	//Test ECB: AES_256
	{
		char Data[] = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff };
		char Key[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f };
		char DataENCRYPTED[] = { 0x8e, 0xa2, 0xb7, 0xca, 0x51, 0x67, 0x45, 0xbf, 0xea, 0xfc, 0x49, 0x90, 0x4b, 0x49, 0x60, 0x89 };

		std::vector<char> DataVector(Data, Data + sizeof(Data));

		std::vector<char> KeyVector(Key, Key + sizeof(Key));

		std::vector<char> DataENCRYPTEDVector(DataENCRYPTED, DataENCRYPTED + sizeof(DataENCRYPTED));

		std::vector<char> DataVectorEncrypted = DataVector;

		Result = EncryptECB(utils::crypto::AES::tAES_CYPHER_256, DataVectorEncrypted, KeyVector) == tAES_CYPHER_ERR_None;

		std::vector<char> DataVectorDecrypted = DataVectorEncrypted;

		Result = Result && DecryptECB(utils::crypto::AES::tAES_CYPHER_256, DataVectorDecrypted, KeyVector) == tAES_CYPHER_ERR_None;

		Result = Result && DataVector == DataVectorDecrypted && DataVector != DataVectorEncrypted && DataENCRYPTEDVector == DataVectorEncrypted;

		utils::test::RESULT("ECB: AES_256", Result);
	}

	//Test ECB: AES_128 - Data 16 bytes
	{
		char Data[] = "QWERTYUIOPASDFGH";//16
		char Key[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

		std::vector<char> DataVector(Data, Data + strlen(Data));

		std::vector<char> KeyVector(Key, Key + sizeof(Key));

		std::vector<char> DataVectorEncrypted = DataVector;

		Result = EncryptECB(utils::crypto::AES::tAES_CYPHER_128, DataVectorEncrypted, KeyVector) == tAES_CYPHER_ERR_None;

		std::vector<char> DataVectorDecrypted = DataVectorEncrypted;

		Result = Result && DecryptECB(utils::crypto::AES::tAES_CYPHER_128, DataVectorDecrypted, KeyVector) == tAES_CYPHER_ERR_None;

		Result = Result && DataVector == DataVectorDecrypted && DataVector != DataVectorEncrypted;

		utils::test::RESULT("ECB: AES_128 - Data 16 bytes", Result);
	}

	//Test ECB: AES_128 - Data 32 bytes
	{
		char Data[] = "QWERTYUIOPASDFGHqwertyuiopasdfgh";//32
		char Key[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

		std::vector<char> DataVector(Data, Data + strlen(Data));

		std::vector<char> KeyVector(Key, Key + sizeof(Key));

		std::vector<char> DataVectorEncrypted = DataVector;

		Result = EncryptECB(utils::crypto::AES::tAES_CYPHER_128, DataVectorEncrypted, KeyVector) == tAES_CYPHER_ERR_None;

		std::vector<char> DataVectorDecrypted = DataVectorEncrypted;

		Result = Result && DecryptECB(utils::crypto::AES::tAES_CYPHER_128, DataVectorDecrypted, KeyVector) == tAES_CYPHER_ERR_None;

		Result = Result && DataVector == DataVectorDecrypted && DataVector != DataVectorEncrypted;

		utils::test::RESULT("ECB: AES_128 - Data 32 bytes", Result);
	}

	//Test ECB: AES_128 - Data 64 bytes
	{
		char Data[] = "QWERTYUIOPASDFGHqwertyuiopasdfgh…÷” ≈Õ√ÿŸ«’⁄‘€¬¿œ–ŒÀƒ∆›ﬂ◊—Ã»“‹¡ﬁ";//64
		char Key[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

		std::vector<char> DataVector(Data, Data + strlen(Data));

		std::vector<char> KeyVector(Key, Key + sizeof(Key));

		std::vector<char> DataVectorEncrypted = DataVector;

		Result = EncryptECB(utils::crypto::AES::tAES_CYPHER_128, DataVectorEncrypted, KeyVector) == tAES_CYPHER_ERR_None;

		std::vector<char> DataVectorDecrypted = DataVectorEncrypted;

		Result = Result && DecryptECB(utils::crypto::AES::tAES_CYPHER_128, DataVectorDecrypted, KeyVector) == tAES_CYPHER_ERR_None;

		Result = Result && DataVector == DataVectorDecrypted && DataVector != DataVectorEncrypted;

		utils::test::RESULT("ECB: AES_128 - Data 64 bytes", Result);
	}

	//Test ECB: AES_128 - EncryptECB Data 24 bytes (wrong size)
	{
		char Data[] = "QWERTYUIOPASDFGHJKLZXCVB";//24
		char Key[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

		std::vector<char> DataVector(Data, Data + strlen(Data));

		std::vector<char> KeyVector(Key, Key + sizeof(Key));

		std::vector<char> DataVectorEncrypted = DataVector;

		tAES_CYPHER_ERR CERR = EncryptECB(utils::crypto::AES::tAES_CYPHER_128, DataVectorEncrypted, KeyVector);

		Result = CERR == tAES_CYPHER_ERR_DataSize;

		utils::test::RESULT("ECB: AES_128 - EncryptECB Data 24 bytes (wrong size)", Result);
	}

	//Test ECB: AES_128 - EncryptECB Key 15 bytes (wrong size)
	{
		char Data[] = "QWERTYUIOPASDFGH";//16
		char Key[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E'};

		std::vector<char> DataVector(Data, Data + strlen(Data));

		std::vector<char> KeyVector(Key, Key + sizeof(Key));

		std::vector<char> DataVectorEncrypted = DataVector;

		tAES_CYPHER_ERR CERR = EncryptECB(utils::crypto::AES::tAES_CYPHER_128, DataVectorEncrypted, KeyVector);

		Result = CERR == tAES_CYPHER_ERR_KeySize;

		utils::test::RESULT("ECB: AES_128 - EncryptECB Key 15 bytes (wrong size)", Result);
	}

	//Test ECB: AES_128 - DecryptECB Data 15 bytes (wrong size)
	{
		char Data[] = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff };
		char Key[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };

		std::vector<char> DataVector(Data, Data + sizeof(Data));

		std::vector<char> KeyVector(Key, Key + sizeof(Key));

		std::vector<char> DataVectorEncrypted = DataVector;

		Result = EncryptECB(utils::crypto::AES::tAES_CYPHER_128, DataVectorEncrypted, KeyVector) == tAES_CYPHER_ERR_None;

		std::vector<char> DataVectorDecrypted = std::vector<char>(DataVectorEncrypted.begin(), DataVectorEncrypted.end() - 1);

		tAES_CYPHER_ERR CERR = DecryptECB(utils::crypto::AES::tAES_CYPHER_128, DataVectorDecrypted, KeyVector);

		Result = Result && CERR == tAES_CYPHER_ERR_DataSize && DataVector != DataVectorEncrypted;

		utils::test::RESULT("ECB: AES_128 - DecryptECB Data 15 bytes (wrong size)", Result);
	}

	//Test ECB: AES_128 - DecryptECB Key 15 bytes (wrong size)
	{
		char Data[] = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff };
		char Key[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };

		std::vector<char> DataVector(Data, Data + sizeof(Data));

		std::vector<char> KeyVector(Key, Key + sizeof(Key));

		std::vector<char> DataVectorEncrypted = DataVector;

		Result = EncryptECB(utils::crypto::AES::tAES_CYPHER_128, DataVectorEncrypted, KeyVector) == tAES_CYPHER_ERR_None;

		std::vector<char> DataVectorDecrypted = DataVectorEncrypted;

		KeyVector = std::vector<char>(KeyVector.begin(), KeyVector.end() - 1);

		tAES_CYPHER_ERR CERR = DecryptECB(utils::crypto::AES::tAES_CYPHER_128, DataVectorDecrypted, KeyVector);

		Result = Result && CERR == tAES_CYPHER_ERR_KeySize && DataVector != DataVectorEncrypted;

		utils::test::RESULT("ECB: AES_128 - DecryptECB Key 15 bytes (wrong size)", Result);
	}


	//Test ECB: AES_192 - Data 16 bytes
	{
		char Data[] = "QWERTYUIOPASDFGH";//16
		char Key[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'J', 'K', 'L', 'Z', 'X', 'C' };

		std::vector<char> DataVector(Data, Data + strlen(Data));

		std::vector<char> KeyVector(Key, Key + sizeof(Key));

		std::vector<char> DataVectorEncrypted = DataVector;

		Result = EncryptECB(utils::crypto::AES::tAES_CYPHER_192, DataVectorEncrypted, KeyVector) == tAES_CYPHER_ERR_None;

		std::vector<char> DataVectorDecrypted = DataVectorEncrypted;

		Result = Result && DecryptECB(utils::crypto::AES::tAES_CYPHER_192, DataVectorDecrypted, KeyVector) == tAES_CYPHER_ERR_None;

		Result = Result && DataVector == DataVectorDecrypted && DataVector != DataVectorEncrypted;

		utils::test::RESULT("ECB: AES_192 - Data 16 bytes", Result);
	}

	//Test ECB: AES_256 - Data 16 bytes
	{
		char Data[] = "QWERTYUIOPASDFGH";//16
		char Key[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'J', 'K', 'L', 'Z', 'X', 'C', 'g', 'h', 'j', 'k', 'l', 'z', 'x', 'c' };

		std::vector<char> DataVector(Data, Data + strlen(Data));

		std::vector<char> KeyVector(Key, Key + sizeof(Key));

		std::vector<char> DataVectorEncrypted = DataVector;

		Result = EncryptECB(utils::crypto::AES::tAES_CYPHER_256, DataVectorEncrypted, KeyVector) == tAES_CYPHER_ERR_None;

		std::vector<char> DataVectorDecrypted = DataVectorEncrypted;

		Result = Result && DecryptECB(utils::crypto::AES::tAES_CYPHER_256, DataVectorDecrypted, KeyVector) == tAES_CYPHER_ERR_None;

		Result = Result && DataVector == DataVectorDecrypted && DataVector != DataVectorEncrypted;

		utils::test::RESULT("ECB: AES_256 - Data 16 bytes", Result);
	}

	//Test CBC: AES_128 - Data 16 bytes
	{
		char Data_1[] = "QWERTYUIOPASDFGH";//16
		char Data_2[] = "qwertyuiopasdfgh";//16
		char Data_3[] = "jklzxcvbnm[]{}:;";//16
		char Key[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

		std::vector<char> KeyVector(Key, Key + sizeof(Key));


		std::vector<char> DataVector_1(Data_1, Data_1 + strlen(Data_1));

		std::vector<char> DataVectorEncrypted_1 = DataVector_1;

		Result = EncryptECB(utils::crypto::AES::tAES_CYPHER_128, DataVectorEncrypted_1, KeyVector) == tAES_CYPHER_ERR_None;

		std::vector<char> DataVector_2(Data_2, Data_2 + strlen(Data_2));

		std::vector<char> DataVectorEncrypted_2 = DataVector_2;

		Result = EncryptCBC(utils::crypto::AES::tAES_CYPHER_128, DataVectorEncrypted_2, KeyVector, DataVectorEncrypted_1) == tAES_CYPHER_ERR_None;

		std::vector<char> DataVector_3(Data_3, Data_3 + strlen(Data_3));

		std::vector<char> DataVectorEncrypted_3 = DataVector_3;

		Result = EncryptCBC(utils::crypto::AES::tAES_CYPHER_128, DataVectorEncrypted_3, KeyVector, DataVectorEncrypted_2) == tAES_CYPHER_ERR_None;


		std::vector<char> DataVectorDecrypted_1 = DataVectorEncrypted_1;

		Result = Result && DecryptECB(utils::crypto::AES::tAES_CYPHER_128, DataVectorDecrypted_1, KeyVector) == tAES_CYPHER_ERR_None;

		std::vector<char> DataVectorDecrypted_2 = DataVectorEncrypted_2;

		Result = Result && DecryptCBC(utils::crypto::AES::tAES_CYPHER_128, DataVectorDecrypted_2, KeyVector, DataVectorEncrypted_1) == tAES_CYPHER_ERR_None;

		std::vector<char> DataVectorDecrypted_3 = DataVectorEncrypted_3;

		Result = Result && DecryptCBC(utils::crypto::AES::tAES_CYPHER_128, DataVectorDecrypted_3, KeyVector, DataVectorEncrypted_2) == tAES_CYPHER_ERR_None;


		Result = Result &&
			DataVector_1 == DataVectorDecrypted_1 && DataVector_1 != DataVectorEncrypted_1 &&
			DataVector_2 == DataVectorDecrypted_2 && DataVector_2 != DataVectorEncrypted_2 &&
			DataVector_3 == DataVectorDecrypted_3 && DataVector_3 != DataVectorEncrypted_3;

		utils::test::RESULT("CBC: AES_128 - Data 16 bytes", Result);
	}

	//Test CBC: AES_192 - Data 16 bytes
	{
		char Data_1[] = "QWERTYUIOPASDFGH";//16
		char Data_2[] = "qwertyuiopasdfgh";//16
		char Data_3[] = "jklzxcvbnm[]{}:;";//16
		char Key[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'J', 'K', 'L', 'Z', 'X', 'C' };

		std::vector<char> KeyVector(Key, Key + sizeof(Key));


		std::vector<char> DataVector_1(Data_1, Data_1 + strlen(Data_1));

		std::vector<char> DataVectorEncrypted_1 = DataVector_1;

		Result = EncryptECB(utils::crypto::AES::tAES_CYPHER_192, DataVectorEncrypted_1, KeyVector) == tAES_CYPHER_ERR_None;

		std::vector<char> DataVector_2(Data_2, Data_2 + strlen(Data_2));

		std::vector<char> DataVectorEncrypted_2 = DataVector_2;

		Result = EncryptCBC(utils::crypto::AES::tAES_CYPHER_192, DataVectorEncrypted_2, KeyVector, DataVectorEncrypted_1) == tAES_CYPHER_ERR_None;

		std::vector<char> DataVector_3(Data_3, Data_3 + strlen(Data_3));

		std::vector<char> DataVectorEncrypted_3 = DataVector_3;

		Result = EncryptCBC(utils::crypto::AES::tAES_CYPHER_192, DataVectorEncrypted_3, KeyVector, DataVectorEncrypted_2) == tAES_CYPHER_ERR_None;


		std::vector<char> DataVectorDecrypted_1 = DataVectorEncrypted_1;

		Result = Result && DecryptECB(utils::crypto::AES::tAES_CYPHER_192, DataVectorDecrypted_1, KeyVector) == tAES_CYPHER_ERR_None;

		std::vector<char> DataVectorDecrypted_2 = DataVectorEncrypted_2;

		Result = Result && DecryptCBC(utils::crypto::AES::tAES_CYPHER_192, DataVectorDecrypted_2, KeyVector, DataVectorEncrypted_1) == tAES_CYPHER_ERR_None;

		std::vector<char> DataVectorDecrypted_3 = DataVectorEncrypted_3;

		Result = Result && DecryptCBC(utils::crypto::AES::tAES_CYPHER_192, DataVectorDecrypted_3, KeyVector, DataVectorEncrypted_2) == tAES_CYPHER_ERR_None;


		Result = Result &&
			DataVector_1 == DataVectorDecrypted_1 && DataVector_1 != DataVectorEncrypted_1 &&
			DataVector_2 == DataVectorDecrypted_2 && DataVector_2 != DataVectorEncrypted_2 &&
			DataVector_3 == DataVectorDecrypted_3 && DataVector_3 != DataVectorEncrypted_3;

		utils::test::RESULT("CBC: AES_192 - Data 16 bytes", Result);
	}

	//Test CBC: AES_256 - Data 16 bytes
	{
		char Data_1[] = "QWERTYUIOPASDFGH";//16
		char Data_2[] = "qwertyuiopasdfgh";//16
		char Data_3[] = "jklzxcvbnm[]{}:;";//16
		char Key[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'J', 'K', 'L', 'Z', 'X', 'C', 'g', 'h', 'j', 'k', 'l', 'z', 'x', 'c' };

		std::vector<char> KeyVector(Key, Key + sizeof(Key));


		std::vector<char> DataVector_1(Data_1, Data_1 + strlen(Data_1));

		std::vector<char> DataVectorEncrypted_1 = DataVector_1;

		Result = EncryptECB(utils::crypto::AES::tAES_CYPHER_256, DataVectorEncrypted_1, KeyVector) == tAES_CYPHER_ERR_None;

		std::vector<char> DataVector_2(Data_2, Data_2 + strlen(Data_2));

		std::vector<char> DataVectorEncrypted_2 = DataVector_2;

		Result = EncryptCBC(utils::crypto::AES::tAES_CYPHER_256, DataVectorEncrypted_2, KeyVector, DataVectorEncrypted_1) == tAES_CYPHER_ERR_None;

		std::vector<char> DataVector_3(Data_3, Data_3 + strlen(Data_3));

		std::vector<char> DataVectorEncrypted_3 = DataVector_3;

		Result = EncryptCBC(utils::crypto::AES::tAES_CYPHER_256, DataVectorEncrypted_3, KeyVector, DataVectorEncrypted_2) == tAES_CYPHER_ERR_None;


		std::vector<char> DataVectorDecrypted_1 = DataVectorEncrypted_1;

		Result = Result && DecryptECB(utils::crypto::AES::tAES_CYPHER_256, DataVectorDecrypted_1, KeyVector) == tAES_CYPHER_ERR_None;

		std::vector<char> DataVectorDecrypted_2 = DataVectorEncrypted_2;

		Result = Result && DecryptCBC(utils::crypto::AES::tAES_CYPHER_256, DataVectorDecrypted_2, KeyVector, DataVectorEncrypted_1) == tAES_CYPHER_ERR_None;

		std::vector<char> DataVectorDecrypted_3 = DataVectorEncrypted_3;

		Result = Result && DecryptCBC(utils::crypto::AES::tAES_CYPHER_256, DataVectorDecrypted_3, KeyVector, DataVectorEncrypted_2) == tAES_CYPHER_ERR_None;


		Result = Result &&
			DataVector_1 == DataVectorDecrypted_1 && DataVector_1 != DataVectorEncrypted_1 &&
			DataVector_2 == DataVectorDecrypted_2 && DataVector_2 != DataVectorEncrypted_2 &&
			DataVector_3 == DataVectorDecrypted_3 && DataVector_3 != DataVectorEncrypted_3;

		utils::test::RESULT("CBC: AES_256 - Data 16 bytes", Result);
	}

	//Test CBC: AES_128 - Data 16 bytes, Encrypt IV 15 bytes (wrong size IV)
	{
		char Data_1[] = "QWERTYUIOPASDFGH";//16
		char Data_2[] = "qwertyuiopasdfgh";//16
		char Key[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

		std::vector<char> KeyVector(Key, Key + sizeof(Key));


		std::vector<char> DataVector_1(Data_1, Data_1 + strlen(Data_1));

		std::vector<char> DataVectorEncrypted_1 = DataVector_1;

		Result = EncryptECB(utils::crypto::AES::tAES_CYPHER_128, DataVectorEncrypted_1, KeyVector) == tAES_CYPHER_ERR_None;

		std::vector<char> DataVector = std::vector<char>(DataVectorEncrypted_1.begin(), DataVectorEncrypted_1.end() - 1);

		std::vector<char> DataVector_2(Data_2, Data_2 + strlen(Data_2));

		std::vector<char> DataVectorEncrypted_2 = DataVector_2;

		Result = EncryptCBC(utils::crypto::AES::tAES_CYPHER_128, DataVectorEncrypted_2, KeyVector, DataVector) == tAES_CYPHER_ERR_IVSize;


		std::vector<char> DataVectorDecrypted_1 = DataVectorEncrypted_1;

		Result = Result && DecryptECB(utils::crypto::AES::tAES_CYPHER_128, DataVectorDecrypted_1, KeyVector) == tAES_CYPHER_ERR_None;

		std::vector<char> DataVectorDecrypted_2 = DataVectorEncrypted_2;

		Result = Result && DecryptCBC(utils::crypto::AES::tAES_CYPHER_128, DataVectorDecrypted_2, KeyVector, DataVectorEncrypted_1) == tAES_CYPHER_ERR_None;


		utils::test::RESULT("CBC: AES_128 - Data 16 bytes, Encrypt IV 15 bytes (wrong size IV)", Result);
	}

	//Test CBC: AES_128 - Data 16 bytes, Decrypt IV 15 bytes (wrong size IV)
	{
		char Data_1[] = "QWERTYUIOPASDFGH";//16
		char Data_2[] = "qwertyuiopasdfgh";//16
		char Key[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

		std::vector<char> KeyVector(Key, Key + sizeof(Key));


		std::vector<char> DataVector_1(Data_1, Data_1 + strlen(Data_1));

		std::vector<char> DataVectorEncrypted_1 = DataVector_1;

		Result = EncryptECB(utils::crypto::AES::tAES_CYPHER_128, DataVectorEncrypted_1, KeyVector) == tAES_CYPHER_ERR_None;

		
		std::vector<char> DataVector_2(Data_2, Data_2 + strlen(Data_2));

		std::vector<char> DataVectorEncrypted_2 = DataVector_2;

		std::vector<char> DataVector;

		Result = EncryptCBC(utils::crypto::AES::tAES_CYPHER_128, DataVectorEncrypted_2, KeyVector, DataVector) == tAES_CYPHER_ERR_IVSize;


		std::vector<char> DataVectorDecrypted_1 = DataVectorEncrypted_1;

		Result = Result && DecryptECB(utils::crypto::AES::tAES_CYPHER_128, DataVectorDecrypted_1, KeyVector) == tAES_CYPHER_ERR_None;

		DataVector = std::vector<char>(DataVectorEncrypted_1.begin(), DataVectorEncrypted_1.end() - 1);

		std::vector<char> DataVectorDecrypted_2 = DataVectorEncrypted_2;

		Result = Result && DecryptCBC(utils::crypto::AES::tAES_CYPHER_128, DataVectorDecrypted_2, KeyVector, DataVector) == tAES_CYPHER_ERR_IVSize;


		utils::test::RESULT("CBC: AES_128 - Data 16 bytes, Decrypt IV 15 bytes (wrong size IV)", Result);
	}



	std::cout<<std::endl;
}

		}
	}
}
