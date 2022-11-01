#include "EntityComponentSystem.h"
#include "Application.h"
#include "Transform.h"
#include "Material.h"
#include "Mesh.h"
#include "Camera.h"
#include "Tag.h"


EntityComponentSystem::EntityComponentSystem()
{
	//init core
	componentManager = std::make_unique<ComponentManager>();
	entityManager = std::make_unique<EntityManager>();
	systemManager = std::make_unique<SystemManager>();
}

EntityComponentSystem::~EntityComponentSystem()
{
}

void EntityComponentSystem::Init()
{
	//register all components
	RegisterComponent<TagComponent>();
	RegisterComponent<Transform>();
	RegisterComponent<Mesh>();
	RegisterComponent<Material>();
	RegisterComponent<Camera>();

}

void EntityComponentSystem::SetSignatures()
{
	
}

Entity EntityComponentSystem::CreateEntity()
{
	return entityManager->CreateEntity();
}

void EntityComponentSystem::DestroyEntity(Entity entity)
{
	entityManager->DestroyEntity(entity);
	componentManager->EntityDestroyed(entity);
	systemManager->EntityDestroyed(entity);
}

Signature EntityComponentSystem::GetEntitySignature(Entity entity)
{
	return entityManager->GetSignature(entity);
}

std::uint32_t EntityComponentSystem::GetEntities()
{
	return entityManager->GetEntities();
}
