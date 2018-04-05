#include "chWindow.h"
#include "chMacros.h"
#include "chMathLib.h"
#include "chSoftwareRenderer.h"
#include "chQTimer.h"

chEulerAngles euler;
chMatrix bmat1,bmat2,matrix;
chQuaternion q1,q2;

chSoftwareRenderer *sRenderer = 0;

struct cubeStruct
{
	chVector3 v[4];
};
cubeStruct box[6];


chQTimer* tim;

bool SetUp();
void Update();
void CleanUp();
void render();
void InputHandler();


LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);


	int wd=640,ht = 480;
	chWindow *window;
	float fps=0.0f;


int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
{
	MSG msg;
	TCHAR* appName = "HLSL try1";

	window = new chWindow(hInstance,"Test Math Lib Application",wd,ht);
	window->CreateWnd(WindowProc);


	sRenderer = new chSoftwareRenderer(window->getHandle());
	window->show(nShowCmd);

	if(!SetUp())
	{
		MessageBox(0,"SetUp Failed",0,0);
		return -1;
	}

	tim = new chQTimer();
	tim->reset();

	float tsum = 0.0f;
	int cnt = 0;

	ZeroMemory(&msg,sizeof(MSG));

	while( msg.message!=WM_QUIT )
	{

		if( PeekMessage(&msg,0,0,0,PM_REMOVE) )
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			tsum += tim->getTimeElapsed_float();
			++cnt;

			if(tsum>=1)
			{
				fps = cnt/tsum;
				tsum = 0.0f;
				cnt = 0;
			}

			Update();
			InputHandler();
			render();
		}

	}

	CleanUp();
	return msg.wParam;
}

void CleanUp()
{
SAFE_DELETE(window);
}

bool SetUp()
{


	////////mathlib code

	box[0].v[0] = chVector3(-1.0f,-1.0f,-1.0f);
	box[0].v[1] = chVector3(-1.0f,1.0f,-1.0f);
	box[0].v[2] = chVector3(1.0f,1.0f,-1.0f);
	box[0].v[3] = chVector3(1.0f,-1.0f,-1.0f);

	box[1].v[0] = chVector3(-1.0f,-1.0f,1.0f);
	box[1].v[1] = chVector3(-1.0f,1.0f,1.0f);
	box[1].v[2] = chVector3(1.0f,1.0f,1.0f);
	box[1].v[3] = chVector3(1.0f,-1.0f,1.0f);

	box[2].v[0] = chVector3(-1.0f,-1.0f,-1.0f);
	box[2].v[1] = chVector3(-1.0f,-1.0f,1.0f);
	box[2].v[2] = chVector3(-1.0f,1.0f,1.0f);
	box[2].v[3] = chVector3(-1.0f,1.0f,-1.0f);

	box[3].v[0] = chVector3(1.0f,-1.0f,-1.0f);
	box[3].v[1] = chVector3(1.0f,-1.0f,1.0f);
	box[3].v[2] = chVector3(1.0f,1.0f,1.0f);
	box[3].v[3] = chVector3(1.0f,1.0f,-1.0f);

	box[4].v[0] = chVector3(-1.0f,1.0f,-1.0f);
	box[4].v[1] = chVector3(-1.0f,1.0f,1.0f);
	box[4].v[2] = chVector3(1.0f,1.0f,1.0f);
	box[4].v[3] = chVector3(1.0f,1.0f,-1.0f);

	box[5].v[0] = chVector3(-1.0f,-1.0f,-1.0f);
	box[5].v[1] = chVector3(-1.0f,-1.0f,1.0f);
	box[5].v[2] = chVector3(1.0f,-1.0f,1.0f);
	box[5].v[3] = chVector3(1.0f,-1.0f,-1.0f);

	matrix.Identity();

	bmat1.Identity();
	bmat2.Identity();

	chVector3 pos(0.0f,0.0f,-10.0f);
	bmat1.MakeViewMatrix(&pos,&chVector3(0.0f,0.0f,1.0f),&chVector3(0.0f,1.0f,0.0f),&chVector3(1.0f,0.0f,0.0f));

	bmat2.MakeProjectionMatrix(CH_PI/4.0f,((float)wd/(float)ht));

	if(!sRenderer->MakeFrameBuffer())
	{
		MessageBox(0,"MakeBuffer failed",0,0);
	}
	sRenderer->GetViewMatrix(&bmat1);
	sRenderer->GetProjectionMatrix(&bmat2);

	return true;
}

void Update()
{
	static float angle = 0.0001f;
	angle += 0.00015f;
	bmat1.Identity();
	bmat1.SetRotationX(angle);
	bmat2.Identity();
	bmat2.SetRotationY(angle);
	matrix=bmat1*bmat2;
}

void InputHandler()
{
	

}

void render()
{
	
	sRenderer->ClearFrameBuffer();
	sRenderer->DrawPrimitive(box[0].v,4,&matrix);
	sRenderer->DrawPrimitive(box[1].v,4,&matrix);
	sRenderer->DrawPrimitive(box[2].v,4,&matrix);
	sRenderer->DrawPrimitive(box[3].v,4,&matrix);
	sRenderer->DrawPrimitive(box[4].v,4,&matrix);
	sRenderer->DrawPrimitive(box[5].v,4,&matrix);

	char data[64];
	sprintf(data,"%f",fps);
	TextOut(sRenderer->hdcFrameBuffer,10,10,data,10);

	sRenderer->Present();

}


LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case WM_KEYDOWN:
		if(wParam == VK_ESCAPE)
		{
			DestroyWindow(hwnd);
		}
		return 0;
	case WM_SIZE:
		sRenderer->MakeFrameBuffer();
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd,message,wParam,lParam);
}