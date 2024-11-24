#include "lcg.h"
namespace
{
constexpr uint64_t MODULUS    = (1ull << 24);
constexpr uint64_t MULTIPLIER = 323;
constexpr uint64_t INCREMENT  = 2;
constexpr uint64_t SEED       = 2;
}


int main()
{
    Lcg lcg1(MODULUS, MULTIPLIER, INCREMENT, SEED);
    lcg1.generateValues(100000);
    lcg1.displayValues(10);
    std::cout << "Calculated period is " << lcg1.getPeriod() << "\n";
    std::cout << "Expected value = " << lcg1.getExpectedValue() << "\n";
    std::cout << "Statistical dispersion = " << lcg1.getStatisticalDispersion() << "\n";
    std::cout << "Standard deviation = " << lcg1.getStandardDeviation() << "\n";
    std::cout << "Interval size = " << lcg1.getIntervalSize() << "\n";
    std::cout << "Values percentage in interval = " << lcg1.getValuesFrequencyInInterval()
              << " %\n";
    std::cout << "Quantity of left half values = " << lcg1.getLeftCount() << "\n";
    std::cout << "Quantity of right half values = " << lcg1.getRightCount() << "\n";
    return 0;
}