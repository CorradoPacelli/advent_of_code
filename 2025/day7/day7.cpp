#include <fstream>
#include <iostream>
#include <string>
#include <map>

using namespace std;

//1630 one star :)
//47857642990160 SECOND STAR OLE!!!!

int main () {

    ifstream file("input.txt");

    if (!file) {
        cout << "Unable to open file";
        return 1;
    } 

    string line{};
    getline(file, line);

    map<size_t, long long unsigned int> beams_positions_and_relative_timelines;
    beams_positions_and_relative_timelines.insert(make_pair(line.find('S'), 1));

    while (getline(file, line)) {
        size_t position_of_splitter = line.find('^');
        map<size_t, long long unsigned int> beams_positions_and_relative_timelines_to_be_added;
        while (!(position_of_splitter == std::string::npos)){
            auto it = beams_positions_and_relative_timelines.begin();
            while (it != beams_positions_and_relative_timelines.end()) {
                if ((*it).first == position_of_splitter){
                    
                    if (beams_positions_and_relative_timelines_to_be_added.empty()) {
                        beams_positions_and_relative_timelines_to_be_added.insert( make_pair((*it).first - 1, (*it).second) );
                        beams_positions_and_relative_timelines_to_be_added.insert( make_pair((*it).first + 1, (*it).second) );
                    } else {
                        auto b1 = beams_positions_and_relative_timelines_to_be_added.find( (*it).first - 1 );
                        if ( b1 == beams_positions_and_relative_timelines_to_be_added.end()){
                            beams_positions_and_relative_timelines_to_be_added.insert( make_pair((*it).first - 1, (*it).second) );
                        } else {
                            b1->second += (*it).second;
                        }
                        auto b2 = beams_positions_and_relative_timelines_to_be_added.find( (*it).first + 1 );
                        if ( b2 == beams_positions_and_relative_timelines_to_be_added.end()){
                            beams_positions_and_relative_timelines_to_be_added.insert( make_pair((*it).first + 1, (*it).second) );
                        } else {
                            b2->second += (*it).second;
                        }
                    }

                    it = beams_positions_and_relative_timelines.erase(it);
                } else {
                    ++it;
                }
            }
            position_of_splitter = line.find('^', position_of_splitter + 1);
        }
        for (auto& beam : beams_positions_and_relative_timelines_to_be_added){
            auto it = beams_positions_and_relative_timelines.find(beam.first);
            if ( it == beams_positions_and_relative_timelines.end()){
                beams_positions_and_relative_timelines.insert(beam);
            } else {
                it->second += beam.second;
            }
        }

        long long unsigned int partial_timelines{0};
        for (auto& beam : beams_positions_and_relative_timelines){
            partial_timelines += beam.second;
        }
        cout << "Partial number of timelines: " << partial_timelines << endl;
    }
    long long unsigned int timelines{0};
    for (auto& beam : beams_positions_and_relative_timelines){
        timelines += beam.second;
    }
    cout << "Total number of timelines: " << timelines << endl;
}

/* part 1
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
*/