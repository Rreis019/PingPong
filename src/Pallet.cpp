#include "Pallet.h"
#include "CWindow.h"
#include "CInput.h"
void Pallet::onUpdate()
{
    int dir = 0;
    if(CInput::isKeyDown(UPKEY)){dir = -1;}
    else if(CInput::isKeyDown(DOWNKEY)){ dir = 1;}
    Vec2 moveVec = Vec2(0,dir*speed);
    this->owner->move(moveVec);

    //Is out of bounds?
    Vec2 ownerpos = this->owner->getPos();
    CWindow& window = CWindow::Get();
    if(ownerpos.y < 0){ this->owner->setPos(Vec2(ownerpos.x,0));}
    if(ownerpos.x < 0) { this->owner->setPos(Vec2(0,ownerpos.y));}
    if(ownerpos.y > window.height - this->height)  {this->owner->setPos(Vec2(ownerpos.x,window.height - this->height));}
    if(ownerpos.x > window.width - this->width) {this->owner->setPos(Vec2(window.width - this->width,ownerpos.y));}

}

void Pallet::onRender()
{
   CGraphics* g = CWindow::Get().getGraphics();

   g->DrawRect(this->owner->getPos().x, this->owner->getPos().y,width,height,1,{255,255,255,255});
}