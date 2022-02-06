#pragma once
#include "CComponent.h"
#include "CGameObject.h"
#include "Vec2.h"
#include "RGBA.h"


class CSprite;

#define DRAW_COLLIDER 0
class CColider : public CComponent
{
    public:
        CColider(Vec2 pos, Vec2 size);
        CColider(){this->name = "CColider";}
        CColider(int priority){this->name = "CColider";this->priority = priority;}
        void onStart();
        void onUpdate();
        void onRender();
        
        bool isColliding(CColider* other);
        Vec2 size = Vec2(0,0);
        void setPriority(int priority){this->priority = priority;}
        void serialise(FILE* fp);
        void deserialise(FILE* fp);
    private:
        void getVertices(Vec2* vertices);
        //pos is relative position to the parent
        //absolute position = parent position + relative position
        Vec2 pos = Vec2(0,0);

        RGBA color = {255,0,0,255};
        RGBA colorVert = {0,255,0,255};
        
        //prio
        int priority = 0;
};