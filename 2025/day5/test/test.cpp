#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "IntervalFreshID.hpp"
#include <vector>
#include <algorithm>

TEST_CASE("Testing Interval Research Logic") {
    std::vector<IntervalFreshID> vector_of_intervals;
    vector_of_intervals.push_back(IntervalFreshID(1,3));
    vector_of_intervals.push_back(IntervalFreshID(5,10));
    vector_of_intervals.push_back(IntervalFreshID(15,20));
    vector_of_intervals.push_back(IntervalFreshID(40,50));
    vector_of_intervals.push_back(IntervalFreshID(52,60));

    IntervalFreshID new_interval(7,19);

    SUBCASE("Lower Bound Accuracy") {
        auto lower_position = std::lower_bound(vector_of_intervals.begin(), vector_of_intervals.end(), 
            new_interval.get_interval().first, 
            [](const IntervalFreshID& interval,  const long long unsigned int& element){
                return (interval.get_interval().second < element);
            });

        auto upper_position = std::upper_bound(vector_of_intervals.begin(), vector_of_intervals.end(), 
            new_interval.get_interval().second, 
            [](const long long unsigned int& element, const IntervalFreshID& interval){
                return (element < interval.get_interval().first);
            });
        
        // 15 is between 10 and 30, so lower_bound should point to 30
        CHECK(vector_of_intervals.begin()->get_interval().first == 1);
        CHECK(lower_position->get_interval().first == 5);
        CHECK(upper_position->get_interval().second == 50);
        
    }

    SUBCASE("Erase Range") {
        vector_of_intervals.erase(vector_of_intervals.begin(), vector_of_intervals.end());
        CHECK(vector_of_intervals.size() == 0);
    }
}