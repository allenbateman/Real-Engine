#include "EntityComponentSystem.h"

EntityComponentSystem::EntityComponentSystem(bool active) : Module(active)
{
}

EntityComponentSystem::~EntityComponentSystem()
{
}

bool EntityComponentSystem::Awake()
{
	return true;
}

bool EntityComponentSystem::Start()
{
	return true;
}

bool EntityComponentSystem::PreUpdate()
{
	return true;
}

bool EntityComponentSystem::Update()
{
	return true;
}

bool EntityComponentSystem::PostUpdate()
{
	return true;
}

bool EntityComponentSystem::CleanUp()
{
	return true;
}

Entity EntityComponentSystem::CreateEntity()
{
	return Entity();
}

void EntityComponentSystem::DestroyEntity(Entity entity)
{
}


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
inline std::shared_ptr<T> EntityComponentSystem::RegisterSystem()
{
	return systemManager->RegisterSystem<T>();
}

template<typename T>
inline void EntityComponentSystem::SetSystemSignature(Signature signature)
{
	systemManager->SetSignature<T>(signature);
}

