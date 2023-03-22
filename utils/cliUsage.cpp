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
        std::cout << "List of all avaible commande :" << std::endl;
        std::cout << "\t\tkeygen \tGeneration of RSA key" << std::endl;
}

/**
 * @brief Print Help for User, this help include print_release and print_usage.
 * 
 */
void cliUsage::print_help() {
        cliUsage::print_release();
        cliUsage::print_usage();
        std::cout << std::endl;
        exit(0);    
}

void cliUsage::print_keygen_usage(){
        std::cout << std::endl << "keygen" << std::endl;
        std::cout << "Usage:" << "keygen" << "| [-s | --size] "<< std::endl;
        std::cout << "\t\t-h  Help" << std::endl;
        std::cout << "\t\t-s  RSA key gen with bits size" << std::endl;
        std::cout << std::endl << "Example : ./" << "keygen  -s 1024" << std::endl;
}