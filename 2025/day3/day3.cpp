#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
typedef int position;
typedef char value;

constexpr int DIMENTION = 12;

int main()
{
    string line{};
    ifstream file("input.txt");

    if (!file) {
        cout << "Unable to open file";
        return 1;
    }

    long long unsigned int sum_joltage{0};
    while (getline (file, line)) {
        cout << line << endl;
        
        vector<pair<position,value>> vector_of_PV;
        pair<position,value> single_pair{make_pair(0,'0')};

        int current_selection{0};
        int offset_from_right{0};
        int offset_from_left{0};
     
        while(current_selection < DIMENTION){

            int i{offset_from_left};
            while(i < line.length() - offset_from_right){
                if ( (single_pair.second < line.at(i)) ){
                    single_pair.first = i;
                    single_pair.second = line.at(i);
                }
                ++i;
            }

            if (single_pair.first <= line.length() - (DIMENTION - current_selection) ){
                vector_of_PV.push_back(single_pair);
                offset_from_left = single_pair.first + 1;
                current_selection++;
                if(current_selection < DIMENTION){
                    single_pair.first = offset_from_left;
                    single_pair.second = line.at(offset_from_left);
                }
                offset_from_right = 0;
                continue;
            }

            offset_from_right = line.length() - single_pair.first;
            single_pair = make_pair(0,'0');
        }

        long long unsigned int current_joltage{0};

        for(int k = 0; k < DIMENTION; k++){
            current_joltage = (vector_of_PV.at(k).second - '0') + current_joltage*10;
        }
        cout << "Current joltage: " << current_joltage << endl;

        sum_joltage = sum_joltage + current_joltage;
        cout << "Partial sum: " << sum_joltage << endl;

        vector_of_PV.clear();
    }
}
