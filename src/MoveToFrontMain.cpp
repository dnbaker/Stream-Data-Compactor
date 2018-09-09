#include <iostream>
#include <iomanip>
#include <string>

#include "shared.h"

#include "MoveToFront.h"
#include <getopt.h>

namespace
{
    const size_t ERROR_IN_COMMAND_LINE = 1;
    const size_t SUCCESS = 0;
    const size_t ERROR_UNHANDLED_EXCEPTION = 2;

} // namespace

void usage() {
    std::fprintf(stderr, "-h/--help: Emit help menu\n"
                         "-e/--encode: Encode\n"
                         "-d/--decode: Decode\n"
                         "-x/--hexdump: Emit in hex format\n");
}

int main(int argc, char** argv)
{
    int c, option_index;
    bool encode(false), decode(false), use_hex(false);
    static struct option long_options[] =
        {
          /* These options don’t set a flag.
             We distinguish them by their indices. */
          {"help",     no_argument,      0, 'h'},
          {"encode",   no_argument,      0, 'e'},
          {"decode",   no_argument,      0, 'd'},
          {"hexdump",   no_argument,     0, 'x'},
          {0, 0, 0, 0}
        };
    while((c = getopt_long(argc, argv, "hexd", long_options, &option_index)) >= 0) {
        switch(c) {
            case 'e': encode  = true; break;
            case 'd': decode  = true; break;
            case 'x': use_hex = true; break;
            case 'h':
                std::cout << "Move to front command line tool" << std::endl <<
                    "Usage: " << basename(argv[0]) << " [-h+-] [-x]" << std::endl;
                usage();
                std::exit(EXIT_FAILURE);
        }
    }

    std::string appName = basename(argv[0]);
    /** Define and parse the program options
     *      */

    if (encode)
    {
        if (use_hex)
        {
            std::stringstream sout;
            bw::MoveToFront::encode(std::cin, sout);
            int bytes = 0;
            char c;
            while (sout.get(c))
            {
                std::cout << std::hex << std::setfill('0') << std::setw(2) << (int) c << " ";
                bytes++;
            }

            std::cout.clear();
            std::cout << std::endl << std::dec << bytes * 8 << " bits" << std::endl;
        }
        else
        {
            bw::MoveToFront::encode(std::cin, std::cout);
        }
    }

    if (decode)
    {
        bw::MoveToFront::decode(std::cin, std::cout);
    }

    return SUCCESS;

} // main
