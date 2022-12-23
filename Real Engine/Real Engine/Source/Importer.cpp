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
    return true;
}


//texture operators--------------------------------
//wrtie
std::ostream& operator<<(std::ostream& out, const Texture& tex)
{
    out << "<id>" << '[' + tex.id + ']';
    out << "<type> " << '[' + tex.type << ']';
    out << "<path>" << '[' + tex.path << ']' + '\n';

    return out;
}
//Read
std::ifstream& operator>>(std::ifstream& infile, const Texture& tex)
{

    std::string line;
    while (std::getline(infile, line, '<'))
    {
        std::istringstream iss(line);

    }

    return infile;
}

void TextureImporter::Save(const Texture tex, const std::string& filename)
{
    std::ofstream out(filename);
    if (out.is_open())
    {
        nlohmann::json json_obj;
        json_obj["uid"] = tex.uid;
        json_obj["id"] = tex.id;
        json_obj["path"] = tex.path;
        json_obj["type"] = tex.type;
        std::string json_str = json_obj.dump();
        out << json_str.c_str();
    }

    //if (out.is_open())
    //{
    //    out << tex << '\n';
    //}
    //else {
    //    cout << "Error saving texture: " + filename;
    //}

    out.close();
}

void TextureImporter::LoadAiMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName, shared_ptr<Resource>& resource)
{
    shared_ptr<ResourceMaterial> resourceMat = static_pointer_cast<ResourceMaterial>(resource);
    std::vector<Texture> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        bool Skip = false;
        string name = str.C_Str();
        string path = ASSETS_DIR + name;
        shared_ptr<Resource> texture;
        for (const auto& texPath : app->importer->importedTextures)
        {

            if (std::strcmp(texPath.string().data(), path.data()) == 0)
            {
                UID resourceID = app->resourceManager->FindResource(texPath.string().c_str());
                texture = app->resourceManager->GetResource(resourceID);

                if (texture == nullptr)
                {
                    cout << "ERROR::METRAIL_IMPORTER::RESOURCE_IS_NULL\n";
                    return;
                }
                shared_ptr<ResourceTexture> t = dynamic_pointer_cast<ResourceTexture>(texture);
                pair<string, ResourceTexture > tResource{ "texture_diffuse",*t };
                resourceMat->resourcesTexture.push_back(tResource);
                Skip = true;
                break;
            }
        }
        if (!Skip)
        {

            texture = app->resourceManager->CreateNewResource(path, Resource::Type::Texture);
            TextureImporter::Import(texture);
            shared_ptr<ResourceTexture> t = dynamic_pointer_cast<ResourceTexture>(texture);
            pair<string, ResourceTexture > tResource{ "texture_diffuse",*t };
            resourceMat->resourcesTexture.push_back(tResource);
        }
    }
}

void TextureImporter::Import(shared_ptr<Resource>& resource){

    string id = resource->GetID();
    shared_ptr<ResourceTexture> rt = static_pointer_cast<ResourceTexture>(resource);
    
    if (ilLoadImage(resource->GetAssetPath().string().c_str()))
    {
        cout << "Texture id: " <<  id << " loaded with devIL" << endl;
    }
    else {
        cout << "Image not loaded with devIL "<< resource->name << endl;
    }

    ILubyte* data = ilGetData();
    ILuint width = ilGetInteger(IL_IMAGE_WIDTH), height = ilGetInteger(IL_IMAGE_HEIGHT);
    ILuint depth = ilGetInteger(IL_IMAGE_DEPTH);
    ILubyte channels = ilGetInteger(IL_IMAGE_CHANNELS);
    ILenum format = ilGetInteger(IL_IMAGE_FORMAT);
    ILenum type = ilGetInteger(IL_IMAGE_TYPE);

    rt->width = width;
    rt->height = height;
    rt->depth = depth;
    rt->channels = channels;
    rt->format = format;
    rt->type = type;

    string path = LIBRARY_DIR;
    std::string storePath = path + "Textures\\" + id + ".dds";

    if (ilSave(IL_DDS, storePath.c_str()))
    {
        cout << "saved file with devil\n";
        rt->SetLibraryPath(storePath);
    }
    else
    {
        cout << "could not save file with devil \n";
        app->importer->importedTextures.push_back("Save Failed: " + resource->name);
    }
    //Save meta file
    rt->Save();
  
    app->importer->importedTextures.push_back(resource->GetAssetPath().c_str());
}
//Material operators--------------------------------
std::ostream& operator <<(std::ostream& out, const Material& material)
{
    out << "<textures>" << '[' << material.textures.size() << ']' << '\n';
    vector<Texture>::const_iterator t = material.textures.begin();
    while (t != material.textures.end())
    {
        out << "<id>" << '[' << t->uid << "]" << "<type>" << '[' << t->type << ']' << "<path>" << '[' << t->path << ']' << '\n';
        t++;
    }
    return out;
}
UID MaterialImporter::Import(const aiMaterial* material, shared_ptr<Resource> resource)
{
    shared_ptr<ResourceMaterial> resourceMat = dynamic_pointer_cast<ResourceMaterial>(resource);

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
          
            if (std::strcmp(texPath.string().data(), path.data()) == 0)
            {
                UID resourceID = app->resourceManager->FindResource(texPath.string().c_str());
                     
                shared_ptr<Resource> textureDiff = app->resourceManager->GetResource(resourceID);
                if (textureDiff == nullptr)
                {
                    cout << "ERROR::METRAIL_IMPORTER::RESOURCE_IS_NULL\n"; 
                    return "";
                }
                shared_ptr<ResourceTexture> t = dynamic_pointer_cast<ResourceTexture>(textureDiff);
                pair<string, ResourceTexture > tResource{ "texture_diffuse",*t};
                resourceMat->resourcesTexture.push_back(tResource);
                Skip = true;
                break;
            }
        }
        if (!Skip)
        {
    
            shared_ptr<Resource> textureDiff = app->resourceManager->CreateNewResource(path, Resource::Type::Texture);
            TextureImporter::Import(textureDiff);
            shared_ptr<ResourceTexture> t = dynamic_pointer_cast<ResourceTexture>(textureDiff);
            pair<string, ResourceTexture > tResource{ "texture_diffuse",*t };
            resourceMat->resourcesTexture.push_back(tResource);
        }
    }
    for (unsigned int i = 0; i < material->GetTextureCount(aiTextureType_SPECULAR); i++)
    {
        aiString str;
        material->GetTexture(aiTextureType_SPECULAR, i, &str);
        string path = str.C_Str();
        path = ASSETS_DIR + path;

        for (const auto& texPath : app->importer->importedTextures)
        {

            if (std::strcmp(texPath.string().data(), path.data()) == 0)
            {
                UID resourceID = app->resourceManager->FindResource(texPath.string().c_str());

                shared_ptr<Resource> textureDiff = app->resourceManager->GetResource(resourceID);
                if (textureDiff == nullptr)
                {
                    cout << "ERROR::METRAIL_IMPORTER::RESOURCE_IS_NULL\n";
                    return "";
                }
                shared_ptr < ResourceTexture> t = dynamic_pointer_cast<ResourceTexture>(textureDiff);
                pair<string, ResourceTexture > tResource{ "texture_specular",*t };
                resourceMat->resourcesTexture.push_back(tResource);
                Skip = true;
                break;
            }
        }
        if (!Skip) {
            shared_ptr<Resource> textureSpecular = app->resourceManager->CreateNewResource(str.C_Str(), Resource::Type::Texture);
            TextureImporter::Import(textureSpecular);

            shared_ptr<ResourceTexture> t = dynamic_pointer_cast<ResourceTexture>(textureSpecular);
            pair<string, ResourceTexture > tResource{ "texture_specular",*t };
            resourceMat->resourcesTexture.push_back(tResource);
        }
    }

    Material mat;

    for (const auto& tex : resourceMat->resourcesTexture)
    {
        Texture newTex;
        newTex.uid = tex.second.GetID();
        newTex.path = tex.second.GetAssetPath().string().c_str();
        newTex.type = tex.first;
        mat.textures.push_back(newTex);
    }

    resourceMat->SetLibraryPath("..\\Output\\Library\\Materials\\" + resourceMat->GetID() + ".material");
    MaterialImporter::Save(mat, resourceMat->GetLibraryPath().string().c_str());
    resourceMat->Save();   

    return resourceMat->GetID();
}
void MaterialImporter::Import(shared_ptr<Resource>& resource)
{
}
//
//void MaterialImporter::Import(shared_ptr<Resource>& resource)
//{
//    shared_ptr<ResourceMaterial> resourceMat = static_pointer_cast<ResourceMaterial>(resource);
//   
//}

void MaterialImporter::Load(const Material* mat, const std::string& filename)
{
}

void MaterialImporter::Save(const Material mat, const std::string& filename)
{
    std::ofstream out(filename);

    if (out.is_open())
    {
        out << mat << '\n';
    }
    else {
        cout << "Error saving material: " + filename;
    }
    out.close();
}

//Mesh operators--------------------------------
std::ostream& operator <<(std::ostream& out, const Mesh& mesh)
{
    out << "Vertices:" << mesh.vertices.size() << '\n';
    out << "Indices:" <<  mesh.indices.size() << '\n';
    out << "Material Id:" << mesh.material_UID << '\n';

    for (const auto& v : mesh.vertices)
    {
        out << "<position>" << '[' << v.Position.x << ',' << v.Position.x << ',' << v.Position.x << ']';
        out << "<normals>" << '[' << v.Normal.x << ',' << v.Normal.y << ',' << v.Normal.z << ']';
        out << "<tex coord>" << '[' << v.TexCoords.x << ',' << v.TexCoords.y << ']';
        out << "<color>" << '[' << v.Color.x << ',' << v.Color.y << ',' << v.Color.z << ',' << v.Color.w << ']' << "\n";
    }
    return out;
}
std::ifstream& operator >>(std::ifstream& in, const Mesh& mesh)
{
    return in;
}
void MeshImporter::Save(const Mesh mesh, const std::string& filename)
{

    std::ofstream out(filename);
    if (out.is_open())
    {
        nlohmann::json json_obj;
        for (const auto& v : mesh.vertices)
        {
            nlohmann::json::value vec3Array;
            vec3Array[0] = v.Position.x;
            vec3Array[1] = v.Position.y;
            vec3Array[2] = v.Position.z;
        }
        std::string json_str = json_obj.dump();
        out << json_str.c_str();
    }

    if (out.is_open())
    {
        out << mesh << '\n';
    }
    else {
        cout << "Error saving mesh: " + filename;
    }
    out.close();
}

Mesh* MeshImporter::Import(const aiMesh* mesh, shared_ptr<Resource> resource)
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
    Mesh* newMesh = new Mesh();
    newMesh->vertices = vertices;
    newMesh->indices = indices;
  
    return newMesh;
}

void MeshImporter::Import(shared_ptr<Resource>& resource)
{
    shared_ptr<ResourceMesh> resourceMesh = static_pointer_cast<ResourceMesh>(resource);

}

//Fbx operators--------------------------------
void SceneImporter::Import(shared_ptr<Resource>& resource)
{
    const aiScene* scene = aiImportFile(resource->GetAssetPath().string().c_str(), aiProcessPreset_TargetRealtime_MaxQuality);
    shared_ptr<ResourceScene> rScene = static_pointer_cast<ResourceScene>(resource);

    if (scene != nullptr && scene->HasMeshes())
    { 
        rScene->name = resource->GetAssetPath().stem().string();
        rScene->SetLibraryPath("..\\Output\\Library\\Objects\\" + rScene->GetID() + ".scene");
        GameObject* root = new GameObject(rScene->name);
        rScene->root = root;
        SceneImporter::ProcessaNode(scene->mRootNode, scene, rScene->root, rScene);

        string savePath = rScene->GetLibraryPath().string();
        SceneImporter::Save(*root, savePath);
        rScene->Save();

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
    // process all the node's meshes (if any)  
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        rNode->meshIndex.push_back(i);
        SceneImporter::ProcessaMesh(mesh, scene, rNode,rFbx);
    }
    // then do the same for each of its children
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        GameObject* newNode = new GameObject("n");
        newNode->GetComponent<Transform>().parent = &rNode->GetComponent<Transform>();
        rNode->GetComponent<Transform>().AddChild(&newNode->GetComponent<Transform>());
        rNode->meshCount = node->mNumMeshes;
        rNode->childsCount= node->mNumChildren;
        SceneImporter::ProcessaNode(node->mChildren[i], scene, newNode,rFbx);
    }
}

void SceneImporter::ProcessaMesh(aiMesh* mesh, const aiScene* scene, GameObject* rNode, shared_ptr<ResourceScene>& rFbx)
{   
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
                    NewMaterial = false;
                }
            }   
            if (NewMaterial)
            {
                matId = SceneImporter::ProcessMaterial(mesh, scene, rNode, rFbx);
                if (matId == "") cout << "ERROR::PROCESS_MATERIAL\n";
            }
        }   
    }
    string name = mesh->mName.C_Str();
    shared_ptr<Resource> resourceMesh = app->resourceManager->CreateNewResource("..\\Output\\Assets\\" + name, Resource::Type::Mesh);
    resourceMesh->name = name;

    shared_ptr<ResourceMesh> rm = static_pointer_cast<ResourceMesh>(resourceMesh);
    string savePath = "..\\Output\\Library\\Meshes\\" + rm->GetID() + ".mesh";
    rm->SetLibraryPath(savePath);
    rm->materialIndex = mesh->mMaterialIndex;
    rm->Save();

    Mesh* newMesh = MeshImporter::Import(mesh, resourceMesh);
    newMesh->material_UID = matId;
    MeshImporter::Save(*newMesh, savePath);

    rNode->AddComponent(*newMesh);
    rFbx->meshes.push_back(resourceMesh->GetID());
}
UID  SceneImporter::ProcessMaterial(aiMesh* mesh, const aiScene* scene, GameObject* rNode, shared_ptr<ResourceScene>& rFbx)
{
    //aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
   
    //for (const auto& mat : app->importer->importedMaterials)
    //{
    //    if (mat.first == mesh->mMaterialIndex && mat.second == name)
    //    {
    //        return mat.second;
    //    }
    //}
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
    string name = material->GetName().C_Str();
    shared_ptr<Resource> resourceMat = app->resourceManager->CreateNewResource("..\\Output\\Assets\\" + name, Resource::Type::Material);
    TextureImporter::LoadAiMaterialTextures(material,aiTextureType_DIFFUSE, "texture_diffuse", resourceMat);
    TextureImporter::LoadAiMaterialTextures(material,aiTextureType_SPECULAR, "texture_specular", resourceMat);



    MaterialImporter::Import(material, resourceMat);
    rFbx->materials.push_back(resourceMat->GetID());
    std::pair<int, UID> p{ mesh->mMaterialIndex ,resourceMat->GetID() };
    app->importer->importedMaterials.push_back(p);

    return resourceMat->GetID();
}

std::ostream& operator <<(std::ostream& out, const GameObject& scene)
{
    out << "Components count:" << scene.components.size();
    for (int i = 0; i< scene.components.size(); i++)
    {
        out << "component " << i << ":\n";
        out << "resource active:" << scene.components.at(i).active;
        out <<"resource id:" << scene.components.at(i).resource->GetID();
    }

    return out;
}
void SceneImporter::Save(const GameObject scene, const std::string& filename)
{
    std::ofstream out(filename);
    if (out.is_open())
    {
        out << scene << '\n';
    }
    else {
        cout << "Error saving mesh: " + filename;
    }
    out.close();
}

void SceneImporter::LoadObject(const std::string file_path)
{
}
//
//void SceneImporter::ProcessNode(aiNode* node, const aiScene* scene, GameObject* go, shared_ptr<ResourceScene>& rScene)
//{
//    go->GetComponent<Transform>().localMatrix = node->mTransformation.;
//    // process all the node's meshes (if any)
//    for (unsigned int i = 0; i < node->mNumMeshes; i++)
//    {
//        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
//        parentGo.AddComponent(ProcessMesh(mesh, scene, parentGo));
//    }
//    // then do the same for each of its children
//    for (unsigned int i = 0; i < node->mNumChildren; i++)
//    {
//        GameObject* childGo = new GameObject(rScene->name + std::to_string(i));
//        childGo->GetComponent<Transform>().parent = &parentGo.GetComponent<Transform>();
//        parentGo.GetComponent<Transform>().childs.push_back(&childGo->GetComponent<Transform>());
//        ProcessNode(node->mChildren[i], scene, *childGo, result);
//
//        result.push_back(childGo);
//    }
//}
//
//Mesh SceneImporter::ProcessMesh(aiMesh* mesh, const aiScene* scene, GameObject* go)
//{
//    //temporary varaibles to store the mesh data
//    std::vector<Vertex> vertices;
//    std::vector<unsigned int> indices;
//    std::vector<Texture> textures;
//
//    for (unsigned int vi = 0; vi < mesh->mNumVertices; vi++)
//    {
//        Vertex vertex;
//        vec3 vector;
//        vector.x = mesh->mVertices[vi].x;
//        vector.y = mesh->mVertices[vi].y;
//        vector.z = mesh->mVertices[vi].z;
//        vertex.Position = vector;
//
//        vector.x = mesh->mNormals[vi].x;
//        vector.y = mesh->mNormals[vi].y;
//        vector.z = mesh->mNormals[vi].z;
//        vertex.Normal = vector;
//
//        vec4 color;
//        color.r = 0;
//        color.g = 0;
//        color.b = 0;
//        color.a = 0;
//        vertex.Color = color;
//
//        if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
//        {
//            vec2 vec;
//            vec.x = mesh->mTextureCoords[0][vi].x;
//            vec.y = mesh->mTextureCoords[0][vi].y;
//            vertex.TexCoords = vec;
//        }
//        else
//            vertex.TexCoords = vec2(0.0f, 0.0f);
//
//        vertices.push_back(vertex);
//    }
//
//    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
//    {
//        aiFace face = mesh->mFaces[i];
//        for (unsigned int j = 0; j < face.mNumIndices; j++)
//            indices.push_back(face.mIndices[j]);
//    }
//
//    //load material attached to the obj
//    if (mesh->mMaterialIndex >= 0)
//    {
//        go->AddComponent(ProcessMaterial(mesh, scene));
//    }
//
//    return Mesh(vertices, indices);
//}
//
Material SceneImporter::ProcessMaterial(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Texture> textures;
    //aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
    //std::vector<Texture> diffuseMaps = TextureImporter::LoadAiMaterialTextures(material,
    //    aiTextureType_DIFFUSE, "texture_diffuse");
    //textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    //std::vector<Texture> specularMaps = TextureImporter::LoadAiMaterialTextures(material,
    //    aiTextureType_SPECULAR, "texture_specular");
    //textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

    return Material(textures);
}
