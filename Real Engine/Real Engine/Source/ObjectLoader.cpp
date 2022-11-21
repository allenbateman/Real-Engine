#include "ObjectLoader.h"
#include "EntityComponentSystem.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Transform.h"
#include <stdio.h>

//https://openil.sourceforge.net/docs/DevIL%20Manual.pdf

static const char* LibraryDir = "../Output/Library/";

ObjectLoader::ObjectLoader()
{
}

ObjectLoader::~ObjectLoader()
{
}

vector<GameObject*>  ObjectLoader::LoadObject(const std::string file_path)
{
    bool ret = true;
    const aiScene* scene = aiImportFile(file_path.c_str(), aiProcessPreset_TargetRealtime_MaxQuality);
    GameObject* newGameObject = nullptr;

    std::vector<GameObject*> result;

    if (scene != nullptr && scene->HasMeshes())
    {
        directory = file_path.substr(0, file_path.find_last_of('/')); 
        std::size_t from = file_path.find_last_of('/');
        std::size_t to = file_path.find_last_of('.');
        fileName = file_path.substr(from+1,to);

        newGameObject = new GameObject(fileName);
        ProcessNode(scene->mRootNode, scene, *newGameObject, result);
        result.push_back(newGameObject);
        aiReleaseImport(scene);
    }
    else
    {
        std::cout << aiGetErrorString();
        LOG(aiGetErrorString());
    }
    return  result;
}

void ObjectLoader::ProcessNode(aiNode* node, const aiScene* scene, GameObject parentGo, std::vector<GameObject*>& result)
{
    // process all the node's meshes (if any)
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        parentGo.AddComponent(ProcessMesh(mesh, scene, parentGo));
    }
    // then do the same for each of its children
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        GameObject* childGo = new GameObject(fileName + std::to_string(i));
        childGo->GetComponent<Transform>().parent = &parentGo.GetComponent<Transform>();
        parentGo.GetComponent<Transform>().childs.push_back(&childGo->GetComponent<Transform>());
        ProcessNode(node->mChildren[i], scene, *childGo, result);

       result.push_back(childGo);
    }
}

Mesh ObjectLoader::ProcessMesh(aiMesh* mesh, const aiScene* scene, GameObject go)
{

    //temporary varaibles to store the mesh data
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

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

        vec4 color;
        color.x = 255;
        color.y = 0;
        color.z = 0;
        color.w = 255;
        vertex.Color = color;

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

    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
        indices.push_back(face.mIndices[j]);
    }

    //load material attached to the obj
    if (mesh->mMaterialIndex >= 0)
    {
        go.AddComponent(ProcessMaterial(mesh, scene));
    }

    return Mesh(vertices, indices);
}

Material ObjectLoader::ProcessMaterial(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Texture> textures;
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
    std::vector<Texture> diffuseMaps = loadMaterialTextures(material,
        aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    std::vector<Texture> specularMaps = loadMaterialTextures(material,
        aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

    return Material(textures);
}

std::vector<Texture> ObjectLoader::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
    std::vector<Texture> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        bool skip = false;

        string filepath = directory + "/" + str.C_Str();
        string filename = str.C_Str();

        for (unsigned int j = 0; j < loadedtextures.size(); j++)
        {
            if (std::strcmp(loadedtextures[j].path.data(), filepath.c_str()) == 0)
            {
                textures.push_back(loadedtextures[j]);
                skip = true;
                break;
            }
        }
        if (!skip)
        {   
            // if texture hasn't been loaded already, load it

            // import image and store it in our file format

          
            if (ilLoadImage(filepath.c_str()))
            {
                cout << "Texture: "<< str.C_Str() << " loaded with devIL"<<endl;
            }
            else {
                cout << "Image not loaded with devIL" << endl;
            }


            //for textures
            string fileName = filename.substr(0, filename.find_last_of('.'));
            cout << fileName<<endl;
            string storePath = LibraryDir + fileName +".dds";
            cout << storePath << endl;

            if (ilSave(IL_DDS, storePath.c_str()))
                cout << "saved file with devil\n";
            else
                cout << "could not save file with devil \n";

            //this creates a texture and load it to the GPU
            //Load texture from library folder
            //create index for it
            Texture texture;
            texture.id = LoadTexture(filepath);
                
            texture.path = filepath;
            texture.type = typeName;
            textures.push_back(texture);
            loadedtextures.push_back(texture); // add to loaded textures
            
        }
    }
    return textures;
}


