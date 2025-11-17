#include <iostream>
#include <fstream>
#include <string>
#include <vector>
//#include <algorithm>
//not 568658
using namespace std;

const string ON = "turn on ";
const string OFF = "turn off ";
const string TOG = "toggle ";
const string THROUGH = " through ";
const string POINT_SEPARATOR = ",";

struct Point {
    int x;
    int y;

    Point(int x, int y) : x(x), y(y) {};
    Point() : Point(0,0) {};
    Point(const Point& other) : x(other.x), y(other.y) {}
    bool operator== (const Point& other){
        return other.x == this->x && other.y == this->y;
    }
    Point operator= (const Point& other) {
        this->x = other.x;
        this->y = other.y;
        return *this;
    } 
};

void read_line(const string&, string&, Point&, Point&);

void turn_on(bool[1000][1000], const Point&, const Point&);

void turn_off(bool[1000][1000], const Point&, const Point&);

void toggle(bool[1000][1000], const Point&, const Point&);

int number_of_light_on(bool[1000][1000]);

int main (){
    bool matrix[1000][1000]{false};
    string line{},command{};
    Point start{};
    Point end{};

    ifstream file("input.txt");

    if (!file) {
        cout << "Unable to open file";
        return 1;
    }

    while (getline (file, line)) {

        read_line(line, command, start, end);

        if ( command == OFF ){
            turn_off(matrix, start, end);
        } else if ( command == ON ){
            turn_on(matrix, start, end);
        } else if ( command == TOG) {
            toggle(matrix, start, end);
        }
    }

    cout<< "the number of light up are: " << number_of_light_on(matrix) << endl;

}

void read_line(const string& line, string& command, Point& start, Point& end){
    int end_command_position{0};
    int first_separator_position{line.find_first_of(POINT_SEPARATOR)};
    int start_through_position{line.find(THROUGH)};
    int end_through_position{start_through_position + THROUGH.length()};
    int second_separator_position{line.find_last_of(POINT_SEPARATOR)};
    if(line.find(ON,0) != std::string::npos){
        end_command_position = ON.length();
    } else if (line.find(OFF,0) != std::string::npos){
        end_command_position = OFF.length();
    } else if (line.find(TOG,0) != std::string::npos){
        end_command_position = TOG.length();
    }
    command = line.substr(0, end_command_position);
    start = Point(
        stoi(line.substr(end_command_position, first_separator_position-end_command_position)), 
        stoi(line.substr(first_separator_position+1, start_through_position-first_separator_position+1))
    );
    end = Point(
        stoi(line.substr(end_through_position, second_separator_position-end_through_position)), 
        stoi(line.substr(second_separator_position+1, line.length()-second_separator_position+1))
    );
}

void turn_on(bool matrix[1000][1000], const Point& start, const Point& end){
    for (int i = start.x; i <= end.x; ++i){
        for (int k = start.y; k <= end.y; ++k){
            matrix[i][k] = true;
        }
    }
}

void turn_off(bool matrix[1000][1000], const Point& start, const Point& end){
    for (int i = start.x; i <= end.x; ++i){
        for (int k = start.y; k <= end.y; ++k){
            matrix[i][k] = false;
        }
    }
}

void toggle(bool matrix[1000][1000], const Point& start, const Point& end){
    for (int i = start.x; i <= end.x; ++i){
        for (int k = start.y; k <= end.y; ++k){
            matrix[i][k] = !matrix[i][k];
        }
    }
}

int number_of_light_on(bool matrix[1000][1000]){
    int number_of_light_on{0};
    for (int i = 0; i < 1000; ++i){
        for (int k = 0; k < 1000; ++k){
            if(matrix[i][k]){
                ++number_of_light_on;
            }
        }
    }
    return number_of_light_on;
}
