#include "Bullet.h"
#include "Object.h"
#include "Collision.h"
#include "Info.h"
#include "Animation.h"
#include "Sprite.h"
#include "Mario.h"
Bullet::Bullet():Object(){}
Bullet::Bullet(float _x, float _y, float _width, float _height,float _vx, Sprite *_sprite,Sprite* _sprite1):Object(_x,_y,_width,_height)
{
	sprite = _sprite;
	sprite1 = _sprite1;
	ani = new Animation(4,1,0,sprite);
	isNeedDelete = false;
	timedelay=0;
	timeblow=0;
	vx=_vx;
	vy=ay=0;
	oldRect = rect;
	xOld = _x;
	yOld = _y;
	state = BS_IDLE;
	collisionList = new list<Object*>;
}

Bullet::~Bullet(void)
{
	if(collisionList!=NULL)
		delete collisionList;
	collisionList=NULL;
}
void Bullet::Move(float TPF,list<Object*> *staObjs,list<Object*> *dynObjs)
{
	Object* obj;
	//theo phuong x
	x+=vx*TPF;
	ResetRect();
	list<Object*>::iterator i;
	for(i=staObjs->begin();i!=staObjs->end();i++)
	{
		obj=*i;
		if(obj->ID>=20&&obj->ID<=28)
		{
			if(Collision::RectVsRect(rect,obj->rect)==true)
			{
				vx=0;
				x=xOld;
				SetVar("state",BS_BLOW);///				
			}	
		}
		else if(obj->ID==29)
		{
			if(x>=obj->x+30)
				SetVar("state",BS_BLOW);
		}
	}
	//Theo phương y
	if(state!=BS_BLOW)
	{
	ay=G;
	vy+=ay*TPF;
	y+=vy*TPF+1.0/2*ay*TPF*TPF;
	/*if(vx==0)
		y=yOld;*/
	oldRect=rect;
	ResetRect();
	collisionList->clear();
	for(i=staObjs->begin();i!=staObjs->end();i++)
	{
		obj=*i;
		if(obj->ID>=20&&obj->ID<=29)				//Nếu là thùng, đá , gạch...
			if(Collision::RectVsRect(rect,obj->rect)==true)	
				collisionList->push_back(obj);
	}

	//Xét va chạm để không bị rơi
	if(collisionList->size()>0)
	{
		Object* obj;
		list<Object*>::iterator i;
		for(i=collisionList->begin();i!=collisionList->end();i++)
		{
			obj=*i;
			if(oldRect.bottom<obj->rect.bottom)
				if(obj->y-height<y)
				{
					y=obj->y-height;
					vy=-400;					
				}
		}
		ResetRect();
	}

	//xet va cham doi tuong dong
	for(i=dynObjs->begin();i!=dynObjs->end();i++)
	{
		obj=*i;
		if(Collision::RectVsRect(rect,obj->rect)==true)
		{
			switch(obj->ID)
			{
			case 42:
				if(obj->GetVar("state")==ES_ACTIVING)
				{
					if(vx>0)
						obj->Huong=1;
					else obj->Huong=2;
					obj->SetVar("state",ES_FALL);					
					SetVar("state",BS_BLOW);
				}
				break;
			case 41:
				if(obj->GetVar("state")==ES_ACTIVING)
				{
					if(vx>0)
						obj->Huong=1;
					else obj->Huong=2;
					obj->SetVar("state",ES_FALL);
					SetVar("state",BS_BLOW);					
				}
				break;		
			case 33:
				obj->SetVar("state",IS_ATE);
				SetVar("state",BS_BLOW);
				break;
			}
		}
	}
	}
	xOld=x;
	yOld=y;
	
}
void Bullet::ChangeState(char _state)
{
	state = _state;
	switch(state)
	{
	case BS_ACTIVING:
		ay=G;
		vy=100;/////thay doi van toc y 
		//vx=200;
		break;
	case BS_BLOWED:
		isNeedDelete=true;
		break;
	}
}
void Bullet::SetVar(char* varName,int val)
{
	if(strcmp(varName,"state")==0)
	{
		ChangeState(val);		
	}
}
int Bullet::GetVar(char *varName)
{
	if(strcmp(varName,"state")==0)
		return state;
	if(strcmp(varName,"isNeedDelete")==0)
		return isNeedDelete;
	return -1;
}
void Bullet::Render(Camera *camera)
{
	switch(state)
	{
	case BS_ACTIVING:
		sprite->Draw(x-camera->x-11,y-12,ZOOM,ZOOM,ani->rect,0.5);
		break;
	case BS_BLOW:
		
		sprite1->Draw(x-camera->x-TILE_SIZE/2,y,ZOOM,ZOOM,ani->rect,0.5);
		break;
	}
}
void Bullet::Update(list<Object*>* staObjs,list<Object*>* dynObjs,Input* input, float TPF)
{
	switch(state)
	{
	case BS_ACTIVING:
		Move(TPF,staObjs,dynObjs);		
		ani->Update(0,3,TPF);
		break;
	case BS_BLOW:			
		ani = new Animation(3,1,0,sprite1);
		timeblow+=TPF;
		if(timeblow>0.1)
			ani->SetIndex(1);
		if(timeblow>0.2)
			ani->SetIndex(2);
		timedelay+=TPF;
		if(timedelay>0.3)
			SetVar("state",BS_BLOWED);		
		break;
	case BS_BLOWED:
		isNeedDelete=true;
		break;
	}
}