#pragma once
#include <iostream>
#include <vector>
#include "Mesh.h"


struct Cube
{
    
    const std::vector<vec3> pos =
    {
       vec3 (-1.0f, 1.0f, -1.0f),
       vec3(-1.0f, -1.0f, -1.0f),
       vec3(1.0f, -1.0f, -1.0f ),
       vec3(1.0f, 1.0f, -1.0f  ),

       vec3(-1.0f, 1.0f, 1.0f  ),
       vec3(-1.0f, -1.0f, 1.0f ),
       vec3(1.0f, -1.0f, 1.0f  ),
       vec3( 1.0f, 1.0f, 1.0f  )
    };

    std::vector<Vertex> vertices;
    Vertex tempVertex[8];
    std::vector<Texture> textures;


    Cube()
    {
        for (int i = 0; i < 8; i++)
        {
            vertices.push_back(tempVertex[i]);
        }
        
        for (int i = 0; i < 8; i++)
        {
            vertices[i].Position.x = pos[i].x;
            vertices[i].Position.y = pos[i].y;
            vertices[i].Position.z = pos[i].z;
        }
        for (int i = 0; i < 8; i++)
        {
            vertices[i].Color.r = 255;
            vertices[i].Color.g = 0;
            vertices[i].Color.b = 155;
            vertices[i].Color.a = 255;
        }
       
        
    }
    ~Cube()
    {
        vertices.clear();
    }
        


    const  std::vector<unsigned int> indices
    {
      //Back
      2,1,0,
      0,3,2,
      //Bottom
      1,2,6,
      5,1,6,
      //Left
      4,0,1,
      1,5,4,
      //Right
      3,7,6,
      6,2,3,
      //Top
      0,4,7,
      3,0,7,
      //Front
      4,5,6,
      4,6,7,

    };
    
};
