#include "VectorIntervalFreshID.hpp"
#include <algorithm>

VectorIntervalFreshID::VectorIntervalFreshID(IntervalFreshID first_interval){
    vector_of_intervals.push_back(first_interval);
}

void VectorIntervalFreshID::add_interval(IntervalFreshID new_raw_interval){
    if(vector_of_intervals.size() == 0) {
        vector_of_intervals.push_back(new_raw_interval);
        return;
    }

    auto lower_position = std::lower_bound(vector_of_intervals.begin(), vector_of_intervals.end(), 
        new_raw_interval.get_interval().first, 
        [](const IntervalFreshID& interval,  const long long unsigned int& element){
                return (interval.get_interval().second < element);
            });

    auto upper_position = std::upper_bound(vector_of_intervals.begin(), vector_of_intervals.end(), 
        new_raw_interval.get_interval().second, 
            [](const long long unsigned int& element, const IntervalFreshID& interval){
                return (element < interval.get_interval().first);
            });

    if (lower_position == vector_of_intervals.end()){
        //just append the new set at the end
        vector_of_intervals.push_back(new_raw_interval);
        return;
    }

    if (upper_position == vector_of_intervals.begin() && new_raw_interval.get_interval().second < lower_position->get_interval().first) {
        //just append the new set at the start
        vector_of_intervals.insert(vector_of_intervals.begin(), new_raw_interval);
        return;
    }

    if (upper_position->contains(new_raw_interval) || lower_position->contains(new_raw_interval)){
        //nothing to do, the new_interval is already contained in the structure.
        return;
    }

    // now you are in the middile so you have to adjust the intervals a bit
    IntervalFreshID new_refined_interval(
        std::min(new_raw_interval.get_interval().first, lower_position->get_interval().first),
        std::max(new_raw_interval.get_interval().second, std::prev(upper_position)->get_interval().second));
    
    auto new_position = vector_of_intervals.erase(lower_position, upper_position);
    vector_of_intervals.insert(new_position, new_refined_interval);
    return;
}

long long unsigned int VectorIntervalFreshID::number_of_elements() const{
    long long unsigned int result = 0;
    for(auto i : vector_of_intervals){
        result += i.number_of_elements();
    }
    return result;
}