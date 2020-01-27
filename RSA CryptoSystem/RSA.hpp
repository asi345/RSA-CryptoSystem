//
//  RSA.hpp
//  RSA CryptoSystem
//
//  Created by Ata İnan on 23.01.2020.
//  Copyright © 2020 Ata İnan. All rights reserved.
//

#ifndef RSA_hpp
#define RSA_hpp

#include <stdio.h>
#include "BigInt.hpp"

class RSA { //depends on the fact that factoring n is hard
    
public:
    unsigned int length; //length of primes
    BigInt p; //first prime
    BigInt q; //second prime
    BigInt n; //modulo value, belongs to the public key
    BigInt phi; //phi(n), Euler's Phi Function
    BigInt firstExponent; //belongs to the public key
    BigInt secondExponent; //belongs to the private key
    
    RSA(unsigned int length);
    BigInt generateRandomNumber(int length);
    bool isPrime(BigInt& x); //Miller Rabin Primality Test, does not work for 1-digit numbers, 1/4 error probability
//  if x is composite
    bool isPrime(BigInt& x, int repeat); //does the Miller Rabin test "repeat" times (often repeat = 4 for speed)
    void generatePrimes(); //determines p and q
    void generateNandPhi(); //n = p * q and phi = (p - 1) * (q - 1)
    void generateExponents(); //satisfies firstExponent * secondExponent mod phi = 1
    BigInt encrypt(BigInt& x); //pow(x, first exponent) mod n
    BigInt decrypt(BigInt& y); //pow(y, second exponent) mod n
};

#endif /* RSA_hpp */
