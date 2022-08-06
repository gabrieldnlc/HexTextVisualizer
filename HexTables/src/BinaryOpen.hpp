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
Container binary_load(std::string const& bin_file_name)
{
    std::ifstream in(bin_file_name, std::ios::binary);
    if (!in) {
        throw std::runtime_error("Could not open \"" + bin_file_name +
            "\" for reading");
    }
    std::noskipws(in); 
    return Container(std::istream_iterator<std::uint8_t>(in),
        std::istream_iterator<std::uint8_t>()); 

}

template<class Container>
void binary_save(Container&& data, std::string const& bin_file_name)
{
    std::ofstream out(bin_file_name, std::ios::binary);
    if (!out) {
        throw std::runtime_error("Could not open \"" + bin_file_name +
            "\" for writing");
    }
    std::copy(data.begin(), data.end(),
        std::ostream_iterator<std::uint8_t>(out, "")); 
}

static string IntAsHexString(uint8_t i)
{
    if (i == 0) return "00";
    string ret = std::format("{:x}", i);
    transform(ret.begin(), ret.end(), ret.begin(), ::toupper);
    return ret;
}

static string IntAsHex(uint8_t i)
{
    static stringstream stream;
    stream << std::hex << i;
    string ret = stream.str();
    stream.str(string());
    stream.clear();
    return ret;
}