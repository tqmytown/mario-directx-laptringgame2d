#pragma once

#include "Animation.h"
#include "Sprite.h"
#include "Object.h"
#include <list>
using namespace std;

class QBrick:public Object
{
private:
	char	state;
	float	vy;
	float	ay;
	float	yOld;
public:
	bool	isChanged;
	bool	isBright;

	QBrick();
	QBrick(float _x, float _y,float width,float height,bool _isBright,int _ID,Sprite* _sprite);
	void Update(list<Object*>* staObjs,list<Object*>* dynObjs,Input* input, float TPF);
	void SetVar(char* varName,int val);
	int GetVar(char* varName);
	void Render(Camera *camera);
	void ChangeState(char _state);
	void UpdateAnimation(float TPF);
	void ResetWhenReload(Sprite* _sprite);
	void Save(fstream *fs);
	void Load(fstream *fs);
};