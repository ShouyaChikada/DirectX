#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

//キーの種類
typedef enum
{
	JOYKEY_UP = 0,		//十字キー(上)
	JOYKEY_RIGHT = 0,	//十字キー(右)
	JOYKEY_DOWN = 0,	//十字キー(下)
	JOYKEY_LEFT = 0,	//十字キー(左)
	JOYKEY_START = 0,	//STARTキー
}JOYKEY;

//キーボードのプロトタイプ宣言
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);
void UninitKeyboard(void);
void UpdateKeyboard(void);
bool GetKeyboardPress(int nKey);
bool KeyboardTrigger(int nKey);
bool KeyboardRelease(int nKey);
bool KeyboardRepeat(int nKey);

//ジョイパッドのプロトタイプ宣言
HRESULT InitJoypad(void);
void UninitJoypad(void);
void UpdateJoypad(void);
bool GetJoypadPress(JOYKEY key);
#endif


