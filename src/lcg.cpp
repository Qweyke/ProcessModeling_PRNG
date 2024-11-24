#include "lcg.h"

constexpr uint16_t PERCENTS = 100;

double Lcg::normalize(const uint64_t num, const uint64_t mod)
{
    return static_cast<double>(num) / static_cast<double>(mod - 1);
}

void Lcg::generateValues(const uint64_t modulus,
                         const uint64_t multiplier,
                         const uint64_t increment,
                         uint64_t       seed)
{
    while (std::find(this->values.begin(), this->values.end(), normalize(seed, modulus))
           == this->values.end())
    {
        this->values.push_back(normalize(seed, modulus));
        seed = (multiplier * seed + increment) % modulus;
    }
    std::sort(this->values.begin(), this->values.end());

    this->period        = this->values.size();
    this->expectedValue = calculateExpectedValue(1);
    calculateStandardDeviation();
    calculateValuesFrequency();
    calculateHalvesQuantity();
}

double Lcg::calculateExpectedValue(uint16_t power)
{
    double sum = 0;
    for (const double& element : this->values)
    {
        if (power == 1)
            sum += element;
        else if (power == 2)
            sum += element * element;
        else
            sum += pow(element, power);
    }
    return (1 / static_cast<double>(this->values.size())) * sum;
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
                        [this](double element)
                        {
                            return (element >= (this->expectedValue - this->standardDeviation)
                                    && element <= (this->expectedValue + this->standardDeviation));
                        });

    this->valuesFrequencyInInterval = static_cast<double>(qnty) / this->period * PERCENTS;
}

void Lcg::calculateHalvesQuantity()
{
    size_t rightHalf = std::count_if(this->values.begin(),
                                     this->values.end(),
                                     [this](double element) { return (element >= 0.5); });

    this->rightCount = static_cast<uint64_t>(rightHalf);
    this->leftCount  = this->period - this->rightCount;
}

void Lcg::displayValues()
{
    for (const double& element : this->values)
    {
        std::cout << element << " ";
    }
}

void Lcg::compareResults() {}

std::vector<double> Lcg::getValuesSet() { return Lcg::values; }

uint64_t Lcg::getPeriod() const { return this->period; }
double   Lcg::getExpectedValue() const { return this->expectedValue; }
double   Lcg::getStatisticalDispersion() const { return this->statisticalDispersion; }
double   Lcg::getStandardDeviation() const { return this->standardDeviation; }
double   Lcg::getIntervalSize() const { return this->intervalSize; }
double   Lcg::getValuesFrequencyInInterval() const { return this->valuesFrequencyInInterval; }
uint64_t Lcg::getLeftCount() const { return this->leftCount; }
uint64_t Lcg::getRightCount() const { return this->rightCount; }
