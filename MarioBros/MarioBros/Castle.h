#pragma once

#include "Animation.h"
#include "Sprite.h"
#include "Object.h"
#include <list>
using namespace std;

class Castle:public Object
{
public:
	Castle();
	Castle(float _x, float _y,float width,float height,int _ID,Sprite* _sprite);
	void Render(Camera *camera);
	void ResetRect();
	void ResetWhenReload(Sprite* _sprite);
	void Save(fstream *fs);
	void Load(fstream *fs);
	
};