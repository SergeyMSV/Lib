///////////////////////////////////////////////////////////////////////////////////////////////////
// utilsCryptoAES.h
//
// Created by Sergey Maslennikov
// Tel.:   +7-916-540-09-19
// E-mail: maslennikovserge@yandex.ru
//
// |   version  |    release    | Description
// |------------|---------------|---------------------------------
// |      1     |   2018 01 16  |
// |      2     |   2019 09 15  | Added const
// |            |               |
///////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef LIB_UTILS_CRYPTO_AES_H
#define LIB_UTILS_CRYPTO_AES_H

#include <libConfig.h>

#include <vector>

namespace utils
{
	namespace crypto
	{
		namespace AES
		{

enum tAES_CYPHER 
{
	tAES_CYPHER_128,
	tAES_CYPHER_192,
	tAES_CYPHER_256,
};

enum tAES_CYPHER_ERR
{
	tAES_CYPHER_ERR_None,
	tAES_CYPHER_ERR_KeySize,
	tAES_CYPHER_ERR_DataSize,
	tAES_CYPHER_ERR_IVSize,

	tAES_CYPHER_ERR_Unknown = 0xFF,
};

int GetDataBlockSize(tAES_CYPHER mode);

tAES_CYPHER_ERR EncryptECB(tAES_CYPHER mode, std::vector<char>& data, const std::vector<char>& key);//Electronic Codebook (ECB)
tAES_CYPHER_ERR DecryptECB(tAES_CYPHER mode, std::vector<char>& data, const std::vector<char>& key);//Electronic Codebook (ECB)
tAES_CYPHER_ERR EncryptCBC(tAES_CYPHER mode, std::vector<char>& data, const std::vector<char>& key, const std::vector<char>& iv);//Cipher Block Chaining (CBC)
tAES_CYPHER_ERR DecryptCBC(tAES_CYPHER mode, std::vector<char>& data, const std::vector<char>& key, const std::vector<char>& iv);//Cipher Block Chaining (CBC)

		}
	}
}

#endif//LIB_UTILS_CRYPTO_AES_H
