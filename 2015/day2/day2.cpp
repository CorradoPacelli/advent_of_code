#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void get_dimentions(int&, int&, int&, const string&);


int main (){
    string line{};
    vector<int> dimentions{0,0,0};
    int square_feet_of_wrapping_paper{0};
    int square_feet_of_ribbon{0};
    ifstream file("input.txt");

    if (!file) {
        cout << "Unable to open file";
        return 1;
    }

    while (getline (file, line)) {
        //cout << line << endl;
        get_dimentions(dimentions[0],dimentions[1],dimentions[2],line);

        square_feet_of_wrapping_paper += dimentions[0]*dimentions[1]*2 + 
                                    dimentions[1]*dimentions[2]*2 + 
                                    dimentions[0]*dimentions[2]*2;

        square_feet_of_ribbon += dimentions[0]*dimentions[1]*dimentions[2];

        std::sort(dimentions.begin(),dimentions.end());

        square_feet_of_wrapping_paper += dimentions[0]*dimentions[1];
        square_feet_of_ribbon += dimentions[0]*2 + dimentions[1]*2;
    }

    cout << "Santa total amount of square feet of wrapping paper is: " << square_feet_of_wrapping_paper <<endl;
    cout << "Santa total amount of square feet of ribbon is: " << square_feet_of_ribbon <<endl;
}

void get_dimentions(int& d1, int& d2, int& d3,const string& line){
    unsigned long long int position_of_first_x{line.find_first_of('x')};
    unsigned long long int position_of_second_x{line.find_last_of('x')};
    d1 = stoi(line.substr(0, position_of_first_x));
    d2 = stoi(line.substr(position_of_first_x + 1, position_of_second_x));
    d3 = stoi(line.substr(position_of_second_x + 1, line.length()));
}