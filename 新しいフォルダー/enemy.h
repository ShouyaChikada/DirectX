#pragma once
#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "main.h"
//まくろ
#define MAX_ENEMY (128)//敵数
//敵構造隊
typedef enum
{
	ENEMYSTATE_NORMAL = 0,
	ENEMYSTATE_DAMAGE,
	ENEMYSTATE_MAX,
}ENEMYSTATE;
typedef struct
{
	D3DXVECTOR3 pos; //位置
	int nType;       //種類
	ENEMYSTATE state;
	int nCounterState;
	int nLife;
	int nCntS;
	bool bUse;		 //使用しているか

}Enemy;
//プロトタイプ
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos,int nType);//位置、種類
Enemy* GetEnemy(void);
void HitEnemy(int nCntEnemy, int nDamege);
int GetNumEnemy();
#endif
