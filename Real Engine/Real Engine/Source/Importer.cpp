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
        out << tex << '\n';
    }
    else {
        cout << "Error saving texture: " + filename;
    }

    out.close();
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
       // return ;
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
    out << "header\n";
    out << "<textures>" << '[' << material.textures.size() << ']' << '\n';
    vector<Texture>::const_iterator t = material.textures.begin();
    while (t != material.textures.end())
    {
        out << "<id>" << '[' << t->id << "]" << "<type>" << '[' << t->type << ']' << "<path>" << '[' << t->path << ']' << '\n';
        t++;
    }
    return out;
}
int MaterialImporter::Import(const aiMaterial* material, shared_ptr<Resource> resource)
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
                    return -1;
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
                    return -1;
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

        newTex.path = tex.second.GetAssetPath().string().c_str();
        newTex.type = tex.first;
        mat.textures.push_back(newTex);
    }

    resourceMat->SetLibraryPath("..\\Output\\Library\\Materials\\" + resourceMat->GetID() + ".material");
    MaterialImporter::Save(mat, resourceMat->GetLibraryPath().string().c_str());
    resourceMat->Save();   

    return -1;
}

void MaterialImporter::Import(shared_ptr<Resource>& resource)
{
    shared_ptr<ResourceMaterial> resourceMat = static_pointer_cast<ResourceMaterial>(resource);
   
}

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
        cout << "Error importing material: " + filename;
    }
    out.close();
}

//Mesh operators--------------------------------
std::ostream& operator <<(std::ostream& out, const Mesh& mesh)
{
    out << "Vertices:" << mesh.vertices.size() << '\n';
    out << "Indices:" <<  mesh.indices.size() << '\n';
    out << "Material Id:" << mesh.MatId << '\n';

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
    Mesh newMesh;
    newMesh.vertices = vertices;
    newMesh.indices = indices;
    newMesh.MatId = mesh->mMaterialIndex;
  
    shared_ptr<ResourceMesh> rm = static_pointer_cast<ResourceMesh>(resource);
    string savePath = "..\\Output\\Library\\Meshes\\" + rm->GetID() + ".mesh";

    rm->SetLibraryPath(savePath);

    MeshImporter::Save(newMesh, savePath);

    rm->materialIndex = mesh->mMaterialIndex;
    rm->Save();

    return &newMesh;
}

void MeshImporter::Import(shared_ptr<Resource>& resource)
{
    shared_ptr<ResourceMesh> resourceMesh = static_pointer_cast<ResourceMesh>(resource);

}

//Fbx operators--------------------------------
void FbxImporter::Import(shared_ptr<Resource>& resource)
{
    const aiScene* scene = aiImportFile(resource->GetAssetPath().string().c_str(), aiProcessPreset_TargetRealtime_MaxQuality);
    shared_ptr<ResourceFbx> fbx = static_pointer_cast<ResourceFbx>(resource);
    if (scene != nullptr && scene->HasMeshes())
    { 
        fbx->name = resource->GetAssetPath().stem().string();
        fbx->SetLibraryPath("..\\Output\\Library\\Objects\\" + fbx->GetID() + ".object");
        FbxNode* root = (struct FbxNode*)malloc(1 * sizeof(struct FbxNode));
        FbxNode* c = (struct FbxNode*)malloc(MAX_CHILDS * sizeof(struct FbxNode));
        root->childs.push_back(*c);
        root->meshIndex = (unsigned int*)malloc(1 * sizeof(unsigned int));
        fbx->root = root;
        FbxImporter::ProcessaNode(scene->mRootNode, scene,fbx->root,fbx );

        fbx->Save();
        free(root);
      //  free(c);

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

void FbxImporter::ProcessaNode(aiNode* node, const aiScene* scene, FbxNode* rNode, shared_ptr<ResourceFbx>& rFbx)
{
   
    // process all the node's meshes (if any)  
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        rNode->meshIndex[i] = i;
        FbxImporter::ProcessaMesh(mesh, scene, rNode,rFbx);
    }
    // then do the same for each of its children
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        FbxNode* newNode = (struct FbxNode*)malloc(1 * sizeof(struct FbxNode));
        FbxNode* c = (struct FbxNode*)malloc(MAX_CHILDS * sizeof(struct FbxNode));
        newNode->parent = rNode;
        newNode->childs.push_back(*c);
        newNode->meshIndex = new unsigned int();
        rNode->childs[i] = *newNode;
        rNode->meshCount = node->mNumMeshes;
        rNode->childsCount= node->mNumChildren;
        FbxImporter::ProcessaNode(node->mChildren[i], scene, &rNode->childs[i],rFbx);
        free(newNode);
        free(c);
    }
}

void FbxImporter::ProcessaMesh(aiMesh* mesh, const aiScene* scene, FbxNode* rNode, shared_ptr<ResourceFbx>& rFbx)
{
    int matId;
    //load material attached to the obj
    if (mesh->mMaterialIndex >= 0)
    {
        matId = FbxImporter::ProcessMaterial(mesh, scene, rNode, rFbx);
        if (matId == -1) cout << "ERROR::PROCESS_MATERIAL\n";
    }
    string name = mesh->mName.C_Str();
    shared_ptr<Resource> resourceMesh = app->resourceManager->CreateNewResource("..\\Output\\Assets\\" + name, Resource::Type::Mesh);
    resourceMesh->name = name;
    MeshImporter::Import(mesh, resourceMesh)->MatId = matId;
    rFbx->meshes.push_back(resourceMesh->GetID());
    rNode->meshIndex = (unsigned int*)rFbx->meshes.size();
    rNode->meshIndex++;

}
int  FbxImporter::ProcessMaterial(aiMesh* mesh, const aiScene* scene, FbxNode* rNode, shared_ptr<ResourceFbx>& rFbx)
{
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
    string name = material->GetName().C_Str();
    for (const auto& mat : app->importer->importedMaterials)
    {
        if (mat.first == mesh->mMaterialIndex && mat.second.stem() == name)
        {
            return mat.first;
        }
    }

    shared_ptr<Resource> resourceMat = app->resourceManager->CreateNewResource("..\\Output\\Assets\\" + name, Resource::Type::Material);
    resourceMat->name = name;
    MaterialImporter::Import(material, resourceMat);
    rFbx->materials.push_back(resourceMat->GetID());
    std::pair<int, UID> p{ mesh->mMaterialIndex ,resourceMat->GetID() };
    app->importer->importedMaterials.push_back(p);

    return mesh->mMaterialIndex;
}
