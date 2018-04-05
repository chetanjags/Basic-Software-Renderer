#include "chWindow.h"
#include "chMacros.h"

chWindow::chWindow(HINSTANCE inst,TCHAR* wndName,int wd,int ht)
{
	this->Init(inst,wndName,wd,ht);
}

chWindow::~chWindow(void)
{
	this->wndTitle.clear();
}

void chWindow::Init(HINSTANCE inst,TCHAR* wndName,int wd,int ht)
{
	customWndProc = false;
	this->initialized = true;
//this->wndTitle = NULL;
	this->wndhInstance = inst;
	this->wndHeight = ht;
	this->wndWidth = wd;
	this->wndTitle = wndName;
}

bool chWindow::CreateWnd(WNDPROC wndProc)
{
	if(!this->initialized)
	{
		return false;
	}

	if(wndProc!=NULL)
	{
		this->ptrWndProc = wndProc;
		customWndProc = true;
	}

	WNDCLASSEX wndClass;

	wndClass.cbClsExtra = 0;
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(0,IDC_ARROW);
	wndClass.hIcon = LoadIcon(0,IDI_APPLICATION);
	wndClass.hIconSm = 0;
	wndClass.hInstance = this->wndhInstance;
	wndClass.lpfnWndProc = MSGRouter;
	wndClass.lpszClassName = this->wndTitle.c_str();
	wndClass.lpszMenuName = 0;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	//registerclass
	if(!RegisterClassEx(&wndClass))
	{
		//MessageBox(0,_T("Class registeration Failed"),this->wndTitle,MB_ICONERROR);
		return false;
	}

	//createwnd function call

	this->wndhandle = CreateWindowA(this->wndTitle.c_str(),this->wndTitle.c_str(),WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,
		this->wndWidth,this->wndHeight,0,0,this->wndhInstance,(void*)this);

	if(!this->wndhandle)
	{
		return false;
	}

	return true;

}


bool chWindow::CreateWnd()
{
	if(this->CreateWnd(NULL))
	{
		return true;
	}

	return false;

}

void chWindow::show(int nCmdShow)
{

	ShowWindow(this->wndhandle,nCmdShow);
	UpdateWindow(this->wndhandle);
	
}


LRESULT CALLBACK chWindow::MSGRouter(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	chWindow *handle = 0;

	if(message == WM_NCCREATE)
	{
		SetWindowLongPtr(hwnd,GWL_USERDATA,(LONG_PTR)((LPCREATESTRUCT(lParam))->lpCreateParams));
	}

	handle = (chWindow *)GetWindowLongPtr(hwnd,GWL_USERDATA);

	if(handle==0)
		return DefWindowProc(hwnd,message,wParam,lParam);

	return ( (handle->customWndProc) ? handle->ptrWndProc(hwnd,message,wParam,lParam) : handle->WndProc(hwnd,message,wParam,lParam));
}


LRESULT CALLBACK chWindow::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case WM_KEYDOWN:
		if(wParam == VK_ESCAPE)
		{
			DestroyWindow(hwnd);
		}
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd,message,wParam,lParam);
}