#pragma once
#include "Module.h"
#include "EntityManager.h"
#include "ComponentManager.h"
#include "SystemManager.h"
class EntityComponentSystem : Module
{
public :
	bool Awake();
	bool Start();
	bool PreUpdate();
	bool Update();
	bool PostUpdate();
	bool CleanUp();
	Entity CreateEntity();
	void DestroyEntity(Entity entity);


	// Component methods
	template<typename T>
	void RegisterComponent();
	template<typename T>
	void AddComponent(Entity entity, T component);
	template<typename T>
	void RemoveComponent(Entity entity);
	template<typename T>
	ComponentType GetComponentType();
	
	//System methods
	template<typename T>
	std::shared_ptr<T> RegisterSystem();
	template<typename T>
	void SetSystemSignature(Signature signature);
	
	//Event methods


};

