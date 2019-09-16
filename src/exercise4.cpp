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
    // return std::sqrt( sum((x * x)) / 26.0 - std::pow( sum(x) / 26.0, 2) );
    double length = x.size();
    double E = 0;
    double Ravg = sum(x) / length;
    for (auto ri : x)
        E += std::pow(ri.second - Ravg, 2);
    return std::sqrt( E / (length - 1));
}

void magic(std::string data)
{
    int sd[16];
    for (int k = 5; k <= 15; k++)
    {
        double sum = 0;
        for (int block = 0; block < data.length() / k; block++)
        {
            std::map<char, int> freq;
            for (int i = block * k; i < block * k + k; i++)
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

    /*
    i came to security from cryptography and thought of the problem in a military like fashion
    most writings about security come from this perspective and it can be summed up pretty easily
    security threats are to be avoided using preventive countermeasures
    this is how encryption works
    the threat is eaves dropping and encryption provides the prophylactic
    this could all be explained with block diagrams
    alice is communicating with bob
    both are identified by boxes and there is a line between them signifying the communication
    eve is the eaves dropper she also is a box and has a dotted line attached to the communications line
    she is able to intercept the communication
    the only way to prevent eve from learning what alice and bob are talking about is through apreventive
    counter measure encryption theres no detection theres no response theres no risk management
    you have to avoid the threat for decades we have used this approach to computer security
    we draw boxes around the different players and lines between them
    we defined if ferent attackers eaves droppers impersonators thieves and their capabilities
    we use preventive countermeasures like encryption and access control to avoid different threats
    if we can avoid the threats weve won if we cant weve lost
    imagine my surprise when i learned that the world doesnt work this way
    some history from the vigenere wikipage
    the first well documented description of apolyalphabetic cipher was
    formulated by leon battistaalberti around and use dametal cipher disc to
    switch between cipher alphabets albert is system only switched alphabets after several words and switches were indicated by writing the letter of thecorrespondingalphabetintheciphertextlaterinjohannestrithemiusinhisworkpoligraphiainventedthetabularectaacriticalcomponentofthevigenrecipherthetrithemiuscipherhoweveronlyprovidedaprogressiverigidandpredictablesystemforswitchingbetweencipheralphabetswhatisnowknownasthevigenerecipherwasoriginallydescribedbygiovanbattistabellasoinhisbooklacifradelsiggiovanbattistabellasohebuiltuponthetabularectaoftrithemiusbutaddedarepeatingcountersignakeytoswitchcipheralphabetseveryletterwhereasalbertiandtrithemiususedafixedpatternofsubstitutionsbellasosschememeantthepatternofsubstitutionscouldbeeasilychangedsimplybyselectinganewkeykeysweretypicallysinglewordsorshortphrasesknowntobothpartiesinadvanceortransmittedoutofbandalongwiththemessagebellasosmethodthusrequiredstrongsecurityforonlythekeyasitisrelativelyeasytosecureashortkeyphrasesaybyapreviousprivateconversationbellasossystemwasconsiderablymoresecureblaisedevigenerepublishedhisdescriptionofasimilarbutstrongerautokeycipherbeforethecourtofhenryiiioffranceinlaterinthethcenturytheinventionofbellasoscipherwasmisattributedtovigeneredavidkahninhisbookthecodebreakerslamentedthemisattributionbysayingthathistoryhadignoredthisimportantcontributionandinsteadnamedaregressiveandelementarycipherforhimvigenerethoughhehadnothingtodowithitthevigenereciphergainedareputationforbeingexceptionallystrongnotedauthorandmathematiciancharleslutwidgedodgsonlewiscarrollcalledthevigenerecipherunbreakableinhispiecethealphabetcipherinachildrensmagazineinscientificamericandescribedthevigenrecipherasimpossibleoftranslationthisreputationwasnotdeservedcharlesbabbageisknowntohavebrokenavariantofthecipherasearlyashoweverhedidntpublishhisworkkasiskientirelybrokethecipherandpublishedthetechniqueinthethcenturyevenbeforethisthoughsomeskilledcryptanalystscouldoccasionallybreakthecipherinthethcenturycryptographicslideruleusedasacalculationaidbytheswissarmybetweenandthevigenerecipherissimpleenoughtobeafieldcipherifitisusedinconjunctionwithcipherdiskstheconfederatestatesofamericaforexampleusedabrasscipherdisktoimplementthevigenerecipherduringtheamericancivilwartheconfederacysmessageswerefarfromsecretandtheunionregularlycrackedtheirmessagesthroughoutthewartheconfederateleadershipprimarilyrelieduponthreekeyphrasesmanchesterbluffcompletevictoryandasthewarcametoaclosecomeretributiongilbertvernamtriedtorepairthebrokenciphercreatingthevernamvigenerecipherinbutnomatterwhathedidthecipherwasstillvulnerabletocryptanalysisvernamsworkhowevereventuallyledtotheonetimepadaprovablyunbreakablecipher
    */
}   