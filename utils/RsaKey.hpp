#include <iostream>
#include <string>
#include "/opt/homebrew/include/gmpxx.h" // May change for you
#include <vector>

class RsaKey
{
    private:
        const static mpz_class prime_number[25];
        mpz_class private_key;
        mpz_class public_key;
        mpz_class key_size;
        mpz_class p;
        mpz_class q;
        mpz_class phi_n;
        mpz_class n;
        mpz_class dp;
        mpz_class dq;
        mpz_class block_size;
        unsigned int bits_Key_size;
        void genKey();
        mpz_class fast_mod(mpz_class, mpz_class);
        int is_prime(mpz_class);
        void genPriv();
        mpz_class gen_block_size();
    public:
        RsaKey();
        RsaKey(unsigned int);
        RsaKey(mpz_class, mpz_class);
        void print_key();
        mpz_class crypt(mpz_class);
        mpz_class decrypt(mpz_class);
        bool isValidKey();
        std::vector<mpz_class> crypt(std::vector<mpz_class> c);
        std::vector<mpz_class> decrypt(std::vector<mpz_class>);
};