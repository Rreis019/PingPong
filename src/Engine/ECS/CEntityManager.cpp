#include "CEntityManager.h"
#include <algorithm>

CGameObject* CEntityManager::addEntity(char* name,Vec2 pos)
{
    CGameObject* e = new CGameObject(name,pos);
    std::unique_ptr<CGameObject> uPtr{e};
    entities.emplace_back(std::move(uPtr));
    return e;
}

CGameObject* CEntityManager::addEntity()
{
    CGameObject* e = new CGameObject();
    std::unique_ptr<CGameObject> uPtr{e};
    entities.emplace_back(std::move(uPtr));
    return e;
}


void CEntityManager::onUpdate()
{
    //if the entity is not alive, remove it from the list
    entities.erase(
        std::remove_if(
            entities.begin(), entities.end(), [](const std::unique_ptr<CGameObject>& entity) {
        return !entity->isAlive;
    }), entities.end());

    //sort the entities by their layer lowest to highest  and  only sort if the layer is different
    std::sort(entities.begin(), entities.end(), [](const std::unique_ptr<CGameObject>& a, const std::unique_ptr<CGameObject>& b) {
        return a->layer < b->layer;
    });
 

    //loop through all entities and call their onUpdate()
    for (auto& entity : entities)
    {
        entity->onUpdate();
    }
}

void CEntityManager::clear()
{
    entities.clear();
}