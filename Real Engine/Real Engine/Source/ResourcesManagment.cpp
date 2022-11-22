#include "ResourcesManagment.h"
#include <filesystem>
ResourcesManagment::ResourcesManagment()
{
}

ResourcesManagment::~ResourcesManagment()
{
}

UID ResourcesManagment::ImportFile(const char* new_file_in_assets)
{

	//Resource* resource =  CreateNewResource(new_file_in_assets, type);
	return UID();
}

Resource::Type ResourcesManagment::FilterFile(const char* file_path)
{
        std::filesystem::path filePath = file_path;
        Resource::Type type = Resource::Type::UNKNOWN;
        if (filePath.extension() == ".fbx") // Heed the dot.
        {
            std::cout << filePath.stem() << " is a valid type.\n";
            type = Resource::Type::Fbx;
        }
        else if (filePath.extension() == ".dds")
        {
            std::cout << filePath.stem() << " is a valid type.\n";
        }
        else if (filePath.extension() == ".png")
        {
            std::cout << filePath.stem() << " is a valid type.\n";
        }
        return type;
}
