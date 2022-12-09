#pragma once
#include "Resource.h"
#include "GameObject.h"
class ResourceFbx : public Resource
{
public :
    ResourceFbx(UID uid);
    ~ResourceFbx();


	void Save()const;
	void Load()const;
	void UnLoad()const;

	static std::shared_ptr<Resource> Load(std::shared_ptr<Resource> resource, std::ifstream& data);
	struct FbxNode {
		std::string name;
		unsigned int childsCount;
		std::vector<UID> reources;
	};
	std::vector<FbxNode> nodes;
};

