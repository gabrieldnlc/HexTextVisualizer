
// FOR OLD MAIN ONLY

#include <string>
#include <sstream>
#include <vector>
#include <iostream>

#include "BinaryOpen.hpp"
#include "MirroredHex.hpp"

using std::string;
using std::vector;

// FOR OLD MAIN ONLY

#include "Application.hpp"

#ifndef HEX_DEBUG
#include "Windows.h"
#endif


int main(int, char**)
{
#ifndef HEX_DEBUG
    FreeConsole();
#endif

    string infile = "names.bin";
    auto data(binary_load<vector<std::uint8_t>>(infile));

    tables::MirroredHex mirror(std::move(data));

    gui::Application app(std::move(mirror));
    return app.Start();
}

int main_old(int argc, char* argv[])
{
    //string infile = argv[1];
    


    auto x = "baba booey";
    //binary_save(data, outfile);

    return 0;
}