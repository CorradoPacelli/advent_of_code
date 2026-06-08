#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <numeric>

#include "point.hpp"

constexpr int CONNECTION_TO_MAKE = 1000;

using namespace std;

// Union-Find data structure to easily track connected circuits
struct CircuitTracker {
    vector<int> parent_leader;
    vector<int> circuit_size;

    CircuitTracker(int total_elements) {
        parent_leader.resize(total_elements);
        circuit_size.resize(total_elements, 1);
        iota(parent_leader.begin(), parent_leader.end(), 0);
    }

    int find_leader(int box_index) {
        if (parent_leader[box_index] == box_index)
            return box_index;
        return parent_leader[box_index] = find_leader(parent_leader[box_index]);
    }

    void connect_boxes(int box_a, int box_b) {
        int leader_a = find_leader(box_a);
        int leader_b = find_leader(box_b);
        if (leader_a != leader_b) {
            if (circuit_size[leader_a] < circuit_size[leader_b])
                swap(leader_a, leader_b);
            parent_leader[leader_b] = leader_a;
            circuit_size[leader_a] += circuit_size[leader_b];
        }
    }
};

int main() {
    ifstream input_file("input.txt");

    if (!input_file) {
        cout << "Unable to open file\n";
        return 1;
    }

    string line;
    vector<point_3d> junction_boxes;

    while (getline(input_file, line)) {
        stringstream coordinate_stream(line);
        string x, y, z;
        getline(coordinate_stream, x, ',');
        getline(coordinate_stream, y, ',');
        getline(coordinate_stream, z, ',');
        junction_boxes.emplace_back(stoi(x), stoi(y), stoi(z));
    }

    struct PotentialConnection {
        int box_a_index;
        int box_b_index;
        long long squared_distance;
    };

    vector<PotentialConnection> possible_connections;
    for (int i = 0; i < junction_boxes.size(); ++i) {
        for (int j = i + 1; j < junction_boxes.size(); ++j) {
            possible_connections.push_back({i, j, junction_boxes[i].squared_distance_to(junction_boxes[j])});
        }
    }

    // Sort possible connections by distance ascending
    sort(possible_connections.begin(), possible_connections.end(), [](const PotentialConnection& a, const PotentialConnection& b) {
        return a.squared_distance < b.squared_distance;
    });

    CircuitTracker circuit_tracker(junction_boxes.size());

    //int connections_to_process = min(CONNECTION_TO_MAKE, (int)possible_connections.size());
    int connections_to_process = (int)possible_connections.size();
    bool stop{false};
    for (int i = 0; i < connections_to_process; ++i) {
        circuit_tracker.connect_boxes(possible_connections[i].box_a_index, possible_connections[i].box_b_index);
        for (auto sizes : circuit_tracker.circuit_size){
            if (sizes == 1000){
                cout << "found what you need for part 2:)" << endl;
                cout << "index of point 1: " << possible_connections[i].box_a_index << endl;
                cout << "index of point 2: " << possible_connections[i].box_b_index << endl;
                cout << " point 1 x" << junction_boxes[possible_connections[i].box_a_index].get_x() << endl;
                cout << " point 2 x" << junction_boxes[possible_connections[i].box_b_index].get_x() << endl;
                cout << " the anwers is: " << junction_boxes[possible_connections[i].box_a_index].get_x() * junction_boxes[possible_connections[i].box_b_index].get_x() << endl;
                stop = true;
            }
        }
        if (stop){
            break;
        }
    }

    // Collect the sizes of all distinct circuits
    vector<int> final_circuit_sizes;
    for (int i = 0; i < junction_boxes.size(); ++i) {
        if (circuit_tracker.parent_leader[i] == i) { // If it's a root, it represents a distinct circuit
            final_circuit_sizes.push_back(circuit_tracker.circuit_size[i]);
        }
    }

    // Sort descending to easily access the largest circuits
    sort(final_circuit_sizes.rbegin(), final_circuit_sizes.rend());

    long long circuit_size_product = 1;
    int circuits_to_multiply = min(3, (int)final_circuit_sizes.size());
    for (int i = 0; i < circuits_to_multiply; ++i) {
        circuit_size_product *= final_circuit_sizes[i];
    }

    cout << "Product of the sizes of the 3 largest circuits: " << circuit_size_product << endl;

    return 0;
}