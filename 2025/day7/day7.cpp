#include <fstream>
#include <iostream>
#include <string>
#include <set>

using namespace std;

//1630 one star :)

int main () {

    ifstream file("input.txt");

    if (!file) {
        cout << "Unable to open file";
        return 1;
    } 

    string line{};

    getline(file, line);

    set<size_t> beams_positions;
    beams_positions.insert(line.find('S'));
    int number_of_splits{0};

    while (getline(file, line)) {
        size_t position_of_splitter = line.find('^');
        set<size_t> beams_positions_to_be_added;
        while (!(position_of_splitter == std::string::npos)){
            auto it = beams_positions.begin();
            while (it != beams_positions.end()) {
                if (*it == position_of_splitter){
                    ++number_of_splits;
                    beams_positions_to_be_added.insert((*it) - 1);
                    beams_positions_to_be_added.insert((*it) + 1);
                    it = beams_positions.erase(it);
                } else {
                    ++it;
                }
            }
            position_of_splitter = line.find('^', position_of_splitter + 1);
        }
        beams_positions.insert(beams_positions_to_be_added.begin(), beams_positions_to_be_added.end());
        cout << "Partial number of splits: " << number_of_splits << endl;
    }
    cout << "Total number of beams: " << number_of_splits << endl;
}