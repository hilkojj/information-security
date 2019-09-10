#include <iostream>
#include <string>

std::string cipher(std::string &in, char shift)
{
    std::string result = in;
    int i = -1;
    while (in[++i])
    {
        char original = in[i];

        bool lowerLetter = original >= 'a' && original <= 'z';
        bool upperLetter = original >= 'A' && original <= 'Z';

        if (lowerLetter || upperLetter)
        {
            char base = lowerLetter ? 'a' : 'A';
            result[i] = (in[i] + shift - base) % 26 + base;
        }
        else result = in[i]; // non-letter
    }
    return result;
}


int main(int argc, char *argv[])
{
    bool honorCasing = false, decrypt = false;

    for (int i = 0; i < argc; i++)
    {
        if (std::string(argv[i]) == "-o")
            honorCasing = true;
        if (std::string(argv[i]) == "-d")
            decrypt = true;
    }

    std::string in;
    std::getline(std::cin, in);

    int i = -1;
    while (!honorCasing && in[++i]) in[i] = std::tolower(in[i]);

    std::cout << "output is: " << cipher(in, 3) << "\n";

    return 0;
}

