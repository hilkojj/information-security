#include <iostream>
#include <cmath>
#include <vector>

typedef u_int32_t word;
typedef u_int8_t byte;
#define w 32

// The additional parentacies around the X's are there to make shure the math rules do not override what we asume will happen
#define ROTR(n, x)     ((x) << n) | ((x) >> (w - n))
#define SHR(n, x)      ((x) >> n)

#define Ch(x, y, z)    (x & y) ^ (~x & z)
#define Maj(x, y, z)   (x & y) ^ (x & z) ^ (y & z)

#define Summation0(x)  (ROTR(2,  (x)) ^ ROTR(13, (x)) ^ ROTR(22, (x)))
#define Summation1(x)  (ROTR(6,  (x)) ^ ROTR(11, (x)) ^ ROTR(25, (x)))
#define Sigma0(x)      (ROTR(7,  (x)) ^ ROTR(18, (x)) ^  SHR(3,  (x)))
#define Sigma1(x)      (ROTR(17, (x)) ^ ROTR(19, (x)) ^  SHR(10, (x)))

/**
 * this function is implemented by using the following file:
 * http://csrc.nist.gov/publications/fips/fips180-4/fips-180-4.pdf
 * 
 * ASUMPTIONS: Addition (+) is performed modulo 2^32
 */
std::string sha256(std::string M) {
    int N = 1; // TODO: figure out what this value should be

    // int l = M.length() * 8;
    // if (l >= std::pow(2, 64))
    //     throw std::invalid_argument("SHA-256 may be used to hash a message, M, having a length of l bits, where 0 <= l < 2^64");

    // These words represent the first thirty-two bits of the fractional parts of the cube roots of the 
    // first sixty-four prime numbers  
    word K[64] = {
        0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
        0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
        0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
        0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
        0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
        0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
        0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
        0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
    };


    // initial hash values
    // https://en.cppreference.com/w/c/language/array_initialization
    word H[N][8] = {
        {
            0x6a09e667,
            0xbb67ae85,
            0x3c6ef372,
            0xa54ff53a,
            0x510e527f,
            0x9b05688c,
            0x1f83d9ab,
            0x5be0cd19,
        },
        // {0,0,0, ...}
        // {..........}
    };

    word T1, T2, a, b, c, d, e, f, g, h;

    word W[64] = {0,/*...*/};


    for (int i=1; i<=N; i++) {
        // 1. Prepare the message schedule, {W t }:
        for (int t=0; t<=15; t++)
            W[t] = M[t];
        for (int t=16; t<=63; t++)
            W[t] = Sigma1(W[t - 2]) + W[t - 7] + Sigma0(W[t - 15]) + W[t - 16]; 

        // 2. Initialize the eight working variables, a, b, c, d, e, f, g, and h, with the (i - 1) st hash value:
        a = H[i - 1][0];
        b = H[i - 1][1];
        c = H[i - 1][2];
        d = H[i - 1][3];
        e = H[i - 1][4];
        f = H[i - 1][5];
        g = H[i - 1][6];
        h = H[i - 1][7];

        // 3. For t=0 to 63:
        for (int t=0; t<=63; t++) {
            T1 = h + Summation1(e) + Ch(e, f, g) + K[t] + W[t];
            T1 = Summation0(a) + Maj(a, b, c);
            h = g;
            g = f;
            f = e;
            e = d + T1;
            d = c;
            c = b;
            b = a;
            a = T1 + T2;
        }

        // 4. Compute the i th intermediate hash value H[i-1] (i) :
        H[i][0] = a + H[i-1][0];
        H[i][1] = b + H[i-1][1];
        H[i][2] = c + H[i-1][2];
        H[i][3] = d + H[i-1][3];
        H[i][4] = e + H[i-1][4];
        H[i][5] = f + H[i-1][5];
        H[i][6] = g + H[i-1][6];
        H[i][7] = h + H[i-1][7];
    }
    
    // tmp print
    for (int n=0; n<N; n++)
        for (int z=0; z<8; z++) 
            std::cout << std::hex << H[n][z];
    std::cout << std::endl;
    
    return "Mooi";
}

int main() {
    std::cout << sha256("Feistel") << std::endl;
    // 184b4d16bbe3200c5a5f500cc09efa68cddd42cbda27c1e49fa7a0f2e2735007
    return 0;
}