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
        CmdLine cmd("Hex Text Visualizer", ' ', "0.1");

        UnlabeledValueArg<string> f("filename", "Name of the file to be opened.", true, "", "string");
        cmd.add(f);
        ValueArg<int> s("s", "start", "Table first byte", false, 0, "integer");
        cmd.add(s);
        ValueArg<int> e("e", "end", "Table last byte", false, -1, "integer");
        cmd.add(e);

        cmd.parse(argc, argv);

        string infile = f.getValue();
        int table_start = s.getValue();
        int table_end = e.getValue();

        vector<int> data(binary_load<vector<int>>(infile));

        if (table_end < 0)
        {
            table_end = data.size() - 1;
        }

        if (table_start > table_end)
        {
            throw std::runtime_error("'End' byte needs to come before 'Start' byte");
        }

        gui::Application app(std::move(data), infile);
        app.ui.first_byte = table_start;
        app.ui.last_byte = table_end;
        
        return app.Start();
        
    }
    catch (const ArgException& err)
    {
        std::cout << "Could not parse command line arguments: " << err.what() << '\n';
    }
    catch (const std::exception& err)
    {
        std::cout << "Error opening window: " << err.what() << '\n';
    }

    
    
}