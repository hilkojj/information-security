#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h> 

typedef unsigned char byte;

template<typename T, size_t n>
void print_array(T const(& arr)[n])
{
	for (size_t i = 0; i < n; i++)
		std::cout << arr[i] << ' ';
}

void print_hex(const std::string& s)
{
    std::cout << std::hex << std::setfill('0');
    for(unsigned char c : s)
        std::cout << std::setw(2) << static_cast<int>(c) << ' ';
    std::cout << std::dec << '\n';
}

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

    // Pseudo-random generation-algoritme
    // for (int index=300; index >= 0; index--)
    // {
        int index = 256;
        int textIndex = -1 - index;
        // std::cout << "\n" << index << " ";
        while (++textIndex < L)
        {
            i = (i + 1) % 256;
            j = (j + S[i]) % 256;
            std::swap(S[i], S[j]);
            byte K = S[(S[i] + S[j]) % 256];

            if (textIndex >= 0)
            {
                // std::cout << K << '^' << text[textIndex] << " = ";
                char c = char(text[textIndex] ^ K);
                // std::cout << c << '\n';
                out += c;
            }

            // std::coi

            // if (textIndex >= 0) 
        }

    // }
    return out;
}

int main(int argc, char *argv[])
{
    // https://en.wikipedia.org/wiki/RC4#Test_vectors
    byte input_key[] = {'2', '0', '1', '9'};
    // byte input_text[] = {'P', 'l', 'a', 'i', 'n', 't', 'e', 'x', 't'}; // "Plaintext"

    std::string input_text_str, line;
    while (std::getline(std::cin, line)) input_text_str += line + '\n';

    byte input_text[input_text_str.size()];
    int i = 0;
    for (auto &c : input_text_str) input_text[i++] = byte(c);
    

    std::string output_keystream = "EB9F7781B734CA72A719...";
    std::string output_ciphertext = "BBF316E8D940AF0AD3";

    std::cout << RC4(input_text, input_text_str.size(), input_key, 4);
}