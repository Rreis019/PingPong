#include "CCamera.h"
#include "CGameObject.h"
#include  "CWindow.h"
#include "CScene.h"
#include "CComponentFactory.h"

/*
CComponent* createCamera(CGameObject* gameObject)
{
    return (CComponent*)&gameObject->addComponent<CCamera>();
}

static bool registerCamera =  m_componentMap.insert(std::make_pair("CCamera", createCamera)).second;
*/

REGISTER_COMPONENT(CCamera)

bool CCamera::WorldToScreen(Vec2 pos,Vec2 size,Vec2& out)
{
    Vec2 screenPos = pos -  owner->getPos();
    if(screenPos.x  + size.x < 0 || screenPos.x > CWindow::Get().width || screenPos.y + size.y < 0 || screenPos.y > CWindow::Get().height)
        return false;
    out = screenPos;
    return true;
}

bool CCamera::WorldToScreen(Vec2 pos,Vec2& out)
{
    Vec2 screenPos = pos -  owner->getPos();
    if(screenPos.x  < 0 || screenPos.x > CWindow::Get().width || screenPos.y < 0 || screenPos.y > CWindow::Get().height)
        return false;
    out = screenPos;
    return true;
}


void CCamera::serialise(FILE* fp)
{

}
