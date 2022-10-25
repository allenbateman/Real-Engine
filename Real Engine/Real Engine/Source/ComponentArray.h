#pragma once
#include "Entity.h"
#include "Component.h"
#include <array>
#include <cassert>
#include <unordered_map>
class IComponentArray {
public:
	virtual ~IComponentArray() = default;
	virtual void EntityDestroyed(Entity entity) = 0;
};

template<typename T>
class ComponentArray : IComponentArray
{
public:
	void InsertData(Entity entity, T component);
	void RemoveData(Entity entity);
	T& GetData(Entity entity);
	void EntityDestroyed(Entity entity) override;
private:
	std::array<T, MAX_ENTITIES> compoenentArray{};
	std::unordered_map <Entity, size_t> entityToIndexMap{};
	std::unordered_map <size_t, Entity> indexToEntityMap{};
	size_t size{};
};

