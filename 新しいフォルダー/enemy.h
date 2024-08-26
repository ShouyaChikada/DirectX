#pragma once
#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "main.h"
//�܂���
#define MAX_ENEMY (128)//�G��
//�G�\����
typedef enum
{
	ENEMYSTATE_NORMAL = 0,
	ENEMYSTATE_DAMAGE,
	ENEMYSTATE_MAX,
}ENEMYSTATE;
typedef struct
{
	D3DXVECTOR3 pos; //�ʒu
	int nType;       //���
	ENEMYSTATE state;
	int nCounterState;
	int nLife;
	int nCntS;
	bool bUse;		 //�g�p���Ă��邩

}Enemy;
//�v���g�^�C�v
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos,int nType);//�ʒu�A���
Enemy* GetEnemy(void);
void HitEnemy(int nCntEnemy, int nDamege);
int GetNumEnemy();
#endif
