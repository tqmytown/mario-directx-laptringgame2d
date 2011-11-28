#pragma once
#include "Object.h"
#include "Sprite.h"
#include "Animation.h"
#include <list>

using namespace std;
class Mario;
class Bullet :	public Object
{
private: 
	float vx;
	float vy;
	float ay;
	float xOld;
	float yOld;
	float timedelay;
	float timeblow;
	RECT oldRect;
	bool isNeedDelete;
	list<Object*>* collisionList;
	Sprite* sprite1;//explosion
	Mario* mario;
public:
	char state;
	Bullet(void);
	~Bullet(void);
	Bullet(float _x,float _y,float width,float height,float _vx,Sprite* _sprite,Sprite* _sprite1);
	void Update(list<Object*>* staObjs,list<Object*>* dynObjs,Input* input, float TPF);
	void Render(Camera* camera);	
	void Move(float TPF,list<Object*>* staObjs,list<Object*>* dynObjs);
	void ChangeState(char _state);
	void SetVar(char* varName,int val);
	int GetVar(char* varName);
};
