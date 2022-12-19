#pragma once
#include "Panel.h"
#include "ResourcesManagement.h"
class ResourcesPanel :  public Panel
{
public:
	ResourcesPanel(int _id, bool isActive);
	~ResourcesPanel();

	void Begin();
	void End();
	void Init();
	void Update();
	bool CleanUp();

	void ResfreshList(std::map<UID, std::shared_ptr<Resource>>* resources);

private:
	std::map<UID, std::shared_ptr<Resource>> *resourcesToDisplay;
};

