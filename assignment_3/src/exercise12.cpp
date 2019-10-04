#include <iostream>
#include <tuple>
using namespace std;

#define NTH_BIT(n, k) ((n & ( 1 << k )) >> k)

long pow_mod_n(long base, long power, long n, long value = 1, long index = 32)
{
    if (index == -1) return value % n; // if we looked at all bits return value, 

    value = (value * value) % n;
    if (NTH_BIT(power, index)) value = (value * base) % n; // if bit is 1, multiply by the base  (%n)
    
    return pow_mod_n(base, power, n, value, --index); // next bit
}

int lcm(int n1, int n2)
{
    int max = std::max(n1, n2);
    do {
        if (max % n1 == 0 && max % n2 == 0)
            return max;
        else
            ++max;
    } while (true);

    return -1;
}

class RsaUser {
    int N, e, d;

    private:
    int modular_multiplicative_inverse(int e, int p, int q) {
        int d = 0;
        while ((e*d) % lcm((p-1),(q-1)) != 1)  { d += 1; }
        return d;
    }
 
    public:
        RsaUser(int p, int q, int e) : N(p*q), e(e), d(modular_multiplicative_inverse(e, p, q)) {}
        
        std::tuple<int, int> get_public_key() { return {e, N}; }
        int encrypt(int M, std::tuple<int, int> publicKey) { return pow_mod_n(M, std::get<0>(publicKey), std::get<1>(publicKey)); }
        int decrypt(int C) { return pow_mod_n(C, d, N); }
};

int main(int argc, char const *argv[])
{
// • What is the public key, what is the private key?
    int p = 31, q = 41; // d = mmi(e) private key
    int N = p*q, e = 7; //            Public key 

    RsaUser user1 = RsaUser(p, q, e);

    // https://en.wikipedia.org/wiki/Modular_multiplicative_inverse
    p = 61; q = 53; // d = mmi(e) private key
    N = p*q; e = 17; //            Public key 

    RsaUser user2 = RsaUser(p, q, e);


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
