#include "CComponent.h"

class CWASD : public CComponent
{
    float speed = 2.0f;

    public:
        CWASD(){};
        void onStart(){};
        void onUpdate();
        void onRender(){};
        void serialise(FILE * fp){};

    private:


};
