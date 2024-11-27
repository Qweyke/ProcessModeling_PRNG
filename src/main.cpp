#include "PrngTester.h"
#include <random>
#include <stdexcept>
#include <string>

namespace
{
constexpr uint64_t MODULUS    = (1ull << 25);
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
            if (valuesUnordered.find(normalize(x, this->modulus)) != valuesUnordered.end())
                throw std::logic_error("Identical value found! Period = " + std::to_string(seed)
                                       + "\n");

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

    try
    {
        lcgValues = lcgGenerator.generateValues(QUANTITY);
    }
    catch (const std::logic_error& e)
    {
        std::cout << e.what();
        return 1;
    }

    for (int i = 0; i < QUANTITY; i++)
    {
        mtValues.push_back(normalize(mtGenerator));
    }


    PrngTester lcgTester(lcgValues);
    PrngTester mtTester(mtValues);

    lcgTester.displayValues(10);
    mtTester.displayValues(10);


    std::cout << "LCG results: \n";
    std::cout << "Lcg. Period = " << lcgGenerator.calculatePeriod() << "\n\n";
    lcgTester.testGeneratedValues();

    std::cout << "MT19937 results: \n";
    mtTester.testGeneratedValues();

    return 0;
}