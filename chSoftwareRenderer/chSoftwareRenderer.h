#pragma once

#include"chMatrix.h"
#include <windows.h>
#include "chVector3.h"

class chSoftwareRenderer
{
public:
	chSoftwareRenderer(HWND windowHandle);
	~chSoftwareRenderer(void);

	void GetViewMatrix(const chMatrix* viewMat);
	void GetProjectionMatrix(const chMatrix* projMat);

	bool MakeFrameBuffer();
	//void EndDrawing();
	void ClearFrameBuffer();
	void Present();
	void DrawPrimitive(chVector3* vertices,int size,const chMatrix* worldMatrix);

//private:
	int wd,ht,vx,vy;

	chMatrix projMatrix;
	chMatrix viewMatrix;

	HWND wndHandle;

	HDC hdcFrameBuffer;

	HBITMAP hbtFrameBuffer,hOldBitmap;

	void DrawLine(const chVector3* v1,const chVector3 *v2);
};
