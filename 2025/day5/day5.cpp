#include <iostream>
#include <fstream>
#include <vector>
#include <set>

using namespace std;

void re_arrange_intervals(set<std::pair<long long unsigned int, long long unsigned int>>&, 
    std::pair<long long unsigned int, long long unsigned int>);

int main() {
    std::ifstream file("rinput.txt");
    std::string line;

    long long unsigned int current_ID{0};
    set<std::pair<long long unsigned int, long long unsigned int>> intervals_of_IDs{};
    long long unsigned int fresh_IDs{0};
    
    if (!file) {
        cout << "Unable to open file";
        return 1;
    }

    while (std::getline(file, line)) {
        if (line == ""){
            break;
        } 
        int position_of_separator = line.find("-");
        re_arrange_intervals(intervals_of_IDs,make_pair(
                strtoull(line.substr(0, position_of_separator).c_str(),nullptr, 10),
                strtoull(line.substr(position_of_separator + 1).c_str(),nullptr, 10)
            ));
    }

    for(auto p: intervals_of_IDs){
        fresh_IDs = p.second-p.first + 1;
    }

    cout << "Number of fresh items: " << fresh_IDs << endl;
}

void re_arrange_intervals(set<std::pair<long long unsigned int, long long unsigned int>>& intervals_of_IDs,
    std::pair<long long unsigned int, long long unsigned int> new_pair){
    if (intervals_of_IDs.size()==0){
        intervals_of_IDs.emplace(new_pair);
        return;
    }
    
    // TODO devi controllare non solo new.first con p.first ma anche con p.second
    for(auto p : intervals_of_IDs){
        if ( (new_pair.first >= p.first) && (new_pair.second <= p.second) ) return; 
        if ( (new_pair.first >= p.first) && (new_pair.second <= p.second) ){
            intervals_of_IDs.emplace(new_pair);
            intervals_of_IDs.erase(p);
            return;
        } else if ( (new_pair.first < p.first) && (new_pair.second <= p.second) ){
            //increase left part of the pair
            intervals_of_IDs.emplace(new_pair.first,p.second);
            intervals_of_IDs.erase(p);
            return;
        } else if ( (new_pair.first >= p.first) && (new_pair.second > p.second) ){
            intervals_of_IDs.emplace(p.first,new_pair.second);
            intervals_of_IDs.erase(p);
            return;
        } 
    }
    intervals_of_IDs.emplace(new_pair);
}