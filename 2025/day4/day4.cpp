#include <iostream>
#include <fstream>
#include <vector>
#include <set>

using namespace std;

bool adiacent_more_than_4 (std::vector<std::string>, int, int, int, int);
void remove_accessible_rolls(std::vector<std::string>&, set<std::pair<int,int>>);

int main() {

    std::ifstream file("input.txt");
    std::vector<std::string> matrix;
    std::string line;
    set<std::pair<int,int>> positions_to_be_removed{};
    
    if (!file) {
        cout << "Unable to open file";
        return 1;
    }

    while (std::getline(file, line)) {
        matrix.push_back(line);
    }

    int row {matrix[0].length()};
    int col {matrix.size()};
    int sums_of_roll_of_paper{0};

    do {
        remove_accessible_rolls(matrix, positions_to_be_removed);
        positions_to_be_removed.clear();
        int i{0}, j{0};
        for (; i < row; i++){
            for (j = 0; j < col; j++){
                if (matrix[i][j] == '@'){
                    if ( adiacent_more_than_4(matrix,i,j,row,col) ) {
                        ++sums_of_roll_of_paper;
                        positions_to_be_removed.insert(make_pair(i,j));
                    }
                }
            }
        }
        cout << "Rolls so far " << sums_of_roll_of_paper << endl;
    } while (!positions_to_be_removed.empty());

    cout << "Rolls to count: "<< sums_of_roll_of_paper << endl;

}

bool adiacent_more_than_4 (std::vector<std::string> matrix, int row, int col, int max_row, int max_col){
    int adiacent_rolls{0};
    int i{row - 1}, j{col - 1};
    for (; i <= row + 1; i++){
        if ((i < 0) || (i >= max_row)) continue;
        for (j = col - 1; j <= col + 1; j++){
            if ((j < 0) || (j >= max_col)) continue;
            if (matrix[i][j] == '@'){
                ++adiacent_rolls;
            }
        }
    }

    if (adiacent_rolls < 5) {
        return true;
    }

    return false;
}

void remove_accessible_rolls(std::vector<std::string>& matrix, set<std::pair<int,int>> positions_to_be_removed){

    set<std::pair<int,int>>::iterator it;
    for(it = positions_to_be_removed.begin(); it != positions_to_be_removed.end(); it++){
        matrix[it->first][it->second] = 'x';
    }

}
