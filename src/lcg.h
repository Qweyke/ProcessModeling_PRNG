#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <unordered_set>

#pragma once

class Lcg
{
public:
    Lcg(const uint64_t modulus,
        const uint64_t multiplier,
        const uint64_t increment,
        const uint64_t seed);

    void generateValues(uint64_t quantity);
    void displayValues(uint64_t quantity) const;
    void compareResults();

    std::vector<long double> getValuesVector();

    uint64_t    getPeriod() const;
    long double getExpectedValue() const;
    long double getStatisticalDispersion() const;
    long double getStandardDeviation() const;
    long double getIntervalSize() const;
    long double getValuesFrequencyInInterval() const;
    uint64_t    getLeftCount() const;
    uint64_t    getRightCount() const;

private:
    std::vector<long double> values;

    const uint64_t modulus;
    const uint64_t multiplier;
    const uint64_t increment;
    uint64_t       seed;

    uint64_t    period;
    long double expectedValue;
    long double standardDeviation;
    long double statisticalDispersion;
    long double intervalSize;
    long double valuesFrequencyInInterval;
    uint64_t    leftCount;
    uint64_t    rightCount;

    long double normalize(uint64_t num, uint64_t mod) const;

    long double calculateExpectedValue(uint16_t power);
    void        calculateStandardDeviation();
    void        calculateValuesFrequency();
    void        calculateHalvesQuantity();
};
