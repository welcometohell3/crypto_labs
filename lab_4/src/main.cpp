#include <iostream>
#include "md4.hpp"

int main()
{
    std::string hash1 = "1bee69a46ba811185c194762abaeae90";
    std::string hash2 = "b86e130ce7028da59e672d56ad0113df";
    std::string hash3 = "31d6cfe0d16ae931b73c59d7e0c089c0";

    std::string test1 = "The quick brown fox jumps over the lazy dog";
    std::string test2 = "The quick brown fox jumps over the lazy cog";
    std::string test3 = "";

    MD4 md4_1;
    MD4 md4_2;
    MD4 md4_3;

    if (hash1 == md4_1.hash(test1))
    {
        std::cout << "test 1 passed" << std::endl;
    }
    else
    {
        std::cout << "test 1 failed" << std::endl;
    }

    if (hash2 == md4_2.hash(test2))
    {
        std::cout << "test 2 passed" << std::endl;
    }
    else
    {
        std::cout << "test 2 failed" << std::endl;
    }

    if (hash3 == md4_3.hash(test3))
    {
        std::cout << "test 3 passed" << std::endl;
    }
    else
    {
        std::cout << "test 3 failed" << std::endl;
    }

    return 0;
}