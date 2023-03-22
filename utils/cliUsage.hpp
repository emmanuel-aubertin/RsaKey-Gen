#include <iostream>
#include <string>

class cliUsage
{
    private:
        static const std::string PROGNAME;
        static const std::string RELEASE;
        static const std::string AUTHOR;
        static const std::string COPYRIGHT;

    public:
        void static print_release();
        void static print_usage();
        void static print_help();
        void static print_keygen_usage();
};