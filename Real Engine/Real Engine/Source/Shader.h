#ifndef SHADER_H
#define SHADER_H
#include <GL/glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>
#include "glmath.h"
#include "ResourceShader.h"
struct Shader {
	std::shared_ptr<ResourceShader> resource;
};
#endif