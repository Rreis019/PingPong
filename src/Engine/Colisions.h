#include "Vec2.h"

class Colisions
{
    public:
        static bool intersectPolygons(Vec2* verticesA, Vec2* verticesB, int vertACount, int vertBCount); //SAT algorithm
        static bool intersectPolygons(Vec2* verticesA, Vec2* verticesB, int vertACount, int vertBCount,Vec2& resolution); //SAT algorithm
    
        static bool intersectRectvsPoint(Vec2& rectPos, Vec2& rectSize, Vec2& point);
    private:
        static void projectVertices(Vec2* vertices,Vec2 axis, float* min, float* max,int VertCounts);

};