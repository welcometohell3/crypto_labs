#include <iostream>
#include <random>
#include <unordered_set>
#include <thread>
#include "MD4.hpp"
#include <fstream>

size_t extract_bits(std::string message, size_t n)
{
    MD4 md4;
    std::string hash = md4.hash(message);

    std::stringstream ss;
    ss << std::hex << hash.substr(0, n);
    unsigned long long number;
    ss >> number;

    return number & ((1ULL << n) - 1);
}

std::string random_string()
{
    const std::string CHARACTERS = "abcdefghijklmnopqrstuvwxyz";

    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> distribution(0, CHARACTERS.size() - 1);

    std::string random_string;

    for (size_t i = 0; i < 5; ++i)
    {
        random_string += CHARACTERS[distribution(generator)];
    }

    return random_string;
}

double calculate_avg(const std::vector<size_t> &v)
{
    double avg = 0;
    for (const auto &i : v)
    {
        avg += i;
    }
    return avg / v.size();
}

void process_msg(const std::string &originalMessage, size_t N)
{
    std::ofstream resultsFile(originalMessage + "_results.csv");
    resultsFile << "Message,N,AveragePreimageComplexity,AverageCollisionComplexity\n";

    for (size_t n = 4; n <= 12; n += 2)
    {
        size_t originalHash = extract_bits(originalMessage, n);
        std::vector<size_t> preimageSteps;
        std::vector<size_t> collisionSteps;
        for (size_t experiment = 0; experiment < N; ++experiment)
        {
            std::vector<size_t> hashes;
            size_t step = 0, temp_step = 0;
            size_t a = 0, b = 0;
            while (1)
            {
                step++;
                std::string message = random_string();
                size_t hash = extract_bits(message, n);

                if (hash == originalHash && a != 1)
                {
                    preimageSteps.push_back(step);
                    a = 1;
                }

                if (b != 1)
                {
                    for (const auto &h : hashes)
                    {
                        temp_step++;
                        if (hash == h)
                        {
                            collisionSteps.push_back(temp_step + step);
                            b = 1;
                        }
                    }
                }
                hashes.push_back(hash);
                if (a == 1 && b == 1)
                {
                    break;
                }
            }
        }
        double average1 = calculate_avg(preimageSteps);

        double average2 = calculate_avg(collisionSteps);

        resultsFile
            << originalMessage << ","
            << n << ","
            << average1 << ","
            << average2 << "\n";
    }

    resultsFile.close();
}

int main()
{
    const size_t N = 1000;
    std::vector<std::string> originalMessages = {"askdmaskd", "wnjrjqrjqk", ""};

    std::vector<std::thread> threads;
    for (const auto &originalMessage : originalMessages)
    {
        threads.push_back(std::thread(process_msg, originalMessage, N));
    }

    for (auto &t : threads)
    {
        t.join();
    }

    return 0;
}