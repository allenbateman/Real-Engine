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
        int i, j;
        int indicator = 0;
        Vertex vert;
        vert.Color.r = 255;
        vert.Color.a = 255;
        
        for (i = 0; i <= lats; i++) {
            double lat0 = M_PI * (-0.5 + (double)(i - 1) / lats);            
            double z0 = sin(lat0);
            double zr0 = cos(lat0);

            double lat1 = M_PI * (-0.5 + (double)i / lats);
            double z1 = sin(lat1);
            double zr1 = cos(lat1);

            for (j = 0; j <= longs; j++) {
                double lng = 2 * M_PI * (double)(j - 1) / longs;              
                double x = cos(lng);
                double y = sin(lng);

                

                vert.Position.x = x * zr0;
                vert.Position.y = y * zr0;
                vert.Position.z = z0;

                vertices.push_back(vert);

                /*vertices.push_back(x * zr0);
                vertices.push_back(y * zr0);
                vertices.push_back(z0);*/
                indices.push_back(indicator);
                indicator++;

                vert.Position.x = x * zr1;
                vert.Position.y = y * zr1;
                vert.Position.z = z1;
                vertices.push_back(vert);
                /*vertices.push_back(x * zr1);
                vertices.push_back(y * zr1);
                vertices.push_back(z1);*/
                indices.push_back(indicator);
                indicator++;
            }
            //indices.push_back(GL_PRIMITIVE_RESTART_FIXED_INDEX);


        }
    }
   
};