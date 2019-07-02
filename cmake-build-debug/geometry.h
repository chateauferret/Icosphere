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

struct Vertex {
public:
    Cartesian cartesian;
    std::vector<Vertex*> neighbours;              // neighbouring vertices
    uint32_t id;
    unsigned level;
};

struct Triangle {
public:
    Vertex* vertices [3];
    unsigned level;
};

#endif