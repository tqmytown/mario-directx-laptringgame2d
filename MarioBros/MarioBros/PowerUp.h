#pragma once

#include "Animation.h"
#include "Sprite.h"
#include "Object.h"
#include <list>
using namespace std;

//Là nấm khi Mario còn nhỏ, nếu Mario lớn rồi thì nó là hoa.
class PowerUp:public Object
{
public:
	Object* container;
	float	vx;
	float	vy;
	float	ay;
	float	xOld;
	float	yOld;
	char	state;
	bool	isFungus;
	bool	isCheckedContainer;
	bool	isNeedDelete;

	PowerUp();
	PowerUp(float _x, float _y,float width,float height,int _ID,Sprite* _sprite);
	void Update(list<Object*>* staObjs,list<Object*>* dynObjs,Input* input, float TPF);
	void CheckObjects(list<Object*>* staObjs,list<Object*>* dynObjs);
	void ChangeState(int _state);
	void Move(float TPF,list<Object*>* staObjs,list<Object*>* dynObjs);
	void Render(Camera* camera);
	void UpdateAnimation(float TPF);
	void SetVar(char* varName,int val);
	int GetVar(char* varName);
	void ResetWhenReload(Sprite* _sprite);
	void Save(fstream *fs);
	void Load(fstream *fs);
};