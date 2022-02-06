#include "CComponent.h"
#include "Vec2.h"

class CCarMovement : public CComponent
{
    public:
        int dir = 0;
        float currentVel = 0.0;
        float maxVel = 5.0f;
        
        float speed = 0.3f;

        float friction = 0.1f;

        float angleSpeed = 5.0f;
        void onStart();
        void onUpdate();
        void onRender(){};
        void onTriggerEnter(CGameObject* other);
        void serialise(FILE* fp);


    private:

};