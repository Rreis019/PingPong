#include "CScene.h"
#include  "CEntityManager.h"
#include  "CGameObject.h"
#include "Serialization.h"


void CScene::loadScene(char* fileName)
{
    FILE* fp = fopen(fileName,"r");
    auto& manager = CEntityManager::Get();

    int EntityCount = 0;
    READ(fp, EntityCount);
    for (int i = 0; i < EntityCount; i++)
    {
        CGameObject* gameObject = manager.addEntity();
        gameObject->deserialise(fp);
        gameObject->print();
    }
    
  
    fclose(fp);
}

void CScene::saveScene(char* fileName)
{
    FILE* fp = fopen(fileName, "w");
    auto& manager = CEntityManager::Get();

    int EntSize = manager.getEntityCount();
    SAVE(fp,EntSize);
    for(int i = 0 ; i < EntSize;i++)
    {
        CGameObject* GameObject = manager.getEntity(i);
        GameObject->serialise(fp);
    }
    

    fclose(fp);
}
