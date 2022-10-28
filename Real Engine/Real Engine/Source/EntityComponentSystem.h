#pragma once
#include "EntityManager.h"
#include "ComponentManager.h"
#include "SystemManager.h"
#include <unordered_map>
class EntityComponentSystem {
public :

	EntityComponentSystem();
	~EntityComponentSystem();

	void Init();
	void SetSignatures();
	// Entity methods
	Entity CreateEntity();
	void DestroyEntity(Entity entity);
	Signature GetEntitySignature(Entity entity);
	std::uint32_t GetEntities();

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
	template<typename T>
	std::uint8_t GetComponentType();

	//System methods
	template<typename T>
	std::shared_ptr<T> RegisterSystem();
	template<typename T>
	void SetSystemSignature(Signature signature);


	template<typename T>
	bool HasComponent(Entity entity);
private:
	std::unique_ptr<ComponentManager> componentManager;
	std::unique_ptr<EntityManager> entityManager;
	std::unique_ptr<SystemManager> systemManager;
};

template<typename T>
inline void EntityComponentSystem::RegisterComponent()
{
	componentManager->RegisterComponent<T>();
}

template<typename T>
inline void EntityComponentSystem::AddComponent(Entity entity, T component)
{
	componentManager->AddComponent(entity, component);
	auto signature = entityManager->GetSignature(entity);
	signature.set(componentManager->GetComponentType<T>(), true);
	entityManager->SetSignature(entity, signature);
	systemManager->EntitySignatureChanged(entity, signature);
}

template<typename T>
inline void EntityComponentSystem::RemoveComponent(Entity entity)
{
	componentManager->RemoveComponent<T>(entity);
	auto signature = entityManager->GetSignature(entity);
	signature.set(componentManager->GetComponentType<T>(), false);
	entityManager->SetSignature(entity, signature);

	systemManager->EntitySignatureChanged(entity, signature);
}

template<typename T>
inline T& EntityComponentSystem::GetComponent(Entity entity)
{
	return componentManager->GetComponent<T>(entity);
}

template<typename T>
inline T& EntityComponentSystem::GetComponentType(Entity entity)
{
	return componentManager->GetComponentType<T>(entity);
}

template<typename T>
inline std::uint8_t EntityComponentSystem::GetComponentType()
{
	return componentManager->GetComponentType<T>();
}

template<typename T>
inline std::shared_ptr<T> EntityComponentSystem::RegisterSystem()
{
	return systemManager->RegisterSystem<T>();
}

template<typename T>
inline void EntityComponentSystem::SetSystemSignature(Signature signature)
{
	systemManager->SetSignature<T>(signature);
}

template<typename T>
inline bool EntityComponentSystem::HasComponent(Entity entity)
{
	return componentManager->EntityHasComponent<T>(entity);
}

