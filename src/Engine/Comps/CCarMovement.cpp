#include "CCarMovement.h"
#include "CGameObject.h"
#include "CInput.h"
#include <stdio.h>
#include "CScene.h"
#include "CComponentFactory.h"
REGISTER_COMPONENT(CCarMovement);

void CCarMovement::onStart()
{
    this->name = "CCarMovement";
}


void CCarMovement::onUpdate()
{
    Vec2 forward = owner->getForward();

    
    bool move = false;
    if(CInput::Get().isKeyDown(SDL_SCANCODE_W))
    {
        dir = 1;
        currentVel += speed;
        move = true;
    }
    if(CInput::Get().isKeyDown(SDL_SCANCODE_S))
    {
        dir = -1;
        currentVel += speed;
        move = true;
    }
     
      if(CInput::Get().isKeyDown(SDL_SCANCODE_A))
        {
            owner->angle -= angleSpeed;
        }
        if(CInput::Get().isKeyDown(SDL_SCANCODE_D))
        {
            owner->angle += angleSpeed;
        }
    
    if(currentVel > maxVel)
        currentVel = maxVel;

     if(currentVel < 0)
        currentVel = 0;

    owner->move((forward * dir) * currentVel);
    currentVel -= friction;
    //printf("cvel:%f\n",currentVel);
    //printf("Velx: %f Vely: %f\n",velocity.x,velocity.y);
}

 void CCarMovement::onTriggerEnter(CGameObject* other)
 {
     currentVel = 0;
     //owner->destroy();
 }



void CCarMovement::serialise(FILE* fp)
{

}


