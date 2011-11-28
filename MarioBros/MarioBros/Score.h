#pragma once

#include "Animation.h"
#include "Sprite.h"
#include "Object.h"
#include <list>
using namespace std;

class Score:public Object
{
public:
	float	distanceMove;
	float	vy;
	bool	isNeedDelete;
	int		score;

	Score();
	Score(Sprite* _sprite,float _x,float _y,int _score);
	void Update(float TPF);
	void Render(Camera* camera);
	int	GetVar(char* varName);
};