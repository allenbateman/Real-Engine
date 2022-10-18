#include "GameObject.h"

enum componentType
{
		DEFAULT = 0,
};

class Component
{
public:
	Component(componentType type);
	~Component();

	componentType type;
	bool active;
	GameObject* owner;
	
		
	virtual void Enable();
	virtual void Update();
	virtual void Disable();
	
};