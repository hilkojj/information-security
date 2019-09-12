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
    double length = x.size();
    double E = 0;
    double Ravg = sum(x) / length;
    for (auto ri : x)
        E += std::pow(ri.second - Ravg, 2);

    return std::sqrt( E / (length - 1));
}

void magic(std::string data)
{
    for (int block_size = 5; block_size <= 15; block_size++)
    {
        double sum = 0;
        for (int i = 0; i < block_size; i++)
        {
            std::map<char, int> fr;
            
            for(int j = i * block_size; j < (i * block_size) + block_size; j++)
            {
                fr[data[j]] += 1;
            }
            sum += standard_deviation(fr);
        }

        std::cout << block_size << " " << sum * data.length() / double(block_size) << std::endl;
    }
}

int main()
{
    std::ifstream t("data/ex4_schneier.enc");
    std::string data((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());

    magic(data);

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

        char maxChar; // f
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
}   