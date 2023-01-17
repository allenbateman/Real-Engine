#pragma once
#include "Component.h"

class GameObject;
//
struct Transform : public  Component
{
	//properties
	vec3 localPosition{ 0,0,0 };
	vec3 localRotation{ 0,0,0 };
	vec3 localScale{ 0,0,0 };

	vec3 position{ 0,0,0 };		//Stores position x,y,z
	vec3 eulerAngles{ 0,0,0};		//stores euler angles rotation
	vec4 rotation{ 0,0,0,1 };	//Quaternion that stores rotation x,y,z,w
	vec3 scale{ 1,1,1 };	    //Stores scale x,y,z

	mat4x4 localMatrix{};		//Stores transformation of the object in a matrix from parent reference
	mat4x4 worldMatrix{};		//Stores transformation of the object in a matrix from world reference

	mat4x4 worldToLocal;

	vec3 forward{ 0,0,1 };	//stores normalized vector z
	vec3 up{ 0,1,0 };			//stores normalized vector z
	vec3 right{ 1,0,0 };		//stores normalized vector z

	vec3 localEulerAngles;

	//herarchy data
	Transform* parent = nullptr;
	std::vector<Transform*> childs;

	GameObject* owner = nullptr;

	void CalcualteWorldMatrix()
	{
		worldMatrix = parent->worldMatrix * localMatrix;
	}


	void SetParent(Transform* newParent)
	{
		for (auto& c : childs)
		{
			if (c != newParent)
			{

				parent = newParent;
				//recalculate 
				localMatrix = parent->localMatrix.inverse() * worldMatrix;
				localPosition = localMatrix.translation();
			}
		}
		parent = newParent;
		//recalculate 
		localMatrix = parent->localMatrix.inverse() * worldMatrix;
		parent->localPosition;
		localPosition = localMatrix.translation();
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

		//means the root is origin
		//move world pos
		mat4x4 tmp = localMatrix;

		//apply changes
		localMatrix.translate(x, y, z);
		localPosition = localMatrix.translation();

	    worldMatrix = parent->worldMatrix * localMatrix;

		position = worldMatrix.translation();
		
		//world parent to propagate to the childs
		mat4x4 wpt =  tmp * worldMatrix;

		//move all childs
		for (auto& c : childs)
		{
			c->PropagateTransform(wpt);
		}

		worldMatrix = wpt;
	}

	void Rotate(float angle, vec3 u) {

		//means the root is origin
		//move world pos
		mat4x4 tmp = localMatrix;

		//apply changes
		localMatrix.rotate(angle, u);
		localRotation = localMatrix.rotation();

		worldMatrix = parent->worldMatrix * localMatrix;
		eulerAngles = worldMatrix.rotation();
		//world parent to propagate to the childs
		mat4x4 wpt = tmp * worldMatrix;

		//move all childs
		for (auto& c : childs)
		{
			c->PropagateTransform(wpt);
		}

		worldMatrix = wpt;
	}

	void Rotate(float pitch, float yaw, float roll) {

		//means the root is origin
		//move world pos
		mat4x4 tmp = localMatrix;

		//apply changes
		localMatrix.rotate( pitch, yaw,roll);
		localRotation = localMatrix.rotation();

		worldMatrix = parent->worldMatrix * localMatrix;
		eulerAngles = vec3(pitch, yaw, roll);
		//world parent to propagate to the childs
		mat4x4 wpt = tmp * worldMatrix;

		//move all childs
		for (auto& c : childs)
		{
			c->PropagateTransform(wpt);
		}
		worldMatrix = wpt;
	}


	void Scale(float x, float y, float z) {

		//means the root is origin
		//move world pos
		mat4x4 tmp = localMatrix;

		//apply changes
		localMatrix.scale(x, y, z);
		localScale = localMatrix.scale();

		worldMatrix = parent->worldMatrix * localMatrix;
		scale = worldMatrix.scale();
		//world parent to propagate to the childs
		mat4x4 wpt = tmp * worldMatrix;

		//move all childs
		for (auto& c : childs)
		{
			c->PropagateTransform(wpt);
		}

		worldMatrix = wpt;
	}

	vec3 Position()
	{
		return worldMatrix.translation();
	}
	vec3 LocalPosition()
	{
		return localPosition;
	}
	vec3 LocalRotation()
	{
		//return localMatrix.rotation();
		return eulerAngles;
	}
	vec3 LocalScale()
	{
		return localScale;
	}
	//void ApplyTransformation(vec3 _position, vec3 _rotation,vec3 _scale)
	//{
	//	//means the root is origin
	//	//move world pos
	//	mat4x4 pretransformation = localMatrix;
	//	mat4x4 newTransforamtion;

	//	localMatrix = newTransforamtion.GetMatrixFromTransform(_position, _rotation, _scale);
	//	worldMatrix = parent->worldMatrix * localMatrix;		

	//	position = worldMatrix.translation();
	//	//scale = worldMatrix.scale();
	//	//rotation = worldMatrix.rotation();

	//	//world parent to propagate to the childs
	//	mat4x4 wpt = pretransformation * worldMatrix;

	//	//move all childs
	//	for (auto& c : childs)
	//	{
	//		c->PropagateTransform(wpt);
	//	}

	//	worldMatrix = wpt;
	//}

	void ApplyTransformation(mat4x4 newtransformation)
	{
		//save mat
		mat4x4 tmp = localMatrix;

		worldMatrix = parent->worldMatrix * localMatrix * newtransformation;
		localMatrix = localMatrix * newtransformation;
		//world parent to propagate to the childs
		mat4x4 wpt = tmp * worldMatrix;


		position = worldMatrix.translation();
		scale = worldMatrix.scale();
		eulerAngles = worldMatrix.rotation();

		//move all childs
		for (auto& c : childs)
		{
			c->PropagateTransform(wpt);
		}

	//	worldMatrix = wpt;
	}

	void PropagateTransform(mat4x4& T)
	{
		worldMatrix = T * localMatrix;
		position = worldMatrix.translation();
		scale = worldMatrix.scale();
		eulerAngles = worldMatrix.rotation();
		for (auto& c : childs)
		{
			c->PropagateTransform(worldMatrix);
		}
	}
};

