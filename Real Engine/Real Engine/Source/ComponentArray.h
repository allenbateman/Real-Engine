#include "EntityManager.h"
class ICOmponentArray {
public:
	virtual ~ICOmponentArray() = default;
	virtual void EntityDestroyed(Entity entity) = 0;
};

template<typename T>
class ComponentArray : ICOmponentArray
{
public:
	void InsertData(Entity entity, T component);
	void RemoveData(Entity entity);
	T& GetData(Entity entity);
	void EntityDestroyed(Entity entity) override;
private:
	std::array<T, MAX_ENTITIES> compoenentArray;
};

