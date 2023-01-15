#pragma once
#include "Panel.h"
#include "Events.h"
#include "Resource.h"
#include "Texture.h"
#include "Material.h"
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
	shared_ptr<Resource> SelectResource(const char* text,Resource::Type type);
	void SelectTexture(Material& material, unsigned int id);
};

