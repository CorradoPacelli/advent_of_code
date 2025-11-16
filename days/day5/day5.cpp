#include <iostream>
#include <fstream>
#include <string>
#include <vector>
//#include <algorithm>

using namespace std;

const vector<string> not_good {"ab","cd","pq","xy"};

bool contains_3_vowels(const string&);
bool is_vowels(const char&);
bool contains_twice_in_a_row(const string&);
bool contains_bad_strings(const string&);
bool contains_duplicate_pair(const string&);
bool contains_121_pattern(const string&);

int main (){
    int counter_good_strings{0};
    int counter_good_strings_part2{0};
    string line{};
    ifstream file("input.txt");

    if (!file) {
        cout << "Unable to open file";
        return 1;
    }

    while (getline (file, line)) {
        cout<< line<< endl;
        if (contains_3_vowels(line) && contains_twice_in_a_row(line) && !contains_bad_strings(line)){
            ++counter_good_strings;
        }
        if (contains_121_pattern(line) && contains_duplicate_pair(line)){
            ++counter_good_strings_part2;
        }
    }
    cout << "Number of good strings part 1: "<< counter_good_strings << endl;
    cout << "Number of good strings part 2: "<< counter_good_strings_part2 << endl;
}

bool contains_121_pattern(const string& s){
    for (int i = 0; i<s.length()-2; i++){
        if(s.at(i) == s.at(i+2)){
            return true;
        }
    }
    return false;
}


bool contains_duplicate_pair(const string& s){
    string cheked_substring{s.substr(0,2)};
    for (int i = 1; i<s.length()-1; i++){
        for(int k = i+1; k<s.length()-1; k++){
            if(cheked_substring==s.substr(k,2)){
                return true;
            }
        }
        cheked_substring = s.substr(i,2);
    }
    return false;
}

bool contains_3_vowels (const string& s){
    int number_of_vowels{0};
    for (auto c : s){
        if (is_vowels(c)){
            if(++number_of_vowels>=3){
                return true;
            }
        }
    }
    return false;
}

bool is_vowels(const char& c){
    return (c=='a' || c=='e'|| c=='i'|| c=='o' || c=='u');
}

bool contains_twice_in_a_row (const string& s){
    char temporary_char{s.at(0)};
    for (auto c : s.substr(1,s.length())){
        if(c==temporary_char){
            return true;
        }
        temporary_char=c;
    }
    return false;
}

bool contains_bad_strings(const string& s){
    for (int i = 1; i<s.length(); i++){
        string cheked_substring{s.substr(i-1,2)};
        for(auto duo : not_good){
            if(duo == cheked_substring){
                return true;
            }
        }
    }
    return false;
}