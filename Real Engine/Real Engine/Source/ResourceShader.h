#pragma once
#include "Resource.h"
#include <GL/glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <variant>
#include <unordered_map>
#include "glmath.h"
#include <ImGui/imgui.h>
#include <ImGui/backends/imgui_impl_glfw.h>
#include <ImGui/backends/imgui_impl_opengl3.h>

using UniformValue = std::variant<int,float,vec2,vec3, bool, double,unsigned int, std::string>;
struct Uniform
{
	std::string name;
	UniformValue value;
	GLint location;
	GLenum type;
};

class ResourceShader : public Resource
{
public:
	ResourceShader(UID uid);
	ResourceShader();
	~ResourceShader();
	void SaveData();
	void LoadData();
	void Load();
	void UnLoad();
	bool Load(const char* vertexPath, const char* fragmentPath);
	//use/active shader
	void Use();
	// deactivate sharder setting to default shader
	void StopUse();
	//utillity unifrom functions
	void SetBool(const std::string& name, bool value) const;
	void SetInt(const std::string& name, int value) const;
	void SetFloat(const std::string& name, float value) const;
	void SetVec2(const std::string& name, vec2& value) const;
	void SetVec3(const std::string& name, vec3& value) const;
	void SetMat4(const std::string& name, float* mat4)const;

	static void SetShaderUniform(GLuint shaderProgram, const char* uniformName, float value);
	void LoadActiveUniforms();
	void UpdateUniformValues();
	void LoadUniform(std::string location);
	std::vector<Uniform> uniforms;

	void SetUniformValue(std::string name, UniformValue value,GLint location,GLenum type) {
		for (auto& uniform : uniforms) {
			if (uniform.name == name) {
				uniform.value = value;
				uniform.location = location;
				uniform.type = type;
				return;
			}
		}
		// If uniform not found, add it to the list
		uniforms.push_back({ name, value, location, type });
	}

public:
	//program ID
	unsigned int ID;
	std::filesystem::path vertex;
	std::filesystem::path fragment;
};
