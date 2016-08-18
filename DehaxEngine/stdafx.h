#pragma once

#ifdef DEHAXENGINE_EXPORTS
#define DEHAXENGINE_API __declspec(dllexport)
#else
#define DEHAXENGINE_API __declspec(dllimport)
#endif

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <d3d11_2.h>
#include <DirectXMath.h>
#include <DirectXColors.h>
#include <d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

#pragma warning(disable : 4251)
#pragma warning(disable : 4316)
