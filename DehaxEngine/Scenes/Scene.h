#pragma once
#include "..\stdafx.h"

#include <vector>

#include "..\Models\Model.h"

class DEHAXENGINE_API Scene {
public:
	Scene();
	~Scene();

	void AddModel(Model *model);
	void RemoveModel(const int &index);

	unsigned int getNumObjects() const;
	Model *operator[](const int &i);
private:
	const float AXIS_SCALE = 10.0f;

	void CreateAxisModels();

	std::vector<Model *> m_objects;
};
