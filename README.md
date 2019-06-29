# icosphere

This is a fast(ish) way to subdivide the icosahedron to obtain a sphere approximation in C++. It's based on Andreas Kahler's implementation in C# (http://blog.andreaskahler.com/2009/06/creating-icosphere-mesh-in-code.html) with the following adaptations:

   - it does not generate a mesh, but a walkable grid which we can use for performing computations in spherical geometry, such as fictional planet generation. We can quickly find a data value for the nearest point on the grid to given geographical (i.e. spherical) coordinates.
   
   - it does not therefore keep the triangles as they are generated, but instead saves the vertices and the edges connecting them, throwing the triangles away. We therefore generate the grid progressively not by iterating over the triangles generated in the previous pass, but by recursively subdividing the new triangle until the desired level of detail is reached. (We do still have up to 5% of the total number of triangles in memory at a time because each top-level triangle can't be deleted until all of its children, grandchildren and so on down to the lowest level of detail have been generated).
   
   - since Andreas wrote his blog post, newer and faster hashmap implementations have become available. I am using this by Martin Ankerl: https://github.com/martinus. With this implementation, there is no slowdown from having all the edges in the edgemap instead of truncating it after each layer, which enables the recurive approach.
   
On my machine this now generates about 2.5 million vertices in 5 seconds, or 10 million in 20 seconds, but runs out of stack space if further subdivision is attempted (the layered version along the lines of Andreas' solution also breaks at that level, failing to allocate space for the next layer). This is with 16 MB RAM on an i7 processor running Ubuntu 19.04.   
