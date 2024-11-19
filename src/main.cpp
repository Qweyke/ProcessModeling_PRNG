#include <cmath>
#include <cstdint>
#include <iostream>
#include <unordered_set>


namespace
{
constexpr uint64_t MODULUS    = (1ull << 25);
constexpr uint64_t MULTIPLIER = 323;
constexpr uint64_t INCREMENT  = 2;
constexpr uint64_t SEED       = 2;
}

uint64_t lcg(uint64_t mod,
             uint64_t mult,
             uint64_t incr,
             uint64_t seed)  // Linear Congruential Generator
{
    return (mult * seed + incr) % mod;
}

void detectPrngPeriod(uint64_t mod, uint64_t mult, uint64_t incr, uint64_t seed)
{
    std::unordered_set<uint64_t> values;
    uint64_t                     num    = seed;
    uint64_t                     period = 0;

    while (values.find(num) == values.end())
    {
        values.insert(num);
        num = lcg(mod, mult, incr, num);
        /*std::cout << num << std::endl;*/
        period++;
    }
    std::cout << "Period = " << period << std::endl;
}

int main() { detectPrngPeriod(MODULUS, MULTIPLIER, INCREMENT, SEED); }