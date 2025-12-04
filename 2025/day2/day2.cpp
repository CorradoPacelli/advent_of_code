#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <set>

using namespace std;

// too h 18446744073589231191
// too PERFECT PART2 -> 45814076230
// too l 35077080239
// too l 8469614167

bool is_repeated_twice(long long unsigned int);
bool is_repeated(long long unsigned int);

int main()
{
    char character{};

    long long unsigned int sum_of_invalid_IDs{0};

    long long unsigned int start_ID{0};
    long long unsigned int end_ID{0};
    bool populating_first{true};
    set<long long unsigned int> IDs{};
    std::pair<std::set<long long unsigned int>::iterator,bool> ret;
    
    ifstream file("input.txt");

    if (!file) {
        cout << "Unable to open file";
        return 1;
    }

    while (file.get(character)) {
        if (character == '-'){
            populating_first= false;
        } else if (character == ','){

            long long unsigned int current_ID = start_ID;
            while (current_ID<=end_ID){
                if (is_repeated(current_ID)){
                    ret = IDs.insert(current_ID);
                    if (ret.second){
                        sum_of_invalid_IDs += current_ID;
                    }
                    
                }
                ++current_ID;
            }

            start_ID = 0;
            end_ID = 0;
            populating_first = true;
        } else if(populating_first) {
            int digit = character - '0';
            start_ID = start_ID*10 + digit;
        } else {
            int digit = character - '0';
            end_ID = end_ID*10 + digit;
        }
    }

    std::set<long long unsigned int>::iterator it;
    std::cout << "myset contains:";
    for (it=IDs.begin(); it!=IDs.end(); ++it){
        std::cout << ' ' << *it;
    }
    std::cout << '\n';

    long long unsigned int tmp{0};
    for (it=IDs.begin(); it!=IDs.end(); ++it){
        tmp += *it;
        std::cout << ' ' << tmp << endl;
    }
    
    cout << "Summing all invalid ID will bring us to " << sum_of_invalid_IDs <<endl;
    cout << "Summing all invalid ID will bring us to " << tmp <<endl;
}

bool is_repeated(long long unsigned int number){
    string s_number = to_string(number);
    int i{0};
    while(i < s_number.length()/2){
        string tmp{s_number.substr(0,i+1)};
        int k{0};
        if (s_number.length()%tmp.length() == 0) {
            while ( (k < s_number.length()/(i+1)) && (tmp == s_number.substr(tmp.length()*(k),tmp.length())) ){
                ++k;
            }
            if ( k == s_number.length()/(i+1) ){
                return true;
            }
        }
        ++i;
    }
    return false;
}

bool is_repeated_twice(long long unsigned int number){
    string s_number = to_string(number);
    if (s_number.length()%2 != 0){
        return false;
    }
    int i{0};
    while(i < s_number.length()/2){
        if (s_number.at(i) != s_number.at(i+s_number.length()/2)){
            return false;
        }
        ++i;
    }
    return true;
}
