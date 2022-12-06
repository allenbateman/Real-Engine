#pragma once
#include "Resource.h"
class ResourceFbx : public Resource
{
public :
    ResourceFbx(UID uid);
    ~ResourceFbx();


	void Save()const;
	void Load()const;
	void UnLoad()const;

	static  Resource* Load(Resource* resource, std::ifstream& data);
	struct FbxNode {
		std::string name;
		unsigned int childsCount;
		std::vector<UID> reources;
	};
	std::vector<FbxNode> nodes;
};

