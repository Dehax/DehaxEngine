#ifdef DEHAXENGINE_EXPORTS
#define DEHAXENGINE_API __declspec(dllexport)
#else
#define DEHAXENGINE_API __declspec(dllimport)
#endif

class DEHAXENGINE_API DehaxEngine {
public:
	DehaxEngine();
};
