#include <Windows.h>
#include <string>
#include <sstream>


//using namespace std;
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParm) {
	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(69);
		break;
	case WM_KEYDOWN:
	{
		if (wParam == 'F') {
			SetWindowText(hWnd, "Down");
		}
	}
	break;
	case WM_KEYUP:
	{
		if (wParam == 'F')
			SetWindowText(hWnd, "Up");
		break;
	}
	case WM_CHAR:
	{
		static std::string title;
		title.push_back(wParam);
		SetWindowText(hWnd, title.c_str( ));
	}
	case WM_LBUTTONDOWN:
	{
		const POINTS pt = MAKEPOINTS(lParm);
		std::ostringstream oss;
		oss << "(" << pt.x << "," << pt.y << ")";
		SetWindowText(hWnd, oss.str().c_str());
	}
	}
	return DefWindowProc(hWnd,msg,wParam,lParm);
}
int CALLBACK WinMain(
	 HINSTANCE hInstance,
	 HINSTANCE hPrevInstance,
	 LPSTR     lpCmdLine,
	 int       nCmdShow )
{
	const auto pClassName = "First Window";
	//Register
	WNDCLASSEX wc = {0};
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = nullptr;
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = pClassName;
	wc.hIconSm = nullptr;

	RegisterClassEx(&wc);


	//Call Window
	HWND hWnd = CreateWindowEx(
		0,
		pClassName,
		"Hello World",
		WS_BORDER | WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		200, 100, 800, 600,
		nullptr,nullptr,hInstance,nullptr
		);
	//Show Window
	ShowWindow(hWnd, SW_SHOW);
	
	//Send Message
	MSG msg;
	BOOL gResult;
	while (gResult = (GetMessage(&msg, hWnd, 0, 0)) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	//test exit code
	if (gResult == -1) {
		return -1;
	}
	else {
		return msg.wParam;
	}
	
}