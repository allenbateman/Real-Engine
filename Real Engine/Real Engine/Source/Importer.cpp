#include "Importer.h"
#include "EntityComponentSystem.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <filesystem>
#include "EventSystem.h"
#include "Events.h"
#include "Debugger.h"
#include "TextureLoader.h"
#include <sstream>
#include <string>

#include "ResourceTexture.h"

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
Texture* TextureImporter::Load(const std::string& filename)
{
    std::ifstream texFile(filename);
    Texture* loadTex = new Texture();
    if (texFile.is_open())
    {
        texFile >> *loadTex;
    }
    return loadTex;
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
}

void TextureImporter::Import(Resource* resource)
{

    string id = resource->GetID();

    bool skip = false;
    for (unsigned int j = 0; j < app->importer->loadedtextures.size(); j++)
    {
        if (std::strcmp(app->importer->loadedtextures[j].path.data(), id.c_str()) == 0)
        {
            // app->importer->loadedtextures[j];
  
            skip = true;
            break;
        }
    }
    if (!skip)
    {
        if (ilLoadImage(resource->GetAssetPath()))
        {
            cout << "Texture id: " <<  id << " loaded with devIL" << endl;
        }
        else {
            cout << "Image not loaded with devIL" << endl;
        }

        Texture texture;
        ILubyte* data = ilGetData();
        ILuint width = ilGetInteger(IL_IMAGE_WIDTH), height = ilGetInteger(IL_IMAGE_HEIGHT);
        ILuint depth = ilGetInteger(IL_IMAGE_DEPTH);
        ILubyte channels = ilGetInteger(IL_IMAGE_CHANNELS);
        ILenum format = ilGetInteger(IL_IMAGE_FORMAT);
        ILenum type = ilGetInteger(IL_IMAGE_TYPE);

        ResourceTexture* rt = static_cast<ResourceTexture*>(resource);

        rt->width = width;
        rt->height = height;
        rt->depth = depth;
        rt->channels = channels;
        rt->format = format;
        rt->type = type;

        string storePath = LIBRARY_DIR + id + ".dds";

        if (ilSave(IL_DDS, storePath.c_str()))
            cout << "saved file with devil\n";
        else
            cout << "could not save file with devil \n";

        
    }
}


std::vector<Texture> TextureImporter::Import(const aiMaterial* mat, aiTextureType type, std::string typeName)
{
    std::vector<Texture> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);

        string filepath = app->importer->directory + "/" + str.C_Str();
        string filename = str.C_Str();

        bool skip = false;
        for (unsigned int j = 0; j < app->importer->loadedtextures.size(); j++)
        {
            if (std::strcmp(app->importer->loadedtextures[j].path.data(), str.C_Str()) == 0)
            {
                textures.push_back(app->importer->loadedtextures[j]);
                skip = true;
                break;
            }
        }
        if (!skip)
        {
            if (ilLoadImage(filepath.c_str()))
            {
                cout << "Texture: " << str.C_Str() << " loaded with devIL" << endl;
            }
            else {
                cout << "Image not loaded with devIL" << endl;
            }

            // if texture hasn't been loaded already, load it
            Texture texture;

            //for textures
            string fileName = filename.substr(0, filename.find_last_of('.'));
            cout << fileName << endl;
            string storePath = LIBRARY_DIR + fileName + ".dds";
            cout << storePath << endl;

            if (ilSave(IL_DDS, storePath.c_str()))
                cout << "saved file with devil\n";
            else
                cout << "could not save file with devil \n";


            texture.id = LoadTexture(app->importer->directory + "/" + str.C_Str());

            texture.path = app->importer->directory + "/" + str.C_Str();
            texture.type = typeName;
            textures.push_back(texture);
            app->importer->loadedtextures.push_back(texture); // add to loaded textures
        }
    }
    return textures;
}

//Material operators--------------------------------
std::ostream& operator <<(std::ostream& out, const Material& material)
{
    out << "header\n";
    out << "<textures>" << '[' << material.textures.size() << ']' << '\n';
    out << "<active>" << '[' << material.active << ']' << '\n';

    vector<Texture>::const_iterator t = material.textures.begin();
    while (t != material.textures.end())
    {
        out << "<id>" << '[' << t->id << "]" << "<type>" << '[' << t->type << ']' << "<path>" << '[' << t->path << ']' << '\n';
    }
    return out;
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
}

void MaterialImporter::Import(const aiMaterial* material, Material* ourMaterial)
{
    std::vector<Texture> textures;
    std::vector<Texture> diffuseMaps = TextureImporter::Import(material,
        aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    std::vector<Texture> specularMaps = TextureImporter::Import(material,
        aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

    ourMaterial = new Material(textures);
}

//Mesh operators--------------------------------
std::ostream& operator <<(std::ostream& out, const Mesh& mesh)
{
    out << "<Vertices>" << '[' << mesh.vertices.size() << ']';
    out << "<Indices>" << '[' << mesh.indices.size() << ']';
    out << "<Material Id>" << '[' << mesh.MatId << ']' << '\n';

    for (const auto& v : mesh.vertices)
    {
        out << "<position>" << '[' << v.Position.x << ',' << v.Position.x << ',' << v.Position.x << ']';
        out << "<noramls>" << '[' << v.Normal.x << ',' << v.Normal.y << ',' << v.Normal.z << ']';
        out << "<tex coord>" << '[' << v.TexCoords.x << ',' << v.TexCoords.y << ']';
        out << "<color>" << '[' << v.Color.x << ',' << v.Color.y << ',' << v.Color.z << ',' << v.Color.w << ']';
    }
    return out;
}
std::ifstream& operator >>(std::ifstream& in, const Mesh& mesh)
{
    return in;
}
void MeshImporter::Save(const Mesh mesh, const std::string& filename)
{

    std::ofstream out("../Output/Library/Mesh/" + filename);
    if (out.is_open())
    {
        out << mesh << '\n';
    }
    else {
        cout << "Error saving mesh: " + filename;
    }
}

Mesh* MeshImporter::Import(const aiMesh* mesh)
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

    return new Mesh(vertices, indices);
}

//Fbx operators--------------------------------
void FbxImporter::Import(const std::string& file_path)
{
    const aiScene* scene = aiImportFile(file_path.c_str(), aiProcessPreset_TargetRealtime_MaxQuality);

    if (scene != nullptr && scene->HasMeshes())
    {
        app->importer->directory = file_path.substr(0, file_path.find_last_of('/'));

        std::size_t from = file_path.find_last_of('/');
        std::size_t to = file_path.find_last_of('.');
        fbxName = file_path.substr(from + 1, to);
        fbxName = fbxName.substr(0, fbxName.find_last_of('.'));
        vector<Mesh> meshes;
        FbxImporter::ProcessNode(scene->mRootNode, scene, &meshes);
        aiReleaseImport(scene);

    }
    else
    {
        std::cout << aiGetErrorString();
        LOG(aiGetErrorString());
    }
}

void FbxImporter::ProcessNode(aiNode* node, const aiScene* scene, vector<Mesh>* meshes)
{
    // process all the node's meshes (if any)  
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        Mesh* ourMesh = FbxImporter::ProcessMesh(mesh, scene);
        meshes->push_back(*ourMesh);
        MeshImporter::Save(*ourMesh, fbxName + std::to_string(i) + ".mesh");
    }
    // then do the same for each of its children
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        FbxImporter::ProcessNode(node->mChildren[i], scene, meshes);
    }
}

Mesh* FbxImporter::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
    //load material attached to the obj
    if (mesh->mMaterialIndex >= 0)
    {
        FbxImporter::ProcessMaterial(mesh, scene);
    }

    return  MeshImporter::Import(mesh);
}

Material FbxImporter::ProcessMaterial(aiMesh* mesh, const aiScene* scene)
{
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
    Material ourMaterial;
    MaterialImporter::Import(material, &ourMaterial);
    return ourMaterial;
}
