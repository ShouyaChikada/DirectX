#ifndef _PLAYER_H_
#define _PLEYER_H_

//�}�N��
#define PLAYER_WIDTH (250.0f) //��
#define PLAYER_HEIGHT (250.0f) //����
//�v���C���[�̏��
typedef enum
{
	PLAYERSTATE_APPEAR = 0,	//�o�����(�_��)
	PLAYERSTATE_NORMAL,		//�ʏ���
	PLAYERSTATE_DAMAGE,		//�_���[�W���
	PlAYERSTATE_DEATH,		//���S���
}PLAYERSTATE;
typedef struct
{
	D3DXVECTOR3 pos; //�ʒu
	D3DXVECTOR3 rot; //����
	D3DXVECTOR3 move;//�ړ���
	D3DXVECTOR3 state;//�v���C���[�̏��
	int nCounterAnim;
	int nPatternAnim;
	int nCounterState;//��ԊǗ��J�E���^�[
	int nLife;//�v���C���[�̗̑�
	float fLength;//�Ίp���̒���
	float fAngle; //�Ίp���̊p�x
	bool bDisp;//�\�����邩���Ȃ���
	bool bUse;
}Player;

void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
Player* GetPlayer(void);
void HitPlayer(int nDamage);
#endif
