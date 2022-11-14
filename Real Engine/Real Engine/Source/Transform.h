#pragma once
#include "Component.h"

class GameObject;

struct Transform : public  Component
{

	//properties

	vec3 localPosition{0,0,0};
	vec4 localRotation{0,0,0,0};
	vec3 localScale{0,0,0};

	vec3 position{ 0,0,0 };		//Stores position x,y,z
	vec4 rotation{ 0,0,0,0 };	//Quaternion that stores rotation x,y,z,w
	vec3 scale{ 1,1,1 };	    //Stores scale x,y,z

	mat4x4 transform;		//Stores transformation of the object in a matrix from parent reference
	mat4x4 worldMatrix;		//Stores transformation of the object in a matrix from world reference


	vec3 forward{0,0,1};	//stores normalized vector z
	vec3 up{0,1,0};			//stores normalized vector z
	vec3 right{1,0,0};		//stores normalized vector z

	vec3 eulerAngles;		//Stores rotation in euler angles x,y,z
	vec3 localEulerAngles;

	//herarchy data
	Transform* parent = nullptr;
	std::vector<Transform*> childs;

	GameObject* owner = nullptr;


	void SetParent(Transform* newParent)
	{
		for (auto& c : childs)
		{
			if (c != newParent)
			{
				parent = newParent;
				return;
			}
		}
		parent = newParent;
	}

	bool AddChild(Transform* child)
	{
		//check if the child does already exist 
		for (auto& c : childs)
		{
			if (c == child)
				return false;
		}
		// check that the child is not his own parent
		if (child != parent)
		{
			childs.push_back(child);
			return true;
		}

		return false;
	}

	void RemoveChild(const Transform& target)
	{
		for (std::vector<Transform*>::iterator it = childs.begin(); it != childs.end(); it++)
		{
			if ((*it)->owner == target.owner)
			{
				childs.erase(it);
				break;
			}

		}
	}
	void Translate(float x, float y, float z) {

		for (auto &c : childs)
		{
			c->Translate(position.x + x, position.y + y, position.z + z);
		}

		transform.translate(x, y, z);
	}

	vec3 Position()
	{
		transform = transform * parent->transform;

		return transform.translation();
	}

	//vec3 Rotation()
	//{
	//	return localMatrix.rotario
	//}

};

