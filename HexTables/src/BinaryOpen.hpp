#pragma once

#include <string>
#include <sstream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <stdexcept>
#include <cstdint>
#include <format>

using std::string;
using std::vector;
using std::stringstream;

template<class Container>
Container binary_load(string path)
{
    std::ifstream in(path, std::ios::binary);
    if (!in) throw std::runtime_error("Could not open file \"" + path + "\".");

    std::noskipws(in); 
    return Container(std::istream_iterator<std::uint8_t>(in), std::istream_iterator<std::uint8_t>()); 

}

template<class Container>
void binary_save(Container&& data, string path)
{
    std::ofstream out(path, std::ios::binary);
    if (!out) throw std::runtime_error("Could not write to file \"" + path + "\".");

    std::copy(data.begin(), data.end(), std::ostream_iterator<std::uint8_t>(out, "")); 
}