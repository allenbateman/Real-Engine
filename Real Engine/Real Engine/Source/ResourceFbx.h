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

	static  Resource* Load(std::string UUID, std::ifstream& data);
    unsigned int ChildCount;
    
};

