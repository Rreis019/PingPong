#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include "Object.h"
#include "CGameObject.h"
class Pallet : public CComponent
{
    public:
        Pallet(int UPKEY,int DOWNKEY){this->UPKEY = UPKEY; this->DOWNKEY = DOWNKEY;};
        virtual void onStart(){};
        virtual void onUpdate();
        virtual void onRender();
        virtual void onTriggerEnter(CGameObject* other){};
        int width = 20;
        int height = 100;
    private:
        int UPKEY = 0;
        int DOWNKEY = 0;
        int speed = 5;
};