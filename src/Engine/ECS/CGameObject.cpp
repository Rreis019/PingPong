#include "CGameObject.h"
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include "CScene.h"
#include "CComponentFactory.h"
#include "Serialization.h"

CGameObject::CGameObject(){}

CGameObject::CGameObject(char* name,Vec2 pos)
{
    this->name = name;
    this->pos = pos;
}

void CGameObject::onUpdate()
{
    for(auto& component : components)
    {
        component->onUpdate();
    }
}

void CGameObject::onRender()
{
    for(auto& component : components)
    {
        component->onRender();
    }
}

void CGameObject::onTriggerEnter(CGameObject* other)
{
    for (int i = 0; i < components.size(); i++)
    {
        if (components[i]->isactive)
        {
            components[i]->onTriggerEnter(other);
        }
    }
}


Vec2 CGameObject::getForward()
{
    return Vec2::forward(angle);
}

void CGameObject::move(Vec2 pos)
{ 
    this->pos += pos;
    for(int i = 0; i < children.size(); i++){children[i]->move(pos);}
}

void CGameObject::destroy()
{
    isAlive = false;
}


void CGameObject::addChild(CGameObject* child)
{
    children.push_back(child);
    child->parent = this;
}

void CGameObject::removeChild(CGameObject* child)
{
    children.erase(std::remove(children.begin(), children.end(), child), children.end());
}

CGameObject::~CGameObject()
{
    //printf("Destroying %s\n", name);
    components.clear();

    for(int i = 0; i < children.size(); i++){
        children[i]->destroy();
    }

    if(parent != nullptr){
        parent->removeChild(this);
    }

    parent = nullptr;
}


void CGameObject::serialise(FILE * fp)
{
    SAVE(fp, name);
    SAVE(fp,pos.x);
    SAVE(fp,pos.y);
    SAVE(fp,scale.x);
    SAVE(fp,scale.y);
    SAVE(fp,layer);
    SAVE(fp,tag);
    SAVE(fp,angle);

    int componentSize = components.size();
    SAVE(fp,componentSize);
    for(int i = 0; i < components.size(); i++)
    {
        std::string& compName = components[i]->name;
        SAVE(fp,compName);
        components[i]->serialise(fp);
    }



    if(saveFormat == ESF_TEXT){ fprintf(fp,"\n");}
}
void CGameObject::deserialise(FILE * fp)
{
    READ(fp,name);
    READ(fp,pos.x);
    READ(fp,pos.y);
    READ(fp,scale.x);
    READ(fp,scale.y);
    READ(fp,layer);
    READ(fp,tag);
    READ(fp,angle);

    int componentSize = 0;
    READ(fp,componentSize);

    std::string compName = "";
    for(int o = 0 ;o < componentSize; o++)
    {
        READ(fp,compName);
        CComponent* c = CComponentFactory::createComponent(this,(char*)compName.c_str());
        if(c == 0x0) continue;
        c->deserialise(fp);
        c->onStart();
    }

}

void CGameObject::print()
{
    printf("GameObject: %s\n", name.c_str());
    printf("Pos: %f, %f\n", pos.x, pos.y);
    printf("Scale: %f, %f\n", scale.x, scale.y);
    printf("Layer: %d\n", layer);
    printf("Tag: %d\n", tag);
    printf("Angle: %f\n", angle);
    printf("Components: %d\n", components.size());
    printf("\n");
}