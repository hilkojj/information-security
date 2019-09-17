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
    welcome to the course about information security
    this course is about securing information
    in this context we think for example about how to prevent the unauthorized reading of information or about how to prevent the unauthorized modification of information
    encryption is the basic tool for securing information
    many encryption methods exist some already thousands years old initially well focus on simple methods to encrypt information following this well use characteristic values identifying information making it difficult to modify information unnotified
    later in this course well introduce personal encryption ways to control access to information and how to keep your privacy
    we hope you will enjoy this course about information security
    */
}
