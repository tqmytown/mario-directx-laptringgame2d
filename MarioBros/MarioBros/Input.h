#pragma once

#define DIRECTINPUT_VERSION 0x0800
#include "dinput.h"
#include "windows.h"

bool InitInput(HINSTANCE,HWND);

class Input
{
private:
	char buffer[256];
	char KeyPressState[256];
	int width;
	int height;
	
	
	LPDIRECTINPUT8 dInput;
	LPDIRECTINPUTDEVICE8 mouse;
	LPDIRECTINPUTDEVICE8 keyboard;
public:
	
	DIMOUSESTATE mouseState;
	bool isInitSuccess;
	int xMouse;
	int yMouse;

	Input();
	Input(HWND hWnd,HINSTANCE hInstance,int _width, int _height);
	~Input();
	void GetKey();
	void GetMouse();
	bool KeyDown(int key);
	bool KeyUp(int key);
	bool KeyPress(int key);
};