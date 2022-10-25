#include "ComponentManager.h"


template<typename T>
inline void ComponentManager::RegisterComponent()
{
	const char* typeName = typeid(T).name();
	assert(componentTypes.find(typeName) == componentTypes.end() && "Registering component type more than once");

	componentTypes.insert({ typeName, nextComponentType });
	componentArrays.insert({ typeName, std::make_shared<ComponentArray<T>>() });
	nextComponentType++;
}

template<typename T>
inline ComponentType ComponentManager::GetComponentType()
{
	const char* typeName = typeid(T).name();
	assert(componentTypes.find(typeName) != componentTypes.end() && "Component not registered before use.");
	return componentTypes[typeName];
}

template<typename T>
inline void ComponentManager::AddComponent(Entity entity, T component)
{
	// Add a component to the array for an entity
	GetComponentArray<T>()->InsertData(entity, component);
}

template<typename T>
inline void ComponentManager::RemoveComponent(Entity entity)
{
	// Remove a component from the array for an entity
	GetComponentArray<T>()->GetData(entity);
}
template<typename T>
T& ComponentManager::GetComponent(Entity entity)
{
	// Get a reference to a component from the array for an entity
	return GetComponentArray<T>()->GetData(entity);
}

void ComponentManager::EntityDestroyed(Entity entity)
{
	// Notify each component array that an entity has been destroyed
	// If it has a component for that entity, it will remove it
	for(auto const& pair : componentArrays)
	{
		auto const& component = pair.second;

		component->EntityDestroyed(entity);
	}
}

template<typename T>
inline std::shared_ptr<ComponentArray<T>> ComponentManager::GetComponentArray()
{
	const char* typeName = typeid(T).name();

	assert(componentTypes.find(typeName) != componentTypes.end() && "Component not registered before use");

	return std::static_pointer_cast<ComponentArray<T>>(componentArrays[typeName]);
}