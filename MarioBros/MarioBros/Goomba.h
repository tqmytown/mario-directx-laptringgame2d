#pragma once

#include "Animation.h"
#include "Sprite.h"
#include "Object.h"
#include <list>
using namespace std;

class Goomba:public Object
{
private:
	list<Object*>* collisionList;
	RECT	oldRect;
public:
	bool	isBright;
	bool	isAlive;

	float	xOld;
	float	yOld;
	float	vx;
	float	vy;
	float	ay;

	char	state;
	bool	isNeedDelete;
	float	waitIdle;
	Game*	game;

	Goomba();
	Goomba(float _x, float _y,float width,float height,bool _isBright,int _ID,Sprite* _sprite,Game* _game);
	~Goomba();
	void Update(list<Object*>* staObjs,list<Object*>* dynObjs,Input* input, float TPF);
	void Move(float TPF,list<Object*>* staObjs);
	void UpdateAnimation(float TPF);
	void Render(Camera* camera);
	void ChangeState(char _state);
	void SetVar(char* varName,int val);
	int GetVar(char* varName);
	void ResetWhenReload(Sprite* _sprite);
	void Save(fstream *fs);
	void Load(fstream *fs);
};