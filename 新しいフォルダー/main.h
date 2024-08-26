#pragma once
#ifndef _MAIN_H_
#define _MAIN_H_
#include<windows.h>
#include"d3dx9.h"
#define DIRECTINPUT_VERSION (0x0800)//ビルド時の警告用マクロ
#include "dinput.h" //キーボード入力処理に必要
#include "Xinput.h" //ジョイパッド入力処理に必要
#include "xaudio2.h"//サウンド処理に必要
//ライブラリのリンク
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"dinput8.lib")	//キーボード入力処理に必要
#pragma comment(lib,"xinput.lib")	//ジョイパッド入力処理に必要
//マクロ定義
#define CLASS_NAME "WindowsClass" //ウィンドウクラスの名前
#define WINDOW_NAME "DirectXの基本処理" //ウィンドウの名前(キャプションに表示)
#define SCREEN_WIDTH (1280) //ウィンドウの幅
#define SCREEN_HEIGHT (720) //ウィンドウの高さ
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1) //頂点フォーマット[2D]
typedef struct
{
	D3DXVECTOR3 pos;//頂点座標
	float rhw;		//座用変換用係数(1.0fで固定)
	D3DCOLOR col;	//頂点カラー
	D3DXVECTOR2 tex;//テクスチャ座標
}VERTEX_2D;
//画面(モード)の種類
typedef enum
{
	MODE_TITLE = 0,	//タイトル画面
	MODE_GAME,		//ゲーム画面
	MODE_RESULT,	//リザルト画面
	MODE_MAX
}MODE;
//プロトタイプ宣言
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
LPDIRECT3DDEVICE9 GetDevice(void);
void Uninit(void);
void Update(void);
void Draw(void);
void SetMode(MODE mode);
MODE GetMode(void);

//VERTEX_2D g_aVertex[8];//頂点情報を格納
#endif
