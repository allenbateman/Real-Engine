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

struct Sphere
{
    std::vector<Vertex> vertices;
    Vertex tempVertex[8];
    std::vector<Texture> textures;
    std::vector<unsigned int> indices;

    double latitudeBands = 30;
    double longitudeBands = 30;
    double radius = 2;

    ~Sphere()
    {
        vertices.clear();
    }
    Sphere()
    {
        for (int i = 0; i < 8; i++)
        {
            //vertices.push_back(tempVertex[i]);
        }

        for (double latNumber = 0; latNumber <= latitudeBands; latNumber++) {
            double theta = latNumber * M_PI / latitudeBands;
            double sinTheta = sin(theta);
            double cosTheta = cos(theta);

            for (double longNumber = 0; longNumber <= longitudeBands; longNumber++) {
                double phi = longNumber * 2 * M_PI / longitudeBands;
                double sinPhi = sin(phi);
                double cosPhi = cos(phi);

                Vertex vs[3];
                vs[0].Normal = cosPhi * sinTheta;   // x
                vs[1].Normal = cosTheta;            // y
                vs[2].Normal = sinPhi * sinTheta;   // z
                vs[0].TexCoords = 1 - (longNumber / longitudeBands); // u
                vs[1].TexCoords = 1 - (latNumber / latitudeBands);   // v
                vs[0].Position = radius * vs[0].Normal;
                vs[1].Position = radius * vs[1].Normal;
                vs[2].Position = radius * vs[2].Normal;
                vs[0].Color.r = 255;
                vs[0].Color.a = 255;
                vs[1].Color.r = 255;
                vs[1].Color.a = 255;
                vs[2].Color.r = 255;
                vs[2].Color.a = 255;

                vertices.push_back(vs[0]);
                vertices.push_back(vs[1]);
                vertices.push_back(vs[2]);
            }

            for (int latNumber = 0; latNumber < latitudeBands; latNumber++) {
                for (int longNumber = 0; longNumber < longitudeBands; longNumber++) {
                    int first = (latNumber * (longitudeBands + 1)) + longNumber;
                    int second = first + longitudeBands + 1;

                    
                    indices.push_back(first);
                    indices.push_back(second);
                    indices.push_back(first + 1);

                    indices.push_back(second);
                    indices.push_back(second + 1);
                    indices.push_back(first + 1);

                }
            }


        }
    }
   
};