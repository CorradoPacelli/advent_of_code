#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    int sum_j{0};
    string line{};
    ifstream file("input.txt");

    if (!file) {
        cout << "Unable to open file";
        return 1;
    }

    while (getline (file, line)) {
        int max{0};
        int second_max{0};
        int i{0};
        while(i < line.length()){
            if (line.at(max) < line.at(i)){
                max = i;
            }
            ++i;
        }
        
        if (max == line.length()-1 ){
            i = 0;
            while(i < line.length()-1){
                if (line.at(second_max) < line.at(i)){
                    second_max = i;
                }
                ++i;
            }
            sum_j = sum_j + ((line.at(second_max)-'0')*10 + (line.at(max)-'0'));
        } else {
            i = max + 1;
            second_max = max + 1;
            while(i < line.length()){
                if (line.at(second_max) < line.at(i)){
                    second_max = i;
                }
                ++i;
            }
            sum_j = sum_j + ((line.at(max)-'0')*10 + (line.at(second_max)-'0'));
        }
        cout << "The sum is: " << sum_j << endl;
    }

    
}
