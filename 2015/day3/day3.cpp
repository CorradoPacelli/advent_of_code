#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

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

void increase_counter_or_add_house(std::vector<Point> &grid, Point &new_location, int &counter_houses_already_visited);

int main()
{
    char character{};
    int counter_new_houses_visited{1};
    vector<Point> grid{Point{0,0}};
    Point old_location_santa{0,0};
    Point old_location_robo{0,0};
    Point new_location{0,0};
    Point* pointer_old_location = &old_location_santa;
    bool switcher{true};
    ifstream file("input.txt");

    if (!file) {
        cout << "Unable to open file";
        return 1;
    }

    while (file.get(character)) {
        if (character== 'v'){ 
            new_location = Point (pointer_old_location->x, pointer_old_location->y -1);
            increase_counter_or_add_house(grid, new_location, counter_new_houses_visited);
        } else if (character== '^'){ 
            new_location = Point (pointer_old_location->x, pointer_old_location->y +1);
            increase_counter_or_add_house(grid, new_location, counter_new_houses_visited);
        } else if (character== '>'){ 
            new_location = Point (pointer_old_location->x +1, pointer_old_location->y);
            increase_counter_or_add_house(grid, new_location, counter_new_houses_visited);
        } else { // character== '<'
            new_location = Point (pointer_old_location->x -1, pointer_old_location->y);
            increase_counter_or_add_house(grid, new_location, counter_new_houses_visited);
        }
        if(switcher){
            old_location_santa = new_location;
            pointer_old_location = &old_location_robo;
            switcher = false;
            //cout << "tocca a robo!" << endl;
        } else {
            old_location_robo = new_location;
            pointer_old_location = &old_location_santa;
            switcher = true;
            //cout << "tocca a santa!" << endl;
        }
    }

    cout << "Santa total amount houses visited is: " << counter_new_houses_visited <<endl;
}

void increase_counter_or_add_house(std::vector<Point> &grid, Point &new_location, int &counter_new_houses_visited)
{
    if (find(grid.begin(), grid.end(), new_location) == grid.end()) {
        //cout << "Nuova casa visitata in posizione (" << new_location.x << "," << new_location.y << ")" <<endl;
        ++counter_new_houses_visited;
        //cout << "Santa total amount houses visited is: " << counter_new_houses_visited <<endl;
        grid.push_back(new_location);
    }/* else {
        cout << "Casa gia' vista in posizione (" << new_location.x << "," << new_location.y << ")" <<endl;
    }
    cout<< "Resoconto grid: ";
    for(auto e : grid){
        cout << "("<< e.x << "," << e.y << ")";
    }
    cout << endl;*/
}
