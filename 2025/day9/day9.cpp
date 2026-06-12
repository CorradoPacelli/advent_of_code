#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <limits>

using namespace std;

//4758121828 correct part1
//4682519154 part2 answer too hight
//4591114350 part2 too right
//213817848 too low :(

/* good idea but this time the input file is already better */
auto comparator_order_by_x = [](const pair<int, int>& a, const pair<int, int>& b) {
    if (a.first == b.first) {
        return a.second < b.second;
    }
    return a.first < b.first;
};

    
auto comparator_order_by_y = [](const pair<int, int>& a, const pair<int, int>& b) {
    if (a.second == b.second) {
        return a.first < b.first;
    }
    return a.second < b.second;
};


bool is_valid_rectangle(
    long long x1,
    long long y1,
    long long x2,
    long long y2,
    const map< int, set<pair<int, int>> >& complete_set_of_points_ordered_by_x
);

void display(const std::map<int, std::set<pair<int, int>>>& map);

void complete_shape(    
    map< int, set<pair<int, int>> >& points
);

// Funzione helper per fondere un nuovo intervallo [start, end] all'interno del nostro set
void add_interval(std::set<std::pair<int, int>>& intervals, int start, int end) {
    auto it = intervals.lower_bound({start, std::numeric_limits<int>::min()});
    if (it != intervals.begin()) {
        auto prev_it = std::prev(it);
        if (prev_it->second >= start - 1) {
            it = prev_it;
        }
    }
    int new_start = start;
    int new_end = end;
    while (it != intervals.end() && it->first <= new_end + 1) {
        new_start = std::min(new_start, it->first);
        new_end = std::max(new_end, it->second);
        it = intervals.erase(it);
    }
    intervals.insert({new_start, new_end});
}

int main() {
    ifstream input_file("input.txt");

    if (!input_file) {
        cout << "Unable to open file\n";
        return 1;
    }

    string line;
    vector<pair<int, int>> vector_of_points;
    map< int, set<pair<int, int>> > complete_set_of_points_ordered_by_x{};

    getline(input_file, line);
    int position_of_comma = line.find(',');

    int first_x = stoi(line.substr(0, position_of_comma));
    int first_y = stoi(line.substr(position_of_comma + 1));
    vector_of_points.emplace_back(first_x, first_y);
    
    int prev_x = first_x;
    int prev_y = first_y;

    while (getline(input_file, line)) {
        position_of_comma = line.find(',');

        int x = stoi(line.substr(0, position_of_comma));
        int y = stoi(line.substr(position_of_comma + 1));
        
        int min_x = min(prev_x, x);
        int min_y = min(prev_y, y);
        int max_x = max(prev_x, x);
        int max_y = max(prev_y, y);
        
        if (min_x < max_x) { // Linea Orizzontale
            for (int i = min_x; i <= max_x; ++i) {
                add_interval(complete_set_of_points_ordered_by_x[i], prev_y, prev_y);
            }
        } else if (min_y < max_y) { // Linea Verticale
            add_interval(complete_set_of_points_ordered_by_x[x], min_y, max_y);
        }

        vector_of_points.emplace_back(x, y);
        prev_x = x;
        prev_y = y;
    }

    // Chiudiamo il perimetro connettendo l'ultimo punto parseato al primissimo punto originale
    int min_x = min(prev_x, first_x);
    int min_y = min(prev_y, first_y);
    int max_x = max(prev_x, first_x);
    int max_y = max(prev_y, first_y);
    
    if (min_x < max_x) {
        for (int i = min_x; i <= max_x; ++i) {
            add_interval(complete_set_of_points_ordered_by_x[i], prev_y, prev_y);
        }
    } else if (min_y < max_y) {
        add_interval(complete_set_of_points_ordered_by_x[first_x], min_y, max_y);
    }

    input_file.close();

    complete_shape(complete_set_of_points_ordered_by_x);
    //display(complete_set_of_points_ordered_by_x);


    long long max_area{0};
    for (size_t i{0}; i < vector_of_points.size(); ++i ){
        for (size_t j{i + 1}; j < vector_of_points.size(); ++j){
            long long x1 = vector_of_points[i].first;
            long long x2 = vector_of_points[j].first;
            long long y1 = vector_of_points[i].second;
            long long y2 = vector_of_points[j].second;
            long long height = abs(y1 - y2) + 1;
            long long base = abs(x1 - x2) + 1;
            long long area = base * height;

            if (area > max_area){
                if (is_valid_rectangle(x1, y1, x2, y2, complete_set_of_points_ordered_by_x)){
                    max_area = area;
                }
            }
        }
    }

    cout << "Max area: " << max_area << endl;
    return 0; 
}

void complete_shape(    
    map< int, set<pair<int, int>> >& points
){
    // Avendo già fuso tutti i perimetri in segmenti [y1, y2], per chiudere la shape ci 
    // basta unire ogni coppia di intervalli per la regola pari/dispari della geometria!
    for (auto& [x, intervals] : points) {
        if (intervals.empty()) continue;
        
        set<pair<int, int>> filled_intervals;
        auto it = intervals.begin();
        while (it != intervals.end()) {
            int start = it->first;
            int end = it->second;
            ++it;
            if (it != intervals.end()) {
                end = it->second;
                ++it;
            }
            filled_intervals.insert({start, end});
        }
        intervals = std::move(filled_intervals);
    }
}

void display(const std::map<int, std::set<pair<int, int>>>& points_by_x) {
    if (points_by_x.empty()) return;

    int min_x = points_by_x.begin()->first;
    int max_x = points_by_x.rbegin()->first;

    int min_y = std::numeric_limits<int>::max();
    int max_y = std::numeric_limits<int>::min();

    for (const auto& [x, intervals] : points_by_x) {
        if (!intervals.empty()) {
            min_y = std::min(min_y, intervals.begin()->first);
            max_y = std::max(max_y, intervals.rbegin()->second);
        }
    }

    std::cout << "--- Printing the 2D Grid ---" << std::endl;

    for (int y = min_y; y <= max_y; ++y) {
        for (int x = min_x; x <= max_x; ++x) {
            auto it_map = points_by_x.find(x);
            bool found = false;
            if (it_map != points_by_x.end()) {
                auto it = it_map->second.upper_bound({y, std::numeric_limits<int>::max()});
                if (it != it_map->second.begin()) {
                    --it;
                    if (it->first <= y && y <= it->second) {
                        found = true;
                    }
                }
            }
            if (found) {
                std::cout << "X ";
            } else {
                std::cout << ". ";
            }
        }
        std::cout << std::endl;
    }
}

bool is_valid_rectangle(
    long long x1,
    long long y1,
    long long x2,
    long long y2,
    const map< int, set<pair<int, int>> >& complete_set_of_points_ordered_by_x
) {
    if (x1 < x2) {
        swap(x1,x2);
    }
    if (y1 < y2) {
        swap(y1,y2);
    }

    for (int i = x2; i <= x1; ++i){
        auto it_map = complete_set_of_points_ordered_by_x.find(i);
        if (it_map == complete_set_of_points_ordered_by_x.end()) return false;
        
        bool covered = false;
        auto it = it_map->second.upper_bound({y2, std::numeric_limits<int>::max()});
        if (it != it_map->second.begin()) {
            --it;
            if (it->first <= y2 && it->second >= y1) {
                covered = true;
            }
        }
        if (!covered) return false;
    }
    return true;
}

/*
void display(set<pair<int, int>, decltype(comparator_order_by_x)>&  set_x, set<pair<int, int>, decltype(comparator_order_by_y)>&  set_y){
    std::cout << "--- Printing the 2D Grid ---" << std::endl;

    // 1. Deduce the maximum row index
    auto max_row_x = std::max_element(set_x.begin(), set_x.end(),
        [](const auto& a, const auto& b) { return a.first < b.first; });
    
    // 2. Deduce the maximum column index
    auto max_col_x = std::max_element(set_x.begin(), set_x.end(),
        [](const auto& a, const auto& b) { return a.second < b.second; });

    // 1. Deduce the maximum row index
    auto max_row_y = std::max_element(set_y.begin(), set_y.end(),
        [](const auto& a, const auto& b) { return a.first < b.first; });
    
    // 2. Deduce the maximum column index
    auto max_col_y = std::max_element(set_y.begin(), set_y.end(),
        [](const auto& a, const auto& b) { return a.second < b.second; });

    // Matrix size needs to be (max_index + 1) to include the point safely
    int rows = max(max_row_x->first + 1, max_row_y->first + 1);
    int cols = max(max_col_x->first + 1, max_col_y->first + 1);

    // Loop through each row and column of the matrix
    for (int r = 0; r <= rows; ++r) {
        for (int c = 0; c <= cols; ++c) {
            // Check if the current coordinate {r, c} exists in our set
            if (set_x.count({r, c})) {
                std::cout << "X "; // Character representing a stored point
            } else if (set_y.count({r, c})){
                std::cout << "Y "; // Character representing a stored point
            } else {
                std::cout << ". "; // Character representing an empty space
            }
        }
        std::cout << std::endl; // Move to the next line after each row
    }
}


bool is_valid_rectangle(
    long long x1,
    long long y1,
    long long x2,
    long long y2,
    set<pair<int, int>, decltype(comparator_order_by_x)>& points_ordered_by_x,
    set<pair<int, int>, decltype(comparator_order_by_y)>& points_ordered_by_y
){
    
    if ((x1 >= x2 && y2 >= y1) || (x1 <= x2 && y1 >= y2)) {
        // you have top right and bottom left
        if (x1 < x2) {
            // force 1 to be top right
            swap(x1, x2);
            swap(y1, y2);
        }

        
        //x1 = 7
        //y1 = 1

        //x2 = 11
        //y2 = 1

        //Y
        //.
        //. x2       x1
        //..............
        //.......#...A..  y1
        //..............
        //..B....#......  y2
        //..............
        //..#......#....
        //..............
        //.........#.#..
        //.....................X
        // A(x1,y1)
        // B(x2,y2)

        auto y_start = points_ordered_by_y.lower_bound({std::numeric_limits<int>::min(), y1});
        auto y_end = points_ordered_by_y.lower_bound({std::numeric_limits<int>::min(), y1 + 1});
        auto it = y_start;
        for (; it != y_end; ++it) {
            if (it->first <= x2) {
                break;
            }
        }

        if (it == y_end) {
            // Not foud :(
            return false;
        }

        y_start = points_ordered_by_y.lower_bound({std::numeric_limits<int>::min(), y2});
        y_end = points_ordered_by_y.lower_bound({std::numeric_limits<int>::min(), y2 + 1});
        it = y_start;
        for (; it != y_end; ++it) {
            if (it->first >= x1) {
                break;
            }
        }

        if (it == y_end) {
            // Not foud :(
            return false;
        } 

        auto x_start = points_ordered_by_x.lower_bound({x1, std::numeric_limits<int>::min()});
        auto x_end = points_ordered_by_x.lower_bound({x1 + 1, std::numeric_limits<int>::min()});

        it = x_start;
        for (; it != x_end; ++it) {
            if (it->first <= y2) {
                break;
            }
        }

        if (it == x_end) {
            // Not foud :(
            return false;
        } 

        x_start = points_ordered_by_x.lower_bound({x2, std::numeric_limits<int>::min()});
        x_end = points_ordered_by_x.lower_bound({x2 + 1, std::numeric_limits<int>::min()});
        it = x_start;
        for (; it != x_end; ++it) {
            if (it->first >= y1) {
                break;
            }
        }

        if (it == x_end) {
            // Not foud :(
            return false;
        } 

        
    } else {
        //((x1 >= x2 && y1 <= y2) || (x1 >= x2 && y1 <= y2))
        // you have top left and bottom right
        if (x1 > x2) {
            // force 1 to be the top left
            swap(x1, x2);
            swap(y1, y2);
        }

        //x1 = 2
        //y1 = 3

        //x2 = 9
        //y2 = 5

        //Y
        //.
        //.      x1  x2
        //..............
        //.......A...#..  y1
        //..............
        //..#....#......
        //..............
        //..#......#....
        //..............
        //.........#.B..  y2
        //.....................X
        // A(x1,y1)
        // B(x2,y2)

        auto y_start = points_ordered_by_y.lower_bound({std::numeric_limits<int>::min(), y1});
        auto y_end = points_ordered_by_y.lower_bound({std::numeric_limits<int>::min(), y1 + 1});
        auto it = y_start;
        for (; it != y_end; ++it) {
            if (it->first >= x2) {
                break;
            }
        }

        if (it == y_end) {
            // Not foud :(
            return false;
        } 

        y_start = points_ordered_by_y.lower_bound({std::numeric_limits<int>::min(), y2});
        y_end = points_ordered_by_y.lower_bound({std::numeric_limits<int>::min(), y2 + 1});
        it = y_start;
        for (; it != y_end; ++it) {
            if (it->first <= x1) {
                break;
            }
        }

        if (it == y_end) {
            // Not foud :(
            return false;
        } 

        auto x_start = points_ordered_by_x.lower_bound({x1, std::numeric_limits<int>::min()});
        auto x_end = points_ordered_by_x.lower_bound({x1 + 1, std::numeric_limits<int>::min()});
        it = x_start;
        for (; it != x_end; ++it) {
            if (it->first <= y2) {
                break;
            }
        }

        if (it == x_end) {
            // Not foud :(
            return false;
        } 

        x_start = points_ordered_by_x.lower_bound({x2, std::numeric_limits<int>::min()});
        x_end = points_ordered_by_x.lower_bound({x2 + 1, std::numeric_limits<int>::min()});
        it = x_start;
        for (; it != x_end; ++it) {
            if (it->first >= y1) {
                break;
            }
        }

        if (it == x_end) {
            // Not foud :(
            return false;
        } 
    }
    return true;
}


bool is_valid_rectangle(
    long long x1,
    long long y1,
    long long x2,
    long long y2,
    set<pair<int, int>, decltype(comparator_order_by_x)>& points_ordered_by_x,
    set<pair<int, int>, decltype(comparator_order_by_y)>& points_ordered_by_y
){
    
    if ((x1 >= x2 && y1 >= y2) || (x1 <= x2 && y1 <= y2)) {
        // you have top right and bottom left
        if (x1 < x2) {
            // force 1 to be top right
            swap(x1, x2);
            swap(y1, y2);
        }
        // look for 2 points:
        // one has to have (x <= x2 AND y = y1) OR (y <= y2 AND x = x1)
        // the second has to have (x >= x1 AND y = y2) OR (y >= y1 AND x = x2)

        // look for the first point first "OR" (x <= x2 AND y = y1)
        pair<int,int> dummy_y1_lower{std::numeric_limits<int>::min(), static_cast<int>(y1)};
        //pair<int,int> dummy_y1_upper{std::numeric_limits<int>::min(), static_cast<int>(y1+1)};
        auto lower_bound_y = points_ordered_by_y.lower_bound( dummy_y1_lower );
       
        if(lower_bound_y != points_ordered_by_y.end() && lower_bound_y->first <= x2){
            // first point found
        } else {
            // look for the first point second "OR" (y <= y2 AND x = x1)
            pair<int,int> dummy_x1_lower{static_cast<int>(x1), std::numeric_limits<int>::min()};
            auto lower_bound_x = points_ordered_by_x.lower_bound( dummy_x1_lower );
            if(lower_bound_x != points_ordered_by_x.end() && lower_bound_y->second <= y2){
                // first point found
            } else {
                return false;
            }
        }

        // look for the second point first "OR" (x >= x1 AND y = y2)
        pair<int,int> dummy_y2_lower{static_cast<int>(x2), static_cast<int>(y2)};
        auto upper_bound_y = points_ordered_by_y.upper_bound( dummy_y2_lower );

        if(upper_bound_y != points_ordered_by_y.end() && upper_bound_y->second >= x1){
            // first point found
        } else {
            // look for the second point second "OR" (y >= y1 AND x = x2)
            pair<int,int> dummy_x2_upper{static_cast<int>(x2), static_cast<int>(y2)};
            auto upper_bound_x = points_ordered_by_x.upper_bound( dummy_x2_upper );
            if (upper_bound_x != points_ordered_by_x.end() && upper_bound_x->second >= y1){
                // first point found
            } else {
                return false;
            }
        }

    } else {
        //((x1 >= x2 && y1 <= y2) || (x1 >= x2 && y1 <= y2))
        // you have top left and bottom right
        if (x1 < x2) {
            // force 1 to be the bottom left
            swap(x1, x2);
            swap(y1, y2);
        }

        // look for 2 points:
        // one has to have (x <= x1 AND y = y1) OR (y >= y2 AND x = x1)
        // the second has to have (x >= x2 AND y = y2) OR (y <= y2 AND x = x2)

        // look for (x <= x1 AND y = y1)
        pair<int,int> dummy_y1_lower{std::numeric_limits<int>::min(), static_cast<int>(y1)};
        auto lower_bound_y = points_ordered_by_y.lower_bound( dummy_y1_lower );

        if(lower_bound_y != points_ordered_by_y.end() && lower_bound_y->first <= x1){
            // first point found
        } else {
            // look for (y >= y2 AND x = x1)
            pair<int,int> dummy_x1_upper{static_cast<int>(x1), static_cast<int>(y2)};
            auto upper_bound_x = points_ordered_by_x.upper_bound( dummy_x1_upper );
            if(upper_bound_x != points_ordered_by_x.end() && lower_bound_y->second >= y2){
                // first point found
            } else {
                return false;
            }
        }

        // look for (x >= x2 AND y = y2)
        pair<int,int> dummy_y2_upper{static_cast<int>(x2), static_cast<int>(y2)};
        auto upper_bound_y = points_ordered_by_y.upper_bound( dummy_y2_upper );

        if(upper_bound_y != points_ordered_by_y.end() && upper_bound_y->second >= x2){
            // first point found
        } else {
            // look for (y <= y2 AND x = x2)
            pair<int,int> dummy_x2_lower{static_cast<int>(x2), std::numeric_limits<int>::min()};
            auto lower_bound_x = points_ordered_by_x.lower_bound( dummy_x2_lower );
            if (lower_bound_x != points_ordered_by_x.end() && lower_bound_x->second <= y2){
                // first point found
            } else {
                return false;
            }
        }

    }
    return true;
}
*/