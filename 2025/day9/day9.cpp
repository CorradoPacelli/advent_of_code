#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <set>
#include <cmath>
#include <map>

using namespace std;

//4758121828 correct part1
//4682519154 part2 answer too hight
//4591114350 part2 too hight
//1577956170 --> correct part2!!!!
//213817848 too low :(


struct Point {
    long long x, y;
};

struct Event {
    double x_start;
    double x_end;
    int parity_change; // 1 for crossing, 0 for U-turn

    bool operator<(const Event& other) const {
        return x_start < other.x_start;
    }
};

// removed useless points like .....X.....Y.....Z... 
// they all share the same y coordinate, they create an orizontal line, Y is useless and can be removed 
vector<Point> get_cleaned_polygon(const vector<Point>& original) {
    vector<Point> p = original;
    bool changed = true;
    while (changed && p.size() >= 4) {
        changed = false;
        vector<Point> next_p;
        int cur_n = p.size();
        for (int i = 0; i < cur_n; ++i) {
            Point prev = p[(i - 1 + cur_n) % cur_n];
            Point curr = p[i];
            Point next = p[(i + 1) % cur_n];
            if ((prev.x == curr.x && curr.x == next.x) || (prev.y == curr.y && curr.y == next.y)) {
                changed = true;
            } else {
                next_p.push_back(curr);
            }
        }
        p = next_p;
    }
    return p;
}

vector<pair<double, double>> get_valid_x_intervals(double y, const vector<Point>& vertices) {
    vector<Event> events;
    int n = vertices.size();
    for (int i = 0; i < n; ++i) {
        Point p1 = vertices[i];
        Point p2 = vertices[(i + 1) % n];

        if (p1.x == p2.x) { // Vertical edge
            double y_min = min(p1.y, p2.y);
            double y_max = max(p1.y, p2.y);
            if (y_min < y && y < y_max) {
                events.push_back({(double)p1.x, (double)p1.x, 1});
            }
        } else if (p1.y == p2.y) { // Horizontal edge
            if ((double)p1.y == y) {
                double x_min = min(p1.x, p2.x);
                double x_max = max(p1.x, p2.x);
                
                Point p_prev = vertices[(i - 1 + n) % n];
                Point p_next = vertices[(i + 2) % n];
                
                double y_adj1 = p_prev.y;
                double y_adj2 = p_next.y;
                
                int parity = ((y_adj1 > y) != (y_adj2 > y)) ? 1 : 0;
                events.push_back({x_min, x_max, parity});
            }
        }
    }

    sort(events.begin(), events.end());

    vector<pair<double, double>> valid_intervals;
    bool inside = false;
    double current_start = -1;

    for (const auto& ev : events) {
        if (ev.x_start == ev.x_end) { // Cross
            if (inside) {
                valid_intervals.push_back({current_start, ev.x_start});
                inside = false;
            } else {
                inside = true;
                current_start = ev.x_start;
            }
        } else { // H_Seg
            if (inside) {
                if (ev.parity_change == 1) {
                    valid_intervals.push_back({current_start, ev.x_end});
                    inside = false;
                }
            } else {
                if (ev.parity_change == 1) {
                    current_start = ev.x_start;
                    inside = true;
                } else {
                    valid_intervals.push_back({ev.x_start, ev.x_end});
                }
            }
        }
    }

    return valid_intervals;
}

int main() {
    ifstream input_file("input.txt");
    if (!input_file) {
        cout << "Unable to open file\n";
        return 1;
    }

    string line;
    vector<Point> original_vertices;

    while (getline(input_file, line)) {
        if (line.empty()) continue;
        int position_of_comma = line.find(',');
        if (position_of_comma != string::npos) {
            long long x = stoll(line.substr(0, position_of_comma));
            long long y = stoll(line.substr(position_of_comma + 1));
            original_vertices.push_back({x, y});
        }
    }
    input_file.close();

    vector<Point> clean_polygon = get_cleaned_polygon(original_vertices);

    set<double> rep_y_set;
    for (const auto& p : original_vertices) {
        rep_y_set.insert(p.y);
    }

    vector<double> rep_y_list(rep_y_set.begin(), rep_y_set.end());
    vector<double> all_rep_ys;
    for (size_t i = 0; i < rep_y_list.size(); ++i) {
        all_rep_ys.push_back(rep_y_list[i]);
        if (i + 1 < rep_y_list.size()) {
            all_rep_ys.push_back((rep_y_list[i] + rep_y_list[i+1]) / 2.0);
        }
    }

    map<double, vector<pair<double, double>>> Intervals;
    for (double y : all_rep_ys) {
        Intervals[y] = get_valid_x_intervals(y, clean_polygon);
    }

    long long max_area{0};
    int n = original_vertices.size();
    
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            long long x_start = min(original_vertices[i].x, original_vertices[j].x);
            long long x_end = max(original_vertices[i].x, original_vertices[j].x);
            long long y_start = min(original_vertices[i].y, original_vertices[j].y);
            long long y_end = max(original_vertices[i].y, original_vertices[j].y);

            bool valid = true;
            
            auto it_start = lower_bound(all_rep_ys.begin(), all_rep_ys.end(), (double)y_start);
            
            for (auto it = it_start; it != all_rep_ys.end() && *it <= (double)y_end + 1e-9; ++it) {
                double y = *it;
                const auto& intervals = Intervals[y];
                bool covered = false;
                for (const auto& interval : intervals) {
                    if (interval.first <= x_start && x_end <= interval.second) {
                        covered = true;
                        break;
                    }
                }
                if (!covered) {
                    valid = false;
                    break;
                }
            }
            
            if (valid) {
                long long area = (x_end - x_start + 1) * (y_end - y_start + 1);
                if (area > max_area) {
                    max_area = area;
                }
            }
        }
    }

    cout << "Max area: " << max_area << endl;
    return 0; 
}
