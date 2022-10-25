#pragma once
#include "System.h"
#include "Component.h"
#include <cassert>
#include <memory>
#include <unordered_map>
class SystemManager
{
public:
	template<typename T>
	std::shared_ptr<T> RegisterSystem();
	template<typename T>
	void SetSignature(Signature signature);
	void EntityDestroyed(Entity entity);
	void EntitySignatureChanged(Entity entity, Signature entitySignature);

private:
	std::unordered_map<const char*, Signature> signatures{};
	std::unordered_map<const char*, std::shared_ptr<System>> systems{};
};