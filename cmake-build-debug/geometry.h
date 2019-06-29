#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <cstdint>
#include <vector>
#include <forward_list>
#include <list>

struct Cartesian {
public:
    double x, y, z;
};

struct Geolocation {
public:
    double lat, lon, height;
};

struct Vertex {
public:
    Cartesian cartesian;
    std::forward_list<Vertex*> neighbours;              // neighbouring vertices
    uint32_t id;
    unsigned level;
};

struct Triangle {
public:
    Vertex* vertices [3];
    unsigned level;
};

#endif