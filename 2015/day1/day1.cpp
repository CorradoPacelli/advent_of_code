#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    char character{};
    int floor{0},position{1};
    bool already_entered{false};
    ifstream file("input.txt");

    if (!file) {
        cout << "Unable to open file";
        return 1;
    }

    while (file.get(character)) {
        if(character=='('){
            ++floor;
        }else if (character==')'){
            --floor;
        }
        if(floor<0 && !already_entered){
            cout << "Santa the position that forced you do go to the basement is: " << position <<endl;
            already_entered=true;
        }
        ++position;
    }
    cout << "Santa you should go to the floor: " << floor <<endl;
}
