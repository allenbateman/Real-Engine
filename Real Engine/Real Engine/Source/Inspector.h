#pragma once
#include "Panel.h"
#include "Events.h"
#include "Resource.h"
#include "Texture.h"
class Inspector : public Panel
{
public:
	Inspector(int _id,bool isActive);
	~Inspector();
	void Init();
	void Update();
	void DrawComponents(Entity entity);
	OnFOVChange fovChange;
	Entity context = -1;
private:
	bool SearchTabOpen = false;
	void ShowSearchField(Entity entity);

	void ListAvailableResources(Resource::Type  type,shared_ptr<Resource>& resource);
	Texture* SelectTexture();
};

