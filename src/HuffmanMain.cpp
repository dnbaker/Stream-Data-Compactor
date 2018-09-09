#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <fstream>
#include <getopt.h>

#include "shared.h"
#include "Huffman.h"
#include "istreambin.h"
#include "ostreambin.h"

namespace
{
    const size_t ERROR_IN_COMMAND_LINE = 1;
    const size_t SUCCESS = 0;
    const size_t ERROR_UNHANDLED_EXCEPTION = 2;

} // namespace
void usage() {
    std::fprintf(stderr, "-h/--help: Emit help menu\n"
                         "-i/--input: Set input file\n"
                         "-o/--output: Set input file\n"
                         "-e/--encode: Encode\n"
                         "-d/--decode: Decode\n"
                         "-x/--hexdump: Emit in hex format\n");
}


int main(int argc, char** argv)
{
    std::string sif;
    std::string sof;
    std::string appName = basename(argv[0]);
    int option_index, c;
    bool use_hex(false), encode(false), decode(false);
    static struct option long_options[] =
        {
          /* These options don’t set a flag.
             We distinguish them by their indices. */
          {"help",     no_argument,      0, 'h'},
          {"encode",   no_argument,      0, 'e'},
          {"decode",   no_argument,      0, 'd'},
          {"hexdump",   no_argument,     0, 'x'},
          {"output",   required_argument,     0, 'o'},
          {"input",   required_argument,     0, 'i'},
          {0, 0, 0, 0}
        };
    while((c = getopt_long(argc, argv, "i:o:hexd", long_options, &option_index)) >= 0) {
        switch(c) {
            case 'e': encode  = true; break;
            case 'd': decode  = true; break;
            case 'i': sif     = optarg; break;
            case 'o': sof     = optarg; break;
            case 'x': use_hex = true; break;
            case 'h':
                std::cout << "Huffman command line tool" << std::endl <<
                    "Usage: " << basename(argv[0]) << " [-h+-] [-x]" << std::endl;
                usage();
                std::exit(EXIT_FAILURE);
        }
    }

    std::ifstream ifs;
    std::ofstream ofs;
    if (sif.size())
        ifs.open(sif.c_str(), std::ios::binary | std::ios::in);
    if (sof.size())
        ofs.open(sof.c_str(), std::ios::binary | std::ios::out);

    bw::istreambin streamin(ifs.is_open() ? &ifs : &std::cin);
    bw::ostreambin streamout(ofs.is_open() ? &ofs : &std::cout);

    if (encode)
    {
        if (use_hex)
        {
            std::stringstream sout;
            bw::ostreambin streamout_ex(&sout);
            bw::Huffman::compress(streamin, streamout_ex);
            int bytes = 0;
            char c;
            while (sout.get(c))
            {
                std::cout << std::hex << std::setfill('0') << std::setw(2) << int(0xff & ((int) c)) << " ";
                bytes++;
            }

            std::cout.clear();
            std::cout << std::endl << std::dec << bytes * 8 << " bits" << std::endl;
        }
        else
        {
            bw::Huffman::compress(streamin, streamout);
        }
    }

    if (decode)
    {
        bw::Huffman::expand(streamin, streamout);
    }

    return SUCCESS;

} // main
