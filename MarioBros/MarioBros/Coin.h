#pragma once

#include "Animation.h"
#include "Sprite.h"
#include "Object.h"
#include <list>
using namespace std;

class Coin:public Object
{
private:

	float	yTemp;
	float	vy;
	float	ay;

	Object* container;
	bool	isCheckedContainer;
	bool	isNeedDelete;
	void CheckContainer(list<Object*>* staObjs);
public:
	char	state;
	int	numCoin;

	Coin();
	Coin(float _x, float _y,float width,float height,int _ID,Sprite* _sprite);
	void Update(list<Object*>* staObjs,list<Object*>* dynObjs,Input* input, float TPF);
	void Render(Camera* camera);
	void ChangeState(char _state);
	void SetVar(char* varName,int val);
	int GetVar(char* varName);
	void ResetWhenReload(Sprite* _sprite);
	void ResetRect();
	void Save(fstream *fs);
	void Load(fstream *fs);
};