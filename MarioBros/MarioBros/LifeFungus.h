#pragma once

#include "Animation.h"
#include "Sprite.h"
#include "Object.h"
#include <list>
using namespace std;

//Là nấm khi Mario còn nhỏ, nếu Mario lớn rồi thì nó là hoa.
class LifeFungus:public Object
{
private:
	bool	isCheckedContainer;
	list<Object*>* collisionList;
public:

	float	vx;
	float	vy;
	float	ay;
	float	xOld;
	float	yOld;
	char	state;
	RECT	oldRect;
	bool	isNeedDelete;

	Object* container;

	LifeFungus();
	LifeFungus(float _x, float _y,float width,float height,int _ID,Sprite* _sprite);
	~LifeFungus();
	void Update(list<Object*>* staObjs,list<Object*>* dynObjs,Input* input, float TPF);
	void ChangeState(char _state);
	void CheckObjects(list<Object*>* staObjs);
	void Move(float TPF,list<Object*>* staObjs,list<Object*>* dynObjs);
	void Render(Camera* camera);

	void SetVar(char* varName,int val);
	int GetVar(char* varName);
	void ResetWhenReload(Sprite* _sprite);
	void Save(fstream *fs);
	void Load(fstream *fs);
};

