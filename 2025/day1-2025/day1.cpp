#include <iostream>
#include <fstream>

using namespace std;
//my answer is too low (6000) -> 6345 6443 6462 6463 6502 6591 6556 6570 6843 6570 6452
//                                                      6561
int main()
{
    int pointing_to{50};
    int rotate_of{0};
    int number_of_zero{0};
    string line{};
    ifstream file("input.txt");

    if (!file) {
        cout << "Unable to open file";
        return 1;
    }

    while (getline (file, line)) {
        rotate_of = stoi(line.substr(1));
        if(line.at(0) == 'L'){

            while(rotate_of > 0){
                --pointing_to;
                --rotate_of;
                if(pointing_to == 0){
                    ++number_of_zero;
                } else if (pointing_to == -1) {
                    pointing_to = 99;
                }
            }
        
        } else {

            while(rotate_of > 0){
                ++pointing_to;
                --rotate_of;
                if(pointing_to == 100){
                    ++number_of_zero;
                    pointing_to = 0;
                } 
            }

        }
    }

    cout << "Number of time you saw zero: " << number_of_zero <<endl;
}
