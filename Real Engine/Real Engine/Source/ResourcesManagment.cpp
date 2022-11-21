#include "ResourcesManagment.h"

ResourcesManagment::ResourcesManagment()
{
}

ResourcesManagment::~ResourcesManagment()
{
}

int ResourcesManagment::SubscribeEntityToMesh(const char* file_name, Entity ent)
{

	if(loadedMesh.find(file_name) == loadedMesh.end())
	{ 
		if (subscribedMesh.find(loadedMesh.find(file_name)->second) != subscribedMesh.end())
		{
			std::cout << "Adding new loaded mesh: " << loadedMesh.find(file_name)->first << " id: " << loadedMesh.find(file_name)->second << std::endl;
			subscribedMesh.insert({ loadedMesh.find(file_name)->second, { ent } });
			subscribedMesh.find(loadedMesh.find(file_name)->second)->second.push_back(ent);
			return loadedMesh.find(file_name)->second;
		}
	}
	else
	{
		std::cout << "ERROR mesh not is not loaded: " << file_name << std::endl;

		return -1;
	}



}

int  ResourcesManagment::GetLoadedMesh(const char* file_name)
{
	if (loadedMesh.find(file_name) != loadedMesh.end())
	{
		std::cout << "ERROR Could not find loaded mesh: " << file_name << std::endl;
		return -1;
	}

	return loadedMesh.find(file_name)->second;
}

bool ResourcesManagment::AddLoadedMesh(const char* file_name, unsigned int id)
{
	if (loadedMesh.find(file_name) == loadedMesh.end())
	{
		std::cout << "ERROR mesh already loaded: " << file_name << std::endl;
		return false;
	}
	loadedMesh.insert({ file_name, id });
	return true;
}
