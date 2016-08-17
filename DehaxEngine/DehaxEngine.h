#pragma once
#include "stdafx.h"

#include "Renderer.h"
#include "Scenes\Scene.h"

class DEHAXENGINE_API DehaxEngine {
public:
	DehaxEngine();
	~DehaxEngine();

	Renderer *getRenderer() const;
	Scene *getScene() const;
private:
	Renderer *m_renderer;
	Scene *m_scene;
};
