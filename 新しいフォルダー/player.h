#ifndef _PLAYER_H_
#define _PLEYER_H_

//マクロ
#define PLAYER_WIDTH (250.0f) //幅
#define PLAYER_HEIGHT (250.0f) //高さ
//プレイヤーの状態
typedef enum
{
	PLAYERSTATE_APPEAR = 0,	//出現状態(点滅)
	PLAYERSTATE_NORMAL,		//通常状態
	PLAYERSTATE_DAMAGE,		//ダメージ状態
	PlAYERSTATE_DEATH,		//死亡状態
}PLAYERSTATE;
typedef struct
{
	D3DXVECTOR3 pos; //位置
	D3DXVECTOR3 rot; //向き
	D3DXVECTOR3 move;//移動量
	D3DXVECTOR3 state;//プレイヤーの状態
	int nCounterAnim;
	int nPatternAnim;
	int nCounterState;//状態管理カウンター
	int nLife;//プレイヤーの体力
	float fLength;//対角線の長さ
	float fAngle; //対角線の角度
	bool bDisp;//表示するかしないか
	bool bUse;
}Player;

void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
Player* GetPlayer(void);
void HitPlayer(int nDamage);
#endif
