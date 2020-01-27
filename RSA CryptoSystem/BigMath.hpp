//
//  BigMath.hpp
//  RSA CryptoSystem
//
//  Created by Ata İnan on 20.01.2020.
//  Copyright © 2020 Ata İnan. All rights reserved.
//

#ifndef BigMath_hpp
#define BigMath_hpp

#include <stdio.h>
#include "BigInt.hpp"

namespace BigMath {

BigInt intToBigInt(int x);
int BigIntToInt(BigInt& x);
BigInt sum(BigInt& x, BigInt& y);
BigInt sub(BigInt& x, BigInt& y);
BigInt mult(BigInt& x, BigInt& y);
pair<BigInt, BigInt> divmod(BigInt& x, BigInt& y); //assuming y > 0, (q, r) such that x = q * y + r
BigInt div(BigInt& x, BigInt& y);
BigInt mod(BigInt& x, BigInt& n); //x mod n
BigInt expoMod(BigInt& x, BigInt& y, BigInt& n); //pow(x, y) mod n, uses Square and Multiply Algorithm
BigInt gcd(BigInt& x, BigInt& y); //assuming x, y > 0
BigInt inverseMod(BigInt& x, BigInt& n); //inverse of x in the group (Zn, x), uses Extended Euclidean Algorithm
};

#endif /* BigMath_hpp */
