#include "Pirhana.h"
#include "Object.h"
#include "Info.h"
#include "Animation.h"
#include "Sprite.h"
#include "Collision.h"

Pirhana::Pirhana():Object(){}
Pirhana::Pirhana(float _x, float _y,float width,float height,int _ID,Sprite* _sprite):Object(_x,_y,width,height)
{
	sprite	=_sprite;
	ID		=_ID;
	x		+=TILE_SIZE/2;
	yOld	=y;
	y		+=3;					//Cho y xuống một chút;
	state	=IS_IDLE;
	waitIdle=0;
	isNeedDelete	=false;

	ani=new Animation(2,1,0.2,sprite);
}
void Pirhana::Update(list<Object*>* staObjs,list<Object*>* dynObjs,Input* input, float TPF)
{
	switch(state)
	{
	case IS_IDLE:
		waitIdle+=TPF;
		if(waitIdle>1)					//Thời gian ngừng lại
		{
			waitIdle=0;
			ChangeState(IS_ACTIVING);
		}
		break;
	case IS_ACTIVING:
		y+=vy*TPF;
		//96 là chiều cao của cây trong game
		if((vy<0&&y<yOld-56)||(vy>0&&y>yOld))				//Tới mức giới hạn
			ChangeState(IS_IDLE);
		ResetRect();
		break;
	}
	ani->Update(0,1,TPF);
}
void Pirhana::Render(Camera* camera)
{
	sprite->Draw(x-camera->x,y,ZOOM,ZOOM,ani->rect,0.75);
}
void Pirhana::ChangeState(char _state)
{
	state=_state;
	switch(state)
	{
	case IS_ATE:
		isNeedDelete=true;
		break;
	case IS_ACTIVING:
		if(y<yOld)				//Đang nổi lên
			vy=50;	
		else vy=-50;
		break;
	case IS_IDLE:
		waitIdle=0;
		break;
	}
}
void Pirhana::ResetWhenReload(Sprite* _sprite)
{
	sprite=_sprite;
	ani=new Animation(2,1,0.2,sprite);
}
void Pirhana::Save(fstream *fs)
{
	fs->write(reinterpret_cast<char*>(&ID),sizeof(ID));	//int ID, để khi load biết được đang load Obj nào
	int sizeObj=sizeof(*this);
	fs->write(reinterpret_cast<char*>(&sizeObj),sizeof(int));			//int sizeof(obj)
	fs->write(reinterpret_cast<char*>(this),sizeObj);
}
void Pirhana::Load(fstream *fs)
{
	int sizeObj;
	fs->read(reinterpret_cast<char*>(&sizeObj),sizeof(int));			//int sizeof(obj)
	fs->read(reinterpret_cast<char*>(this),sizeObj);
}
int Pirhana::GetVar(char* varName)
{
	if(strcmp(varName,"isNeedDelete")==0)
		return isNeedDelete;
	if(strcmp(varName,"state")==0)
		return state;
	if(strcmp(varName,"vy")==0)
		return vy;
	return -1;
}
void Pirhana::SetVar(char* varName,int val)
{
	if(strcmp(varName,"state")==0)
		ChangeState(val);
}
void Pirhana::ResetRect()
{
	rect.left=x;
	rect.top=y+2;
	rect.right=rect.left+width;
	rect.bottom=rect.top+height;
}