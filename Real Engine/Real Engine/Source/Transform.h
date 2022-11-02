#pragma once
#include "Component.h"
struct Transform
{
	vec3 position{0,0,0}; //Stores position x,y,z
	vec4 rotation{0,0,0}; //Quaternion that stores rotation x,y,z,w
	vec3 scale{1,1,1};	   //Stores scale x,y,z
	vec3 forward{0,0,1}; //stores normalized vector z
	vec3 up{0,1,0}; //stores normalized vector z
	vec3 right{1,0,0}; //stores normalized vector z
	vec3 eulerAngles; //Stores rotation in euler angles x,y,z
	mat4x4 transform; //Stores whole transformation of the object in a matrix
	mat4x4 localWorldMatrix; //Stores whole transformation of the object in a matrix
	vec3 GetEulerAngles() {return eulerAngles;};
	vec3 GetPosition() { return position; };
	vec3 GetSize() { return scale; };
};

