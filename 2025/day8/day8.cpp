#include <fstream>
#include <iostream>
#include <string>
#include <set>
#include <unordered_set>
#include <map>
#include <sstream>

#include "point.hpp"

using namespace std;

//section to limit the number of element to 1000 when it comes to add into the set
constexpr int MAX_ELEMENTS = 10;

void insert_with_limit(set<couple_of_3d_points>& points_ordered_by_euclidean_distance, couple_of_3d_points couple){
    if (points_ordered_by_euclidean_distance.size() < MAX_ELEMENTS){
        points_ordered_by_euclidean_distance.insert(couple);
    } else {
        auto it = points_ordered_by_euclidean_distance.lower_bound(couple);
        if (it != points_ordered_by_euclidean_distance.end()){
            points_ordered_by_euclidean_distance.erase(std::prev(points_ordered_by_euclidean_distance.end()));
            points_ordered_by_euclidean_distance.insert(couple);
        }
    }
}

void compute_euclidean_distance(set<couple_of_3d_points>& points_ordered_by_euclidean_distance){
    for(auto it : points_ordered_by_euclidean_distance){
        cout << ( pow(it.get_first().get_x() - it.get_second().get_x(),2) 
        + pow(it.get_first().get_y() - it.get_second().get_y(),2) 
        + pow(it.get_first().get_z() - it.get_second().get_z(),2) ) << endl;
    }
}
// end section

int main () {
    fstream file("rinput.txt");

    if (!file) {
        cout << "Unable to open file";
        return 1;
    }

    string line{};
    set<couple_of_3d_points> points_ordered_by_euclidean_distance; 

    getline(file, line);
    string x,y,z;
    stringstream raw_points(line);
    getline(raw_points, x, ',');
    getline(raw_points, y, ',');
    getline(raw_points, z, ',');
    point_3d point1(stoi(x), stoi(y), stoi(z));
    getline(file, line);
    stringstream raw_points2(line);
    getline(raw_points2, x, ',');
    getline(raw_points2, y, ',');
    getline(raw_points2, z, ',');
    point_3d point2(stoi(x), stoi(y), stoi(z));

    points_ordered_by_euclidean_distance.insert(couple_of_3d_points(point1, point2));

    while(getline(file, line)){
        stringstream raw_points(line);
        
        string x,y,z;
        getline(raw_points, x, ',');
        getline(raw_points, y, ',');
        getline(raw_points, z, ',');

        point_3d point(stoi(x), stoi(y), stoi(z));

        set<couple_of_3d_points> points_ordered_by_euclidean_distance_to_be_added = points_ordered_by_euclidean_distance;
        for (auto it : points_ordered_by_euclidean_distance){
            if (point != it.get_first()){
                insert_with_limit(points_ordered_by_euclidean_distance_to_be_added, couple_of_3d_points(point, it.get_first()));
            }
            if (point != it.get_second()){
                insert_with_limit(points_ordered_by_euclidean_distance_to_be_added, couple_of_3d_points(point, it.get_second()));
            }
        }
        points_ordered_by_euclidean_distance = points_ordered_by_euclidean_distance_to_be_added;
    }

    cout << "Points in set: " << endl;
    for (auto it = points_ordered_by_euclidean_distance.begin(); it != points_ordered_by_euclidean_distance.end(); ++it) {
        cout << it->get_first().get_x() << "," << it->get_first().get_y() << "," << it->get_first().get_z() << " - ";
        cout << it->get_second().get_x() << "," << it->get_second().get_y() << "," << it->get_second().get_z() << endl;
    }
    cout << "With a total of " << points_ordered_by_euclidean_distance.size() << " pairs." << endl;

    compute_euclidean_distance(points_ordered_by_euclidean_distance);

    map<int, set<point_3d>> circuits_of_points;
    
    int circuit{0};
    for (auto couple_of_points = points_ordered_by_euclidean_distance.begin(); couple_of_points != points_ordered_by_euclidean_distance.end(); ++couple_of_points) {
        bool added = false;
        map<int, set<point_3d>> circuits_of_points_to_be_added = circuits_of_points;
        for (auto pair_circuit_points = circuits_of_points.begin(); pair_circuit_points != circuits_of_points.end(); ++pair_circuit_points) {
            for (auto points : pair_circuit_points->second){
                int first_circuit_found{0};
                if (points == couple_of_points->get_first() || points == couple_of_points->get_second()){
                    if (!added){
                        circuits_of_points_to_be_added.at(pair_circuit_points->first).insert(couple_of_points->get_first());
                        circuits_of_points_to_be_added.at(pair_circuit_points->first).insert(couple_of_points->get_second());
                        first_circuit_found = pair_circuit_points->first;
                        added = true;
                    } else {
                        circuits_of_points_to_be_added.at(first_circuit_found).insert(points);
                        circuits_of_points_to_be_added.erase(pair_circuit_points->first);
                    }
                }
            }
        }
        if (!added) {
            circuits_of_points.insert(make_pair(circuit++, set<point_3d>{couple_of_points->get_first(), couple_of_points->get_second()}));
        } else {
            circuits_of_points_to_be_added = circuits_of_points;
        }
    }

    cout << "There are in total " << circuits_of_points.size() << " neirest neibourgs points." << endl;

    for (auto& circuit : circuits_of_points){
        cout << "Cirtuit number:" << circuit.first << endl;
        for (auto& point : circuit.second){
            cout << "(" << point.get_x() << "," << point.get_y() << "," << point.get_z() << ")" << endl;
        }
    }

}