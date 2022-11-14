#pragma once
#include <iostream>
#include <vector>
#include "Mesh.h"


struct Cube
{
    Vertex vertex0;
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    Vertex vertex;
    vec3 vector;

    
    std::vector<unsigned int> indices
    {
        //Top
        2, 6, 7,
        2, 3, 7,

        //Bottom
        0, 4, 5,
        0, 1, 5,

        //Left
        0, 2, 6,
        0, 4, 6,

        //Right
        1, 3, 7,
        1, 5, 7,

        //Front
        0, 2, 3,
        0, 1, 3,

        //Back
        4, 6, 7,
        4, 5, 7



    };

    




    //vector.x = mesh->mVertices[vi].x;
    //vector.y = mesh->mVertices[vi].y;
    //vector.z = mesh->mVertices[vi].z;
    //vertex.Position = vector;
    //
    //vector.x = mesh->mNormals[vi].x;
    //vector.y = mesh->mNormals[vi].y;
    //vector.z = mesh->mNormals[vi].z;
    //vertex.Normal = vector;


    std::vector<Vertex> vertices{
        //-1, -1,  0.5, //0
        // 1, -1,  0.5, //1
        //-1,  1,  0.5, //2
        // 1,  1,  0.5, //3
        //-1, -1, -0.5, //4
        // 1, -1, -0.5, //5
        //-1,  1, -0.5, //6
        // 1,  1, -0.5  //7
        vertex, vertex0



    };
};
