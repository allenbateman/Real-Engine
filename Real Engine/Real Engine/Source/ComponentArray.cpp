#include "ComponentArray.h"

template<typename T>
inline void ComponentArray<T>::InsertData(Entity entity, T component)
{
	assert(entityToIndexMap.find(entity) == entityToIndexMap.end() && "Component addded to same entity more than once.");
	size_t newIndex = size;
	entityToIndexMap[entity] = newIndex;
	indexToEntityMap[newIndex] = entity;
	compoenentArray[newIndex] = component;
	size++;
}

template<typename T>
inline void ComponentArray<T>::RemoveData(Entity entity)
{
	assert(entityToIndexMap.find(entity) != entityToIndexMap.end() && "Removing non existing component.");

		//copy element at end into deleted element's place to mantain density
	size_t indexOfRemovedEntity = entityToIndexMap[entity];
	size_t indexOfLastElement = size - 1;
	compoenentArray[indexOfRemovedEntity] = compoenentArray[indexOfLastElement];

	//update map to point to moved spot
	Entity entityOfLastElement = indexToEntityMap[indexOfLastElement];
	entityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
	indexToEntityMap[indexOfRemovedEntity ] = entityOfLastElement;

	entityToIndexMap.erase(entity);
	indexToEntityMap.erase(indexOfLastElement);

	size--;
}

template<typename T>
inline T& ComponentArray<T>::GetData(Entity entity)
{
	assert(entityToIndexMap.find(entity) != entityToIndexMap && "Retriving non-existing component.");

	return ComponentArray[entityToIndexMap[entity]];
}