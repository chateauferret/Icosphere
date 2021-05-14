#ifndef ICOSPHERE_H
#define ICOSPHERE_H
#include <iostream>
#include <GeographicLib/Geocentric.hpp>
#include <GeographicLib/Geodesic.hpp>
#include <GeographicLib/Rhumb.hpp>
#include <map>
#include <mutex>
#include "geometry.h"
#include "../containers/robinhood.h"



template<class T>
class Icosphere {
public:

    static constexpr double X = 0.525731112119133606;
    static constexpr double Z = 0.850650808352039932;

    explicit Icosphere<T> (const unsigned int& depth);
    ~Icosphere();
    unsigned long vertexCount();
    unsigned int depth();
    Vertex<T>* nearest (const Geolocation& target, const unsigned int& depth = 0);


    void toGeolocation (const Cartesian& c, Geolocation& g);
    void toCartesian (const Geolocation& g, Cartesian& c);


    inline void divideTriangle (Triangle<T>* t);

protected:
    unsigned _depth;
    uint32_t _count;

    // mesh data structures

    std::vector<Vertex<T>*> _vertices;
    mutable Vertex<T>* _lastVisited;
    inline Triangle<T>* makeTriangle (Vertex<T>* a, Vertex<T>* b, Vertex<T>* c, Triangle<T>* parent);
    inline void makeNeighbours (Vertex<T>* p, Vertex<T>* q);

    inline Vertex<T>* addVertex (const Cartesian& c, int level);

    GeographicLib::Geocentric* _gc;

    // these are working variables for triangle subdivision
    uint32_t k;
    Vertex<T>* e1;
    uint64_t edgeKey;
    bool _initial;
    robin_hood::unordered_map<uint64_t, Vertex<T>*> edgeMap;
    typename robin_hood::unordered_map<uint64_t, Vertex<T>*>::iterator it;

    Vertex<T>* ids0 [3];  // triangles of outer vertices
    Vertex<T>* ids1 [3];  // triangles of edge vertices

    Cartesian c;
    unsigned level;
    uint32_t expectedVertices;
    Vertex<T>* operator [] (const uint32_t& id);

    Vertex<T>* walkTowards (const Geolocation& target, const unsigned int& depth);
    Vertex<T>* walkTowards (const Cartesian& target, const unsigned int& depth) const;

};
#endif // ICOSPHERE_H
