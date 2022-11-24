#pragma once
#include <iostream>
#include <vector>
#include <math.h>
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

struct Sphere
{
    std::vector<Vertex> vertices;
    Vertex tempVertex[8];
    std::vector<Texture> textures;
    std::vector<unsigned int> indices;

    double lats = 100;
    double longs = 100;
    double radius = 2;

    ~Sphere()
    {
        vertices.clear();
    }
    Sphere()
    {
        
        for (int i = 0; i <= lats; ++i) {

            float V = i / (float)lats;
            float phi = V * M_PI;

           
            for (int j = 0; j <= longs; ++j) {

                float U = j / (float)longs;
                float theta = U * (M_PI* 2);
                
                float x = cosf(theta) * sinf(phi);
                float y = cosf(phi);
                float z = sinf(theta) * sinf(phi);

                Vertex vert;
                vert.Color.r = 255;
                vert.Color.g = 0;
                vert.Color.b = 155;
                vert.Color.a = 255;

                vert.Position.x = x;
                vert.Position.y = y;
                vert.Position.z = z;
                vert.Position* radius;
                vertices.push_back(vert);
            }
        }
      
        for (int i = 0; i < longs * lats + longs; ++i) {

            indices.push_back(i);
            indices.push_back(i + longs + 1);
            indices.push_back(i + longs);

            indices.push_back(i + longs + 1);
            indices.push_back(i);
            indices.push_back(i + 1);
        }
    }
   
};