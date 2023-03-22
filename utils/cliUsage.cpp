#include <string>
#include <iostream>
#include "cliUsage.hpp"

const std::string cliUsage::PROGNAME="RsaKey cli";
const std::string cliUsage::RELEASE="Rev 0.1a | Last update 22 mar 2023";
const std::string cliUsage::AUTHOR="Aubertin Emmanuel (aka aTHO_)";
const std::string cliUsage::COPYRIGHT="(c) 2023 "+ AUTHOR + "\n";

/**
 * @brief Print current realse information
 * 
 */
void cliUsage::print_release() {
    std::cout << RELEASE << std::endl << COPYRIGHT << std::endl;
}

/**
 * @brief Print usage guide for user
 * 
 */
void cliUsage::print_usage() 
{
        std::cout << std::endl << cliUsage::PROGNAME << std::endl;
        std::cout << "Contrl+c for exit" << std::endl;
        std::cout << "List of all avaible commande :" << std::endl;
        std::cout << "\tkeygen  \tGeneration of RSA key" << std::endl;
        std::cout << "\tcrypt   \tcrypt a message with the current key. You need to do keygen before." << std::endl;
        std::cout << "\tdecrypt \tdecrypt a message with the current key. You need to do keygen before." << std::endl;
}

/**
 * @brief Print Help for User, this help include print_release and print_usage.
 * 
 */
void cliUsage::print_help() {
        cliUsage::print_release();
        cliUsage::print_usage();
        std::cout << std::endl;
}

void cliUsage::print_keygen_usage(){
        std::cout << std::endl << "keygen" << std::endl;
        std::cout << "Usage:" << " keygen" << "| [-h | --help] | [-s | --size] | [-pub | --public-key] & [-n] "<< std::endl;
        std::cout << "\t-h    \tHelp" << std::endl;
        std::cout << "\t-s    \tRSA key gen with bits size" << std::endl;
        std::cout << "\t-pub  \tGen RSA with public key /!\\ You need -n too /!\\ " << std::endl;
        std::cout << "\t-n    \tGen RSA with n /!\\ You need -pub too /!\\" << std::endl;
        std::cout << std::endl << "Example : " << std::endl << "\tkeygen  -s 1024" << std::endl;
        std::cout << "\tkeygen  -pub 163119273 -n 755918011" << std::endl;
}