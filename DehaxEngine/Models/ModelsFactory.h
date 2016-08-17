#pragma once
#include "..\stdafx.h"

#include "Model.h"

class DEHAXENGINE_API ModelsFactory {
public:
	static Model Box(float width = 1.0L, float length = 1.0L, float height = 1.0L);
	//static Model Cylinder(float radius = 1.0L, float height = 1.0L, int sides = 12);
};
