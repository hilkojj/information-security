#include <iostream>
#include <tuple>
using namespace std;

long pow_mod_n(int base, int power, int n)
{
    std::cout << base << " " << power << " " << n << "\n"; 
    if(power == 0) return 0;
    if(power == 1) return base;
    return (base * pow_mod_n(base, power-1, n)) % n;
}

class RsaUser {
    int N, e, d;
 
    public:
        RsaUser(int p, int q, int e, int d) : N(p*q), e(e), d(d) {}
        
        std::tuple<int, int> get_public_key() { return {N, e}; }
        int encrypt(int M, std::tuple<int, int> publicKey) { return pow_mod_n(M, std::get<0>(publicKey), std::get<1>(publicKey)); }
        int decrypt(int C) { return pow_mod_n(C, d, N); }
};

int main(int argc, char const *argv[])
{
// • What is the public key, what is the private key?
    int p = 31, q = 41, d = 13; // private key
    int N = p*q, e = 7; // Public key 

    RsaUser user1 = RsaUser(p, q, e, d);

    p = 11; q = 19; d = 5; // private key
    N = p*q; e = 3; // Public key 

    RsaUser user2 = RsaUser(p, q, e, d);


    int M = 42; // Message
    int C = user1.encrypt(M, user2.get_public_key()); // Cipher text


// • If the message is 42, what is the encrypted message?
    cout << "Message: " << M << "\n";
    cout << "Encrypted message: " << C << "\n\n\n";
    

// • What does the receiver have to do to retrieve 42 from the received encrypted
//   message? Show the steps to retrieve the unencrypted message.
    int oldM = user2.decrypt(C); // decript it using the priate key

    cout << "Original message: " << oldM << "\n";

    return 0;
}
