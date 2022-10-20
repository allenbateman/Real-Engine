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

        ////bind frame buffer
        //glGenVertexArrays(1, &VAO);
        //glGenBuffers(1, &VBO);
        //glGenBuffers(1, &EBO);
        //glBindVertexArray(VAO);
        //// load data into vertex buffers
        //glBindBuffer(GL_ARRAY_BUFFER, VBO);
        //glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(BoneVertex), &vertices[0], GL_STATIC_DRAW);
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        //glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

        //// set the vertex attribute pointers
        //// vertex Positions
        //glEnableVertexAttribArray(0);
        //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(BoneVertex), (void*)0);
        //// vertex texture coords
        //glEnableVertexAttribArray(2);
        //glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(BoneVertex), (void*)offsetof(BoneVertex, texCoords));

        ////reset
        //glBindVertexArray(0);

      /*  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete! \n";*/
        aiReleaseImport(scene);
    }
    else
    {
        std::cout << aiGetErrorString();
        LOG(aiGetErrorString());
    }
    return ret;
}
