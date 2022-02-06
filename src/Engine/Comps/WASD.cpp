#include "WASD.h"
#include "CInput.h"
#include "CGameObject.h"
#include <stdio.h>
#include "CComponentFactory.h"
REGISTER_COMPONENT(CWASD);

void CWASD::onUpdate()
{
    if(CInput::Get().isKeyDown(SDL_SCANCODE_W))
    {
        owner->move(Vec2(0, -speed));
    }
    if(CInput::Get().isKeyDown(SDL_SCANCODE_S))
    {
        owner->move(Vec2(0, speed));
    }
    if(CInput::Get().isKeyDown(SDL_SCANCODE_A))
    {
        owner->move(Vec2(-speed, 0));
    }
    if(CInput::Get().isKeyDown(SDL_SCANCODE_D))
    {
        owner->move(Vec2(speed, 0));
    }

}