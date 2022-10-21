#pragma once
#include "Component.h"
class Material : public Component
{
public:
	Material();
	~Material();


	void InitMaterial();

	unsigned int RBO;
};

