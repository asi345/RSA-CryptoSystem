//
//  RSA.cpp
//  RSA CryptoSystem
//
//  Created by Ata İnan on 23.01.2020.
//  Copyright © 2020 Ata İnan. All rights reserved.
//

#include "RSA.hpp"
#include "BigMath.hpp"

using namespace BigMath;

RSA::RSA(unsigned int length) {
    this->length = length;
}

BigInt RSA::generateRandomNumber(int length) {
    vector<int> num(length);
    for (int i = 0; i < length; i++)
        num[i] = arc4random() % 10;
    if (num[length - 1] == 0)
        return generateRandomNumber(length);
    return BigInt(length, true, num);
}

bool RSA::isPrime(BigInt &x) {
    BigInt one = intToBigInt(1), two = intToBigInt(2);
    BigInt m = x - one, minus = m;
    unsigned long long int k = 0;
    pair<BigInt, BigInt> q = divmod(m, two);
    while (BigIntToInt(q.second) == 0) {
        k++;
        m = q.first;
        q = divmod(m, two);
    }
    BigInt a = generateRandomNumber(arc4random() % ((x - one).size - 1) + 2);
    BigInt b = expoMod(a, m, x);
    BigInt c = mod(b, x);
    if (c == 1)
        return true;
    for (unsigned long long int i = 0; i < k; i++) {
        if (c == minus)
            return true;
        else
            b = expoMod(b, two, x);
    }
    return false;
}

bool RSA::isPrime(BigInt& x, int repeat) {
    for (int i = 0; i < repeat; i++)
        if (!isPrime(x))
            return false;
    return true;
}

void RSA::generatePrimes() {
    do {
        this->p = generateRandomNumber(this->length);
    } while (!isPrime(this->p, 4));
    do {
        this->q = generateRandomNumber(this->length);
    } while (!isPrime(this->q, 4));
}

void RSA::generateNandPhi() {
    this->n = this->p * this->q;
    BigInt one = intToBigInt(1);
    BigInt factor1 = this->p - one;
    BigInt factor2 = this->q - one;
    this->phi = factor1 * factor2;
}

void RSA::generateExponents() {
    BigInt a;
    do {
        this->firstExponent = generateRandomNumber(arc4random() % (this->phi.size - 1) + 1);
        a = gcd(this->firstExponent, this->phi);
    } while (!(a == 1));
    this->secondExponent = inverseMod(this->firstExponent, this->phi);
}

BigInt RSA::encrypt(BigInt& x) {
    generatePrimes();
    generateNandPhi();
    generateExponents();
    return expoMod(x, this->firstExponent, this->n);
}

BigInt RSA::decrypt(BigInt& y) {
    return expoMod(y, this->secondExponent, this->n);
}
