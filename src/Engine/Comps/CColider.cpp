#include "CColider.h"
#include "CWindow.h"
#include "CSprite.h"
#include "CCamera.h"
#include "CEntityManager.h"
#include "Colisions.h"
#include "CScene.h"
#include "CComponentFactory.h"
#include "serialization.h"
REGISTER_COMPONENT(CColider);

CColider::CColider(Vec2 pos, Vec2 size)
{
    this->name = "CColider";
    this->pos = pos;
    this->size = size;
}

void CColider::onStart()
{
    CSprite* spr = owner->getComponent<CSprite>();
    if(spr != nullptr)
        this->size = Vec2(spr->witdh, spr->height);
}

void CColider::onUpdate()
{
    EntityList* entlist = CEntityManager::Get().getEntities();
    //print ent size
    //printf("entlist size: %d\n", entlist->size());
    for(int i = 0 ; i < entlist->size() ; i++)
    {
        CGameObject* ent = (*entlist)[i].get();
        if(ent == owner) {continue;}
        CColider* col =  ent->getComponent<CColider>();

        if(col == nullptr) {continue;}
        if(isColliding(col))
        {
            this->color = {255,0,0,255};
            return;
        }
        else{
            this->color = {0,255,0,255};
        }
    }
}

void CColider::onRender()
{
    #if DRAW_COLLIDER == 0
        return;
    #endif

    
    CCamera* cam = CEntityManager::Get().getCurrentCamera();
	Vec2 Rectsize = Vec2(size.x*owner->scale.x, size.y*owner->scale.y);
    Vec2 pos = Vec2(pos.x + owner->getPos().x, pos.y + owner->getPos().y);
	Vec2 out = this->pos + owner->getPos(); 

    if(cam != nullptr)
    {
        if(!cam->WorldToScreen(pos,Rectsize, out))
            return;
    }

    CWindow::Get().getGraphics()->DrawRotatedRect
    (
        (int)out.x,
        (int)out.y,
        (int)Rectsize.x,
        (int)Rectsize.y,
        owner->angle,
        color
    );

    Vec2 vertices[4] = {Vec2(0,0), Vec2(0,0), Vec2(0,0), Vec2(0,0)};
    Vec2 verticeOut[4];
    getVertices(vertices);
    for(int i = 0 ; i < 4;i++){verticeOut[i] = vertices[i];}


    if(cam != nullptr)
    {
        for(int i = 0; i < 4; i++){cam->WorldToScreen(vertices[i],verticeOut[i]);}
    }
  
    CWindow::Get().getGraphics()->DrawVertices
    (
        verticeOut,
        4,
        colorVert
    );
    
    //CWindow::Get().getGraphics()->DrawRect(pos.x + owner->pos.x, pos.y + owner->pos.y, size.x, size.y,1,255,0,0,255);
}


void CColider::getVertices(Vec2* vertices)
{
    Vec2 Rectsize = Vec2(size.x*owner->scale.x, size.y*owner->scale.y);

    vertices[0] = Vec2 //Left top
    (
        pos.x + owner->getPos().x,
        pos.y + owner->getPos().y
    );
    
    vertices[1] = Vec2
    (
        pos.x + owner->getPos().x + Rectsize.x,
        pos.y + owner->getPos().y
    ); //Right Top 
        
    vertices[2] = Vec2(
        pos.x + owner->getPos().x + Rectsize.x,
        pos.y + owner->getPos().y + Rectsize.y
    ); //Right Bottom
    vertices[3] = Vec2(
        pos.x + owner->getPos().x,
        pos.y + owner->getPos().y + Rectsize.y
    ); //Left Bottom
    
    Vec2 center = Vec2(
        (pos.x + owner->getPos().x) + Rectsize.x/2,
        (pos.y + owner->getPos().y) + Rectsize.y/2
    );
    for(int i = 0;i < 4;i++){vertices[i] = Vec2::rotate(center,vertices[i],owner->angle);}
}

bool CColider::isColliding(CColider* other)
{
    Vec2 vertices[4] = {Vec2(0,0), Vec2(0,0), Vec2(0,0), Vec2(0,0)};
    Vec2 otherVertices[4] = {Vec2(0,0), Vec2(0,0), Vec2(0,0), Vec2(0,0)};
    getVertices(vertices);
    other->getVertices(otherVertices);
    Vec2 resolution;
    bool overlap = Colisions::intersectPolygons(vertices,otherVertices, 4, 4,resolution);
    if(overlap)
    {
        if(priority > other->priority)
        {
            other->owner->move(resolution * 1);
        }
        else{
            owner->move(resolution);
        }
         owner->onTriggerEnter(other->owner);
         other->owner->onTriggerEnter(owner);
    }

  
    

    return overlap;
}


void CColider::serialise(FILE* fp)
{
    SAVE(fp,pos.y);
    SAVE(fp,pos.x);
    SAVE(fp,size.x);
    SAVE(fp,size.y);
    SAVE(fp,priority);
}

void CColider::deserialise(FILE* fp)
{

    SAVE(fp,pos.x);
    SAVE(fp,pos.y);
    SAVE(fp,size.x);
    SAVE(fp,size.y);
    SAVE(fp,priority);
}
