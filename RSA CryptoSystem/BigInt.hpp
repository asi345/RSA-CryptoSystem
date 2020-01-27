//
//  BigInt.hpp
//  RSA CryptoSystem
//
//  Created by Ata İnan on 20.01.2020.
//  Copyright © 2020 Ata İnan. All rights reserved.
//

#ifndef BigInt_hpp
#define BigInt_hpp

#include <stdio.h>
#include <vector>

using namespace std;

class BigInt {
    
public:
    int size;
    bool sign;
    vector<int> num;
    
    BigInt(int size, bool sign, vector<int> num);
    BigInt();
    void changeSign();
    friend bool operator== (BigInt& x, BigInt& y);
    friend bool operator< (BigInt& x, BigInt& y);
    friend bool operator<= (BigInt& x, BigInt& y);
    friend bool operator> (BigInt& x, BigInt& y);
    friend bool operator>= (BigInt& x, BigInt& y);
    friend bool operator== (BigInt& x, int y);
    friend bool operator< (BigInt& x, int y);
    friend bool operator<= (BigInt& x, int y);
    friend bool operator> (BigInt& x, int y);
    friend bool operator>= (BigInt& x, int y);
    friend BigInt operator+ (BigInt& x, BigInt& y);
    friend BigInt operator+ (BigInt& x, int y);
    friend BigInt operator- (BigInt& x, BigInt& y);
    friend BigInt operator* (BigInt& x, BigInt& y);
    friend ostream& operator<< (ostream& out, BigInt& x);
};

#endif /* BigInt_hpp */
