#include "CSingleton.h"
#include "CGameObject.h"
#include <vector>
#include <memory>
class CCamera;

typedef std::vector<std::unique_ptr<CGameObject>> EntityList;

class CEntityManager : public CSingleton<CEntityManager>
{
    public:
        CGameObject* addEntity(char* name,Vec2 pos);
        CGameObject* addEntity();

        void onUpdate();
        void onRender(){ for(auto &entity : entities){entity->onRender();} }
        void clear();

        void setCurrentCamera(CCamera* camera){CurrentCamera = camera;}
        CCamera* getCurrentCamera(){return CurrentCamera;}

        EntityList* getEntities(){return &entities;}
        CGameObject* getEntity(int index){return entities[index].get();}
        int getEntityCount(){return entities.size();}
    private:
        EntityList entities;
        CCamera* CurrentCamera = nullptr; //CCAMERA IS A COMPONENT must be attached to a gameobject
};