#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

//�L�[�̎��
typedef enum
{
	JOYKEY_UP = 0,		//�\���L�[(��)
	JOYKEY_RIGHT = 0,	//�\���L�[(�E)
	JOYKEY_DOWN = 0,	//�\���L�[(��)
	JOYKEY_LEFT = 0,	//�\���L�[(��)
	JOYKEY_START = 0,	//START�L�[
}JOYKEY;

//�L�[�{�[�h�̃v���g�^�C�v�錾
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);
void UninitKeyboard(void);
void UpdateKeyboard(void);
bool GetKeyboardPress(int nKey);
bool KeyboardTrigger(int nKey);
bool KeyboardRelease(int nKey);
bool KeyboardRepeat(int nKey);

//�W���C�p�b�h�̃v���g�^�C�v�錾
HRESULT InitJoypad(void);
void UninitJoypad(void);
void UpdateJoypad(void);
bool GetJoypadPress(JOYKEY key);
#endif


