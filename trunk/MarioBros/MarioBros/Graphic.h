#pragma once

#include "d3d9.h"
#include "d3dx9.h"
#include "windows.h"

class Graphic
{
private:

public:
	LPDIRECT3DDEVICE9 device;
	LPDIRECT3D9 directX;
	LPDIRECT3DSURFACE9 backBuffer;
	LPD3DXSPRITE spriteDX;
	D3DPRESENT_PARAMETERS present;

	bool isInitSuccess;

	Graphic();
	Graphic(HWND hWnd);
	~Graphic();

	LPDIRECT3DSURFACE9 CreateSurface(char* filePath);
	void DrawTextAdvanced(LPCWSTR text,int x,int y,int width,int height,D3DXCOLOR color,LPD3DXFONT font);
	float DegToRad(float Deg);
};