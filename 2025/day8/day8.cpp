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

    map<int, set<point_3d> > circuits;
    int number_of_circuits{0};
    unordered_set<point_3d> total_points_in_circuits;

    for (auto couple : points_ordered_by_euclidean_distance){
        if ((total_points_in_circuits.find(couple.get_first()) != total_points_in_circuits.end())
            || (total_points_in_circuits.find(couple.get_second()) != total_points_in_circuits.end())) {
            //this means that one of the points already exist so we have to update a circuits
            if ((total_points_in_circuits.find(couple.get_first()) != total_points_in_circuits.end())
            && (total_points_in_circuits.find(couple.get_second()) != total_points_in_circuits.end())) {
                //difficult to implement, since we also have to handle merges of two cirucits
                int circuit_one{-1}, circuit_two{-1};
                for (auto sets = circuits.begin(); sets != circuits.end(); ++sets) {
                    for ( auto point = sets->second.begin(); point != sets->second.end(); ++point ) {
                        if (*point == couple.get_first()) {
                            circuit_one = sets->first;
                            break;
                        }
                        if (*point == couple.get_second()) {
                            circuit_two = sets->first;
                            break;
                        }
                    }
                }

                if (circuit_one != circuit_two) {
                    circuits[circuit_one].insert(circuits[circuit_two].begin(), circuits[circuit_two].end());
                    circuits.erase(circuit_two);
                }


            } else {
                //just one of the 2 points is already in the circuits, so we can just add the other point
                if (total_points_in_circuits.find(couple.get_first()) != total_points_in_circuits.end()) {
                    // insert second elemenmt
                    for (auto sets = circuits.begin(); sets != circuits.end(); ++sets) {
                        for ( auto point = sets->second.begin(); point != sets->second.end(); ++point ) {
                            if (*point == couple.get_first()) {
                                circuits[sets->first].emplace(couple.get_second());
                                break;
                            }
                        }
                    }
                } else {
                    // insert first element
                    for (auto sets = circuits.begin(); sets != circuits.end(); ++sets) {
                        for ( auto point = sets->second.begin(); point != sets->second.end(); ++point ) {
                            if (*point == couple.get_second()) {
                                circuits[sets->first].emplace(couple.get_first());
                                break;
                            }
                        }
                    }
                }
            }
        } else {
            circuits.emplace(number_of_circuits++, std::move(set<point_3d>{couple.get_first(), couple.get_second()}));
            total_points_in_circuits.emplace(couple.get_first());
            total_points_in_circuits.emplace(couple.get_second());
        }
    }

    for (auto circuit = circuits.begin(); circuit != circuits.end(); ++circuit) {
        cout << "Cirtuit number:" << circuit->first << endl;
        for (auto& point : circuit->second){
            cout << "(" << point.get_x() << "," << point.get_y() << "," << point.get_z() << ")" << endl;
        }
    }

}