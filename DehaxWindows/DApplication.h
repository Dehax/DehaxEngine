#pragma once

#include "DehaxWindows.h"

typedef void(*ApplicationUpdateHandler)();

class DEHAXWINDOWS_API DApplication {
public:
	DApplication();
	int Run();

	void setUpdateHandler(ApplicationUpdateHandler updateHandler);
private:
	HACCEL m_hAccelTable = nullptr;
	ApplicationUpdateHandler m_updateHandler = nullptr;
};
