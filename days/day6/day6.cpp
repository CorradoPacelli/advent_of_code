#include <iostream>
#include <fstream>
#include <string>
#include <vector>
//#include <algorithm>
// not 9759642 too low
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

void turn_on(int**, const Point&, const Point&);

void turn_off(int**, const Point&, const Point&);

void toggle(int**, const Point&, const Point&);

int number_of_light_on(int**);

int main (){
    int **matrix = new int*[1000]{0};
    for(int i = 0; i < 1000; i++){
        matrix[i] = new int[1000]{0};
    }
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

    int * m = new int[1000];
    *(m+10) = 12;

    cout<< "The luminosity of light is: " << number_of_light_on(matrix) << endl;

    for(int i = 0; i< 1000; ++i){
        delete [] matrix[i];
    }
    delete [] matrix;
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

void turn_on(int **matrix, const Point& start, const Point& end){
    for (int i = start.x; i <= end.x; ++i){
        for (int k = start.y; k <= end.y; ++k){
            ++matrix[i][k];
        }
    }
}

void turn_off(int **matrix, const Point& start, const Point& end){
    for (int i = start.x; i <= end.x; ++i){
        for (int k = start.y; k <= end.y; ++k){
            if(matrix[i][k]>0){
                --matrix[i][k];
            }
        }
    }
}

void toggle(int **matrix, const Point& start, const Point& end){
    for (int i = start.x; i <= end.x; ++i){
        for (int k = start.y; k <= end.y; ++k){
            matrix[i][k]+=2;
        }
    }
}

int number_of_light_on(int **matrix){
    int number_of_light_on{0};
    for (int i = 0; i < 1000; ++i){
        for (int k = 0; k < 1000; ++k){
            number_of_light_on+=matrix[i][k];
        }
    }
    return number_of_light_on;
}
