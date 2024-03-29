#include "Koopa.h"
#include "Object.h"
#include "Info.h"
#include "Animation.h"
#include "Sprite.h"
#include "Collision.h"

Koopa::Koopa():Object(){}
Koopa::Koopa(float _x, float _y,float width,float height,bool _isBright,int _ID,Sprite* _sprite,Game* _game):Object(_x,_y,width,height)
{
	game	=_game;
	isBright	=_isBright;
	sprite	=_sprite;
	ID		=_ID;
	state	=ES_ACTIVING;
	isNeedDelete	=false;
	waitIdle		=0;
	collisionList=new list<Object*>;

	vx=		-50;
	vy=		0;
	ay=		G;
	xOld	=x;
	yOld	=y;

	oldRect	=rect;

	ani=new Animation(4,1,0.2,sprite);
}
Koopa::~Koopa()
{
	if(collisionList!=NULL)
		delete collisionList;
	collisionList=NULL;
}
void Koopa::Update(list<Object*>* staObjs,list<Object*>* dynObjs,Input* input, float TPF)
{
	list<Object*>::iterator i;
	Object* obj;
	switch(state)
	{
	case ES_ACTIVING: 
		Move(TPF,staObjs);
		if(y>HEIGHT)
			ChangeState(ES_DIED);
		break;
	case ES_MOVE_SHELL_LEFT: case ES_MOVE_SHELL_RIGHT:
		Move(TPF,staObjs);
		for(i=dynObjs->begin();i!=dynObjs->end();i++)	
		{
			obj=*i;
			if(obj->ID==41||obj->ID==42&&obj!=this)							//Nếu đụng Goomba thì Goomba chết.
				if(Collision::RectVsRect(rect,obj->rect)&&obj->GetVar("state")!=ES_FALL)
				{
					if(vx>0)
						obj->Huong=1;
					else obj->Huong=2;
					obj->SetVar("state",ES_FALL);
				}
		}
		if(y>HEIGHT)
			ChangeState(ES_DIED);
		break;
	case ES_IDLE:
		waitIdle+=TPF;
		if(waitIdle>5)
		{
			waitIdle-=5;
			ChangeState(ES_ACTIVING);
		}
		break;
	case ES_FALL:
		x+=vx*TPF;
		vy+=ay*TPF;
		y+=vy*TPF+0.5*ay*TPF*TPF;
		ResetRect();
  		if(y>HEIGHT)
			ChangeState(ES_DIED);
		break;
	}
	
	UpdateAnimation(TPF);	
}
void Koopa::Render(Camera* camera)
{
	if(state!=ES_FALL)
	{
		if(vx>0)
			sprite->Draw(x+TILE_SIZE-camera->x,y-TILE_SIZE,-ZOOM,ZOOM,ani->rect,0.5);
		else sprite->Draw(x-camera->x,y-TILE_SIZE,ZOOM,ZOOM,ani->rect,0.5);
	}
	else
		sprite->Draw(x-camera->x,y+TILE_SIZE,ZOOM,-ZOOM,ani->rect,0.5);
}
void Koopa::UpdateAnimation(float TPF)
{
	switch(state)
	{
	case ES_ACTIVING:
		ani->Update(0,1,TPF);
		break;
	case ES_IDLE: case ES_MOVE_SHELL_LEFT: case ES_MOVE_SHELL_RIGHT:
		ani->SetIndex(3);
		break;
	case ES_FALL:
		ani->SetIndex(3);
	}
}
void Koopa::Move(float TPF,list<Object*>* staObjs)
{
	Object* obj;
	//Theo phương x
	x+=vx*TPF;
	ResetRect();
	list<Object*>::iterator i;
	for(i=staObjs->begin();i!=staObjs->end();i++)
	{
		obj=*i;
		if(obj->ID>=20&&obj->ID<=29) //Nếu là thùng, đá , gạch...
			if(Collision::RectVsRect(rect,obj->rect)==true
				&&obj->GetVar("state")!=TS_BREAKING&&obj->GetVar("state")!=TS_BREAKED)
			{
				vx=-vx;
				x=xOld;
			}
	}
	//Theo phương y
	ay=G;
	vy+=ay*TPF;
	y+=vy*TPF+1.0/2*ay*TPF*TPF;
	oldRect=rect;
	ResetRect();
	collisionList->clear();
	for(i=staObjs->begin();i!=staObjs->end();i++)
	{
		obj=*i;
		if(obj->ID>=20&&obj->ID<=29)				//Nếu là thùng, đá , gạch...
			if(Collision::RectVsRect(rect,obj->rect)==true
				&&obj->GetVar("state")!=TS_BREAKING&&obj->GetVar("state")!=TS_BREAKED)
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
					vy=0;
				}
		}
		ResetRect();
	}
	xOld=x;
	yOld=y;
}
void Koopa::ChangeState(char _state)
{
	state=_state;
	switch(state)
	{
	case ES_IDLE:
		waitIdle=0;
		vx=0;
		break;
	case ES_ACTIVING:
		vx=-50;
		break;
	case ES_MOVE_SHELL_LEFT:
		vx=-400;
		break;
	case ES_MOVE_SHELL_RIGHT:
		vx=400;
		break;
	case ES_FALL:
		vy=-200;
		ay=G;
		if(Huong==1)
			vx=200;
		else if(Huong==2)
			vx=-200;
		break;
	case ES_DIED:
		game->score+=100;
		isNeedDelete=true;
		break;
	}
}
int Koopa::GetVar(char* varName)
{
	if(strcmp(varName,"state")==0)
		return state;
	if(strcmp(varName,"isNeedDelete")==0)
		return isNeedDelete;
}
void Koopa::SetVar(char* varName,int val)

{
	if(strcmp(varName,"state")==0)
		ChangeState(val);
}
void Koopa::ResetRect()
{
	rect.left=x;
	rect.right=rect.left+width;
	rect.top=y;
	rect.bottom=y+height;
}
void Koopa::ResetWhenReload(Sprite* _sprite)
{
	sprite=_sprite;
	ani=new Animation(4,1,0.2,sprite);
	collisionList	=new list<Object*>;
}
void Koopa::Save(fstream *fs)
{
	fs->write(reinterpret_cast<char*>(&ID),sizeof(ID));	//int ID, để khi load biết được đang load Obj nào
	int sizeObj=sizeof(*this);
	fs->write(reinterpret_cast<char*>(&sizeObj),sizeof(int));			//int sizeof(obj)
	fs->write(reinterpret_cast<char*>(this),sizeObj);
}
void Koopa::Load(fstream *fs)
{
	int sizeObj;
	fs->read(reinterpret_cast<char*>(&sizeObj),sizeof(int));			//int sizeof(obj)
	fs->read(reinterpret_cast<char*>(this),sizeObj);
}