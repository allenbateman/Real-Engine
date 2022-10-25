#pragma once
#include "Module.h"
#include "EntityManager.h"
#include "ComponentManager.h"
#include "SystemManager.h"
class EntityComponentSystem : public Module
{
public :
	EntityComponentSystem(bool active);
	~EntityComponentSystem();

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
	T& GetComponent(Entity entity);
	template<typename T>
	T& GetComponentType(Entity entity);

	
	//System methods
	template<typename T>
	std::shared_ptr<T> RegisterSystem();
	template<typename T>
	void SetSystemSignature(Signature signature);
	
	//Event methods

private:
	std::unique_ptr<ComponentManager> componentManager;
	std::unique_ptr<EntityManager> entityManager;
	std::unique_ptr<SystemManager> systemManager;
};
