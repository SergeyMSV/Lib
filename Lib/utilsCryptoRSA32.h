///////////////////////////////////////////////////////////////////////////////////////////////////
// utilsCryptoRsa32.h
//
// Created by Sergey Maslennikov
// Tel.:   +7-916-540-09-19
// E-mail: maslennikovserge@yandex.ru
//
// |   version  |    release    | Description
// |------------|---------------|---------------------------------
// |      1     |   2011 10 25  |
// |      2     |   2016 02 02  | Sligntly modified
// |      3     |   2017 03 16  | Placed into utils::crypto::...
// |            |               | Introduced libConfig.h
// |      4     |   2018 01 16  | Introduced namesapce RSA32 instead of class tRsa
// |      5     |   2018 08 25  | Update
// |            |               |
///////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef LIB_UTILS_CRYPTO_RSA32_H
#define LIB_UTILS_CRYPTO_RSA32_H

#include <libConfig.h>

#include <vector>

namespace utils
{
	namespace crypto
	{
		namespace RSA32
		{

std::vector<int> Encrypt(std::vector<int>& msg, int key, int mod);
std::vector<int> Decrypt(std::vector<int>& msg, int key, int mod);

		}
	}
}

#endif//LIB_UTILS_CRYPTO_RSA32_H
