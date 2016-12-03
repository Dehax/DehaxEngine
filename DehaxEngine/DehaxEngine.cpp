#include "stdafx.h"
#include "DehaxEngine.h"

DehaxEngine::DehaxEngine()
	: m_renderer(new DX11Renderer(this)), m_scene(new Scene())
{
}

DehaxEngine::~DehaxEngine()
{
	if (m_scene != nullptr) {
		delete m_scene;
		m_scene = nullptr;
	}

	if (m_renderer != nullptr) {
		delete m_renderer;
		m_renderer = nullptr;
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
