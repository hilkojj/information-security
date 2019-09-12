#include <iostream>
#include <string>


int main()
{
    std::string txt = "dlsjvtlavaoljvbyzlhivbapumvythapvuzljbypafaopzjvby"
                    "zlpzhivbazljbypunpumvythapvupuaopzjvualeadlaopurmv"
                    "ylehtwslhivbaovdavwylcluaaolbuhbaovypglkylhkpunvmp"
                    "umvythapvuvyhivbaovdavwylcluaaolbuhbaovypglktvkpmp"
                    "jhapvuvmpumvythapvulujyfwapvupzaolihzpjavvsmvyzljb"
                    "ypunpumvythapvuthuflujyfwapvutlaovkzlepzazvtlhsylh"
                    "kfaovbzhukzflhyzvskpupaphssfdlssmvjbzvuzptwsltlaov"
                    "kzavlujyfwapumvythapvumvssvdpunaopzdlssbzljohyhjal"
                    "ypzapjchsblzpkluapmfpunpumvythapvuthrpunpakpmmpjbs"
                    "aavtvkpmfpumvythapvubuuvapmplkshalypuaopzjvbyzldls"
                    "spuayvkbjlwlyzvuhslujyfwapvudhfzavjvuayvshjjlzzavp"
                    "umvythapvuhukovdavrllwfvbywypchjfdlovwlfvbdpssluqv"
                    "faopzjvbyzlhivbapumvythapvuzljbypaf";

    for (int j = 0; j < 26; j++)
    {
        int i = -1;
        while (txt[++i]) txt[i] = (txt[i] + 1 - 'a') % 26 + 'a';

        std::cout << "\n\n-------\n" << j << "\n" << txt;
    }
    return 0;
    /*
    ----> 18 <-----
    welcome to the course about information security
    this course is about securing information
    in this context we think for example about how to prevent the unauthorized reading of information or about how to prevent the unauthorized modification of information
    encryption is the basic tool for securing information
    many encryption methods exist some already thousands years old initially well focus on simple methods to encrypt information following this well use characteristic values identifying information making it difficult to modify information unnotified
    later in this course well introduce personal encryption ways to control access to information and how to keep your privacy
    we hope you will enjoy this course about information security
    */
}
