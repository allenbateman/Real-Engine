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
void ResourceMesh::SaveData()
{
    std::ofstream out;
    out.open(libraryPath);
    if (out.is_open())
    {
        nlohmann::json mesh;
        mesh["num_vertices"] = vertices.size();
        mesh["num_indices"] = indices.size();
        mesh["vertices"] = nlohmann::json::array();
        mesh["indices"] = nlohmann::json::array();
        for (auto vertex : vertices)
        {
            nlohmann::json vertex_obj;
            vertex_obj["position"] = {
                {"x",vertex.Position.x},
                {"y",vertex.Position.y},
                {"z",vertex.Position.z}
            };
            vertex_obj["normal"] = {
                {"x",vertex.Normal.x},
                {"y",vertex.Normal.y},
                {"z",vertex.Normal.z}
            };
            vertex_obj["tex_coord"] = {
                {"x",vertex.TexCoords.x},
                {"y",vertex.TexCoords.y}
            };
            vertex_obj["color"] = {
                {"r",vertex.Color.r},
                {"g",vertex.Color.g},
                {"b",vertex.Color.b},
                {"a",vertex.Color.a}
            };
            mesh["vertices"].push_back(vertex_obj);
        }
        for (auto i : indices)
        {
            mesh["indices"].push_back(i);
        }
        std::string json_str = mesh.dump();
        out << json_str.c_str();
    }

    out.close();
}

void ResourceMesh::LoadData()
{
    std::ifstream in;
    in.open(libraryPath);
    if (in.is_open())
    {
        nlohmann::json mesh;
        in >> mesh;
        unsigned int num_indices = mesh["num_indices"].get<unsigned int>();

        for (const auto& index : mesh["indices"])
        {
            indices.push_back(index.get<unsigned int>());
        }

        for (const auto& vertex : mesh["vertices"])
        {
            Vertex v;
            v.Position.x = vertex["position"]["x"].get<float>();
            v.Position.y = vertex["position"]["y"].get<float>();
            v.Position.z = vertex["position"]["z"].get<float>();

            v.Normal.x = vertex["normal"]["x"].get<float>();
            v.Normal.y = vertex["normal"]["y"].get<float>();
            v.Normal.z = vertex["normal"]["z"].get<float>();

            v.TexCoords.x = vertex["tex_coord"]["x"].get<float>();
            v.TexCoords.y = vertex["tex_coord"]["y"].get<float>();

            v.Color.r = vertex["color"]["r"].get<float>();
            v.Color.g = vertex["color"]["g"].get<float>();
            v.Color.b = vertex["color"]["b"].get<float>();
            v.Color.a = vertex["color"]["a"].get<float>();

            vertices.push_back(v);
        }
    }
    in.close();
}

void ResourceMesh::Load()
{
    if (IsLoaded)return;

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
    
    IsLoaded = true;
}

void ResourceMesh::UnLoad()
{
}

void ResourceMesh::Draw(std::shared_ptr<ResourceShader> shader, std::shared_ptr < ResourceMaterial> material)
{
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    for (unsigned int i = 0; i < material->textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        std::string number;
        std::string name = material->textures[i].second->type;
        if (name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if (name == "texture_specular")
            number = std::to_string(specularNr++);

        shader->SetInt(("material." + name + number).c_str(), i);
        glBindTexture(GL_TEXTURE_2D, material->textures[i].second->id);
    }
    glActiveTexture(GL_TEXTURE0);

    // draw meshs
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
