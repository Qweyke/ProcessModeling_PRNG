#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <unordered_set>

#pragma once
class PrngTester
{
public:
    PrngTester(std::vector<long double>& values);

    void displayValues(uint64_t quantity) const;
    void testGeneratedValues();

    long double getExpectedValue() const;
    long double getStatisticalDispersion() const;
    long double getStandardDeviation() const;
    long double getIntervalSize() const;
    long double getValuesFrequencyInInterval() const;
    uint64_t    getLeftCount() const;
    uint64_t    getRightCount() const;

private:
    std::vector<long double>& values;

    uint64_t    valuesCount;
    long double expectedValue;
    long double standardDeviation;
    long double statisticalDispersion;
    long double intervalSize;
    long double valuesFrequencyInInterval;
    uint64_t    leftCount;
    uint64_t    rightCount;

    long double calculateExpectedValue(uint16_t power);
    void        calculateStandardDeviation();
    void        calculateValuesFrequency();
    void        calculateHalvesQuantity();
};
