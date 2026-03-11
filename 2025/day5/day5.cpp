#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include "VectorIntervalFreshID.hpp"

using namespace std;

//1024019360272682  too high
//542291967852951   too high
//348548952146313

int main() {
    std::ifstream file("input.txt");
    std::string line;

    long long unsigned int current_ID{0};
    VectorIntervalFreshID intervals_of_IDs{};

    if (!file) {
        cout << "Unable to open file";
        return 1;
    }

    while (std::getline(file, line)) {
        if (line == ""){
            break;
        } 
        int position_of_separator = line.find("-");
        IntervalFreshID new_interval(
            strtoull(line.substr(0, position_of_separator).c_str(),nullptr, 10),
            strtoull(line.substr(position_of_separator + 1).c_str(),nullptr, 10) );
        intervals_of_IDs.add_interval(new_interval);
    }

    cout << "Number of fresh items: " << intervals_of_IDs.number_of_elements() << endl;
}