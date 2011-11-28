#include "windows.h"
#include "d3d9.h"
#include "d3dx9.h"
#include "Graphic.h"

Graphic::Graphic(){};
Graphic::Graphic(HWND hWnd)
{
	if((directX=Direct3DCreate9(D3D_SDK_VERSION))==NULL)
		isInitSuccess=false;
	ZeroMemory(&present,sizeof(present));
	present.BackBufferCount=1;
	present.BackBufferFormat=D3DFMT_X8R8G8B8;
	present.BackBufferHeight=600;
	present.BackBufferWidth=800;
	present.hDeviceWindow=hWnd; 
	present.SwapEffect=D3DSWAPEFFECT_DISCARD;
	present.Windowed=true;

	if (FAILED(directX->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hWnd,D3DCREATE_HARDWARE_VERTEXPROCESSING,&present,&device)))
		if (FAILED(directX->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hWnd,D3DCREATE_SOFTWARE_VERTEXPROCESSING,&present,&device)))
			if (FAILED(directX->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_REF,hWnd,D3DCREATE_HARDWARE_VERTEXPROCESSING,&present,&device)))
				isInitSuccess=false;

	device->GetBackBuffer(0,0,D3DBACKBUFFER_TYPE_MONO,&backBuffer);	//Lay backBuffer
	D3DXCreateSprite(device,&spriteDX);
	isInitSuccess=true;
}
LPDIRECT3DSURFACE9 Graphic::CreateSurface(char* filePath)
{
	D3DXIMAGE_INFO imageInfo;
	D3DXGetImageInfoFromFile(filePath,&imageInfo);
	IDirect3DSurface9* rSurface;	//return surface
	device->CreateOffscreenPlainSurface(imageInfo.Width,imageInfo.Height,D3DFMT_X8R8G8B8,D3DPOOL_DEFAULT,&rSurface,NULL);
	D3DXLoadSurfaceFromFile(rSurface,NULL,NULL,filePath,NULL,D3DX_DEFAULT,0,NULL);
	return rSurface;
}
void Graphic::DrawTextAdvanced(LPCWSTR text,int x,int y,int width,int height,D3DXCOLOR color, LPD3DXFONT font)
{
	RECT rect;
	rect.left=x;
	rect.right=x+width;
	rect.top=y;
	rect.bottom=y+height;
	font->DrawTextW(NULL,(LPCWSTR)text,-1,&rect,0,color);
}

Graphic::~Graphic()
{
	directX->Release();
	device->Release();
}
float Graphic::DegToRad(float Deg)
{
	return Deg*3.141592654/180;
}