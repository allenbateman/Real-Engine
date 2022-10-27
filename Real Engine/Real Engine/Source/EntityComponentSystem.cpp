#include "EntityComponentSystem.h"
#include "Transform.h"
#include "Material.h"
#include "Mesh.h"
#include "Camera.h"
#include "Application.h"

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

bool EntityComponentSystem::Awake()
{



	//register all components
	RegisterComponent<Transform>();
	RegisterComponent<Mesh>();
	RegisterComponent<Material>();

	auto ent = CreateEntity();
	AddComponent(ent, Transform{});
	AddComponent(ent, Mesh());
	AddComponent(ent, Material());

	std::cout << entityManager.get()->GetSignature(ent)<<endl;
	
	auto& t = GetComponent<Transform>(ent);
	std::cout << typeid(t).name() << " Px: " << t.position.x << " Py: " << t.position.y << " Pz: " << t.position.z << endl;

	t.position.x = 10;
	t.position.y = 10;
	t.position.z = 10;

	auto& t2 = GetComponent<Transform>(ent);
	std::cout << typeid(t2).name() << " Px: " << t2.position.x << " Py: " << t2.position.y << " Pz: " << t2.position.z << endl;


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
