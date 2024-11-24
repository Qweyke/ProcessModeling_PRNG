#include "lcg.h"

constexpr uint16_t PERCENTS = 100;

Lcg::Lcg(const uint64_t modulus,
         const uint64_t multiplier,
         const uint64_t increment,
         const uint64_t seed)
: modulus(modulus)
, multiplier(multiplier)
, increment(increment)
, seed(seed)
{
}

long double Lcg::normalize(const uint64_t num, const uint64_t mod) const
{
    return static_cast<long double>(num) / static_cast<long double>(mod - 1);
}

void Lcg::generateValues(uint64_t quantity)
{
    std::unordered_set<long double> valuesUnordered;

    while (valuesUnordered.find(normalize(this->seed, this->modulus)) == valuesUnordered.end())
    {
        valuesUnordered.insert(normalize(this->seed, this->modulus));
        this->seed = (this->multiplier * this->seed + this->increment) % this->modulus;
    }

    this->values.assign(valuesUnordered.begin(), valuesUnordered.end());
    std::sort(this->values.begin(), this->values.end());

    this->period        = this->values.size();
    this->expectedValue = calculateExpectedValue(1);
    calculateStandardDeviation();
    calculateValuesFrequency();
    calculateHalvesQuantity();
}

long double Lcg::calculateExpectedValue(uint16_t power)
{
    long double sum = 0;
    for (const long double& element : this->values)
    {
        if (power == 1)
            sum += element;
        else if (power == 2)
            sum += element * element;
        else
            sum += pow(element, power);
    }
    return (1 / static_cast<long double>(this->values.size())) * sum;
}

void Lcg::calculateStandardDeviation()
{
    this->statisticalDispersion
        = this->calculateExpectedValue(2) - pow(this->calculateExpectedValue(1), 2);

    this->standardDeviation = sqrt(this->statisticalDispersion);
}

void Lcg::calculateValuesFrequency()
{
    this->intervalSize = ((this->expectedValue + this->standardDeviation)
                          - (this->expectedValue - this->standardDeviation));

    size_t qnty
        = std::count_if(this->values.begin(),
                        this->values.end(),
                        [this](long double element)
                        {
                            return (element >= (this->expectedValue - this->standardDeviation)
                                    && element <= (this->expectedValue + this->standardDeviation));
                        });

    this->valuesFrequencyInInterval = static_cast<long double>(qnty) / this->period * PERCENTS;
}

void Lcg::calculateHalvesQuantity()
{
    size_t rightHalf = std::count_if(this->values.begin(),
                                     this->values.end(),
                                     [this](long double element) { return (element >= 0.5); });

    this->rightCount = static_cast<uint64_t>(rightHalf);
    this->leftCount  = this->period - this->rightCount;
}

void Lcg::displayValues(uint64_t quantity) const
{
    for (int i = 0; i < quantity; i++)
    {
        std::cout << values[i] << " ";
    }
    std::cout << "\n\n";
}

void Lcg::compareResults() {}

std::vector<long double> Lcg::getValuesVector() { return Lcg::values; }

uint64_t    Lcg::getPeriod() const { return this->period; }
long double Lcg::getExpectedValue() const { return this->expectedValue; }
long double Lcg::getStatisticalDispersion() const { return this->statisticalDispersion; }
long double Lcg::getStandardDeviation() const { return this->standardDeviation; }
long double Lcg::getIntervalSize() const { return this->intervalSize; }
long double Lcg::getValuesFrequencyInInterval() const { return this->valuesFrequencyInInterval; }
uint64_t    Lcg::getLeftCount() const { return this->leftCount; }
uint64_t    Lcg::getRightCount() const { return this->rightCount; }
