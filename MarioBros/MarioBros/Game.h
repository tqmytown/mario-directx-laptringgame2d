#pragma once

#include "d3d9.h"
#include "d3dx9.h"

#define SCREEN_WIDTH	800
#define SCREEN_HEIGHT	600

#include "Input.h"
#include "Graphic.h"
#include "TimeManager.h"
#include "Sprite.h"
#include "Animation.h"
#include "QuadTree.h"
#include "Object.h"
#include "Camera.h"
#include "Audio.h" 
//#include "Score.h"		

#include <list>
using namespace std;

class Mario;
class Score;
class CheckPoint;
class Game
{
private:

	//Framework ----------------------
	Graphic		*g;
	Input		*input;
	TimeManager *timeManager;
	float		TPF;					//Time per frame
	HWND		hWnd;
	HINSTANCE	hInstance;
	LPD3DXFONT	fontArial;
	void ProcessInput();
	void Update();
	void Render();
	//--------------------------------

	//Framework ----------------------
public:
	Game(HWND _hWnd, HINSTANCE _hInstance);
	~Game();
	void GameRun();
	Audio       *a; 

	//--------------------------------
	//Mario* _mario;//k
	Sprite* sprites[20];
	QuadTree* quadTree;
	Camera* camera;
	CSound *sBackground, *sGameOver, *sWinState, *sFireBall, *sJump, *sCoin1, *sCoin2,*sCoin3,* sCoin4;
	CSound *sPowerUp, *sDeath, *sMip, *sBonusRise, *sBrickBreaked, *sKick, *sPipeWarp, *sBump, *sLife; ; 
	list<Object*>	staticObjs;
	list<Object*>	dynamicObjs;
	list<Score*>	lScore;					
	list<Score*>	lScoreRemove;
	int		timeGame;				//Đếm ngược thời gian
	float	wait1Sec;

	int		score;
	char	numLife;
	char	coin;
	bool	isUseCheckPoint;	//Có sử dụng checkPoint khi load map hay không

	char	state;
	char	stage;				//Màn chơi
	int		temp;
	Mario*	cloneMario;			//Lưu trữ thông tin Mario khi chuyển màn.
	CheckPoint* checkPoint;
	bool	isBright;
	bool	isInSubStage;
	//float waitbullet;//k
	//------K
	Sprite* mariomenu;			//Mario trỏ menu
	IDirect3DSurface9* menu;	//Background state menu
	//IDirect3DSurface9* itemMenu;//Hiện phần new game, load game...
	IDirect3DSurface9* gameOver; //Background state gameOver
	IDirect3DSurface9* gameWin; //Background state gameWver
	IDirect3DSurface9* about;   //Background state about game
	IDirect3DSurface9* gameConfirm;//Background state game confirm: khi đang chơi mà player nhấn phím ESC thì sẽ hiện
	                               //ra thông báo để hỏi xem player có thực sự muốn thoát hay không?
	RECT menurect;//k
	int posymenu;//k
	int posymenuC;
	void Menu();//k
	void AboutGame();//k
	void GameConfirm();
	//-----------

	void ChangeState(char _state);
	void ChangeStage(char _stage);
	void ChangeSubStage(char _stage);
	void SetIsBright(char _stage);
	void AddScore(int _score,float _x,float _y);			
};
