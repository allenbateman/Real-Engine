#include "ResourceMesh.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>


ResourceMesh::ResourceMesh(UID id) : Resource(id)
{
    SetType(Type::Mesh);
}
ResourceMesh::~ResourceMesh()
{

}
std::ostream& operator <<(std::ostream& out, const ResourceMesh& resource)
{
    out << "name:" << resource.name << '\n';
    out << "id:" << resource.GetID().c_str() << "\n";
    out << "assets path:" << resource.GetAssetPath().string() << "\n";
    out << "library path:" << resource.GetLibraryPath().string() << "\n";
    out << "resource type:" << (int)resource.GetType() << "\n";

    out << "material index:" << resource.materialIndex << "\n";
    return out;
}
void ResourceMesh::Save() const
{
    std::ofstream out(assetsPath.string() + ".mesh.meta");
    if (out.is_open())
    {
        out << *this << '\n';
    }
    else {
        std::cout << "Error creating meta file" + uid;
    }
    out.close();
}

void ResourceMesh::Load()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
        &indices[0], GL_STATIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
    // vertex color
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Color));

    glBindVertexArray(0);
}

void ResourceMesh::UnLoad() const
{
}

void ResourceMesh::Load(std::shared_ptr<Resource>& resource, std::ifstream& data)
{
    std::shared_ptr<ResourceMesh> rm = std::static_pointer_cast<ResourceMesh>(resource);


    if (data.is_open())
    {
        //laod vertices
        std::string indices;
        std::getline(data, indices, ':');
        std::getline(data, indices, '\n');

        rm->materialIndex = stoi(indices);
    }

    data.close();
}

void ResourceMesh::LoadMetaData(std::ifstream& data)
{
    if (data.is_open())
    {
        //laod vertices
        std::string indices;
        std::getline(data, indices, ':');
        std::getline(data, indices, '\n');

        materialIndex = stoi(indices);
    }

    data.close();
}

void ResourceMesh::GenerateMetaFile()
{
}
