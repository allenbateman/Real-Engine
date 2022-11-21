#include "EntityManager.h"

EntityManager::EntityManager()
{
	std::cout << "Starting Entity Manager\n";

	for (Entity entity = 0; entity < MAX_ENTITIES; entity++)
	{
		availableEntities.push(entity);
	}
}

Entity EntityManager::CreateEntity()
{
	assert(livingEntityCount < MAX_ENTITIES && "Too many entities in existence.");
	//get first available entity
	Entity id = availableEntities.front();
	//remove first entity
	availableEntities.pop();
	livingEntityCount++;

	return id;
}

void EntityManager::DestroyEntity(Entity entity)
{
	assert(entity < MAX_ENTITIES && "Entity out of range.");
	signatures[entity].reset();
	availableEntities.push(entity);
	livingEntityCount--;
}

void EntityManager::SetSignature(Entity entity, Signature signature)
{
	assert(entity < MAX_ENTITIES && "Entity out of range.");
	// Put this entity's signature into the array
	signatures[entity] = signature;
}

Signature EntityManager::GetSignature(Entity entity)
{
	assert(entity < MAX_ENTITIES && "Entity out of range.");
	// Get this entity's signature from the array
	return signatures[entity];
}
