#include "PrngTester.h"
#include <random>
#include <stdexcept>
#include <string>

namespace
{
constexpr uint64_t MODULUS    = (1ull << 24);
constexpr uint64_t MULTIPLIER = 323;
constexpr uint64_t INCREMENT  = 2;
constexpr uint64_t SEED       = 2;

constexpr uint64_t QUANTITY = 1000000;
}

class Lcg
{
public:
    Lcg(const uint64_t modulus,
        const uint64_t multiplier,
        const uint64_t increment,
        const uint64_t seed)
    : modulus(modulus)
    , multiplier(multiplier)
    , increment(increment)
    , seed(seed)
    {
    }

    uint64_t calculatePeriod() const
    {
        uint64_t x      = seed;
        uint64_t period = 0;

        std::unordered_set<long double> values;

        while (values.find(normalize(x, this->modulus)) == values.end())
        {
            values.insert(normalize(x, this->modulus));
            x = (this->multiplier * x + this->increment) % this->modulus;
            period += 1;
        }
        return period;
    }

    std::vector<long double> generateValues(uint64_t quantity) const
    {
        std::unordered_set<long double> valuesUnordered;

        uint64_t x      = seed;
        uint64_t period = 0;

        for (int i = 0; i < quantity; i++)
        {
            if (valuesUnordered.find(normalize(x, this->modulus)) == valuesUnordered.end())
                throw std::logic_error("Identical value found! Period = " + std::to_string(seed));

            valuesUnordered.insert(normalize(x, this->modulus));
            x = (this->multiplier * x + this->increment) % this->modulus;
        }

        std::vector<long double> values;
        values.assign(valuesUnordered.begin(), valuesUnordered.end());

        return values;
    }

private:
    const uint64_t modulus;
    const uint64_t multiplier;
    const uint64_t increment;
    const uint64_t seed;

    long double normalize(const uint64_t num, const uint64_t mod) const
    {
        return static_cast<long double>(num) / static_cast<long double>(mod - 1);
    }
};

int main()
{
    std::vector<long double> lcgValues;
    std::vector<long double> mtValues;

    lcgValues.reserve(QUANTITY);
    mtValues.reserve(QUANTITY);

    Lcg                                         lcgGenerator(MODULUS, MULTIPLIER, INCREMENT, SEED);
    std::mt19937                                mtGenerator(SEED);
    std::uniform_real_distribution<long double> normalize(0.0, 1.0);

    lcgValues = lcgGenerator.generateValues(QUANTITY);
    for (int i = 0; i < QUANTITY; i++)
    {
        mtValues.push_back(normalize(mtGenerator));
    }


    PrngTester lcgTester(lcgValues);
    PrngTester mtTester(mtValues);

    /*lcgTester.displayValues(10);*/

    std::cout << "Lcg. Expected value = " << lcgTester.getExpectedValue() << "\n";
    std::cout << "Mt. Expected value = " << mtTester.getExpectedValue() << "\n";

    std::cout << "Lcg. Statistical dispersion = " << lcgTester.getStatisticalDispersion() << "\n";
    std::cout << "Mt. Statistical dispersion = " << mtTester.getStatisticalDispersion() << "\n";

    std::cout << "Lcg. Standard deviation = " << lcgTester.getStandardDeviation() << "\n";
    std::cout << "Mt. Standard deviation = " << mtTester.getStandardDeviation() << "\n";

    std::cout << "Lcg. Interval size = " << lcgTester.getIntervalSize() << "\n";
    std::cout << "Mt. Interval size = " << mtTester.getIntervalSize() << "\n";

    std::cout << "Lcg.Values percentage in interval = " << lcgTester.getValuesFrequencyInInterval()
              << " %\n";
    std::cout << "Mt. Values percentage in interval = " << mtTester.getValuesFrequencyInInterval()
              << " %\n";

    std::cout << "Lcg.Quantity of left half values = " << lcgTester.getLeftCount() << "\n";
    std::cout << "Mt. Quantity of left half values = " << mtTester.getLeftCount() << "\n";

    std::cout << "Lcg.Quantity of right half values = " << lcgTester.getRightCount() << "\n";
    std::cout << "Mt. Quantity of right half values = " << mtTester.getRightCount() << "\n";

    return 0;
}