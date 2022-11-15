#pragma once
#include <iostream>
#include <vector>
#include "Mesh.h"


struct Cube
{
    
      std::vector<Vertex> vertices;
      Vertex tempVertex[8];
    //std::vector<unsigned int> indices;
    std::vector<Texture> textures;


    Cube()
    {
        /*Vertex v;
        vertices.push_back(v);*/
        
        vertices.push_back(tempVertex[0]);
        vertices.push_back(tempVertex[1]);
        vertices.push_back(tempVertex[2]);
        vertices.push_back(tempVertex[3]);
        vertices.push_back(tempVertex[4]);
        vertices.push_back(tempVertex[5]);
        vertices.push_back(tempVertex[6]);
        vertices.push_back(tempVertex[7]);
        

        vertices[0].Position = (-1, -1, 0.5);
        vertices[1].Position = (1, -1, 0.5);
        vertices[2].Position = (-1, 1, 0.5);
        vertices[3].Position = (1, 1, 0.5);
        vertices[4].Position = (-1, -1, -0.5);
        vertices[5].Position = (1, -1, -0.5);
        vertices[6].Position = (-1, 1, -0.5);
        vertices[7].Position = (1, 1, -0.5);
       
        
    }
    
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

    /*std::vector<Vertex> vertices{
        
       vertices[0],
       vertices[1],
       vertices[2],
       vertices[3],
       vertices[4],
       vertices[5],
       vertices[6],
       vertices[7],

    };*/

        //(-1, -1,  0.5), //0
        // (1, -1,  0.5), //1
        //(-1,  1,  0.5), //2
        // (1,  1,  0.5), //3
        //(-1, -1, -0.5), //4
        // (1, -1, -0.5), //5
        //(-1,  1, -0.5), //6
        // (1,  1, -0.5),  //7
};
