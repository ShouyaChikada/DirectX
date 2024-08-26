#ifndef BULLET_H_
#define BULLET_H_

#include "main.h"
typedef enum
{
	BULLETTYPE_PLAYER = 0,	//�^�C�g�����
	BULLETTYPE_ENEMY,		//�Q�[�����
	BULLETTYPE_MAX
}BULLETTYPE;
//�v���g�^�C�v�錾
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move,int nLife,BULLETTYPE type);

#endif
