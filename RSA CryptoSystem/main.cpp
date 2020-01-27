//
//  main.cpp
//  RSA CryptoSystem
//
//  Created by Ata İnan on 19.01.2020.
//  Copyright © 2020 Ata İnan. All rights reserved.
//

#include <iostream>
#include "BigInt.hpp"
#include "BigMath.hpp"
#include "RSA.hpp"
#include <vector>

using namespace std;
using namespace BigMath;

int main(int argc, const char * argv[]) {
    RSA cry(2);
    BigInt x = intToBigInt(3);
    cout << "Plaintext is " << x << endl;
    BigInt y = cry.encrypt(x);
    cout << "Ciphertext is " << y << endl;
    BigInt z = cry.decrypt(y);
    cout << "Decrypted message is " << z << endl;
    return 0;
}
