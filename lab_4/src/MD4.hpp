#ifndef MD4_H
#define MD4_H

#include <iostream>
#include <cstdint>
#include <vector>
#include <iomanip>
#include <sstream>

class MD4
{
public:
    std::string hash(const std::string &message);

private:
    uint32_t A = 0x67452301;
    uint32_t B = 0xefcdab89;
    uint32_t C = 0x98badcfe;
    uint32_t D = 0x10325476;

    std::vector<uint8_t> padMessage(const std::string &message);
    void processBlock(const std::vector<uint8_t> &block, size_t offset);
    void FF(uint32_t &A, uint32_t B, uint32_t C, uint32_t D, uint32_t X, uint32_t s);
    void GG(uint32_t &A, uint32_t B, uint32_t C, uint32_t D, uint32_t X, uint32_t s);
    void HH(uint32_t &A, uint32_t B, uint32_t C, uint32_t D, uint32_t X, uint32_t s);
    uint32_t rotateLeft(uint32_t x, uint32_t n);
    uint32_t swapEndian(uint32_t value);
};

#endif
