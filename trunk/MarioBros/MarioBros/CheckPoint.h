#pragma once

class Object;

class CheckPoint:public Object
{
public:
	char	stage;

	CheckPoint();
	CheckPoint(float _x,float _y, char _stage);
	void Save(fstream *fs);
	void Load(fstream *fs);
};