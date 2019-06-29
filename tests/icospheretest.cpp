#include <limits.h>
#include <gtest/gtest.h>
#include <iostream>
#include <random>
#include <icosphere/icosphere.h>


using namespace Halifirien;

class IcosphereTestRow {
public:
    IcosphereTestRow () { }

protected:


};


class IcosphereTest : public ::testing::TestWithParam<IcosphereTestRow> {
    protected:
    unsigned points;
    double maxdist, totaldist;
    long timeEnd, timeStart;

    Icosphere icosphere = Icosphere (5);
    time_t seed;
    std::default_random_engine e;
    std::uniform_real_distribution<double> random;


    virtual void SetUpTestCase() {
/*        for (int i = 0; i < 8; i++) {
            legend.addEntry (100 * i, colours [i]);
        }
        maxdist = 0.0;
        totaldist = 0.0;
        seed = time (NULL);
        e = std::default_random_engine (seed);
        random = std::uniform_real_distribution<double> (0.0, 1.0);
        timeStart = clock() / static_cast<double> (CLOCKS_PER_SEC);
*/
    }

    virtual void TearDownTestCase() {

    }
};

TEST (IcosphereTest, buildSpeed) {

    for (int j = 4; j < 11; j++) {
        std::cout << "Built icosphere level " << j << ": ";
        double start = clock () / static_cast<double> (CLOCKS_PER_SEC);
        Icosphere* i = new Icosphere (j);
        double end = clock () / static_cast<double> (CLOCKS_PER_SEC);
        std::cout <<  i -> vertexCount () << " vertices in " << end - start << " seconds: " << sizeof (*i) << " bytes\n";
        delete i;
    }
}


TEST (IcosphereTest, searchTimes) {
    std::cout << "Search test\n";
    for (int i = 6; i < 9; i++) {
        Icosphere* icosphere = new Icosphere (i);
        time_t seed = time (NULL);
        std::default_random_engine e = std::default_random_engine (seed);
        std::uniform_real_distribution<double> random = std::uniform_real_distribution<double> (0.0, 1.0);
        double timeStart = clock () / static_cast<double> (CLOCKS_PER_SEC);
        double maxdist = 0.0, totaldist = 0.0;
        unsigned points;
        for (points = 0; points < 100; points++) {

            Geolocation sought;
            sought.lat = (random (e) - 0.5) * 180;
            sought.lon = (random (e) - 0.5) * 360;
            Vertex* found = icosphere -> nearest (sought);
            Cartesian c;
            icosphere -> toCartesian (sought, c);

            double dist = sqrt (icosphere -> distSquared (c, found -> cartesian));
            maxdist = dist > maxdist ? dist : maxdist;
            totaldist += dist;
        }
        double timeEnd = clock () / static_cast<double> (CLOCKS_PER_SEC);

        EXPECT_LT (totaldist / points, maxdist * 2);
        EXPECT_LT (totaldist / points, 0.02);
        std::cout << "Level " << i << ": Found " << points << " points in " << timeEnd - timeStart << " seconds (" << (timeEnd - timeStart) / points * 1000 << " ms per point)\n";
        std::cout << "Maximum distance from a vertex: " << maxdist * 6371 << " km" << "\n";
        std::cout << "Average distance from a vertex: " << (totaldist / points)  * 6371 << " km" << "\n";
        delete icosphere;
    }
}




TEST (IcosphereTest, partialSphere) {
/*
    Icosphere_old* icosphere = new Icosphere_old (4);
    GeoQuad bounds = GeoQuad (Geolocation (0, 0, Degrees), Geolocation  (60, 60, Degrees));
    icosphere -> subdivide (1);
    time_t seed = time (NULL);
    std::default_random_engine e = std::default_random_engine (seed);
    std::uniform_real_distribution<double> random = std::uniform_real_distribution<double> (0.0, 1.0);
    double timeStart = clock() / static_cast<double> (CLOCKS_PER_SEC);
    double maxdist = 0.0, totaldist = 0.0;
    unsigned points;
    for (points = 0; points < 100; points++) {
        double lat = (random (e) - 0.5) * M_PI;
        double lon = (random (e) - 0.5) * M_PI * 2;
        Geolocation sought = Geolocation (lat, lon, Radians);
        Vertex* found = icosphere -> nearest (sought);
        double dist = icosphere -> distance (Math::toGeolocation (found -> getCartesian()), sought);
        maxdist = dist > maxdist ? dist : maxdist;
        totaldist += dist;
    }
    double timeEnd = clock() / static_cast<double> (CLOCKS_PER_SEC);

    EXPECT_LT (totaldist / points, maxdist * 2);
    EXPECT_LT (totaldist / points, 0.02);

    std::cout << "Found " << points <<  " points in " << timeEnd - timeStart << " seconds (" << (timeEnd - timeStart) / points * 1000 << " ms per point)\n";
    std::cout << "Maximum distance from a vertex: " << maxdist * 6371 << " km" << "\n";
    std::cout << "Average distance from a point: " << (totaldist / points) * 6371 << " km" << "\n";
    delete icosphere;
*/
 }

/*
TEST (IcosphereTest, mesh) {
    Icosphere_old icosphere = Icosphere_old (8);
    GeoQuad bounds = GeoQuad (Geolocation (30, 30, Geolocation::DEGS), Geolocation (35, 35, Geolocation::DEGS));
    std::vector<double> vertices;
    std::vector<unsigned> indices;
    icosphere.mesh (bounds, 7, vertices, indices);
}
*/
