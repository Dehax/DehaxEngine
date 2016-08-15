#pragma once

#include "DehaxWindows.h"

class DEHAXWINDOWS_API DApplication {
public:
	DApplication();
	int Run();
private:
	HACCEL m_hAccelTable;
};
