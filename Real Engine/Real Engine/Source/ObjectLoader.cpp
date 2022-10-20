#include "ObjectLoader.h"

ObjectLoader::ObjectLoader()
{
}

ObjectLoader::~ObjectLoader()
{
}

bool ObjectLoader::LoadObject(const char* file_path)
{
    bool ret = true;
    const aiScene* scene = aiImportFile(file_path, aiProcessPreset_TargetRealtime_MaxQuality);
    if (scene != nullptr && scene->HasMeshes())
    {
        for (unsigned int i = 0; i < scene->mNumMeshes; i++)
        {
            aiMesh* newMesh = scene->mMeshes[i];
            meshTest.num_vertices = newMesh->mNumVertices;
            meshTest.vertices = new float[meshTest.num_vertices * 3];
            memcpy(meshTest.vertices, newMesh->mVertices, sizeof(float) * meshTest.num_vertices * 3);
            std::cout << "New mesh with %d vertices" << meshTest.num_vertices << std::endl;
            // copy faces
            if (newMesh->HasFaces())
            {
                meshTest.num_index = newMesh->mNumFaces * 3;
                meshTest.index = new unsigned int[meshTest.num_index]; // assume each face is a triangle
                for (unsigned int i = 0; i < newMesh->mNumFaces; ++i)
                {
                    if (newMesh->mFaces[i].mNumIndices != 3)
                        LOG("WARNING, geometry face with != 3 indices!");
                    else
                        memcpy(&meshTest.index[i * 3], newMesh->mFaces[i].mIndices, 3 * sizeof(unsigned int));
                }
            }
        }
       
        aiReleaseImport(scene);
    }
    else
    {
        std::cout << aiGetErrorString();
        LOG(aiGetErrorString());
    }
    return ret;
}
