#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h> 

typedef unsigned char byte;

std::string RC4(byte text[], int L, byte key[], int N) 
{
    std::string out;

    // initialize
    byte S[256] = {0}; // {1,2,3,...}
    for (int i=0; i<256; i++) S[i] = i;

    // Key-scheduling-algoritme
    int j = 0;
    for (int i=0; i<256; i++)
    {
        j = (j + S[i] + key[(i % N)]) % 256;
        std::swap(S[i], S[j]);
    }
    int i = 0; j = 0;

    int index = 256;
    int textIndex = -1 - index;
    while (++textIndex < L)
    {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        std::swap(S[i], S[j]);
        byte K = S[(S[i] + S[j]) % 256];

        if (textIndex >= 0)
        {
            char c = char(text[textIndex] ^ K);
            out += c;
        }
    }

    return out;
}

int main(int argc, char *argv[])
{
    // https://en.wikipedia.org/wiki/RC4#Test_vectors
    byte input_key[] = {'2', '0', '1', '9'};

    std::string input_text_str, line;
    while (std::getline(std::cin, line)) input_text_str += line + '\n';

    byte input_text[input_text_str.size()];
    int i = 0;
    for (auto &c : input_text_str) input_text[i++] = byte(c);

    std::cout << RC4(input_text, input_text_str.size(), input_key, 4);
}