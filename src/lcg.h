#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <unordered_set>

#pragma once

class Lcg
{
public:
    void generateValues(const uint64_t modulus,
                        const uint64_t multiplier,
                        const uint64_t increment,
                        uint64_t       seed);

    void displayValues();
    void compareResults();

    std::vector<double> getValuesSet();

    uint64_t getPeriod() const;
    double   getExpectedValue() const;
    double   getStatisticalDispersion() const;
    double   getStandardDeviation() const;
    double   getIntervalSize() const;
    double   getValuesFrequencyInInterval() const;
    uint64_t getLeftCount() const;
    uint64_t getRightCount() const;

private:
    std::vector<double> values;

    uint64_t period;
    double   expectedValue;
    double   standardDeviation;
    double   statisticalDispersion;
    double   intervalSize;
    double   valuesFrequencyInInterval;
    uint64_t leftCount;
    uint64_t rightCount;

    double normalize(uint64_t num, uint64_t mod);

    double calculateExpectedValue(uint16_t power);
    void   calculateStandardDeviation();
    void   calculateValuesFrequency();
    void   calculateHalvesQuantity();
};
