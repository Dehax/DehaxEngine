#pragma once
#include "..\stdafx.h"

#include "Camera.h"

class DehaxEngine;

class DEHAXENGINE_API Renderer {
public:
	virtual HRESULT InitDevice(HWND hWnd) = 0;
	virtual void Render() = 0;
	virtual Camera *getCamera() const = 0;
private:
	virtual void CleanupDevice() = 0;
};
