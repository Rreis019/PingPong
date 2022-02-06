#include "Colisions.h"
#include <algorithm>
#include <iostream>
#include <limits>
#include <stdlib.h>
#include <stdio.h>
//https://www.youtube.com/watch?v=Zgf1DYrmSnk&list=PLSlpr6o9vURwq3oxVZSimY8iC-cdd3kIs&index=6

bool Colisions::intersectPolygons(Vec2* verticesA, Vec2* verticesB, int vertACount, int vertBCount)
{
    for(int i = 0 ; i < vertACount;i++)
    {
        Vec2 current  = verticesA[i];
        Vec2 next = verticesA[(i+1)%vertACount];  // % vertcount  to not go out of bounds

        Vec2 edge = next - current;
        Vec2 axis = Vec2(-edge.y, edge.x);

        axis.normalize();

        float minA = 0, maxA = 0;
        float minB = 0, maxB = 0;
   
        Colisions::projectVertices(verticesA,axis,&minA,&maxA,vertACount);
        Colisions::projectVertices(verticesB,axis,&minB,&maxB,vertBCount);

        if(minA >= maxB || minB >= maxA)
            return false; //Find a gap between the two polygons so they are not intersecting
    	
    }

    for(int o = 0;o < vertBCount;o++)
    {
        Vec2 current  = verticesB[o];
        Vec2 next = verticesB[(o+1)%vertBCount];  // % vertcount  to not go out of bounds
        Vec2 edge = next - current;
        Vec2 axis = Vec2(-edge.y, edge.x);

        axis.normalize();

        float minA = 0, maxA = 0;
        float minB = 0, maxB = 0;
   
        Colisions::projectVertices(verticesA,axis,&minA,&maxA,vertACount);
        Colisions::projectVertices(verticesB,axis,&minB,&maxB,vertBCount);

        if(minA >= maxB || minB >= maxA)
            return false; //Find a gap between the two polygons so they are not intersecting
    	
    }

    return true;
}

bool Colisions::intersectPolygons(Vec2* verticesA, Vec2* verticesB, int vertACount, int vertBCount,Vec2& resolution)
{
    resolution = Vec2(0,0);
    float depth = 99999999999999999;
    for(int i = 0 ; i < vertACount;i++)
    {
        Vec2 current  = verticesA[i];
        Vec2 next = verticesA[(i+1)%vertACount];  // % vertcount  to not go out of bounds

        Vec2 edge = next - current;
        Vec2 axis = Vec2(-edge.y, edge.x);

        axis.normalize();

        float minA = 0, maxA = 0;
        float minB = 0, maxB = 0;
   
        Colisions::projectVertices(verticesA,axis,&minA,&maxA,vertACount);
        Colisions::projectVertices(verticesB,axis,&minB,&maxB,vertBCount);

        if(minA >= maxB || minB >= maxA)
            return false; //Find a gap between the two polygons so they are not intersecting

        depth = std::min
        (
            std::min(maxA,maxB) - std::max(minA,minB),
            depth
        );
    }

    for(int o = 0;o < vertBCount;o++)
    {
        Vec2 current  = verticesB[o];
        Vec2 next = verticesB[(o+1)%vertBCount];  // % vertcount  to not go out of bounds
        Vec2 edge = next - current;
        Vec2 axis = Vec2(-edge.y, edge.x);

        axis.normalize();

        float minA = 0, maxA = 0;
        float minB = 0, maxB = 0;
   
        Colisions::projectVertices(verticesA,axis,&minA,&maxA,vertACount);
        Colisions::projectVertices(verticesB,axis,&minB,&maxB,vertBCount);

        if(minA >= maxB || minB >= maxA)
            return false; //Find a gap between the two polygons so they are not intersecting
    	
        depth = std::min(
            std::min(maxA,maxB) - std::max(minA,minB),
            depth
            );

    }

    Vec2 delta =  verticesA[0] - verticesB[0];
    float hyp = delta.lenght();
    resolution.x = (depth  * delta.x) / hyp;
    resolution.y = (depth  * delta.y) / hyp;

    return true;
} 

void Colisions::projectVertices(Vec2* vertices,Vec2 axis, float* min, float* max,int VertCounts)
{
    *min = std::numeric_limits<float>::max();
    *max = std::numeric_limits<float>::min();

    for(int i = 0; i < VertCounts; i++)
    {
        float projected = vertices[i].dot(axis);
        if(projected < *min)
            *min = projected;
        if(projected > *max)
            *max = projected;
    }
}

bool Colisions::intersectRectvsPoint(Vec2& rectPos, Vec2& rectSize, Vec2& point)
{
    if(point.x > rectPos.x && point.x < rectPos.x + rectSize.x)
    {
        if(point.y > rectPos.y && point.y < rectPos.y + rectSize.y)
            return true;
    }
    return false;
}