#include "Input.h"
#include "windows.h"


Input::Input(){};
Input::Input(HWND hWnd,HINSTANCE hInstance,int _width, int _height)
{
	HRESULT hr=DirectInput8Create(hInstance,DIRECTINPUT_VERSION,IID_IDirectInput8,(void**)&dInput,NULL);
	if FAILED(hr) isInitSuccess=false;

	//Create keyboard
	hr=dInput->CreateDevice(GUID_SysKeyboard,&keyboard,NULL);
	if FAILED(hr) 
		isInitSuccess = false;
	hr=keyboard->SetDataFormat(&c_dfDIKeyboard);
	if FAILED(hr) 
		isInitSuccess = false;
	hr=keyboard->SetCooperativeLevel(hWnd,DISCL_FOREGROUND|DISCL_NONEXCLUSIVE);
	if FAILED(hr) 
		isInitSuccess = false;
	hr=keyboard->Acquire();
	if FAILED(hr) 
		isInitSuccess = false;
	
	//Create mouse
	
	hr=dInput->CreateDevice(GUID_SysMouse,&mouse,NULL);
	if FAILED(hr) 
		isInitSuccess = false;
	hr=mouse->SetDataFormat(&c_dfDIMouse);
	if FAILED(hr) 
		isInitSuccess = false;
	hr=mouse->SetCooperativeLevel(hWnd,DISCL_EXCLUSIVE | DISCL_FOREGROUND);
	if FAILED(hr) 
		isInitSuccess = false;
	hr=mouse->Acquire();
	if FAILED(hr) 
		isInitSuccess = false;
	
	// Zero Fill the KeyPressState
	// used to record keypresses
	for (int i = 0; i < 256; i++){
		KeyPressState[i] = 0;
	}
// 
// 	for (int i = 0; i < 256; i++){
// 		buffer[i] = 0;
// 	}

	isInitSuccess=true;
	width=_width;
	height=_height;
	xMouse=width/2;
	yMouse=width/2;
}
void Input::GetKey()
{
	HRESULT hr =keyboard->GetDeviceState(sizeof(buffer),(LPVOID)&buffer);
	if FAILED(hr) keyboard->Acquire();
}
void Input::GetMouse()
{
	HRESULT hr = mouse->GetDeviceState(sizeof(DIMOUSESTATE),(LPVOID)&mouseState);
	if FAILED(hr) mouse->Acquire();
	while( hr == DIERR_INPUTLOST) 
		hr = mouse->Acquire();
	xMouse+=mouseState.lX;
	yMouse+=mouseState.lY;
	if(xMouse<0) xMouse=0;
	else if(xMouse>width) xMouse=width;
	if(yMouse<0) yMouse=0;
	else if(yMouse>height) yMouse=height;
}
bool Input::KeyDown(int key)
{
	//check the state of the key
	if (buffer[key] & 0x80){
		return true;
	} else {
		return false;
	}
}
bool Input::KeyUp(int key)
{
	//check the state of the key
	if (buffer[key] & 0x80){
		return false;
	} else {
		return true;
	}
}
bool Input::KeyPress(int key)
{

	//check for keydown
	if (KeyDown(key)){
		KeyPressState[key] = 1;
	}
	//check for key reaching the keydown state
	if (KeyPressState[key] == 1){
		//check for key release
		if (KeyUp(key))
			KeyPressState[key] = 2;
	}

	//check if key has been pressed and released
	if (KeyPressState[key] == 2){
		//reset the key status
		KeyPressState[key] = 0;
		return true;
	}

	return false;
}

Input::~Input()
{
	keyboard->Unacquire();
	keyboard->Release();
	keyboard = NULL;
	mouse->Unacquire();
	mouse->Release();
	mouse = NULL;
	dInput->Release();
	dInput = NULL;
}

