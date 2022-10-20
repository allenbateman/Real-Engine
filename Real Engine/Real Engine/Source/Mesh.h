#pragma once
#include "Component.h"



class Mesh : public Component
{
public:
	Mesh();
	~Mesh();
	
	unsigned int id_index = 2; // index in VRAM
	unsigned int num_index = 0;
	unsigned int* index = nullptr;
	unsigned int id_vertex = 2; // unique vertex in VRAM
	unsigned int num_vertices = 0;
	float* vertices = nullptr;
	
};

