#pragma once

class Game;
class State
{
public:
	State(){};
	virtual Update(){}=0;
	virtual Render();
};