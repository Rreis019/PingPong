#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include "Object.h"
#include "CGameObject.h"
class Ball : public CComponent
{
    public:
        Ball(){ }
        void onStart();
        void onUpdate();
        void onRender();
        void onTriggerEnter(CGameObject* other);
        int width = 20;
        int height = 100;
    private:
        Vec2 startVel = Vec2(3,3);
        Vec2 startPos = Vec2(0,0);

        Vec2 vel = Vec2(0,0);
        bool reset = false;
        int timereset = 0;
        #define RESET_TIME 2000
        int radius = 10;
};