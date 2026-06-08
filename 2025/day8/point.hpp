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
        return ( x + y + z ) < ( other.x + other.y + other.z );
    }
    
    long long squared_distance_to(const point_3d& other) const {
        long long dx = x - other.x;
        long long dy = y - other.y;
        long long dz = z - other.z;
        return dx*dx + dy*dy + dz*dz;
    }
};