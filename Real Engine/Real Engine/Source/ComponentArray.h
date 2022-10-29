#pragma once
#include "Entity.h"
#include "Component.h"
#include <array>
#include <cassert>
#include <unordered_map>
class IComponentArray {
public:
	virtual ~IComponentArray() = default;
	virtual void EntityDestroyed(Entity entity) {};
};

template<typename T>
class ComponentArray : public IComponentArray
{
public:
	bool HasData(Entity entity);

	void InsertData(Entity entity, T component);
	T& GetData(Entity entity);
	void RemoveData(Entity entity)
	{
		assert(entityToIndexMap.find(entity) != entityToIndexMap.end() && "Removing non existing component.");

		//copy element at end into deleted element's place to mantain density
		size_t indexOfRemovedEntity = entityToIndexMap[entity];
		size_t indexOfLastElement = size - 1;
		componentArray[indexOfRemovedEntity] = componentArray[indexOfLastElement];

		//update map to point to moved spot
		Entity entityOfLastElement = indexToEntityMap[indexOfLastElement];
		entityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
		indexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

		entityToIndexMap.erase(entity);
		indexToEntityMap.erase(indexOfLastElement);

		size--;
	}
	void EntityDestroyed(Entity entity) override
	{
		if (entityToIndexMap.find(entity) != entityToIndexMap.end())
		{
			RemoveData(entity);
		}
	}

private:
	std::array<T, MAX_ENTITIES> componentArray{};
	std::unordered_map <Entity, size_t> entityToIndexMap{};
	std::unordered_map <size_t, Entity> indexToEntityMap{};
	size_t size{};
};

template<typename T>
inline bool ComponentArray<T>::HasData(Entity entity)
{
	return (entityToIndexMap.find(entity) != entityToIndexMap.end()) ?  true :  false;
}

template<typename T>
inline void ComponentArray<T>::InsertData(Entity entity, T component)
{
//	assert(entityToIndexMap.find(entity) == entityToIndexMap.end() && "Component added to same entity more than once.");
	size_t newIndex = size;
	entityToIndexMap[entity] = newIndex;
	indexToEntityMap[newIndex] = entity;
	componentArray[newIndex] = component;
	size++;
}

template<typename T>
inline T& ComponentArray<T>::GetData(Entity entity)
{
	assert(entityToIndexMap.find(entity) != entityToIndexMap.end() && "Retriving non-existing component.");
	
	return componentArray[entityToIndexMap[entity]];
}

