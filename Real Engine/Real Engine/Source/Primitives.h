#pragma once
#include <iostream>
#include <vector>
#include "Mesh.h"

const static std::vector<vec3> vert =
{
            //Back
            (-0.5f,0.5f,-0.5f),
            (-0.5f,-0.5f,-0.5f),
            (0.5f,-0.5f,-0.5f),
            (0.5f,0.5f,-0.5f),

            //Front
            (-0.5f,0.5f,0.5f),
            (-0.5f,-0.5f,0.5f),
            (0.5f,-0.5f,0.5f),
            (0.5f,0.5f,0.5f),

            //Right
            (0.5f,0.5f,-0.5f),
            (0.5f,-0.5f,-0.5f),
            (0.5f,-0.5f,0.5f),
            (0.5f,0.5f,0.5f),

            //Left
            (-0.5f,0.5f,-0.5f),
            (-0.5f,-0.5f,-0.5f),
            (-0.5f,-0.5f,0.5f),
            (-0.5f,0.5f,0.5f),

            //Top
            (-0.5f,0.5f,0.5f),
            (-0.5f,0.5f,-0.5f),
            (0.5f,0.5f,-0.5f),
           (0.5f,0.5f,0.5f),

           //Bottom
            (-0.5f,-0.5f,0.5f),
            (-0.5f,-0.5f,-0.5f),
            (0.5f,-0.5f,-0.5f),
            (0.5f,-0.5f,0.5f)
            
            
};
//const static std::vector<GLuint> ind =
//{
//            0,1,3,
//            3,1,2,
//            4,5,7,
//            7,5,6,
//            8,9,11,
//            11,9,10,
//            12,13,15,
//            15,13,14,
//            16,17,19,
//            19,17,18,
//            20,21,23,
//            23,21,22
//};

//const static std::vector<GLuint> texCords =
//{
//            0,0,
//            0,1,
//            1,1,
//            1,0,
//            0,0,
//            0,1,
//            1,1,
//            1,0,
//            0,0,
//            0,1,
//            1,1,
//            1,0,
//            0,0,
//            0,1,
//            1,1,
//            1,0,
//            0,0,
//            0,1,
//            1,1,
//            1,0,
//            0,0,
//            0,1,
//            1,1,
//            1,0
//};
struct Cube
{
    
    std::vector<Vertex> vertices;
    Vertex tempVertex[24];
    std::vector<Texture> textures;


    Cube()
    {
        for (int i = 0; i < 24; i++)
        {
            vertices.push_back(tempVertex[i]);
        }
        
       
        for (int i = 0; i < 24; i++)
        {
            vertices[i].Position = vert[i];
        }
       
      
         vec3 normals[6] =
        {
           vec3 (0,0,-1),//Back
           vec3(0,0,1), //Front
            vec3(1,0,0), //Right
            vec3(-1,0,0),//Left
            vec3(0,1,0), //Top
            vec3(0,-1,0) //Bottom

        };
         
         
        
        for (int i = 0; i < 6; i++)
        {
            vertices[i * 4 + 0].Normal = normals[i];
            vertices[i * 4 + 1].Normal = normals[i];
            vertices[i * 4 + 2].Normal = normals[i];
            vertices[i * 4 + 3].Normal = normals[i];

        }
        
        vec2 texCoords[4] =
        {
            vec2(0, 0),
            vec2(1, 0),
            vec2(1, 1),
            vec2(0, 1)
        };
       
        /*int texInds[6] = { 0, 1, 3, 3, 1, 2 };
        float textureBuffer[12 * 6];
        for (int i = 0; i < 36; i++) {
            textureBuffer[i * 2 + 0] = texCoords[texInds[i % 4]].x;
            textureBuffer[i * 2 + 1] = texCoords[texInds[i % 4]].y;
        }
        for (int i = 0; i < 36; i++)
        {
            vertices[i/ 6].TexCoords.x = textureBuffer[i * 2 + 0];
            vertices[i / 6].TexCoords.x = textureBuffer[i * 2 + 1];
        }*/
        int counter = 0;
        for (int i = 0; i < 24; i++ )
        {
            vertices[i].TexCoords = texCoords[counter];
            if (counter >= 3) counter = 0;
            else counter++;
            
        }


    }
    ~Cube()
    {
        vertices.clear();
    }
        /*vertices[0].TexCoords = texCords[texInds[0]]*/


    
    const  std::vector<unsigned int> indices 
    {
                0,1,3,
                3,1,2,
                4,5,7,
                7,5,6,
                8,9,11,
                11,9,10,
                12,13,15,
                15,13,14,
                16,17,19,
                19,17,18,
                20,21,23,
                23,21,22
    };
    //std::vector<unsigned int> indices
    //{
    //    //Top
    //    2, 6, 7,
    //    2, 3, 7,

    //    //Bottom
    //    0, 4, 5,
    //    0, 1, 5,

    //    //Left
    //    0, 2, 6,
    //    0, 4, 6,

    //    //Right
    //    1, 3, 7,
    //    1, 5, 7,

    //    //Front
    //    0, 2, 3,
    //    0, 1, 3,

    //    //Back
    //    4, 6, 7,
    //    4, 5, 7

    //};

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
    

    

    /*std::vector <unsigned int> vertices[8] =
    {
        Vector3f(-1, -1, -1),
        Vector3f(1, -1, -1),
        Vector3f(1, 1, -1),
        Vector3f(-1, 1, -1),
        Vector3f(-1, -1, 1),
        Vector3f(1, -1, 1),
        Vector3f(1, 1, 1),
        Vector3f(-1, 1, 1)
    };

    Vector2f texCoords[4] =
    {
        Vector2f(0, 0),
        Vector2f(1, 0),
        Vector2f(1, 1),
        Vector2f(0, 1)
    };

    Vector3f normals[6] =
    {
        Vector3f(0, 0, 1),
        Vector3f(1, 0, 0),
        Vector3f(0, 0, -1),
        Vector3f(-1, 0, 0),
        Vector3f(0, 1, 0),
        Vector3f(0, -1, 0)
    };

    int indices[6 * 6] =
    {
        0, 1, 3, 3, 1, 2,
        1, 5, 2, 2, 5, 6,
        5, 4, 6, 6, 4, 7,
        4, 0, 7, 7, 0, 3,
        3, 2, 7, 7, 2, 6,
        4, 5, 0, 0, 5, 1
    };

    int texInds[6] = { 0, 1, 3, 3, 1, 2 };

    float vertexBuffer[18 * 6];
    for (int i = 0; i < 36; i++) {
        vertexBuffer[i * 3 + 0] = vertices[indices[i]].x;
        vertexBuffer[i * 3 + 1] = vertices[indices[i]].y;
        vertexBuffer[i * 3 + 2] = vertices[indices[i]].z;
    }

    float textureBuffer[12 * 6];
    for (int i = 0; i < 36; i++) {
        textureBuffer[i * 2 + 0] = texCoords[texInds[i % 4]].x;
        textureBuffer[i * 2 + 1] = texCoords[texInds[i % 4]].y;
    }

    float normalBuffer[18 * 6];
    for (int i = 0; i < 36; i++) {
        normalBuffer[i * 3 + 0] = normals[indices[i / 6]].x;
        normalBuffer[i * 3 + 1] = normals[indices[i / 6]].y;
        normalBuffer[i * 3 + 2] = normals[indices[i / 6]].z;
    }*/
};
