#pragma once 

#include <cmath>

class point_3d {
private:
    int x;
    int y;
    int z;

public:
    point_3d(int x, int y, int z): x(x), y(y), z(z) {};;
    int get_x() const {return x;}
    int get_y() const {return y;}
    int get_z() const {return z;}
    bool operator==(const point_3d& other) const {
        return (x == other.x && y == other.y && z == other.z);
    }
    bool operator!=(const point_3d& other) const {
        return !(*this == other);
    }
    bool operator<(const point_3d& other) const {
        return ( pow(x,2) + pow(y,2) + pow(z,2) ) < ( pow(other.x,2) + pow(other.y,2) + pow(other.z,2) );
    }
};

namespace std{
    template <>
    struct hash<point_3d> {
        std::size_t operator()(const point_3d& p) const {
            return (p.get_x()*100 + p.get_y())*100 + p.get_z();
        }
    };
}

class couple_of_3d_points {
private:
    point_3d first;
    point_3d second;

public:
    couple_of_3d_points(point_3d first, point_3d second): first(first), second(second) {};
    point_3d get_first() const {return first;}
    point_3d get_second() const {return second;}

    bool operator<(const couple_of_3d_points& other) const {
        return ( pow(first.get_x() - second.get_x(),2) + pow(first.get_y() - second.get_y(),2) + pow(first.get_z() - second.get_z(),2) )
        < ( pow(other.first.get_x() - other.second.get_x(),2) + pow(other.first.get_y() - other.second.get_y(),2) + pow(other.first.get_z() - other.second.get_z(),2) );
    }

    bool operator==(const couple_of_3d_points& other) const {
        return (first == other.first && second == other.second) || (first == other.second && second == other.first);
    }

    bool operator!=(const couple_of_3d_points& other) const {
        return !(*this == other);
    }
};