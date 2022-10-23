#ifndef SHADER_H
#define SHADER_H


#include <glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "glmath.h"

class Shader {
public:
	//program ID
	unsigned int ID;

	Shader(const char* vertexPath, const char* fragmentPath);
	//use/active shader
	void Use();
	// deactivate sharder setting to default shader
	void StopUse();
	//utillity unifrom functions
	void SetBool(const std::string& name, bool value) const;
	void SetInt(const std::string& name, int value) const;
	void SetFloat(const std::string& name, float value) const;
	void SetMat4(const std::string& name, float* mat4)const;
};
#endif