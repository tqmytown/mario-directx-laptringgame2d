#pragma once

#include "Animation.h"
#include "Sprite.h"
#include "Object.h"
#include <list>
using namespace std;

class Flag:public Object
{
private:
	float yFlag;
	char state;
public:
	Flag();
	Flag(float _x, float _y,float width,float height,int _ID,Sprite* _sprite);
	void Update(list<Object*>* staObjs,list<Object*>* dynObjs,Input* input, float TPF);
	void Render(Camera *camera);
	void ResetWhenReload(Sprite* _sprite);
	void ChangeState(char _state);
	void SetVar(char* varName,int val);
	int GetVar(char* varName);
	void Save(fstream *fs);
	void Load(fstream *fs);
	void ResetRect();
};