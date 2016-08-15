#pragma once

#ifdef DEHAXWINDOWS_EXPORTS
#define DEHAXWINDOWS_API __declspec(dllexport)
#else
#define DEHAXWINDOWS_API __declspec(dllimport)
#endif
