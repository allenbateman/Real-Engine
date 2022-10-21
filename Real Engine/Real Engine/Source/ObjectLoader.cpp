#include "ObjectLoader.h"
#include "glew.h"
#include "glfw3.h"

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
        ProcessNode(scene->mRootNode, scene);
        aiReleaseImport(scene);
    }
    else
    {
        std::cout << aiGetErrorString();
        LOG(aiGetErrorString());
        ret = false;
    }
    return ret;
}

void ObjectLoader::ProcessNode(aiNode* node, const aiScene* scene)
{
    // process all the node's meshes (if any)
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(ProcessMesh(mesh, scene));
    }
    // then do the same for each of its children
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        ProcessNode(node->mChildren[i], scene);
    }
}

Mesh ObjectLoader::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{

    //temporary varaibles to store the mesh data
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    for (unsigned int i = 0; i < scene->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[i];
        for (unsigned int vi = 0; vi < mesh->mNumVertices; vi++)
        {
            Vertex vertex;
            vec3 vector;
            vector.x = mesh->mVertices[vi].x;
            vector.y = mesh->mVertices[vi].y;
            vector.z = mesh->mVertices[vi].z;
            vertex.Position = vector;

            vector.x = mesh->mNormals[vi].x;
            vector.y = mesh->mNormals[vi].y;
            vector.z = mesh->mNormals[vi].z;
            vertex.Normal = vector;

            if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
            {
                vec2 vec;
                vec.x = mesh->mTextureCoords[0][vi].x;
                vec.y = mesh->mTextureCoords[0][vi].y;
                vertex.TexCoords = vec;
            }
            else
                vertex.TexCoords = vec2(0.0f, 0.0f);

            vertices.push_back(vertex);
        }

    }

}


