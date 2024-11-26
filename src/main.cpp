#include "PrngTester.h"
namespace
{
constexpr uint64_t MODULUS    = (1ull << 24);
constexpr uint64_t MULTIPLIER = 323;
constexpr uint64_t INCREMENT  = 2;
constexpr uint64_t SEED       = 2;
}

class Lcg(const uint64_t modulus,
          const uint64_t multiplier,
          const uint64_t increment,
          const uint64_t seed)
{
    uint64_t modulus = modulus;
    uint64_t multiplier;
    uint64_t increment;
    uint64_t seed;

    long double normalize(const uint64_t num, const uint64_t mod);
    {
        return static_cast<long double>(num) / static_cast<long double>(mod - 1);
    }

    long double LcgGenerate(std::unordered_set<long double> set)
    {
        while (set.find(normalize(this->seed, this->modulus)) == set.end())
        {
            set.insert(normalize(this->seed, this->modulus));
            this->seed = (this->multiplier * this->seed + this->increment) % this->modulus;
        }
    }
}


int main()
{
    std::unordered_set<long double> lcg;


    PrngTester lcgTester(MODULUS, MULTIPLIER, INCREMENT, SEED);
    /*lcgTester.generateValues(100000);*/
    lcgTester.displayValues(10);
    // std::cout << "Calculated period is " << lcgTester.getPeriod() << "\n";
    std::cout << "Expected value = " << lcgTester.getExpectedValue() << "\n";
    std::cout << "Statistical dispersion = " << lcgTester.getStatisticalDispersion() << "\n";
    std::cout << "Standard deviation = " << lcgTester.getStandardDeviation() << "\n";
    std::cout << "Interval size = " << lcgTester.getIntervalSize() << "\n";
    std::cout << "Values percentage in interval = " << lcgTester.getValuesFrequencyInInterval()
              << " %\n";
    std::cout << "Quantity of left half values = " << lcgTester.getLeftCount() << "\n";
    std::cout << "Quantity of right half values = " << lcgTester.getRightCount() << "\n";
    return 0;
}