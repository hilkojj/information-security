#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>
#include <stdint.h>
#include <openssl/sha.h>
#include <tuple>

void compute_sha256(char const *str, unsigned char *hash) {
    // Computes the SHA256 hash.
    SHA256_CTX hashing_context;
    SHA256_Init(&hashing_context);
    SHA256_Update(&hashing_context, str, strlen(str));
    SHA256_Final(hash, &hashing_context);
}

typedef uint32_t halfblock;

halfblock f(const unsigned char *key, int round)
{
    halfblock result = key[round * 4];
    return result;
}

void feistel(halfblock *LH, halfblock *RH, const unsigned char *key, int round)
{
    halfblock newR = LH[0] ^ f(key, round);
    LH[0] = RH[0];
    RH[0] = newR;
}

int main()
{
    const char *password = "Henkie";

    unsigned char *key = new unsigned char[SHA256_DIGEST_LENGTH * 2];

    compute_sha256(password, &key[0]);
    compute_sha256((const char *)&key[0], &key[SHA256_DIGEST_LENGTH]);

    std::string input, line;
    while (std::getline(std::cin, line)) input += line + '\n';

    for (int r = 0; r < 16; r++)
    {
        for (int i = 0; i < input.size(); i += 8)
        {
            halfblock *LH = (halfblock *)&input[i], *RH = (halfblock *)&input[i + 4];

            
            feistel(LH, RH, &key[0], r);
        }
    }

    std::cout << input << "\n\n";
}
