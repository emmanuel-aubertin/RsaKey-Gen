#include <iostream>
#include "utils/appInfo.hpp"
#include "utils/RsaKey.hpp"
#include "utils/cliUsage.hpp"
#include <math.h>
#include <stdlib.h>
#include "/opt/homebrew/include/gmp.h" // May change for you
#include <string>
#include <vector>


RsaKey keygen(unsigned int);
RsaKey keygen_from_pub_n(mpz_class , mpz_class);
void cli_engine();
void cli_cmd_parseur(char* cmd);

// Global var key
RsaKey key;

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
    unsigned int keySize = 0;
    mpz_class public_key(0);
    mpz_class n(0);
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
        if(currentArg == "-pub" || currentArg == "--public-key")
        {
            #ifdef DEBUG
                std::cout << "Public key : " << argv[i+1] << std::endl;
            #endif
            public_key = argv[++i];
            continue;
        }
        if(currentArg == "-n")
        {
            #ifdef DEBUG
                std::cout << "n : " << argv[i+1] << std::endl;
            #endif
            n = argv[++i];
            continue;
        }
        if(currentArg == "-cli" || currentArg == "--command-line")
        {
            cli_engine();
            continue;
        }
    }


    if(keySize != 0) {
        keygen(keySize);
    }

    if(public_key != 0 || n != 0) {
        if(n == 0) {
            std::cout << "MISSING -n, see usage :" << std::endl;
            appInfo::print_usage();
            return -1;
        } else if(public_key == 0) {
            std::cout << "MISSING -pub, see usage :" << std::endl;
            appInfo::print_usage();
            return -1;
        }
        keygen_from_pub_n(public_key, n);
    }
     


    return 0;
}

std::vector<mpz_class> cast_str_ascii(std::string inStr){
    std::vector <mpz_class> output;
    for (int i = 0; i < inStr.length(); i++)
    {
        output.push_back((mpz_class)((int)  inStr[i]));
    }
    return output;
}

RsaKey keygen(unsigned int keySize) {
    // KEY GEN
    auto start = std::chrono::system_clock::now();
    
    RsaKey myKey = RsaKey(keySize);

    auto end = std::chrono::system_clock::now();
    auto compute_time = (end - start);
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "Compute time for key generation : " << elapsed_seconds.count() << std::endl;

    myKey.print_key();

    if(!myKey.isValidKey()) {
        std::cerr << "Unvalide Key exit" << std::endl;
        exit(-1);
    }
    return myKey;
}


RsaKey keygen_from_pub_n(mpz_class public_key, mpz_class n){
         #ifdef DEBUGwc
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

        RsaKey myKey = RsaKey(public_key, n);
        myKey.print_key(); 
        
        if(!myKey.isValidKey()) {
            std::cerr << "Unvalide Key exit" << std::endl;
            exit(-1);
        }
        
        return myKey;
}

void cli_engine() {
    printf(">");
    char cmd[256];
    while(fgets(cmd, sizeof(cmd), stdin)){
        std::cout << cmd << std::endl;
        if(cmd != "") {
            cli_cmd_parseur(cmd);
        }
        printf(">");
    }
}

char ** line_to_argv(char* inputChar) {
    char * goodChar = strdup(inputChar);
    char** output ;
    output = (char**) malloc(256 * sizeof(inputChar));
    const char* s = "\n\t ";
    char* line = strtok(goodChar, s);
    int i = 0;
    while (line != NULL) {
        output[i] =line;
        i++;
        line = strtok(NULL, s);
    }
    return output;
}

void cli_cmd_parseur(char* cmd){
    
    char** cmd_agrv ;
    cmd_agrv = (char**) malloc(256 * sizeof(cmd));
    cmd_agrv= line_to_argv(cmd);
    int i = 0;
    // LAUNCH CMD
    if(strcmp(cmd_agrv[0],"test") == 0) {
        if(cmd_agrv[1]){
            std::cout << "This the test commande, all arg will be printed : " << std::endl;
            i = 1;
            while(cmd_agrv[i]){
                std::cout << i << " : " << cmd_agrv[i] << std::endl;
                i++;
            }
            return;
        }
        std::cout << "Ok just a test " << std::endl;
        return;
    }

    /**
     * @brief KEYGEN CMD
     */
    if(strcmp(cmd_agrv[0],"keygen") == 0) {
        mpz_class public_key(0);
        mpz_class n(0);
        if(!cmd_agrv[1]){
            cliUsage::print_keygen_usage();
            return;
        }
        i = 1;
        while(cmd_agrv[i] != NULL)
        {
            std::string currentArg = std::string(cmd_agrv[i]);
            // GENKEY WITH SIZE
            if(currentArg == "-s" || currentArg == "--size")
            {
               key = keygen(atoi(cmd_agrv[++i]));
               i++;
               continue;
            }
            if(currentArg == "-pub" || currentArg == "--public-key")
            {
                public_key = cmd_agrv[++i];
                i++;
                continue;
            }
            if(currentArg == "-n")
            {
                n = cmd_agrv[++i];
                i++;
                continue;
            }
        }
        std::cout << "Out of while" << std::endl;
        if(public_key != 0 || n != 0) {
            if(n == 0) {
                std::cout << "MISSING -n, see usage :" << std::endl;
                cliUsage::print_keygen_usage();
                return;
            } else if(public_key == 0) {
                std::cout << "MISSING -pub, see usage :" << std::endl;
                cliUsage::print_keygen_usage();
                return;
            }
            std::cout << "Generating the key" << std::endl;
            key = keygen_from_pub_n(public_key, n);
        }
        return;
        
    }

    /**
     * @brief CRYPT
     */
    if(strcmp(cmd_agrv[0],"crypt") == 0) {
        i = 1;
        while(cmd_agrv[i] != NULL)
        {
            std::string currentArg = std::string(cmd_agrv[i]);
            if(currentArg == "-m" || currentArg == "--message")
            {
                std::string mStr;
                while(cmd_agrv[++i]){
                    mStr += cmd_agrv[i];
                    mStr += " ";
                }
                std::vector<mpz_class> acsii_m = cast_str_ascii(mStr);
                #ifdef DEBUG    
                    for(mpz_class x : acsii_m){
                        std::cout << x << " ";
                    }std::cout << std::endl;
                #endif
                std::vector<mpz_class> c = key.crypt(acsii_m);
                #ifdef DEBUG    
                    for(mpz_class x : c){
                        std::cout << x << " ";
                    }std::cout << std::endl;
                #endif
                i++;
               continue;
            }
        }
    }

    /**
     * @brief DECRYPT
     */
    if(strcmp(cmd_agrv[0],"decrypt") == 0) {
        i = 1;
        while(cmd_agrv[i] != NULL)
        {
            std::string currentArg = std::string(cmd_agrv[i]);
            if(currentArg == "-m" || currentArg == "--message")
            {
                std::vector<mpz_class> acsii_c;
                while(cmd_agrv[++i]){
                    acsii_c.push_back(mpz_class(cmd_agrv[i]));
                    
                }
                
                #ifdef DEBUG    
                    for(mpz_class x : acsii_c){
                        std::cout << x << " ";
                    }std::cout << std::endl;
                #endif
                std::vector<mpz_class> c = key.decrypt(acsii_c);
                #ifdef DEBUG    
                    for(mpz_class x : c){
                        std::cout << static_cast<char>(x.get_ui());
                    }std::cout << std::endl;
                #endif
                i++;
               continue;
            }
        }
    }

}