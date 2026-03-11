#pragma once

#include "IntervalFreshID.hpp"
#include <vector>

// Invariants:
// 1) this class contains only Intervals that are not overlapped
// 2) the intervals are ordered from the smaller to the biggest in terms of natual number 
// ex: 1-3, 12-13, 15-50000, 50002-50010 etc
class VectorIntervalFreshID {
public:
    VectorIntervalFreshID() = default;

    VectorIntervalFreshID(IntervalFreshID first_interval);

    void add_interval(IntervalFreshID new_interval);

    long long unsigned int number_of_elements() const;

private:
    std::vector<IntervalFreshID> vector_of_intervals;
};