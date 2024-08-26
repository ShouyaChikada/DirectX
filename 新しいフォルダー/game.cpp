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

//�O���[�o���ϐ�
GAMESTATE g_gameState = GAMESTATE_NONE;	//�Q�[���̏��
int g_nCounterGameState = 0;			//��ԊǗ��J�E���^�[

void InitGame(void)
{
	//�w�i�̏���������
	InitBkg();
	//�v���C���[�̏���������
	InitPlayer();
	InitEffect();
	InitBullet();
	
	InitExplosion();
	//�G�̏���������
	InitEnemy();
	SetEnemy(D3DXVECTOR3(800.0f,360.0f,0.0f),1);//�C�ӂ̐������ݒ�
	g_gameState = GAMESTATE_NORMAL;	//�ʏ��Ԃɐݒ�
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
	case GAMESTATE_NORMAL:	//�ʏ���
		break;
	case GAMESTATE_END:		//�I�����
		g_nCounterGameState++;
		if (g_nCounterGameState >= 60)
		{
			g_gameState = GAMESTATE_NONE;	//�������Ă��Ȃ���Ԃɐݒ�
		//���[�h�ݒ�(���U���g��ʂɈڍs)
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
//�Q�[���̎擾
GAMESTATE GetGameState(void)
{
	return g_gameState;
}