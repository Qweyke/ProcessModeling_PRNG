#include "PrngTester.h"
namespace
{
constexpr uint16_t PERCENTS = 100;
}

PrngTester::PrngTester(std::vector<long double>& values) {}

void PrngTester::testGeneratedValues()
{
    this->values = values;
    std::sort(this->values.begin(), this->values.end());

    this->valuesCount   = this->values.size();
    this->expectedValue = calculateExpectedValue(1);
    calculateStandardDeviation();
    calculateValuesFrequency();
    calculateHalvesQuantity();
}

long double PrngTester::calculateExpectedValue(uint16_t power)
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

void PrngTester::calculateStandardDeviation()
{
    this->statisticalDispersion
        = this->calculateExpectedValue(2) - pow(this->calculateExpectedValue(1), 2);

    this->standardDeviation = sqrt(this->statisticalDispersion);
}

void PrngTester::calculateValuesFrequency()
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

    this->valuesFrequencyInInterval = static_cast<long double>(qnty) / this->valuesCount * PERCENTS;
}

void PrngTester::calculateHalvesQuantity()
{
    size_t rightHalf = std::count_if(this->values.begin(),
                                     this->values.end(),
                                     [this](long double element) { return (element >= 0.5); });

    this->rightCount = static_cast<uint64_t>(rightHalf);
    this->leftCount  = this->valuesCount - this->rightCount;
}


void PrngTester::displayValues(uint64_t quantity) const
{
    for (int i = 0; i < quantity; i++)
    {
        std::cout << values[i] << " ";
    }
    std::cout << "\n\n";
}

long double PrngTester::getExpectedValue() const { return this->expectedValue; }
long double PrngTester::getStatisticalDispersion() const { return this->statisticalDispersion; }
long double PrngTester::getStandardDeviation() const { return this->standardDeviation; }
long double PrngTester::getIntervalSize() const { return this->intervalSize; }
long double PrngTester::getValuesFrequencyInInterval() const
{
    return this->valuesFrequencyInInterval;
}
uint64_t PrngTester::getLeftCount() const { return this->leftCount; }
uint64_t PrngTester::getRightCount() const { return this->rightCount; }
