#pragma once
#include "Component.h"
class Transform :  public Component
{
	mat4x4 transform; //Stores whole transformation of the object in a matrix
	vec3 position; //Stores position x,y,z
	vec4 rotation; //Quaternion that stores rotation x,y,z,w
	vec3 scale;	   //Stores scale x,y,z
	vec3 forward; //stores normalized vector z
	vec3 eulerAngles; //Stores rotation in euler angles x,y,z

	vec3 GetEulerAngles();
	vec3 GetPosition();
	vec3 GetSize();
};

