#include <iostream>
#include <fstream>
#include <vector>
#include <set>

using namespace std;


int main() {

    std::ifstream file("input.txt");
    std::string line;

    bool change{false};
    int number_of_fresh_IDs{0};
    long long unsigned int current_ID{0};
    set<std::pair<long long unsigned int, long long unsigned int>> intervals_of_IDs{};
    
    if (!file) {
        cout << "Unable to open file";
        return 1;
    }

    while (std::getline(file, line)) {
        if (line == ""){
            change = true;
            continue;
        } 
        if(!change){
            int position_of_separator = line.find("-");
            intervals_of_IDs.insert(
                make_pair(
                    strtoull(line.substr(0, position_of_separator).c_str(),nullptr, 10),
                    strtoull(line.substr(position_of_separator + 1).c_str(),nullptr, 10)
                ));
        } else {
            current_ID = strtoull(line.c_str(),nullptr,10);
            for(auto p: intervals_of_IDs){
                if (current_ID >= p.first && current_ID <= p.second){
                    ++number_of_fresh_IDs;
                    break;
                }
            }
        }
   
    }

    cout << "Number of fresh items: " << number_of_fresh_IDs << endl;

}