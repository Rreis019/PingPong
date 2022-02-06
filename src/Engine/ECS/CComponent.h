#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include "Object.h"
class CGameObject;
class CComponent : public Object
{
    public:
        //GameObject that owns this component
        CGameObject* owner;

        //name of the component
        std::string name = "CComponent";

        //Active state of the component
        bool isactive = true;

        virtual void onStart(){};
        virtual void onUpdate(){};
        virtual void onRender(){};
        virtual void onTriggerEnter(CGameObject* other){};
        virtual ~CComponent(){};
    private:

};