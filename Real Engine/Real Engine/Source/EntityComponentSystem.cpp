#include "EntityComponentSystem.h"
#include "Transform.h"
#include "Material.h"
#include "Mesh.h"
#include "Camera.h"

EntityComponentSystem::EntityComponentSystem(bool active) : Module(active)
{
	name.Create("Entity component system");
	
}

EntityComponentSystem::~EntityComponentSystem()
{
}

bool EntityComponentSystem::Awake()
{
	
	//init core
	componentManager = std::make_unique<ComponentManager>();
	entityManager = std::make_unique<EntityManager>();
	systemManager = std::make_unique<SystemManager>();

	//register all components
	RegisterComponent<Transform>();

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
	return entityManager->CreateEntity();
}

void EntityComponentSystem::DestroyEntity(Entity entity)
{
	entityManager->DestroyEntity(entity);
	componentManager->EntityDestroyed(entity);
	systemManager->EntityDestroyed(entity);
}
