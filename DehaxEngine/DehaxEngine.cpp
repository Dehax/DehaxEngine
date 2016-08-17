#include "stdafx.h"
#include "DehaxEngine.h"

DehaxEngine::DehaxEngine()
	: m_renderer(new Renderer(this)), m_scene(new Scene())
{
}

DehaxEngine::~DehaxEngine()
{
	if (m_scene != nullptr) {
		delete m_scene;
	}

	if (m_renderer != nullptr) {
		delete m_renderer;
	}
}

Renderer *DehaxEngine::getRenderer() const
{
	return m_renderer;
}

Scene *DehaxEngine::getScene() const
{
	return m_scene;
}
