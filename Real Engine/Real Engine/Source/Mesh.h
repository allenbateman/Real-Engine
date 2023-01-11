#pragma once
#include "Component.h"
//#include "Shader.h"
//#include "Material.h"
#include "ResourceMesh.h"
//RESOUCE

//class Mesh : public  Component
//{
//public:	
//	Mesh();
//	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
//	~Mesh();
//	// mesh data
//	std::vector<Vertex>       vertices;
//	std::vector<unsigned int> indices;
//
//	
//	unsigned int GetVAO() { return VAO; }
//	UID material_UID;
//	void LoadMesh();
//private:
//	unsigned int VAO, VBO, EBO; // idex of the vertex array object in VRam
//
//};
struct  Mesh : public Component
{
	std::shared_ptr<ResourceMesh> resource;
	//void Draw(Shader shader, Material mat)
	//{
 //       unsigned int diffuseNr = 1;
 //       unsigned int specularNr = 1;
 //       for (unsigned int i = 0; i < mat.resource->textures.size(); i++)
 //       {
 //           glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
 //           // retrieve texture number (the N in diffuse_textureN)
 //           std::string number;
 //           std::string name = mat.resource->textures[i].second->type;
 //           if (name == "texture_diffuse")
 //               number = std::to_string(diffuseNr++);
 //           else if (name == "texture_specular")
 //               number = std::to_string(specularNr++);

 //           shader.SetInt(("material." + name + number).c_str(), i);
 //           glBindTexture(GL_TEXTURE_2D, mat.resource->textures[i].second->id);
 //       }
 //       glActiveTexture(GL_TEXTURE0);

 //       // draw meshs
 //       glBindVertexArray(resource->GetVAO());
 //       glDrawElements(GL_TRIANGLES, resource->indices.size(), GL_UNSIGNED_INT, 0);
 //       glBindVertexArray(0);
	//}
};

