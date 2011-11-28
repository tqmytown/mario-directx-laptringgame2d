#include "Sprite.h"
#include "Graphic.h"
#include "Animation.h"
Sprite::Sprite(){};
Sprite::Sprite(Graphic* g,char* path)
{
	spriteHandler=g->spriteDX;
	D3DXIMAGE_INFO imageInfo;
	D3DXGetImageInfoFromFile(path,&imageInfo);
	width=imageInfo.Width;
	height=imageInfo.Height;
	D3DXGetImageInfoFromFile(path,&imageInfo);
	D3DXCreateTextureFromFileEx(g->device,
		path,
		imageInfo.Width,
		imageInfo.Height,
		1,						//Mipmap level
		D3DPOOL_DEFAULT,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(255,0,255),
		&imageInfo,
		NULL,
		&image);
}
void Sprite::Draw(int x,int y, float xScaleRatio, float yScaleRatio,D3DXVECTOR2 vRotatteCenter,float angle,D3DCOLOR color,RECT rSrc,float deep)
{
	D3DXMATRIX mTransform;
	D3DXMatrixTransformation2D(&mTransform,NULL,0,&D3DXVECTOR2(xScaleRatio,yScaleRatio),&vRotatteCenter,angle,&D3DXVECTOR2((float)x,(float)y));
	spriteHandler->SetTransform(&mTransform);
	spriteHandler->Draw(image,&rSrc,NULL,&D3DXVECTOR3(0,0,deep),color);

}
void Sprite::Draw(int x,int y, float xScaleRatio, float yScaleRatio,float deep)
{

	D3DXMATRIX mTransform;
	D3DXMatrixTransformation2D(&mTransform,NULL,0,&D3DXVECTOR2(xScaleRatio,yScaleRatio),&D3DXVECTOR2(0,0),0,&D3DXVECTOR2((float)x,(float)y));
	spriteHandler->SetTransform(&mTransform);
	spriteHandler->Draw(image,NULL,NULL,&D3DXVECTOR3(0,0,deep),D3DCOLOR_XRGB(255,255,255));

}
void Sprite::Draw(int x,int y, float xScaleRatio,float yScaleRatio, RECT rSrc,float deep)
{
	D3DXMATRIX mTransform;
	D3DXMatrixTransformation2D(&mTransform,NULL,0,&D3DXVECTOR2(xScaleRatio,yScaleRatio),&D3DXVECTOR2(0,0),0,&D3DXVECTOR2((float)x,(float)y));
	spriteHandler->SetTransform(&mTransform);
	spriteHandler->Draw(image,&rSrc,NULL,&D3DXVECTOR3(0,0,deep),D3DCOLOR_XRGB(255,255,255));
}
void Sprite::Draw(int x,int y, float xScaleRatio, float yScaleRatio,char numImage,char frameIndex,float deep)
{
	RECT rectSource;
	rectSource.left=width/numImage*frameIndex;
	rectSource.top=0;
	rectSource.right=rectSource.left+width/numImage;
	rectSource.bottom=height;

	D3DXMATRIX mTransform;
	D3DXMatrixTransformation2D(&mTransform,NULL,0,&D3DXVECTOR2(xScaleRatio,yScaleRatio),&D3DXVECTOR2(0,0),0,&D3DXVECTOR2((float)x,(float)y));
	spriteHandler->SetTransform(&mTransform);
	spriteHandler->Draw(image,&rectSource,NULL,&D3DXVECTOR3(0,0,deep),D3DCOLOR_XRGB(255,255,255));
}