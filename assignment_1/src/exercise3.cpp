#include <iostream>
#include <string>

char decrypt(char c) { return (26 + c - 1 - 'a') % 26 + 'a'; }
char encrypt(char c) { return (c + 1 - 'a') % 26 + 'a'; }

int main()
{
    std::string txt, line;
    while(std::getline(std::cin, line)) txt += line + "\n"; // we now keep reading until an EOF

    for (int j = 1; j <= 26; j++) // fixed the of by one error
    {
        int i = -1;
        while (txt[++i]) txt[i] = decrypt(txt[i]);

        std::cout << "\n\n---Decrypt----\n" << j << "\n" << txt;
    }

    for (int j = 1; j <= 26; j++)
    {
        int i = -1;
        while (txt[++i]) txt[i] = encrypt(txt[i]);

        std::cout << "\n\n---Encrypt----\n" << j << "\n" << txt;
    }

    return 0;
    /*
    ----> Decrypting requires a shift of 7 <-----
    ----> Encrypting requires a shift of 19 <-----
    */
}
