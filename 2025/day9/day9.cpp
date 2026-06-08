#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

//2147473713 too low

int main() {
    ifstream input_file("input.txt");

    if (!input_file) {
        cout << "Unable to open file\n";
        return 1;
    }

    string line;
    vector<pair<int, int>> vector_of_points;

    while (getline(input_file, line)) {
        int position_of_comma = line.find(',');

        int x = stoi(line.substr(0, position_of_comma));
        int y = stoi(line.substr(position_of_comma + 1));
        
        vector_of_points.emplace_back(x, y);
    }

    long long max_area{0};
    long long k{0};
    for (size_t i{0}; i < vector_of_points.size(); ++i ){
        for (size_t j{i + 1}; j < vector_of_points.size(); ++j){
            long long height = abs(vector_of_points[i].second - vector_of_points[j].second) + 1;
            long long base = abs(vector_of_points[i].first - vector_of_points[j].first) + 1;
            long long area = base * height;
            if (area > max_area){
                max_area = area;
            }
            k++;
        }

    }

    cout << "There were " << vector_of_points.size() << " points " << endl;
    cout << "We did " << k << " checks " << endl;
    cout << "Max area: " << max_area << endl;

    return 0;
}