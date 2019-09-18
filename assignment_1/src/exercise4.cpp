#include <iostream>
#include <string>
#include <map>
#include <cmath>
#include <fstream>
#include <streambuf>

inline std::map<char, int> operator * (std::map<char, int> a, std::map<char, int> b)
{
    std::map<char, int> newFreq = a;
    for (auto x : b) newFreq[x.first] *= x.second;
    return newFreq;
}

double sum(std::map<char, int> a)
{
    int total = 0;
    for (auto x : a) total += x.second;
    return total;
}

double standard_deviation(std::map<char, int> x)
{
    return std::sqrt( sum((x * x)) / 26.0 - std::pow( sum(x) / 26.0, 2) );
}

int get_most_likely_keysize(std::string data)
{
    int sd[16];
    for (int k = 5; k <= 15; k++)
    {
        double sum = 0;
        for (int keyI = 0; keyI < k; keyI++)
        {
            std::map<char, int> freq;
            for (int i = keyI; i < data.length(); i += k)
                freq[data[i]]++;

            sum += standard_deviation(freq);
        }
            
        sd[k] = sum;
        std::cout << "blocksize: " << k << ", SD: " << sum << "\n";
    }

    int peakK, peakDiff = 0;
    for (int k = 6; k < 15; k++)
    {
        int n = sd[k];
        int n1 = sd[k - 1], n2 = sd[k + 1];
        if (n1 < n && n2 < n)
        {
            int diff = std::abs(n - n1) + std::abs(n - n2);
            if (diff > peakDiff)
            {
                peakDiff = diff;
                peakK = k;
            }
        }
    }
    std::cout << "Peak: " << peakK << "\n\n\n";

    return peakK;
}

int main()
{
    std::string data, line;
    while(std::getline(std::cin, line)) data += line + "\n"; // we now keep reading until an EOF

    int block_size = get_most_likely_keysize(data);;

    auto fr = new std::map<char, int>[block_size];

    for (int i = 0; i < data.length(); i += block_size)
    {
        for (int j = 0; j < block_size; j++)
            fr[j][data[i + j]]++;
    }
    

    std::string keyCandidates[3];
    for (int j = 0; j < block_size; j++)
    {
        auto &freq = fr[j];

        char maxChar[3];
        int maxFreq[3] = {0, 0, 0};

        for (auto x : freq) if (x.second > maxFreq[0])
        {
            maxFreq[2] = maxFreq[1];
            maxFreq[1] = maxFreq[0];
            maxFreq[0] = x.second;

            maxChar[2] = maxChar[1];
            maxChar[1] = maxChar[0];
            maxChar[0] = x.first;
        }

        for (int i = 0; i < 3; i++)
        {
            char keyChar = 'a' + ((maxChar[i] - 'e' + 26) % 26);
            keyCandidates[i] += keyChar;
        }
    }
    std::cout << "Most likely: " << keyCandidates[0] << "\n";
    std::cout << "2nd best   : " << keyCandidates[1] << "\n";
    std::cout << "3rd        : " << keyCandidates[2] << "\n";
    
    std::cout << "\n\n\n----------------\n\n\n";

    std::string key = keyCandidates[0];

    int i = -1;
    while (data[++i])
    {
        char keyChar = key[i % block_size];
        char t = (data[i] - keyChar + 26) % 26 + 'a';
        std::cout << t;
    }
    std::cout << "\n";

    delete[] fr;

    /* i came to security from cryptography and thought of the problem in a military like fashion ... */
}   