#pragma once
#include "stdafx.h"

#include "Renderer\Renderer.h"
#include "Scenes\Scene.h"

class DEHAXENGINE_API DehaxEngine {
public:
	DehaxEngine();
	~DehaxEngine();

	Renderer *getRenderer() const;
	Scene *getScene() const;
private:
	Renderer *m_renderer = nullptr;
	Scene *m_scene = nullptr;
};
