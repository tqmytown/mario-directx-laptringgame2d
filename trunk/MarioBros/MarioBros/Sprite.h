#pragma once

#include "d3d9.h"
#include "d3dx9.h"
class Graphic;
class Animation;
class Sprite
{
private:
	LPDIRECT3DTEXTURE9 image;
	LPD3DXSPRITE spriteHandler;
public:
	int		width;
	int		height;

	Sprite();
	Sprite(Graphic* g,char* path);
	void Draw(int x,int y, float xScaleRatio, float yScaleRatio,D3DXVECTOR2 vRotatteCenter,float angle,D3DCOLOR color,RECT rSrc,float deep);
	void Draw(int x,int y, float xScaleRatio, float yScaleRatio,float deep);
	void Draw(int x,int y, float xScaleRatio, float yScaleRatio,RECT rSrc,float deep);
	void Draw(int x,int y, float xScaleRatio, float yScaleRatio,char numImage,char imageIndex,float deep);
};