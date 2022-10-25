#include "SystemManager.h"


template<typename T>
inline std::shared_ptr<T> SystemManager::RegisterSystem()
{
	const char* typeName = typeid(T).name();
	assert(systems.find(typeName) == systems.end() && "Registering system more than once.");

	auto system = std::make_shared<T>();
	systems.insert({ typeName,system });
	return system;
}

template<typename T>
inline void SystemManager::SetSignature(Signature signature)
{
	const char* typeName = typeid(T).name();

	assert(systems.find(typeName) != systems.end() && "System used before registered.");

	signatures.insert({typeName,signature});
}

void SystemManager::EntityDestroyed(Entity entity)
{
	for (auto const& pair : systems)
	{
		auto const& system = pair.second;
		system->entities.erase(entity);
	}
}

void SystemManager::EntitySignatureChanged(Entity entity, Signature entitySignature)
{
	for (auto const& pair : systems)
	{
		auto const& type = pair.first;
		auto const& system = pair.second;
		auto const& systemSignature = signatures[type];

		if ((entitySignature & systemSignature) == systemSignature)
		{
			system->entities.insert(entity);
		}
		else
		{
			system->entities.erase(entity);
		}
	}
}
