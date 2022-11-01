#pragma once
#include "Entity.h"
#include "Component.h"
#include <array>
#include <cassert>
#include <unordered_map>
#include <iostream>
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
	void DebugMaps();
	void InsertData(Entity entity, T component);
	T& GetData(Entity entity);
	void RemoveData(Entity entity)
	{
		assert(entityToIndexMap.find(entity) != entityToIndexMap.end() && "Removing non existing component.");

		// Copy element at end into deleted element's place to maintain density
		size_t indexOfRemovedEntity = entityToIndexMap[entity];
		size_t indexOfLastElement = size - 1;
		componentArray[indexOfRemovedEntity] = componentArray[indexOfLastElement];

		// Update map to point to moved spot
		Entity entityOfLastElement = indexToEntityMap[indexOfLastElement];
		entityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
		indexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

		entityToIndexMap.erase(entity);
		indexToEntityMap.erase(indexOfLastElement);

		--size;
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
inline void ComponentArray<T>::DebugMaps()
{
	std::cout << "entity -> index" << std::endl;
	for (auto& it : entityToIndexMap)
	{
		std::cout<<"["<< it.first << " :" << it.second << "]" << std::endl;
	}
	std::cout << "index -> entity" << std::endl;
	for (auto& it : indexToEntityMap)
	{
		std::cout << "[" << it.first << " :" << it.second << "]" << std::endl;
	}

	std::cout << "Size: " << size << std::endl;;
}

template<typename T>
inline void ComponentArray<T>::InsertData(Entity entity, T component)
{
	assert(entityToIndexMap.find(entity) == entityToIndexMap.end() && "Component added to same entity more than once.");
	size_t newIndex = size;
	entityToIndexMap[entity] = newIndex;
	indexToEntityMap[newIndex] = entity;
	componentArray[newIndex] = component;
	size++;
}

template<typename T>
inline T& ComponentArray<T>::GetData(Entity entity)
{
	assert(entityToIndexMap.find(entity) != entityToIndexMap.end() && "Retrieving non-existent component.");
	return componentArray[entityToIndexMap[entity]];
}

