#include "..\stdafx.h"
#include "Scene.h"

#include "..\Models\ModelsFactory.h"

Scene::Scene()
{
	CreateAxisModels();
}

Scene::~Scene()
{
	unsigned int size = getNumObjects();

	for (unsigned int i = 0; i < size; i++) {
		delete m_objects[i];
	}
}

void Scene::AddModel(Model *model)
{
	m_objects.push_back(model);
}

void Scene::RemoveModel(const int &index)
{
	m_objects.erase(m_objects.begin() + index);
}

unsigned int Scene::getNumObjects() const
{
	return m_objects.size();
}

Model *Scene::operator[](const int &i)
{
	return m_objects[i];
}

void Scene::CreateAxisModels()
{
	Model *axisX = new Model(ModelsFactory::Box(0.01f * AXIS_SCALE, 1.0f * AXIS_SCALE, 0.01f * AXIS_SCALE));
	axisX->setPosition(DirectX::XMFLOAT3(0.5f * AXIS_SCALE, 0.0f, 0.0f));
	axisX->setColor(DirectX::Colors::Red);
	Model *axisY = new Model(ModelsFactory::Box(0.01f * AXIS_SCALE, 0.01f * AXIS_SCALE, 1.0f * AXIS_SCALE));
	axisY->setPosition(DirectX::XMFLOAT3(0.0f, 0.5f * AXIS_SCALE, 0.0f));
	axisY->setColor(DirectX::Colors::Green);
	Model *axisZ = new Model(ModelsFactory::Box(1.0f * AXIS_SCALE, 0.01f * AXIS_SCALE, 0.01f * AXIS_SCALE));
	axisZ->setPosition(DirectX::XMFLOAT3(0.0f, 0.0f, 0.5f * AXIS_SCALE));
	axisZ->setColor(DirectX::Colors::Blue);

	AddModel(axisX);
	AddModel(axisY);
	AddModel(axisZ);
}
