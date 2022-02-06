#include "Hax.h"
#include "CInput.h"
#include "CEntityManager.h"
#include "Pallet.h"
#include "Ball.h"


void Hax::onStart()
{
      for(int i = 0 ; i < CEntityManager::Get().getEntityCount();i++)
        {
            CGameObject* obj = CEntityManager::Get().getEntity(i);
            if(obj->hasComponent<Ball>())
            {
                ballObj = obj;
                break;
            }
        }
}

void Hax::onUpdate()
{
    if(CInput::isLeftButtonDown())
    {
        Vec2 mousePos = CInput::getMousePos();

        for(int i = 0 ; i < CEntityManager::Get().getEntityCount();i++)
        {
            CGameObject* obj = CEntityManager::Get().getEntity(i);
            if(obj->hasComponent<Pallet>())
            {
                auto p = obj->getComponent<Pallet>();
                auto objPos = obj->getPos();
                int padding = 16;
                if(mousePos.x > objPos.x - padding && mousePos.x < objPos.x + p->width + padding*2)
                {
                    if(mousePos.y > objPos.y - padding && mousePos.y < objPos.y + p->height + padding*2)
                    {
                        obj->setPos(Vec2(mousePos.x - p->width/2,mousePos.y - p->height/2));
                    }
                }
            }
        }
    }

    if(CInput::RightMouseClicked())
    {
        ballObj->setPos(CInput::getMousePos());
    }

}