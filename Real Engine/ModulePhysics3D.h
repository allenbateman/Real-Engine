#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2List.h"
#include "Primitive.h"


// Recommended scale is 1.0f == 1 meter, no less than 0.2 objects
#define GRAVITY btVector3(0.0f, -10.0f, 0.0f) 

class DebugDrawer;
struct PhysBody3D;
struct PhysVehicle3D;
struct VehicleInfo;

class ModulePhysics3D : public Module
{
public:
	ModulePhysics3D(Application* app, bool start_enabled = true);
	~ModulePhysics3D();

	bool Init();
	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	PhysBody3D* AddBody(const Sphere& sphere, float mass = 1.0f);
	PhysBody3D* AddBody(const Cube& cube, float mass = 1.0f);
	PhysBody3D* AddBody(const Cylinder& cylinder, float mass = 1.0f);

	void AddConstraintP2P(PhysBody3D& bodyA, PhysBody3D& bodyB, const vec3& anchorA, const vec3& anchorB);
	void AddConstraintHinge(PhysBody3D& bodyA, PhysBody3D& bodyB, const vec3& anchorA, const vec3& anchorB, const vec3& axisS, const vec3& axisB, bool disable_collision = false);

private:

	bool debug;

};

class DebugDrawer
{
public:
	DebugDrawer() : line(0,0,0)
	{}
	Line line;
	Primitive point;
};