#include "chSoftwareRenderer.h"
#include "assert.h"
#include <string>

chSoftwareRenderer::chSoftwareRenderer(HWND windowHandle)
{
	assert(windowHandle!=0);
	this->wndHandle = windowHandle;
	projMatrix.Identity();
	viewMatrix.Identity();
	RECT rc;
	GetClientRect(wndHandle,&rc);
	vx = rc.left;
	vy = rc.top;
	wd = rc.right - rc.left;
	ht = rc.bottom - rc.top;
}

chSoftwareRenderer::~chSoftwareRenderer(void)
{
	if(hdcFrameBuffer && hbtFrameBuffer)
	{
		SelectObject(hdcFrameBuffer,hOldBitmap);
		DeleteObject(hbtFrameBuffer);
		DeleteObject(hdcFrameBuffer);
		hOldBitmap = NULL;
	}
}


void chSoftwareRenderer::GetViewMatrix(const chMatrix *viewMat)
{
	viewMatrix = *viewMat;
}


void chSoftwareRenderer::GetProjectionMatrix(const chMatrix *projMat)
{
	projMatrix = *projMat;
}

bool chSoftwareRenderer::MakeFrameBuffer()
{
	HDC hdc = NULL;
	hdc = GetDC(wndHandle);
	//DWORD err = GetLastError();

	if(!hdcFrameBuffer)
		hdcFrameBuffer = CreateCompatibleDC(hdc);

	//hdcFrameBuffer = hdc;
	//err = GetLastError();
	if(hbtFrameBuffer)
	{
		SelectObject(hdcFrameBuffer,hOldBitmap);
		DeleteObject(hbtFrameBuffer);
		hbtFrameBuffer = NULL;
		hOldBitmap = NULL;
	}
	
	hbtFrameBuffer = CreateCompatibleBitmap(hdc,wd,ht);
	ReleaseDC(wndHandle,hdcFrameBuffer);
	hdcFrameBuffer = CreateCompatibleDC(hdc);
	///err = GetLastError();
	if(!hbtFrameBuffer)
		return false;
	hOldBitmap = (HBITMAP)SelectObject(hdcFrameBuffer,hbtFrameBuffer);
	ReleaseDC(wndHandle,hdc);
	SetBkMode(hdcFrameBuffer,TRANSPARENT);

	return true;

}

void chSoftwareRenderer::ClearFrameBuffer()
{
	HBRUSH hb = CreateSolidBrush(RGB(255,255,255)),brushOld;
	brushOld = (HBRUSH)SelectObject(hdcFrameBuffer,hb);
	Rectangle(hdcFrameBuffer,vx,vy,wd,ht);
	SelectObject(hdcFrameBuffer,brushOld);
	DeleteObject(hb);
	brushOld = NULL;
}

void chSoftwareRenderer::Present()
{
	HDC hdc = GetDC(wndHandle);
	
	BitBlt(hdc,vx,vy,wd,ht,hdcFrameBuffer,vx,vy,SRCCOPY);
	ReleaseDC(wndHandle,hdc);
}

void chSoftwareRenderer::DrawLine(const chVector3 *v1, const chVector3 *v2)
{
	HPEN   hPen = CreatePen(PS_SOLID,1,RGB(0,0,0)), hOldPen = NULL;
    
	hOldPen = (HPEN)SelectObject(hdcFrameBuffer,hPen);

	MoveToEx(hdcFrameBuffer,(long)v1->x,(long)v1->y,NULL);
	LineTo(hdcFrameBuffer,(long)v2->x,(long)v2->y);

	SelectObject(hdcFrameBuffer,hOldPen);
	DeleteObject(hPen);
	hOldPen = NULL;

}


void chSoftwareRenderer::DrawPrimitive(chVector3* vertices,int size,const chMatrix* worldMatrix)
{
	projMatrix.m43 = -1.0f;
	//viewMatrix->Identity();
	chMatrix mat = (*worldMatrix)*viewMatrix* projMatrix;
	chVector3 vOld,vCurrent,v;

	for(int i=0;i<4;i++)
	{
		vCurrent=vertices[i]*mat;

		vCurrent.x = vCurrent.x*wd/2.0f + vx + wd/2.0f;
		vCurrent.y = -vCurrent.y*ht/2.0f + vy + ht/2.0f;

		if(i==0)
		{
			vOld = vCurrent;
			continue;
		}

		DrawLine(&vOld,&vCurrent);

		vOld = vCurrent;

	}

	
		vCurrent=vertices[0]*mat;
		vCurrent.x = vCurrent.x*wd/2.0f + vx + wd/2.0f;
		vCurrent.y = -vCurrent.y*ht/2.0f + vy + ht/2.0f;

		DrawLine(&vCurrent,&vOld);
		

}