#pragma once
#include "Component.h"
#include "Entity.h"
#include <queue>
#include <array>
#include <assert.h>

class EntityManager
{
public:
	EntityManager();
	Entity CreateEntity();
	void DestroyEntity(Entity entity);
	void SetSignature(Entity entity, Signature signature);
	Signature GetSignature(Entity entity);
	uint32_t GetEntities() { return livingEntityCount; };
private:
	// Queue of unused entity IDs
	std::queue<Entity> availableEntities{};
	// Array of signatures where the index corresponds to the entity ID
	std::array<Signature, MAX_ENTITIES> signatures{};
	// Total living entities - used to keep limits on how many exist
	uint32_t livingEntityCount{};
};

