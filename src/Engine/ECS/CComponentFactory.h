#include <map>
#include "CComponent.h"
#include "CSingleton.h"
#include "CGameObject.h"


typedef CComponent* tp_newComponent (CGameObject* gameObject);
inline std::map<std::string, tp_newComponent*> m_componentMap;


class CComponentFactory
{
    public:
        static CComponent* createComponent(CGameObject* gameObject, const char* name)
        {
            if(m_componentMap.find(name) != m_componentMap.end())
            {
                return m_componentMap[name](gameObject);
            }
            return NULL;
        }

        static void printRegisteredComponents()
        {
            for (auto it = m_componentMap.begin(); it != m_componentMap.end(); ++it)
            {
                printf("%s\n", it->first.c_str());
            }
        }
};


#define REGISTER_COMPONENT(name) \
CComponent* create##name(CGameObject* gameObject) \
{ \
    return (CComponent*)&gameObject->addComponent<name>(); \
} \
static bool registered##name =  m_componentMap.insert(std::make_pair(#name, create##name)).second;