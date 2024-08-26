#include"main.h"
#include"player.h"
#include"bkg.h"
#include"input.h"
#include "bullet.h"
#include "explosion.h"
#include "enemy.h"
#include "game.h"
#include "score.h"
#include "fade.h"
#include "effect.h"

//グローバル変数
GAMESTATE g_gameState = GAMESTATE_NONE;	//ゲームの状態
int g_nCounterGameState = 0;			//状態管理カウンター

void InitGame(void)
{
	//背景の初期化処理
	InitBkg();
	//プレイヤーの初期化処理
	InitPlayer();
	InitEffect();
	InitBullet();
	
	InitExplosion();
	//敵の初期化処理
	InitEnemy();
	SetEnemy(D3DXVECTOR3(800.0f,360.0f,0.0f),1);//任意の数だけ設定
	g_gameState = GAMESTATE_NORMAL;	//通常状態に設定
	g_nCounterGameState = 0;
}
void UninitGame(void)
{
	UninitBkg();
	
	UninitEffect();

	UninitBullet();
	
	UninitExplosion();
	
	UninitPlayer();
	

	UninitEnemy();
	
}
void UpdateGame(void)
{
	UpdateBkg();
	UpdatePlayer();
	UpdateEnemy();
	UpdateEffect();
	UpdateBullet();
	
	UpdateExplosion();
	switch (g_gameState)
	{
	case GAMESTATE_NORMAL:	//通常状態
		break;
	case GAMESTATE_END:		//終了状態
		g_nCounterGameState++;
		if (g_nCounterGameState >= 60)
		{
			g_gameState = GAMESTATE_NONE;	//何もしていない状態に設定
		//モード設定(リザルト画面に移行)
			UpdateFade();
		}
		break;
	}
}
void DrawGame(void)
{
	DrawBkg();
	DrawEffect();
	DrawBullet();
	DrawEnemy();
	DrawExplosion();
	DrawPlayer();
}
void SetGameState(GAMESTATE state)
{
	g_gameState = state;
	g_nCounterGameState = 0;
}
//ゲームの取得
GAMESTATE GetGameState(void)
{
	return g_gameState;
}