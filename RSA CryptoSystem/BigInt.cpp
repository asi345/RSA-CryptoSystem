//
//  BigInt.cpp
//  RSA CryptoSystem
//
//  Created by Ata İnan on 20.01.2020.
//  Copyright © 2020 Ata İnan. All rights reserved.
//

#include "BigInt.hpp"
#include "BigMath.hpp"
#include <iostream>

using namespace std;
using namespace BigMath;

BigInt::BigInt(int size, bool sign, vector<int> num) {
    this->size = size;
    this->sign = sign;
    this->num = num;
}

BigInt::BigInt() {
    BigInt(1, true, vector<int> (1, 0));
}

void BigInt::changeSign() {
    this->sign = !(this->sign);
}

bool operator== (BigInt& x, BigInt& y) {
    if (x.sign != y.sign)
        return false;
    if (x.size != y.size)
        return false;
    for (int i = 0; i < x.size; i++) {
        if (x.num[i] != y.num[i])
            return false;
    }
    return true;
}

bool operator< (BigInt& x, BigInt& y) {
    if (x.sign != y.sign) {
        if (!x.sign)
            return true;
        else
            return false;
    } else {
        if (!x.sign) {
            x.changeSign();
            y.changeSign();
            bool result = y < x;
            x.changeSign();
            y.changeSign();
            return result;
        } else {
            if (x.size < y.size)
                return true;
            else if (x.size > y.size)
                return false;
            else {
                for (int i = x.size - 1; i >= 0; i--) {
                    if (x.num[i] < y.num[i])
                        return true;
                    if (x.num[i] > y.num[i])
                        return false;
                }
                return false;
            }
        }
    }
}

bool operator<= (BigInt& x, BigInt& y) {
    return (x == y) || (x < y);
}

bool operator> (BigInt& x, BigInt& y) {
    return !(x <= y);
}

bool operator>= (BigInt& x, BigInt& y) {
    return !(x < y);
}

bool operator== (BigInt& x, int y) {
    return BigIntToInt(x) == y;
}

bool operator< (BigInt& x, int y) {
    return BigIntToInt(x) < y;
}

bool operator<= (BigInt& x, int y) {
    return (x == y) || (x < y);
}

bool operator> (BigInt& x, int y) {
    return !(x <= y);
}

bool operator>= (BigInt& x, int y) {
    return !(x < y);
}

BigInt operator+ (BigInt& x, BigInt& y) {
    return sum(x, y);
}

BigInt operator+ (BigInt& x, int y) {
    BigInt y2 = intToBigInt(y);
    return sum(x, y2);
}

BigInt operator- (BigInt& x, BigInt& y) {
    return sub(x, y);
}

BigInt operator* (BigInt& x, BigInt& y) {
    return mult(x, y);
}

ostream& operator<< (ostream& out, BigInt& x) {
    if (!x.sign)
        out << "-";
    for (int i = x.size - 1; i >= 0; i--)
        out << x.num[i];
    return out;
}
