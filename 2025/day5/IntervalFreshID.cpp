#include "IntervalFreshID.hpp"
#include <algorithm>

IntervalFreshID::IntervalFreshID(unsigned long long start, unsigned long long end) {
    interval = std::make_pair(std::min(start, end), std::max(start, end));
}

unsigned long long IntervalFreshID::number_of_elements() const {
    return interval.second - interval.first + 1;
}

IntervalFreshID::Interval IntervalFreshID::get_interval() const{
    return interval;
}

bool IntervalFreshID::contains(const IntervalFreshID& other) const{
    return ((other.get_interval().first >= interval.first) && (other.get_interval().second <= interval.second));
}