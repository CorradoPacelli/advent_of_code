#pragma once

#include <utility>

class IntervalFreshID {
public:
    
    using Interval = std::pair<unsigned long long, unsigned long long>;

    IntervalFreshID(unsigned long long start, unsigned long long end);

    Interval get_interval() const;

    unsigned long long number_of_elements() const;

    bool contains(const IntervalFreshID& other) const;

private:
    Interval interval;
};