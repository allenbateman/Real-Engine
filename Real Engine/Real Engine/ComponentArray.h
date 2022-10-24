#include "Entity.h"
class ICOmponentArray {
public:
	virtual ~ICOmponentArray() = default;
	virtual void EntityDestroyed(Entity entity) = 0;
};
class ComponentArray
{
};

