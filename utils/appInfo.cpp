#include <string>
#include <iostream>
#include "appInfo.hpp"



const std::string appInfo::PROGNAME="RSA";
const std::string appInfo::RELEASE="Rev 0.1a | Last update 09 mar 2022";
const std::string appInfo::AUTHOR="Aubertin Emmanuel (aka aTHO_)";
const std::string appInfo::COPYRIGHT="(c) 2023 "+ AUTHOR + "\n";

/**
 * @brief Print current realse information
 * 
 */
void appInfo::print_release() {
    std::cout << RELEASE << std::endl << COPYRIGHT << std::endl;
}

/**
 * @brief Print usage guide for user
 * 
 */
void appInfo::print_usage() 
{
        std::cout << std::endl << appInfo::PROGNAME << std::endl;
        std::cout << "Usage:" << appInfo::PROGNAME << "| [-h | --help] | [-v | --version]  "<< std::endl;
        std::cout << "\t\t-h  Help" << std::endl;
        std::cout << "\t\t-v  Version" << std::endl;
        std::cout << "\t\t-s  RSA key gen with bits size" << std::endl;
        std::cout << std::endl << "Example : ./" << appInfo::PROGNAME << " -s 1024" << std::endl;
}

/**
 * @brief Print Help for User, this help include print_release and print_usage.
 * 
 */
void appInfo::print_help() {
        appInfo::print_release();
        appInfo::print_usage();
        std::cout << std::endl;
        exit(0);    
}