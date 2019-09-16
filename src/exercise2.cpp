#include <iostream>
#include <string>

std::string cipher(std::string &in, char shift)
{
    std::string result = in;
    int i = -1;
    while (char original = in[++i])
    {
        bool lowerLetter = original >= 'a' && original <= 'z';
        bool upperLetter = original >= 'A' && original <= 'Z';

        if (lowerLetter || upperLetter)
        {
            char base = lowerLetter ? 'a' : 'A';
            result[i] = (in[i] + shift - base) % 26 + base;
        }
        else result[i] = in[i]; // non-letter
    }
    return result;
}

std::string mapping_cipher(std::string &in, std::string mapping)
{    
    std::string result = in;

    int i = -1;
    while (char original = in[++i])
    {
        bool lowerLetter = original >= 'a' && original <= 'z';
        bool upperLetter = original >= 'A' && original <= 'Z';

        if (lowerLetter || upperLetter)
        {
            char base = lowerLetter ? 'a' : 'A';
            result[i] = mapping[original - base] + base - 'a';
        }
        else result[i] = in[i]; // non-letter        
    }

    return result;
}

std::string flip_mapping(std::string mapping) 
{   
    std::string newMapping = mapping;

    int i = -1;
    while (char original = mapping[++i])
    {
        if (original < 'a' || original > 'z') throw std::runtime_error("only a-z allowed in mapping string");
        newMapping[original - 'a'] = i + 'a';
    }

    return newMapping;
}


int main(int argc, char *argv[])
{
    bool honorCasing = false, decrypt = false, isMapping = false;
    std::string mapping = "";

    for (int i = 1; i < argc; i++) // the 0'st argument is the full string wich is useless to us
    {
        if (std::string(argv[i]) == "-o")
            honorCasing = true;
        else if (std::string(argv[i]) == "-d")
            decrypt = true;
        else if (mapping.length() == 0) {
            mapping = std::string(argv[i]);

            if (mapping.length() == 26)
                 isMapping = true;
            else if (mapping.find_first_not_of("0123456789") != std::string::npos) {
                std::cout << "We did not understand your mapping. It must be of length 26 or a number." << std::endl;
                return 0;
            }
            
        } else {
            std::cout << "We did not understand " << std::string(argv[i]) << std::endl;
            return 0;
        }
    }

    std::string in;
    std::getline(std::cin, in);

    int i = -1;
    while (!honorCasing && in[++i]) in[i] = std::tolower(in[i]);

    if (isMapping)
        std::cout << "Mapping_cipher output is: " << mapping_cipher(in, (decrypt)? flip_mapping(mapping) : mapping) << std::endl;
    else
        std::cout << "Cipher output is: " << cipher(in, std::atoi(mapping.c_str())) << std::endl;

    return 0;
}