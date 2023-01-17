#include "Importer.h"
#include "EntityComponentSystem.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <filesystem>
#include "EventSystem.h"
#include "Events.h"
#include "Debugger.h"
#include <sstream>
#include <string>
#include "Transform.h"
#include "nlohmann/json.hpp"
#include "SceneManager.h"
#include "UiSystem.h"

Importer::Importer()
{
}

Importer::Importer(bool isActive) : Module(isActive)
{
}

Importer::~Importer()
{
}

bool Importer::Awake()
{
    cout << "Starting Importer\n";

    ilInit();
    cout << "Initialized devIl lib\n";

    return true;
}

bool Importer::Start(){

    app->eventSystem->SubscribeModule(this, ON_FILE_DROP);

    //import all files that exist into custom file formats
    //and create meta files

    return true;
}


//texture operators--------------------------------
bool TextureImporter::LoadAiMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName, shared_ptr<ResourceMaterial>& resourceMat)
{
    std::vector<Texture> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        bool Skip = false;
        std::filesystem::path tmp = str.C_Str();
        string path = app->resourceManager->GetFilePath(ASSETS_DIR,tmp.filename().string()).string();
        if (path == "")
            return false;
        //string path = ASSETS_DIR + tmp.filename().string();
        shared_ptr<Resource> texture;

        app->importer->importedTextures.find(path);

        for (const auto& texPath : app->importer->importedTextures)
        {
            //check if the texture is already imported
            if (std::strcmp(texPath.first.data(), path.data()) == 0)
            {
                UID resourceID = app->resourceManager->FindResource(texPath.first.c_str());
                texture = app->resourceManager->GetResource(resourceID);

                if (texture == nullptr)
                {
                    cout << "ERROR::METRAIL_IMPORTER::RESOURCE_IS_NULL\n";
                    return false;
                }
                shared_ptr<ResourceTexture> t = dynamic_pointer_cast<ResourceTexture>(texture);
                t->type = typeName;
                t->Load();
                t->SaveData();
                pair<string, shared_ptr<ResourceTexture> > tResource{ typeName,t };
                resourceMat->textures.push_back(tResource);
                Skip = true;
            }
        }
        if (!Skip)
        {
            texture = app->resourceManager->CreateNewResource(path, Resource::Type::Texture);
            TextureImporter::Import(texture);
            shared_ptr<ResourceTexture> t = dynamic_pointer_cast<ResourceTexture>(texture);
            t->type = typeName;
            t->Load();
            t->SaveData();
            pair<string, shared_ptr<ResourceTexture> > tResource{ typeName,t };
            resourceMat->textures.push_back(tResource);
            return true;
        }
    }
    return true;
}

void TextureImporter::Import(shared_ptr<Resource>& resource){

    string id = resource->GetID();
    shared_ptr<ResourceTexture> rTexture = std::static_pointer_cast<ResourceTexture>(resource);

    for (auto texture = app->importer->importedTextures.begin(); texture != app->importer->importedTextures.end(); texture++)
    {
        if (texture->first == resource->GetAssetPath().string())
        {
            auto rTex = app->resourceManager->GetResource(texture->second);

            //this means that there is a resource with that same texture
            if (rTex != nullptr)
            {
                app->resourceManager->RemoveResource(resource->GetID());
                resource.reset();
                return;
            }
        }
    }

    if (ilLoadImage(rTexture->GetAssetPath().string().c_str()))
    {
        cout << "Texture  " << rTexture->name << " loaded with devIL" << endl;
    }
    else {
        cout << "Texture not loaded with devIL "<< rTexture->name << endl;
        return;
    }

    ILubyte* data = ilGetData();
    ILenum type = ilGetInteger(IL_IMAGE_TYPE);
    rTexture->width = ilGetInteger(IL_IMAGE_WIDTH);
    rTexture->height = ilGetInteger(IL_IMAGE_HEIGHT);
    rTexture->depth = ilGetInteger(IL_IMAGE_DEPTH);
    rTexture->channels = ilGetInteger(IL_IMAGE_CHANNELS);
    rTexture->format = ilGetInteger(IL_IMAGE_FORMAT);

    rTexture->SaveData();
    std::pair<string,string> texture =  std::make_pair(rTexture->GetAssetPath().string(), rTexture->GetID());
    app->importer->importedTextures.insert(texture);
}
//Material operators--------------------------------
void MaterialImporter::Import(const aiMaterial* material, shared_ptr<ResourceMaterial>& resourceMat)
{
    bool Skip = false;

    //Laod material textures
    for (unsigned int i = 0; i < material->GetTextureCount(aiTextureType_DIFFUSE); i++)
    {
        aiString str;
        material->GetTexture(aiTextureType_DIFFUSE, i, &str);
        string name = str.C_Str();
        string path = ASSETS_DIR + name;
               
        for (const auto& texPath : app->importer->importedTextures)
        {
          
            if (std::strcmp(texPath.first.data(), path.data()) == 0)
            {
                UID resourceID = app->resourceManager->FindResource(texPath.first.c_str());
                     
                shared_ptr<Resource> textureDiff = app->resourceManager->GetResource(resourceID);
                if (textureDiff == nullptr)
                {
                    cout << "ERROR::METRAIL_IMPORTER::RESOURCE_IS_NULL\n"; 
                }
                shared_ptr<ResourceTexture> t = dynamic_pointer_cast<ResourceTexture>(textureDiff);
                pair<string, shared_ptr<ResourceTexture> > tResource{ "texture_diffuse",t};
                resourceMat->textures.push_back(tResource);
                Skip = true;
                break;
            }
        }
        if (!Skip)
        {
            cout << "IMPORTING NEW TEXTURE "<< name <<"\n";
            shared_ptr<Resource> textureDiff = app->resourceManager->CreateNewResource(path, Resource::Type::Texture);
            TextureImporter::Import(textureDiff);
            shared_ptr<ResourceTexture> t = dynamic_pointer_cast<ResourceTexture>(textureDiff);
            pair<string, shared_ptr<ResourceTexture> > tResource{ "texture_diffuse",t };
            resourceMat->textures.push_back(tResource);
        }
    }

    //get specular textures
    for (unsigned int i = 0; i < material->GetTextureCount(aiTextureType_SPECULAR); i++)
    {
        aiString str;
        material->GetTexture(aiTextureType_SPECULAR, i, &str);
        string path = str.C_Str();
        path = ASSETS_DIR + path;

        for (const auto& texPath : app->importer->importedTextures)
        {
            //check if it already exist
            if (std::strcmp(texPath.first.data(), path.data()) == 0)
            {
                UID resourceID = app->resourceManager->FindResource(texPath.first.c_str());

                shared_ptr<Resource> textureDiff = app->resourceManager->GetResource(resourceID);
                if (textureDiff == nullptr)
                {
                    cout << "ERROR::METRAIL_IMPORTER::RESOURCE_IS_NULL\n";
                   
                }
                shared_ptr < ResourceTexture> t = dynamic_pointer_cast<ResourceTexture>(textureDiff);
                pair<string, shared_ptr < ResourceTexture> > tResource{ "texture_specular",t };
                resourceMat->textures.push_back(tResource);
                Skip = true;
                break;
            }
        }
        if (!Skip) {
            shared_ptr<Resource> textureSpecular = app->resourceManager->CreateNewResource(str.C_Str(), Resource::Type::Texture);
            TextureImporter::Import(textureSpecular);

            shared_ptr<ResourceTexture> t = dynamic_pointer_cast<ResourceTexture>(textureSpecular);
            pair<string, shared_ptr < ResourceTexture> > tResource{ "texture_specular",t };
            resourceMat->textures.push_back(tResource);
        }
    }


   
    //set default shader to the material
    auto shaders = app->resourceManager->GetResourceListOfType(Resource::Type::Shader);
    bool exist = false;
    for (auto shader : shaders)
    {
        if (shader->name == "default")
        {
            resourceMat->shader = dynamic_pointer_cast<ResourceShader>(shader);
            exist = true;
            break;
        }
    }
    if (!exist)
    {
        // if default shader does not exist create it
        shared_ptr<Resource> shaderResource = app->resourceManager->CreateNewResource("../Output/Assets/Shaders/default.vertex", Resource::Type::Shader);
        shared_ptr<ResourceShader> shader = dynamic_pointer_cast<ResourceShader>(shaderResource);
        shader->name = "default";
        shader->Load("../Output/Assets/Shaders/default.vertex", "../Output/Assets/Shaders/default.fragment");
        resourceMat->shader = shader;
    }

    resourceMat->SetLibraryPath("..\\Output\\Library\\Materials\\" + resourceMat->GetID() + ".material");
    resourceMat->SaveData();
}

void MeshImporter::Import(const aiMesh* mesh, shared_ptr<ResourceMesh>&  resource)
{
    //temporary varaibles to store the mesh data
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

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

    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    resource->vertices = vertices;
    resource->indices = indices;
}

//Fbx operators--------------------------------
void SceneImporter::Import(shared_ptr<Resource>& resource)
{
    const aiScene* scene;
    if (resource->GetAssetPath().stem().string() == "water_plane")
    {
        scene = aiImportFile(resource->GetAssetPath().string().c_str(), aiProcessPreset_TargetRealtime_MaxQuality);
    }
    else {
         scene = aiImportFile(resource->GetAssetPath().string().c_str(), aiProcessPreset_TargetRealtime_MaxQuality |
            aiProcess_PreTransformVertices);
    }
    
    shared_ptr<ResourceScene> rScene = static_pointer_cast<ResourceScene>(resource);

    if (scene != nullptr && scene->HasMeshes())
    { 
        rScene->name = resource->GetAssetPath().stem().string();
        rScene->SetLibraryPath("..\\Output\\Library\\Objects\\" + rScene->GetID() + ".scene");
        GameObject* root = new GameObject(rScene->name);
        rScene->root = root;
        root->GetComponent<Transform>().localPosition = (0, 0, 0);
        root->GetComponent<Transform>().localRotation = (0, 0, 0);
        root->GetComponent<Transform>().localScale = (1, 1, 1);
        SceneImporter::ProcessaNode(scene->mRootNode, scene, rScene->root, rScene);

        string savePath = rScene->GetLibraryPath().string();

        app->sceneManager->currentScene->AddGameObject(root);

        try
        {
            aiReleaseImport(scene);
        }
        catch(int error)
        {
            cout<<aiGetErrorString();
        }
    }
    else
    {
        std::cout << aiGetErrorString();
        LOG(aiGetErrorString());
    }
}

void SceneImporter::ProcessaNode(aiNode* node, const aiScene* scene, GameObject* rNode, shared_ptr<ResourceScene>& rFbx)
{
    GameObject newNode;
    aiMatrix4x4 transform;
    if (node->mNumMeshes > 0)
    {
        //creeaeting base objekt
        newNode = *(new GameObject(node->mName.C_Str()));
        newNode.GetComponent<Transform>().parent = &rNode->GetComponent<Transform>();
        rNode->GetComponent<Transform>().AddChild(&newNode.GetComponent<Transform>());
        newNode.meshCount = node->mNumMeshes;
        newNode.childsCount = node->mNumChildren;
        auto& t = newNode.GetComponent<Transform>();
        t.localMatrix = rFbx->transform;
        t.Translate(0, 0, 0);
        t.Rotate(0, 0, 0);
        t.localScale =vec3(1,1,1);
        // process all the node's meshes (if any)  
        for (unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            if (i >= 1) break;

            //add the mesh and all the elements the objekt needs
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            newNode.meshIndex.push_back(i);
            newNode.name = scene->mMeshes[node->mMeshes[i]]->mName.C_Str();
            SceneImporter::ProcessaMesh(mesh, scene, &newNode, rFbx);
        }
    }
    else {
        newNode = *rNode;
        rFbx->transform = rFbx->transform * mat4x4(node->mTransformation.a1, node->mTransformation.a2, node->mTransformation.a3, node->mTransformation.a4);
    }
    // continue for all child nodes
    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        SceneImporter::ProcessaNode(node->mChildren[i], scene, &newNode, rFbx);
    }

}

void SceneImporter::ProcessaMesh(aiMesh* mesh, const aiScene* scene, GameObject* rNode, shared_ptr<ResourceScene>& rFbx)
{   
    //create the mesh resource
    string name = mesh->mName.C_Str();
    shared_ptr<Resource> resourceMesh = app->resourceManager->CreateNewResource("..\\Output\\Assets\\" + name, Resource::Type::Mesh);
    shared_ptr<ResourceMesh> rm = static_pointer_cast<ResourceMesh>(resourceMesh);
    rm->name = name;
    //load material attached to the obj
    UID matId;
    bool NewMaterial = true;
    if (mesh->mMaterialIndex >= 0 )
    {
        //if empty load the first mat
        if (rFbx->materials.empty())
        {
            matId = SceneImporter::ProcessMaterial(mesh, scene, rNode, rFbx);
            if (matId == "") cout << "ERROR::PROCESS_MATERIAL\n";
        }
        else {
            for (int i = 0; i < rFbx->materials.size(); i++)
            {
                //check if the material is alrady loaded
                if (mesh->mMaterialIndex == i)
                {
                    matId = rFbx->materials.at(i);
                    Material mat;
                    auto resource = app->resourceManager->GetResource(matId);
                    mat.resource = dynamic_pointer_cast<ResourceMaterial>(resource);
                    rNode->AddComponent<Material>(mat); 
                    NewMaterial = false;
                    break;
                }
            }   
            if (NewMaterial)
            {
                matId = SceneImporter::ProcessMaterial(mesh, scene, rNode, rFbx);
                if (matId == "") cout << "ERROR::PROCESS_MATERIAL\n";
            }
        }   
    }

    string savePath = "..\\Output\\Library\\Meshes\\" + rm->GetID() + ".mesh";
    rm->SetLibraryPath(savePath);
    rm->materialIndex = mesh->mMaterialIndex;
    MeshImporter::Import(mesh, rm);
    rm->material_UID = matId;
    rm->SaveData();
    rm->Load();
    Mesh mComponent;
    mComponent.resource = rm;
    rNode->AddComponent(mComponent);
    rFbx->meshes.push_back(resourceMesh->GetID());
}
UID  SceneImporter::ProcessMaterial(aiMesh* mesh, const aiScene* scene, GameObject* rNode, shared_ptr<ResourceScene>& rFbx)
{
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
    string name = material->GetName().C_Str();


    //check if the material already exist
    for (const auto& mat : app->importer->importedMaterials)
    {
        //compare the asset path and the material index
        if (mat.first == rFbx->GetAssetPath().string() && mat.second.first == mesh->mMaterialIndex)
        {
            return mat.second.second;
        }
    }

    //material does not exits, create a new one 
    bool HasSpecular = false;
    bool HasDiffuse = false;
    shared_ptr<Resource> resourceMat = app->resourceManager->CreateNewResource(rFbx->GetAssetPath(), Resource::Type::Material);
    shared_ptr<ResourceMaterial> rm = static_pointer_cast<ResourceMaterial>(resourceMat);
    rm->name = rNode->name;

    HasDiffuse = TextureImporter::LoadAiMaterialTextures(material,aiTextureType_DIFFUSE, "texture_diffuse", rm);
    HasSpecular =  TextureImporter::LoadAiMaterialTextures(material,aiTextureType_SPECULAR, "texture_specular", rm);
   
    //if resource mat is empty, because the mesh has no mat assigned, 
    //we assing a default mat
    if (!HasDiffuse && !HasSpecular)
    {
        //set base  shader to the material if has no textures
        auto shaders = app->resourceManager->GetResourceListOfType(Resource::Type::Shader);
        bool exist = false;
        for (auto shader : shaders)
        {
            if (shader->name == "basecolor")
            {
                rm->shader = dynamic_pointer_cast<ResourceShader>(shader);
                exist = true;
                break;
            }
        }
        if (!exist)
        {
            // if default shader does not exist create it
            shared_ptr<Resource> shaderResource = app->resourceManager->CreateNewResource("../Output/Assets/Shaders/basecolor.vertex", Resource::Type::Shader);
            shared_ptr<ResourceShader> shader = dynamic_pointer_cast<ResourceShader>(shaderResource);
            shader->name = "basecolor";
            shader->Load("../Output/Assets/Shaders/basecolor.vertex", "../Output/Assets/Shaders/basecolor.fragment");
            rm->shader = shader;
        }
        std::string name = "default_texture.png";
        std::string fullPath = ASSETS_DIR + name;
        if (!app->resourceManager->ExistFileInResources(fullPath))
        {
            shared_ptr<Resource> defaultTex = app->resourceManager->CreateNewResource(fullPath, Resource::Type::Texture);
            TextureImporter::Import(defaultTex);

            shared_ptr<ResourceTexture> rt = dynamic_pointer_cast<ResourceTexture>(defaultTex);
            rt->SaveData();
            rt->Load();
            pair<string, shared_ptr<ResourceTexture> > tResource{ "texture_diffuse",rt };
            rm->textures.push_back(tResource);
        }
        else
        {
           shared_ptr<Resource> texture;
           UID Uid = app->resourceManager->FindResource(fullPath.c_str());
           if (Uid != "")
           {
              texture = app->resourceManager->GetResource(Uid);
              if (texture.get() == nullptr)
              {
                  Debug::Error("ERROR::LOADING_DEFAULT_MATERIAL"); 
              }
              shared_ptr<ResourceTexture> t = dynamic_pointer_cast<ResourceTexture>(texture);
              pair<string, shared_ptr<ResourceTexture> > tResource{ "texture_diffuse",t };
              rm->textures.push_back(tResource);
           }
           else {
               cout << "ERROR::LOADING_DEFAULT_MATERIAL";
                Debug::Error("ERROR::LOADING_DEFAULT_MATERIAL");
           }       
        }
    }
    else {
        //set default shader to the material
        auto shaders = app->resourceManager->GetResourceListOfType(Resource::Type::Shader);
        bool exist = false;
        for (auto shader : shaders)
        {
            if (shader->name == "default")
            {
                rm->shader = dynamic_pointer_cast<ResourceShader>(shader);
                exist = true;
                break;
            }
        }
        if (!exist)
        {
            // if default shader does not exist create it
            shared_ptr<Resource> shaderResource = app->resourceManager->CreateNewResource("../Output/Assets/Shaders/default.vertex", Resource::Type::Shader);
            shared_ptr<ResourceShader> shader = dynamic_pointer_cast<ResourceShader>(shaderResource);
            shader->name = "default";
            shader->Load("../Output/Assets/Shaders/default.vertex", "../Output/Assets/Shaders/default.fragment");
            rm->shader = shader;
        }
    }


    rm->SetLibraryPath("..\\Output\\Library\\Materials\\" + resourceMat->GetID() + ".material");
    rm->SaveData();
    rm->Load();
    Material mat;
    mat.resource = rm;
    rNode->AddComponent(mat); 
    rFbx->materials.push_back(rm->GetID());
    app->importer->importedMaterials.insert(std::make_pair(resourceMat->GetAssetPath().string(),std::make_pair(mesh->mMaterialIndex, resourceMat->GetID())));
    return resourceMat->GetID();
}
void SceneImporter::LoadObject(const std::string file_path)
{
}

void ShaderImporter::Import(shared_ptr<Resource>& resource)
{
    shared_ptr<ResourceShader> rShader = std::static_pointer_cast<ResourceShader>(resource);
    string vertex,fragment;
    vertex = rShader->GetAssetPath().string();
    filesystem::path tmp = rShader->GetAssetPath();
    fragment = tmp.replace_extension("fragment").string();
    rShader->Load(vertex.c_str(), fragment.c_str());
}
