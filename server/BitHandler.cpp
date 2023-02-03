#include "server.hpp"

// std::bitset<120> toBitset(std::string str)
// {
//     std::bitset<120> bitset;
//     while (str.size() < 15) {
//         str += " ";
//     }
//     for (std::size_t i = 0; i < str.size(); ++i) {
//         bitset <<= 8;
//         bitset |= str.c_str()[i];
//     }
//     return bitset;
// }