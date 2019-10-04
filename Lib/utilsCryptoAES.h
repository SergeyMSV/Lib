///////////////////////////////////////////////////////////////////////////////////////////////////
// utilsCryptoAES.h
//
// Standard ISO/IEC 114882, C++17
//
// |   version  |    release    | Description
// |------------|---------------|---------------------------------
// |      1     |   2018 01 16  |
// |      2     |   2019 09 15  | Added const
// |      3     |   2019 10 04  | 
// |            |               |
///////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <libConfig.h>

#include "utilsKey.h"

#include <cassert>
#include <vector>

namespace utils
{
	namespace crypto
	{

enum tAES_ECB_CERR
{
	tAES_ECB_CERR_None,
	tAES_ECB_CERR_DataSize,
	//tAES_ECB_CERR_IVSize,

	tAES_ECB_CERR_Unknown = 0xFF,
};

enum tAES_CBC_CERR
{
	tAES_CBC_CERR_None,
	tAES_CBC_CERR_DataSize,
	tAES_CBC_CERR_IVSize,

	tAES_CBC_CERR_Unknown = 0xFF,
};

		namespace AES
		{

enum tAES_CYPHER_ERR//DEPRECATED
{
	tAES_CYPHER_ERR_None,
	tAES_CYPHER_ERR_KeySize,//[TBD]DEPRECATED
	tAES_CYPHER_ERR_DataSize,
	tAES_CYPHER_ERR_IVSize,

	tAES_CYPHER_ERR_Unknown = 0xFF,
};

enum tAES_CYPHER//used as an index
{
	tAES_CYPHER_128,
	tAES_CYPHER_192,
	tAES_CYPHER_256,
};

int GetDataBlockSize(tAES_CYPHER mode);

//tAES_CYPHER_ERR EncryptECB(tAES_CYPHER mode, std::vector<char>& data, const std::vector<char>& key);//Electronic Codebook (ECB)
//tAES_CYPHER_ERR DecryptECB(tAES_CYPHER mode, std::vector<char>& data, const std::vector<char>& key);//Electronic Codebook (ECB)
tAES_CYPHER_ERR EncryptCBC(tAES_CYPHER mode, std::vector<char>& data, const std::vector<char>& key, const std::vector<char>& iv);//Cipher Block Chaining (CBC)
tAES_CYPHER_ERR DecryptCBC(tAES_CYPHER mode, std::vector<char>& data, const std::vector<char>& key, const std::vector<char>& iv);//Cipher Block Chaining (CBC)

template <class TKey>
constexpr bool IsKeyValid()
{
	return TKey::type_key && (TKey::tKeyValue::Size == 4 || TKey::tKeyValue::Size == 6 || TKey::tKeyValue::Size == 8);
}

template <class TKey>
constexpr tAES_CYPHER GetMode()
{
	return static_cast<AES::tAES_CYPHER>((TKey::tKeyValue::Size - 4) / 2);
}

bool VerifyInputECB(tAES_CYPHER mode, const tVectorUInt8& data);
void Encrypt_ECB(tAES_CYPHER mode, unsigned char* data, int len, const unsigned char* key);//Electronic Codebook (ECB)
void Decrypt_ECB(tAES_CYPHER mode, unsigned char* data, int len, const unsigned char* key);//Electronic Codebook (ECB)

		}

//Electronic Codebook (ECB)
template <class TKey>
typename std::enable_if<AES::IsKeyValid<TKey>(), tAES_ECB_CERR>::type AES_ECB_Encrypt(const TKey& key, tVectorUInt8& data)
{
	AES::tAES_CYPHER Mode = AES::GetMode<TKey>();

	assert(Mode >= 0 && Mode <= 2);

	if (VerifyInputECB(Mode, data))
	{
		tVectorUInt8 KeyVector = ToVector(key);

		AES::Encrypt_ECB(Mode, data.data(), data.size(), KeyVector.data());

		return tAES_ECB_CERR_None;
	}

	return tAES_ECB_CERR_DataSize;
}

//Electronic Codebook (ECB)
template <class TKey>
typename std::enable_if<AES::IsKeyValid<TKey>(), tAES_ECB_CERR>::type AES_ECB_Decrypt(const TKey& key, tVectorUInt8& data)
{
	AES::tAES_CYPHER Mode = AES::GetMode<TKey>();

	assert(Mode >= 0 && Mode <= 2);

	if (VerifyInputECB(Mode, data))
	{
		tVectorUInt8 KeyVector = ToVector(key);

		AES::Decrypt_ECB(Mode, data.data(), data.size(), KeyVector.data());

		return tAES_ECB_CERR_None;
	}

	return tAES_ECB_CERR_DataSize;
}

//Cipher Block Chaining (CBC)
template <class TKey>
typename std::enable_if<AES::IsKeyValid<TKey>(), tAES_CBC_CERR>::type AES_CBC_Encrypt(const TKey& key, tVectorUInt8& data, const tVectorUInt8& iv)
{
	AES::tAES_CYPHER Mode = AES::GetMode<TKey>();

	assert(Mode >= 0 && Mode <= 2);

	/*if (VerifyInputECB(Mode, data))
	{
		tVectorUInt8 KeyVector = ToVector(key);

		AES::Encrypt_ECB(Mode, data.data(), data.size(), KeyVector.data());

		return tAES_CBC_CERR_None;
	}*/

	return tAES_CBC_CERR_DataSize;
}

//Cipher Block Chaining (CBC)
template <class TKey>
typename std::enable_if<AES::IsKeyValid<TKey>(), tAES_CBC_CERR>::type AES_CBC_Decrypt(const TKey& key, tVectorUInt8& data, const tVectorUInt8& iv)
{
	AES::tAES_CYPHER Mode = AES::GetMode<TKey>();

	assert(Mode >= 0 && Mode <= 2);

	/*if (VerifyInputECB(Mode, data))
	{
		tVectorUInt8 KeyVector = ToVector(key);

		AES::Decrypt_ECB(Mode, data.data(), data.size(), KeyVector.data());

		return tAES_CBC_CERR_None;
	}*/

	return tAES_CBC_CERR_DataSize;
}

	}
}
