#include <string>
#include <iostream>
#include "RsaKey.hpp"
#include <math.h>
#include "/opt/homebrew/include/gmpxx.h" // May change for you
#include <ctime>
#include <vector>

#define DEBUG



RsaKey::RsaKey(){}

/**
 * @brief Construct a new Rsa Key:: Rsa Key object from public_key and n
 * 
 * @param public_key 
 * @param n 
 */
RsaKey::RsaKey(mpz_class public_key, mpz_class n)
{
    gmp_randclass rand(gmp_randinit_default);
    rand.seed(time(NULL));
    this->public_key = public_key;
    this->n= n;

    mpz_class sqrt_n;
    mpz_sqrt(sqrt_n.get_mpz_t(), n.get_mpz_t());

   for(mpz_class i(3); i < sqrt_n; i += 2){
        this->p = i;
        if(mpz_probab_prime_p(this->p.get_mpz_t(), 50) != 0 && n % this->p == 0){
            this->q = n/this->p;
            break;
        }
   }

    //phi_n
    this->phi_n = (this->p - 1) * (this->q - 1);
    genPriv();

}

/**
 * @brief  Construct a new Rsa Key:: Rsa Key object from the bit size.
 * 
 * @param inKey_size must not be to big
 * 
 * @author Aubertin Emmanuel (aka aTHO_)
 */
RsaKey::RsaKey(unsigned int inKey_size)
{
    #ifdef DEBUG
        std::cout << "Create New key : " << std::endl;
    #endif
    bits_Key_size = inKey_size;
    mpz_class mpz_exp = inKey_size;
    mpz_class mpz_two = 2;
    mpz_pow_ui(key_size.get_mpz_t(), mpz_two.get_mpz_t(), mpz_exp.get_ui());
    this->genKey();
}

mpz_class RsaKey::fast_mod(mpz_class x, mpz_class y) {
    return (x - y * (x / y));
}

int RsaKey::is_prime(mpz_class n) {
    long primeNumber[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997};
    for(long currPrime : primeNumber){
        if(fast_mod(n, currPrime) != 0) {
            return false;
        }
    }
    return true;
}

/**
 * @brief Gen all value of a RSA key from the bit size
 * 
 * @author Aubertin Emmanuel (aka aTHO_)
 */
void RsaKey::genKey() {
    gmp_randclass rand(gmp_randinit_default);
    rand.seed(time(NULL));

    #ifdef DEBUG
        std::cout << "Genereting p" << std::endl;
    #endif
    // gen p
    mpz_class key_size_2(this->key_size/2);
    this->p = rand.get_z_bits(bits_Key_size);
    do {
        mpz_class out;
        mpz_ui_pow_ui(out.get_mpz_t(), 2, bits_Key_size-1);

        // 2^(size)
        mpz_class bound;
        mpz_ui_pow_ui(bound.get_mpz_t(), 2, bits_Key_size);

        // random offset
        mpz_class rand_nb = rand.get_z_range(bound-out);

        this->p = out + rand_nb;
    } while(mpz_probab_prime_p(this->p.get_mpz_t(), 50) == 0 || this->p < 2);

    // gen q
    #ifdef DEBUG
        std::cout << "\tp = " << p << std::endl;
        std::cout << "Genereting q" << std::endl;
    #endif
    this->q = 0;
    do {
            mpz_class out;
            mpz_ui_pow_ui(out.get_mpz_t(), 2, bits_Key_size-1);

            // 2^(size)
            mpz_class bound;
            mpz_ui_pow_ui(bound.get_mpz_t(), 2, bits_Key_size);

            // random offset
            mpz_class rand_nb = rand.get_z_range(bound-out);

        this->q = out + rand_nb;
    } while(mpz_probab_prime_p( this->q.get_mpz_t(), 50 )  == 0  || q < 2 || q==p);

    #ifdef DEBUG
        std::cout << "\tq = " << q << std::endl;
        std::cout << "Genereting n & phi(n)" << std::endl;
    #endif


    //n
    this->n = p*q;
    //phi_n
    this->phi_n = (this->p - 1) * (this->q - 1);
    
    #ifdef DEBUG
        std::cout << "\tn = " << n << std::endl;
        std::cout << "\tphi(n) = " << phi_n << std::endl;
        std::cout << "Genereting publicKey" << std::endl;
    #endif


    // gen publicKey

   // mpz_class first_inter = key_size /4;
    do {

        // random offset
        mpz_class rand_nb = rand.get_z_range(this->phi_n);
        #ifdef DEBUG
            std::cout << "\tpublic_key = " << this->public_key << std::endl;
        #endif
        this->public_key = rand_nb;
    } while(this->public_key < this->phi_n && gcd(this->public_key, this->phi_n) != 1 );


    #ifdef DEBUG
        std::cout << "\tpublic_key = " << public_key << std::endl;
        std::cout << "Genereting private_key" << std::endl;
    #endif

    genPriv();

    #ifdef DEBUG
        std::cout << "\tprivate_key = " << private_key << std::endl;
        std::cout << "Key has been created" << std::endl;
    #endif

    mpz_class dp, dq;
    mpz_class p_1(p-1);
    mpz_class q_1(q-1);
    mpz_invert(dp.get_mpz_t(), public_key.get_mpz_t(), p_1.get_mpz_t());
    mpz_invert(dq.get_mpz_t(), public_key.get_mpz_t(), q_1.get_mpz_t());
}

/**
 * @brief Crypt a value m.
 * If the returned value is -1, may come if your public_key or n is null.
 * 
 * @param m Value to crypt 
 * @return mpz_class 
 * 
 * @author Aubertin Emmanuel (aka aTHO_)
 */
mpz_class RsaKey::crypt(mpz_class m){
    if(public_key == NULL || n == NULL){
        std::cout << "Missing value in your key : public_key or n" << std::endl;
        return -1;
    }
    mpz_class result;
    mpz_powm(result.get_mpz_t(), m.get_mpz_t(), this->public_key.get_mpz_t(), n.get_mpz_t());
    return result;
}

/**
 * @brief Crypt a message with multiple value.
 * If the vector returned is empty, may come if your private_key or public_key or n is null.
 * 
 * @param c Vector of the crypted message
 * @return std::vector<mpz_class> 
 * 
 * @author Aubertin Emmanuel (aka aTHO_)
 */
std::vector<mpz_class> RsaKey::crypt(std::vector<mpz_class> c){
    if(public_key == NULL || n == NULL){
        std::cout << "Missing value in your key : public_key or n" << std::endl;
        return std::vector<mpz_class>();
    }
    std::vector<mpz_class> ouputM;
    ouputM.reserve(c.size());
    for(const auto& x : c) {
        ouputM.emplace_back(crypt(x));
    }
    return ouputM;
}


/**
 * @brief Decrypt a value c.
 * If the returned value is -1, may come if your private_key or n is null.
 * 
 * @param c 
 * @return mpz_class 
 * 
 * @author Aubertin Emmanuel (aka aTHO_)
 */
mpz_class RsaKey::decrypt(mpz_class c){
    if(private_key == NULL || n == NULL){
        std::cout << "Missing value in your key : private_key or n" << std::endl;
        return -1;
    }
    mpz_class result;
    mpz_powm(result.get_mpz_t(), c.get_mpz_t(),  private_key.get_mpz_t(), n.get_mpz_t());
    return result ;
}


/**
 * @brief Decrypt a message with multiple value.
 * If the vector returned is empty, may come if your private_key or public_key or n is null.
 * 
 * @param c Vector of the crypted message
 * @return std::vector<mpz_class> 
 * 
 * @author Aubertin Emmanuel (aka aTHO_)
 */
std::vector<mpz_class> RsaKey::decrypt(std::vector<mpz_class> c){
    if(public_key == NULL || private_key == NULL || n == NULL){
        std::cout << "Missing value in your key : private_key or public_key or n" << std::endl;
        return std::vector<mpz_class>();
    }
    std::vector<mpz_class> ouputM;
    ouputM.reserve(c.size());
    for(const auto& x : c) {
        ouputM.emplace_back(decrypt(x));
    }
    return ouputM;
}

/**
 * @brief Generate the private key with extended Euclid algorithm.
 * For use this method you need phi_n and public_key
 * 
 * @author Aubertin Emmanuel (aka aTHO_)
 */
void RsaKey::genPriv() {
mpz_class r(this->phi_n);
    mpz_class r_(this->public_key);
    mpz_class u(1);
    mpz_class v(0);
    mpz_class u_(0);
    mpz_class v_(1);
    while (r_!=0){
        mpz_class q(r/r_);

        mpz_class rs(r);
        mpz_class us(u);
        mpz_class vs(v);

        r=r_;
        u=u_;
        v=v_;

        r_=rs-q*r_;
        u_=us-q*u_;
        v_=vs-q*v_;

    }
    if(v < 0){
        this->private_key = v + phi_n;
        return;
    }
    this->private_key = v;
}


/**
 * @brief This public method check if a RSA Key well work.
 * For this check we crypt m, and decrypt.
 * 
 * @return true m_decrypt = m soo the current key work
 * @return false m_decrypt != m soo the current key don't work
 * 
 * @author Aubertin Emmanuel (aka aTHO_)
 */
bool RsaKey::isValidKey(){
    mpz_class m = 9197;
    mpz_class c_test = crypt(m);
    mpz_class m_decrypt = decrypt(c_test);
    #ifdef DEBUG
        std::cout << m << " => " << c_test << std::endl;
        std::cout << c_test << " => " << m << std::endl;
    #endif
    return m_decrypt == m;
}

/**
 * @brief Print info on the key , such as private and public. It also print the arithmetic information of the key (p, q, phi(n), n).
 * 
 * @author Aubertin Emmanuel (aka aTHO_) 
 */
void RsaKey::print_key(){
    std::cout << "##############################################" << std::endl;
    std::cout << "| Key length : " << this->bits_Key_size << std::endl;
    std::cout << "|----------------------------------------------" << std::endl;
    std::cout << "| public key\t==> " << this->public_key << std::endl;
    std::cout << "| private key\t==> " << this->private_key << std::endl;
    std::cout << "|----------------------------------------------" << std::endl;
    std::cout << "| Extra info : " << std::endl;
    std::cout << "| \tn = " << this->n << std::endl;
    std::cout << "| \tphi(n) = " << this->phi_n << std::endl;
    std::cout << "| \tp = " << this->p << std::endl;
    std::cout << "| \tq = " << this->q << std::endl;
    std::cout << "##############################################" << std::endl;
}

// clang++ -I/opt/homebrew/Cellar/gmp/6.2.1_1/include -L/opt/homebrew/Cellar/gmp/6.2.1_1/lib -lgmp -lgmpxx  main.cpp utils/*


// g++ -I/usr/include -L/usr/lib -I/opt/homebrew/Cellar/gmp/6.2.1_1/include -L/opt/homebrew/Cellar/gmp/6.2.1_1/lib -lgmpxx -lgmp -std=c++14 main.cpp utils/*