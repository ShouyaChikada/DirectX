#include"input.h"
//マクロ定義
#define NUM_KEY_MAX (256)
//ぐろーばる
XINPUT_STATE g_joykeyState; //ジョイパッドのプレス情報
LPDIRECTINPUT8 g_pInput = NULL;
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;
BYTE g_aOldState[NUM_KEY_MAX];
BYTE  g_aKeyState[NUM_KEY_MAX];

//キーボードの初期化処理
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInput
	if (FAILED(DirectInput8Create(hInstance,DIRECTINPUT_VERSION,IID_IDirectInput8,(void**)&g_pInput,NULL)))
	{
		return E_FAIL;
	}
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}
	//データフォーマットを設定
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	//協調モード
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	//キーボードへのアクセス権を獲得
	g_pDevKeyboard->Acquire();
	return S_OK;
}
//キーボードの終了処理
void UninitKeyboard(void)
{
	//入力デバイス
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire();
		g_pDevKeyboard->Release();
		g_pDevKeyboard=NULL;
	}
	//Direct
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}
//キーボードの更新処理
void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];
	int nCntKey;
	for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
	{
		g_aOldState[nCntKey] = g_aKeyState[nCntKey];
	}
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			g_aKeyState[nCntKey]=aKeyState[nCntKey];
		}
	}
	else
	{
		g_pDevKeyboard->Acquire();
	}
}
//キーボードのプレス情報
bool GetKeyboardPress(int nKey)
{
	return(g_aKeyState[nKey] & 0x80) ? true : false;
}
bool KeyboardTrigger(int nKey)
{
	bool Trigger = false;
	if (g_aOldState[nKey] & 0x80 && !(g_aKeyState[nKey] & 0x80))
	{
		Trigger = true;
	}
	return Trigger;
}
HRESULT InitJoypad(void)
{
	//メモリのクリア
	memset(&g_joykeyState, 0, sizeof(XINPUT_STATE));

	//Xinputのステートを設定(有効にする)
	XInputEnable(true);

	return S_OK;
}
//ジョイパッドの終了処理
void UninitJoypad(void)
{
	//XInputのステート設定(無効にする)
	XInputEnable(false);
}
//ジョイパッドの更新処理
void UpdateJoypad(void)
{
	XINPUT_STATE joykeyState;	//ジョイパッドの入力情報
	
	//ジョイパッドの状態を取得
	if (XInputGetState(0, &joykeyState) == ERROR_SUCCESS)
	{
		g_joykeyState = joykeyState;	//ジョイパッドのプレス情報の保存
	}
}
//ジョイパッドのプレス情報を保存
bool GetJoypadPress(JOYKEY key)
{
	return (g_joykeyState.Gamepad.wButtons & (0x01 << key)) ? true : false;
}