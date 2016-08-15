typedef void(*DWindowUpdate)();

class DEHAXWINDOWS_API DWindow {
public:
	DWindow(HINSTANCE hInstance, HICON hIcon, HCURSOR hCursor, HBRUSH hBackgroundBrush, LPCWSTR lpszMenuName, LPCWSTR lpszClassName, HICON hIconSmall);
	void setUpdateProcedure(DWindowUpdate updateProcedure);
private:
	ATOM RegisterWindowClass();
	static LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	DWindowUpdate m_updateProcedure;
	HINSTANCE m_hInstance;
	HICON m_hIcon;
	HCURSOR m_hCursor;
	HBRUSH m_hBackgroundBrush;
	LPCWSTR m_lpszMenuName;
	LPCWSTR m_lpszClassName;
	HICON m_hIconSmall;
};
