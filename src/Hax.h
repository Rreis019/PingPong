#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include "Object.h"
#include "CGameObject.h"

class Ball;
class Hax : public CComponent
{
    public:
        Hax(){ }
        void onStart();
        void onUpdate();
        //void onTriggerEnter(CGameObject* other);
    private:
        CGameObject* ballObj;

};