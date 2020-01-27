//
//  BigMath.cpp
//  RSA CryptoSystem
//
//  Created by Ata İnan on 20.01.2020.
//  Copyright © 2020 Ata İnan. All rights reserved.
//

#include "BigMath.hpp"
#include <cmath>
#include <string>

using namespace std;

namespace BigMath {

BigInt intToBigInt(int x) {
    if (x == 0)
        return BigInt(1, true, vector<int> (1, 0));
    else if (x > 0) {
        int xSize = log10(x) + 1;
        vector<int> num(xSize, 0);
        int i = 0;
        while (x > 0) {
            num[i++] = x % 10;
            x /= 10;
        }
        return BigInt(xSize, true, num);
    } else {
        x *= -1;
        BigInt neg = intToBigInt(x);
        neg.sign = false;
        return neg;
    }
}

int BigIntToInt(BigInt& x) {
    int y = 0;
    for (int i = 0; i < x.size; i++)
        y += pow(10, i) * x.num[i];
    if (!x.sign)
        y *= -1;
    return y;
}

BigInt sum(BigInt& x, BigInt& y) {
    bool sign;
    if (x.sign != y.sign) {
        if (x.sign) {
            y.changeSign();
            BigInt result = sub(x, y);
            y.changeSign();
            return result;
        } else {
            x.changeSign();
            BigInt result = sub(y, x);
            x.changeSign();
            return result;
        }
    } else {
        int size = max(x.size, y.size);
        vector<int> num(size, 0);
        for (int i = 0; i < size; i++) {
            if (i < x.size)
                num[i] += x.num[i];
            if (i < y.size)
                num[i] += y.num[i];
            if (num[i] > 9) {
                num[i] -= 10;
                if (i == size - 1) {
                    num.push_back(1);
                    size++;
                } else
                    num[i + 1]++;
            }
        }
        sign = x.sign;
        return BigInt(size, sign, num);
    }
}

BigInt sub(BigInt& x, BigInt& y) {
    if (x.sign != y.sign) {
        y.changeSign();
        BigInt result = sum(x, y);
        y.changeSign();
        return result;
    } else {
        if (x == y)
            return BigInt(1, true, vector<int> (1, 0));
        else if (x < y) {
            BigInt neg = sub(y, x);
            neg.changeSign();
            return neg;
        } else {
            if (x.sign) {
                int size = x.size;
                vector<int> num(x.num);
                for (int i = 0; i < size; i++) {
                    if (i < y.size)
                        num[i] -= y.num[i];
                    if (num[i] < 0) {
                        num[i] += 10;
                        num[i + 1]--;
                    }
                }
                while (num[size - 1] == 0) {
                    size--;
                    num.pop_back();
                }
                return BigInt(size, true, num);
            } else {
                x.changeSign();
                y.changeSign();
                BigInt result = sub(y, x);
                x.changeSign();
                y.changeSign();
                return result;
            }
        }
    }
}

BigInt mult(BigInt& x, BigInt& y) {
    bool sign = (x.sign == y.sign);
    int size = x.size + y.size;
    vector<int> num(size, 0);
    for (int i = 0; i < x.size; i++) {
        for (int j = 0; j < y.size; j++) {
            num[i + j] += x.num[i] * y.num[j];
        }
    }
    int div;
    for (int i = 0; i < size; i++) {
        div = num[i] / 10;
        if (div >= 1) {
            num[i] %= 10;
            num[i + 1] += div;
        }
    }
    while (size != 1 && num[size - 1] == 0) {
        size--;
        num.pop_back();
    }
    return BigInt(size, sign, num);
}

pair<BigInt, BigInt> divmod(BigInt& x, BigInt& y) { //x = q * y + r;
    bool isXPos = x.sign;
    if (!isXPos)
        x.changeSign();
    BigInt r = x;
    int q = 0;
    while (y <= r) {
        q++;
        r = sub(r, y);
    }
    if (!isXPos) {
        x.changeSign();
        q *= -1;
        if (!(r == 0))
            r = sub(y, r);
    }
    BigInt q2 = intToBigInt(q);
    return make_pair(q2, r);
}

BigInt div(BigInt& x, BigInt& y) {
    return divmod(x, y).first;
}

BigInt mod(BigInt& x, BigInt& n) { //x mod n
    return divmod(x, n).second;
}

BigInt expoMod(BigInt& x, BigInt& y, BigInt& n) { //pow(x, y) mod n
    string binary = "";
    int rem;
    BigInt two = intToBigInt(2);
    pair<BigInt, BigInt> q;
    while (!(y == 0)) {
        q = divmod(y, two);
        rem = BigIntToInt(q.second);
        binary = to_string(rem) + binary;
        y = q.first;
    }
    BigInt z = intToBigInt(1);
    for (unsigned long long int i = 0; i < binary.size(); i++) {
        z = z * z;
        z = mod(z, n);
        if (binary.at(i) == '1') {
            z = z * x;
            z = mod(z, n);
        }
    }
    return z;
}

BigInt gcd(BigInt& x, BigInt& y) {
    BigInt a = x, b = y;
    while (!(b == 0)) {
        BigInt temp = b;
        b = mod(a, b);
        a = move(temp);
    }
    return a;
}

BigInt inverseMod(BigInt& x, BigInt& n) {
    BigInt a = x, b = n;
    BigInt c = intToBigInt(0), t = intToBigInt(1);
    pair<BigInt, BigInt> d = divmod(b, a);
    BigInt q = d.first;
    BigInt r = d.second;
    while (r > 0) {
        BigInt temp1 = q * t;
        BigInt temp2 = c - temp1;
        temp2 = mod(temp2, n);
        c = move(t);
        t = move(temp2);
        b = move(a);
        a = move(r);
        d = divmod(b, a);
        q = d.first;
        r = d.second;
    }
    if (!(a == 1))
        return intToBigInt(0);
    else
        return t;
}
}
