#include "CComponent.h"
#include "Vec2.h"
class CCamera : public CComponent
{
    public:
        //Convert 2D coord to screen coords
        //CCamera set name to "Camera"
        void onStart(){ name = "CCamera"; }
        bool WorldToScreen(Vec2 pos,Vec2 size,Vec2& out);
        bool WorldToScreen(Vec2 pos,Vec2& out);
        void serialise(FILE* fp);
    private:

};