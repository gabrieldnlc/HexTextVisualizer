#include <string>
#include <vector>
#include <iostream>

#include "tclap/CmdLine.h"

#include "BinaryOpen.hpp"
#include "Application.hpp"


using std::string;
using std::vector;

using TCLAP::ArgException;
using TCLAP::CmdLine;
using TCLAP::ValueArg;
using TCLAP::UnlabeledValueArg;

int main(int argc, char** argv)
{
    try
    {
        CmdLine cmd("HexTables", ' ', "0.1");

        UnlabeledValueArg<string> f("filename", "Name of the file to be opened.", true, "", "string");
        cmd.add(f);

        cmd.parse(argc, argv);

        string infile = f.getValue();

        auto data(binary_load<vector<std::uint8_t>>(infile));

        gui::Application app(std::move(data), infile);
        return app.Start();
        
    }
    catch (const ArgException& err)
    {
        std::cout << "Could not parse command line arguments: " << err.what() << '\n';
    }

    
    
}