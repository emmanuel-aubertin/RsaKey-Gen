#include <iostream>
#include "utils/appInfo.hpp"
#include "utils/RsaKey.hpp"
#include <math.h>
#include <stdlib.h>
#include "/opt/homebrew/include/gmp.h" // May change for you
#include <string>
#include <vector>

#define DEBUG // DEBUG MOD

// GEN KEY with e and n, and decrypt a msg
#define DEBUG_DECRYPT_WITH_E_N
//Set big a e and n
#define DEBUG_DECRYPT_WITH_BIG_E_N

//#define DEBUG_KEY_GEN_BITS // q1
int main(int argc, char **argv)
{
    #ifdef DEBUG
        std::cout << "Running in DEBUG mode" << std::endl;
    #endif
    int keySize = 4096;
    // PARSE ARG
    for(int i=1; i < argc; i++)
    {
        std::string currentArg = std::string(argv[i]);
        if(currentArg == "-v" || currentArg == "--version")
        {
            appInfo::print_release();
            continue;
        }
        if(currentArg == "-h" || currentArg == "--help")
        {
            appInfo::print_help();
            continue;
        }
        if(currentArg == "-s" || currentArg == "--size")
        {
            #ifdef DEBUG
                std::cout << "Key size : " << argv[i+1] << std::endl;
            #endif
            keySize = atoi(argv[++i]);
            continue;
        }
    }
    #ifdef DEBUG_DECRYPT_WITH_E_N
        auto start = std::chrono::system_clock::now();
        #ifdef DEBUG_DECRYPT_WITH_BIG_E_N
            std::vector<int> m_int = {671828605, 407505023, 288441355, 679172842, 180261802};
            std::vector<mpz_class> m;
            #ifdef DEBUG
                std::cout << "m.reserve(m_int.size());" << std::endl;
            #endif
            m.reserve(m_int.size());
            #ifdef DEBUG
                std::cout << "asign new value" << std::endl;
            #endif
            for (const auto& x : m_int) {
                m.emplace_back(x);
            }
            mpz_class e(163119273);
            mpz_class n(755918011);
        #else
            std::vector<int> m_int = {9197, 6284, 12836, 8709, 4584, 10239, 11553, 4584, 7008, 12523, 9862, 356, 5356, 1159, 10280, 12523, 7506, 6311};
            std::vector<mpz_class> m;
            #ifdef DEBUG
                std::cout << "m.reserve(m_int.size());" << std::endl;
            #endif
            m.reserve(m_int.size());
            #ifdef DEBUG
                std::cout << "asign new value" << std::endl;
            #endif
            for (const auto& x : m_int) {
                m.emplace_back(x);
            }
            mpz_class e(12413);
            mpz_class n(13289);
        #endif



            
        RsaKey myKey = RsaKey(e, n);
        #ifdef DEBUG
            auto end = std::chrono::system_clock::now();
            auto compute_time = (end - start);
            std::chrono::duration<double> elapsed_seconds = end-start;
            std::cout << "Compute time for key generation : " << elapsed_seconds.count() << std::endl;
        #endif
        myKey.print_key(); 


        if(!myKey.isValidKey()) {
            std::cerr << "Unvalide Key exit" << std::endl;
            exit(-1);
        }

        
        std::vector<mpz_class> c;
        c.reserve(m_int.size());
        c = myKey.decrypt(m);

         std::cout << "Decrypted msg :" << std::endl;
        for (const auto& x : c) {
            std::cout << x << " ";
        }
        std::cout << std::endl;
    #endif   

    #ifdef DEBUG_KEY_GEN_BITS
        auto start = std::chrono::system_clock::now();
    
        
        RsaKey myKey = RsaKey(keySize);
        #ifdef DEBUG
            auto end = std::chrono::system_clock::now();
            auto compute_time = (end - start);
            std::chrono::duration<double> elapsed_seconds = end-start;
            std::cout << "Compute time for key generation : " << elapsed_seconds.count() << std::endl;
        #endif
        myKey.print_key();
        #ifdef DEBUG
            start = std::chrono::system_clock::now();
        #endif
        
        if(!myKey.isValidKey()) {
            std::cerr << "Unvalide Key exit" << std::endl;
            exit(-1);
        }

        mpz_class m = 9197;
        mpz_class c = myKey.crypt_with_pub_mod(m);
        #ifdef DEBUG
            end = std::chrono::system_clock::now();
            compute_time = (end - start);
            elapsed_seconds = end-start;
            std::cout << "Compute time for crypt : " << elapsed_seconds.count() << std::endl;
        #endif
        std::cout << m << " => " << c << std::endl;

        #ifdef DEBUG
            start = std::chrono::system_clock::now();
        #endif


        m = myKey.decrypt(c);
        #ifdef DEBUG
            end = std::chrono::system_clock::now();
            compute_time = (end - start);
            elapsed_seconds = end-start;
            std::cout << "Compute time for DEcrypt : " << elapsed_seconds.count() << std::endl;
        #endif
        std::cout << c << " => " << m << std::endl;

        #ifdef DEBUG
            start = std::chrono::system_clock::now();
        #endif
    #endif
    return 0;
}