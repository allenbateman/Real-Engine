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
//class Shader {
//public:
//	//program ID
//	unsigned int ID;
//
//	Shader();
//	Shader(const char* vertexPath, const char* fragmentPath);
//	bool Load(const char* vertexPath, const char* fragmentPath);
//	//use/active shader
//	void Use();
//	// deactivate sharder setting to default shader
//	void StopUse();
//	//utillity unifrom functions
//	void SetBool(const std::string& name, bool value) const;
//	void SetInt(const std::string& name, int value) const;
//	void SetFloat(const std::string& name, float value) const;
//	void SetMat4(const std::string& name, float* mat4)const;
//
//	static void SetShaderUniform(GLuint shaderProgram, const char* uniformName, float value);
//	static std::unordered_map<std::string, float> GetShaderUniforms(GLuint shaderProgram);
//};
#endif