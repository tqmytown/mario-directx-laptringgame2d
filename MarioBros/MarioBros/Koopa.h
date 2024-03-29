#pragma once

#include "Animation.h"
#include "Sprite.h"
#include "Object.h"
#include <list>
using namespace std;

class Koopa:public Object
{
private:
	list<Object*>* collisionList;
	RECT	oldRect;
public:
	float	vx;
	float	vy;
	float	ay;
	float	xOld;
	float	yOld;
	float	waitIdle;

	bool	isBright;
	bool	isNeedDelete;
	char	state;

	Koopa();
	Koopa(float _x, float _y,float width,float height,bool _isBright,int _ID,Sprite* _sprite,Game* _game);
	~Koopa();
	void Update(list<Object*>* staObjs,list<Object*>* dynObjs,Input* input, float TPF);
	void Render(Camera* camera);
	void Move(float TPF,list<Object*>* staObjs);
	void UpdateAnimation(float TPF);
	void ChangeState(char _state);
	int GetVar(char* varName);
	void SetVar(char* varName,int val);
	void ResetRect();
	void ResetWhenReload(Sprite* _sprite);
	void Save(fstream *fs);
	void Load(fstream *fs);
};