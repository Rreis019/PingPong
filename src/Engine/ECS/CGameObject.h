#pragma once
#include <cstdint>
#include "Vec2.h"
#include "CComponent.h"
#include <vector>
#include "Object.h"

#include <algorithm>
#include <array>
#include <bitset>
#include <memory>
#include <string>

typedef int ComponentID;

inline ComponentID getUniqueComponentID() noexcept
{
	static ComponentID lastID{0u};
	return lastID++;
}

template <typename T>
inline ComponentID getComponentTypeID() noexcept
{
	// We an use a `static_assert` to make sure this function
	// is only called with types that inherit from `Component`.
	static_assert(std::is_base_of<CComponent, T>::value,
		"T must inherit from Component");

	static ComponentID typeID{getUniqueComponentID()};
	return typeID;
}

// Let's define a maximum number of components:
constexpr std::size_t maxComponents{32};

// Let's typedef an `std::bitset` for our components:
typedef std::bitset<maxComponents> ComponentBitset;

// And let's also typedef an `std::array` for them:
typedef std::array<CComponent*, maxComponents> ComponentArray;

class CGameObject : Object
{
public:
	std::string name = "CGameObject";
	Vec2 scale = Vec2(1, 1);
	int layer = 0;
	int tag = 0;
	float angle = 0;
	bool isAlive = true;
	
	//GENERIC FUNCTIONS----------------------------------------------------------------------------------------------------------------------
	void onUpdate();
	void onRender();
	void onTriggerEnter(CGameObject* other);
	void destroy();

	//CONSTRUCTORS----------------------------------------------------------------------------------------------------
	CGameObject();
	CGameObject(char* name, Vec2 pos);
	~CGameObject();

	//COMPONENTS-------------------------------------------------------------------------------------------------------
	template <typename T> hasComponent()
	{
		return componentBitset[getComponentTypeID<T>()];
	}

	template <typename T, typename... TArgs>
	T&addComponent(TArgs&&... mArgs)
	{
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->owner = this;
		std::unique_ptr < CComponent > uPtr{ c };
		components.emplace_back(std::move(uPtr));
		componentArray[getComponentTypeID<T>()] = c;
		componentBitset[getComponentTypeID<T>()] = true;
		c->onStart();
		return *c;
	}


	template <typename T> T* getComponent()
	{
		//if has component
		if(!hasComponent<T>()){return nullptr;}
		auto ptr(componentArray[getComponentTypeID<T>()]);
		return static_cast<T*>(ptr);
	}

	CComponent* getComponent(int index){return components[index].get();}
	int getComponentCount(){return components.size();}

	//remove component
	template <typename T> void removeComponent()
	{
		componentBitset[getComponentTypeID<T>()] = false;
		delete componentArray[getComponentTypeID<T>()];
		componentArray[getComponentTypeID<T>()] = nullptr;
	}
	


	//CHILD-------------------------------------------------------------------------------------------------------------
	void addChild(CGameObject* child);
	void removeChild(CGameObject* child);

	//GETTERS------------------------------------------------------------------------------------------------------------
	void move(Vec2 pos);
	void setPos(Vec2 pos) { this->pos = pos; }
	Vec2 getPos() { return pos; }
	Vec2 getForward();

	//SERIALIZE-----------------------------------------------------------------------------------------------------------
	void serialise(FILE * fp);
	void deserialise(FILE * fp);
	void print();

private:
	Vec2 pos = Vec2(0, 0);
	CGameObject* parent = nullptr;
	std::vector<CGameObject*> children;
	std::vector<std::unique_ptr<CComponent>> components;
	ComponentArray componentArray;
	ComponentBitset componentBitset;
};



