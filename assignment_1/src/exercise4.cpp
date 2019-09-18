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
    // double length = x.size();
    // double E = 0;
    // double Ravg = sum(x) / length;
    // for (auto ri : x)
    //     E += std::pow(ri.second - Ravg, 2);
    // return std::sqrt( E / (length-1));
}

void magic(std::string data)
{
    int sd[16];
    for (int k = 5; k <= 15; k++)
    {
        double sum = 0;
        std::map<char, int> freq;
        for (int keyI = 0; keyI < k; keyI++)
        {
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
}

int main()
{
    std::string data, line;
    while(std::getline(std::cin, line)) data += line + "\n"; // we now keep reading until an EOF

    magic(data);

    // std::map<char, int> map{{'a', 1}, {'b', 3}, {'q', 2}};

    // std::cout << standard_deviation(map) << std::endl;

    int block_size = 9;

    auto fr = new std::map<char, int>[block_size];

    for (int i = 0; i < data.length(); i += block_size)
    {
        for (int j = 0; j < block_size; j++)
            fr[j][data[i + j]]++;
    }
    

    std::string key;
    for (int j = 0; j < block_size; j++)
    {
        auto &freq = fr[j];

        char maxChar;
        int maxFreq = 0;

        for (auto x : freq) if (x.second > maxFreq)
        {
            maxFreq = x.second;
            maxChar = x.first;
        }

        char keyChar = 'a' + ((maxChar - 'e' + 26) % 26);
        key += keyChar;

        std::cout << keyChar << " ";
    }
    std::cout << "\n";


    std::cout << "\n\n\n----------------\n\n\n";

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