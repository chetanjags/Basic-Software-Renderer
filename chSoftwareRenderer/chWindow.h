#pragma once
#pragma warning(disable : 4996)

#include <windows.h>
#include <TCHAR.H>
#include <string>

class chWindow
{
public:
	chWindow(void){customWndProc = false;initialized = false;}
	chWindow(HINSTANCE inst,TCHAR* wndName,int wd,int ht);
	~chWindow(void);


	//properties

	HWND getHandle() {return wndhandle;}
	HINSTANCE getHinstance() {return wndhInstance;}
	const char* getTitle() {return wndTitle.c_str();}
	int getHeight() {return this->wndHeight;}
	int getWidth() {return this->wndWidth;}

	void Init(HINSTANCE inst,TCHAR* wndName,int wd,int ht);
	bool CreateWnd();
	bool CreateWnd(WNDPROC);

	void show(int nCmdShow);
	void close();

private:

	//handle of window
	HWND wndhandle;
	HINSTANCE wndhInstance;
	std::string wndTitle;

	int wndHeight,wndWidth;
	bool initialized;
	bool customWndProc;

	WNDPROC ptrWndProc;

	LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

    static LRESULT CALLBACK MSGRouter(HWND,UINT,WPARAM,LPARAM);

};
