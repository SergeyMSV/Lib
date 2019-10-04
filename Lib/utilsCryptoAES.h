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

#include <vector>

namespace utils
{
	namespace crypto
	{
		namespace AES
		{

enum tAES_CYPHER_ERR
{
	tAES_CYPHER_ERR_None,
	tAES_CYPHER_ERR_KeySize,
	tAES_CYPHER_ERR_DataSize,
	tAES_CYPHER_ERR_IVSize,

	tAES_CYPHER_ERR_Unknown = 0xFF,
};

enum tAES_CYPHER 
{
	tAES_CYPHER_128 = 128,
	tAES_CYPHER_192 = 192,
	tAES_CYPHER_256 = 256,
};

int GetDataBlockSize(tAES_CYPHER mode);

tAES_CYPHER_ERR EncryptECB(tAES_CYPHER mode, std::vector<char>& data, const std::vector<char>& key);//Electronic Codebook (ECB)
tAES_CYPHER_ERR DecryptECB(tAES_CYPHER mode, std::vector<char>& data, const std::vector<char>& key);//Electronic Codebook (ECB)
tAES_CYPHER_ERR EncryptCBC(tAES_CYPHER mode, std::vector<char>& data, const std::vector<char>& key, const std::vector<char>& iv);//Cipher Block Chaining (CBC)
tAES_CYPHER_ERR DecryptCBC(tAES_CYPHER mode, std::vector<char>& data, const std::vector<char>& key, const std::vector<char>& iv);//Cipher Block Chaining (CBC)

}

template <class TKey>
constexpr bool IsKeyValid()
{
	return TKey::type_key && (TKey::tKeyValue::Size == 4 || TKey::tKeyValue::Size == 6 || TKey::tKeyValue::Size == 8);
}

template <class TKey>
typename std::enable_if<IsKeyValid<TKey>(), AES::tAES_CYPHER_ERR>::type AES_EncryptECB(const TKey& key, tVectorUInt8& data)//Electronic Codebook (ECB)
{
	unsigned int KeySize = key.Value.Size * 32;//Converts UInt32 to bits

	/////////////////////////////
	/////////////////////////////
	/////////////////////////////
	/////////////////////////////
	/////////////////////////////
	/////////////////////////////

	std::vector<char> data1;
	std::vector<char> key1;

	return EncryptECB(static_cast<AES::tAES_CYPHER>(KeySize), data1, key1);
}

	}
}
