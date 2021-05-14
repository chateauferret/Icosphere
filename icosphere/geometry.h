#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <cstdint>
#include <vector>

struct Cartesian {
public:
    double x, y, z;
};

struct Geolocation {
public:
    double lat, lon, height;
};

template<class T>
class Triangle;

template<class T>
struct Vertex {
public:
    Cartesian cartesian;
    std::vector<Vertex<T>*> neighbours;              // neighbouring vertices
    std::vector<Triangle<T>*> triangles;               // triangles of which this vertex is an apex
    uint32_t id;
    unsigned level;
    T data;
};

template<class T>
class Triangle {
public:
    Vertex<T>* vertices [3];
    unsigned level;
};

class Geometry {
public:
    static double distSquared (const Cartesian& a, const Cartesian& b) {
        double dx = fabs (a.x - b.x);
        double dy = fabs (a.y - b.y);
        double dz = fabs (a.z - b.z);
        double dist = dx * dx + dy * dy + dz * dz;
        return dist;
    }
};


class IcosphereTestRow {
public:
    IcosphereTestRow () { }

protected:


};

#endif