#include "utilsCryptoRSA32.h"

namespace utils
{
	namespace crypto
	{
		namespace RSA32
		{
///////////////////////////////////////////////////////////////////////////////////////////////////
//bool ExtBinEuclid_IsEven(int x) { return (x & 0x01) == 0; }
//bool ExtBinEuclid_IsOdd(int x) { return x & 0x01; }
//void ExtBinEuclid_Swap(int &x, int &y) { x ^= y; y ^= x; x ^= y; }
//bool ExtBinEuclid(int *u, int *v, int *u1, int *u2, int *u3);

int ExtEuclid(int a, int mod)
{
	if (mod == 0)
	{
		return 1;
	}

	int B = mod;

	int X = 0;
	//int Y = 0;

	int X1 = 0;
	//int Y1 = 1;

	int X2 = 1;
	//int Y2 = 0;

	double Q = 0;
	double R = 0;

	while (B > 0)
	{
		Q = a / B;
		R = a % B;//R = a - Q * B;
		
		X = (int)(X2 - Q * X1);
		//Y = (int)(Y2 - Q * Y1);
		
		a = B;
		B = (int)R;
		
		X2 = X1;
		//Y2 = Y1;

		X1 = X;
		//Y1 = Y;
	}

	X = X2;
	//Y = Y2;
	 
	if (X < 0)
	{
		X = X + mod;
	}
	 
	return X;
}

int Qe2(int x1, unsigned int y, int mod)
{
	long long S = 1;

	long long x = x1;

	while (y)
	{
		if (y & 1)
		{
			S = (S * x) % mod;
		}

		y >>= 1;

		x = (x * x) % mod;
	}

	return static_cast<int>(S);
}

int GetGcd(int x, int y)
{
	if (x < 0)
	{
		x = -x;
	}

	if (y < 0)
	{
		y = -y;
	}

	if (x + y == 0)
	{
		return -1;//ERROR
	}

	int G = y;

	while (x > 0)
	{
		G = x;

		x = y % x;

		y = G;
	}

	return G;
}

int GetPrivateKey(int e, int a)
{
	return ExtEuclid(e, a);
}

int GetPrivateKey(int e, int a, int &gcd)
{
	gcd = GetGcd(e, a);

	return ExtEuclid(e, a);
}

std::vector<int> Encrypt(std::vector<int>& msg, int key, int mod)
{
	std::vector<int> Res;//[!!!]it's possible to set its size in advance

	int Length = msg.size();

	for (int i = 0; i < Length; ++i)
	{
		Res.push_back(Qe2(((msg[i] >> 16) & 0x0000FFFF), key, mod));

		Res.push_back(Qe2(msg[i] & 0x0000FFFF, key, mod));
	}

	return Res;
}

std::vector<int> Decrypt(std::vector<int>& msg, int key, int mod)
{
	std::vector<int> Res;//[!!!]it's possible to set its size in advance

	int Length = msg.size();

	for (int i = 0; i < Length; i += 2)
	{	
		int Value = Qe2(msg[i], key, mod) << 16;

		Value |= Qe2(msg[i + 1], key, mod);

		Res.push_back(Value);
	}

	return Res;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
		}
	}
}

/*
//a * x + b * y = gcd(a, b) = d
bool tChipherRSA::ExtBinEuclid(int *u, int *v, int *u1, int *u2, int *u3)
{//-Warning: u and v will be swapped if u < v
	if (*u < *v)
		ExtBinEuclid_Swap(*u, *v);
		//return false;

	int k = 0;

	for (; ExtBinEuclid_IsEven(*u) && ExtBinEuclid_IsEven(*v); ++k)
	{
		*u >>= 1;
		*v >>= 1;
	}

	*u1 = 1;
	*u2 = 0;
	*u3 = *u;

	int T1 = *v;
	int T2 = *u - 1;
	int T3 = *v;

	do
	{
		do
		{
			if (ExtBinEuclid_IsEven(*u3))
			{
				if (ExtBinEuclid_IsOdd(*u1) || ExtBinEuclid_IsOdd(*u2))
				{
					*u1 += *v;
					*u2 += *u;
				}

				*u1 >>= 1;
				*u2 >>= 1;
				*u3 >>= 1;
			}

			if (ExtBinEuclid_IsEven(T3) || *u3 < T3)
			{
				ExtBinEuclid_Swap(*u1, T1);
				ExtBinEuclid_Swap(*u2, T2);
				ExtBinEuclid_Swap(*u3, T3);
			}
		}
		while(ExtBinEuclid_IsEven(*u3));

		while (*u1 < T1 || *u2 < T2)
		{
			*u1 += *v;
			*u2 += *u;
		}

		*u1 -= T1;
		*u2 -= T2;
		*u3 -= T3;
	}
	while (T3 > 0);

	while (*u1 >= *v && *u2 >= *u)
	{
		*u1 -= *v;
		*u2 -= *u;
	}

	*u1 <<= k;
	*u2 <<= k;
	*u3 <<= k;

	return true;
}*/