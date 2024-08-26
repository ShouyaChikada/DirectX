#include "main.h"
#include "player.h"
#include "input.h"
#include "bullet.h"
#include "effect.h"
//�O���[�o���錾
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTexturePlayer1 = NULL;//�e�N�X�`���ւ̃|�C���^

LPDIRECT3DVERTEXBUFFER9 g_pVtebuffPlayer;
LPDIRECT3DVERTEXBUFFER9 g_pVtebuffPlayer1;

Player g_player;
//�|���S���̏���������
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\maxresdefault1.png",
		&g_pTexturePlayer);
	//������
	g_player.nCounterAnim=0;
	g_player.nPatternAnim = 0;
	g_player.pos = D3DXVECTOR3(200.0f, 100.0f,0.0f);//�ʒu������������
	g_player.move = D3DXVECTOR3(0.0f,0.0f,0.0f);//����������������
	g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//����������������

	//�Ίp���̒������Z�o����
	g_player.fLength = sqrtf(PLAYER_WIDTH * PLAYER_WIDTH + PLAYER_HEIGHT * PLAYER_HEIGHT) / 2.0f;
	//�Ίp���̊p�x���Z�o����
	g_player.fAngle = atan2f(PLAYER_WIDTH,PLAYER_HEIGHT);
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtebuffPlayer,
		NULL);
	VERTEX_2D* pVtx;
	//���b�N
	g_pVtebuffPlayer->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W�̐ݒ�
	pVtx[0].pos.x = g_player.pos.x + sinf(g_player.rot.z + (-D3DX_PI + g_player.fAngle)) * g_player.fLength;
	pVtx[0].pos.y = g_player.pos.y + cosf(g_player.rot.z + (-D3DX_PI + g_player.fAngle)) * g_player.fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_player.pos.x + sinf(g_player.rot.z + (D3DX_PI - g_player.fAngle)) * g_player.fLength;
	pVtx[1].pos.y = g_player.pos.y + cosf(g_player.rot.z + (D3DX_PI - g_player.fAngle)) * g_player.fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_player.pos.x + sinf(g_player.rot.z + (0.0f - g_player.fAngle)) * g_player.fLength;
	pVtx[2].pos.y = g_player.pos.y + cosf(g_player.rot.z + (0.0f - g_player.fAngle)) * g_player.fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_player.pos.x + sinf(g_player.rot.z + (0.0f + g_player.fAngle)) * g_player.fLength;
	pVtx[3].pos.y = g_player.pos.y + cosf(g_player.rot.z + (0.0f + g_player.fAngle)) * g_player.fLength;
	pVtx[3].pos.z = 0.0f;

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.25f);
	pVtx[3].tex = D3DXVECTOR2(0.5f, 0.25f);
	//�A�����b�N
	g_pVtebuffPlayer->Unlock();
}

//�|���S���̏I������
void UninitPlayer(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}
	//�e�N�X�`���̔j��
	if (g_pVtebuffPlayer != NULL)
	{
		g_pVtebuffPlayer->Release();
		g_pVtebuffPlayer = NULL;
	}
}
//�|���S���̍X�V����
void UpdatePlayer(void)
{
	VERTEX_2D* pVtx;
	static float fDate=0.2f;
	
	//���b�N
	g_pVtebuffPlayer->Lock(0, 0, (void**)&pVtx, 0);
	g_player.nCounterAnim++;


	//���_���W�̐ݒ�
	if (GetKeyboardPress(DIK_A) == true)
	{
		if (GetKeyboardPress(DIK_W) == true)//W�L�[���������Ƃ�
		{//����ړ�

			g_player.move.x += sinf(-D3DX_PI * 0.75f) * 0.7f;
			g_player.move.y += cosf(-D3DX_PI * 0.75f) * 0.7f;
			if (GetKeyboardPress(DIK_Q) == true)//Q�L�[���������Ƃ�
			{//�E��]
				g_player.rot.z += 0.35f;
			}
			else if (GetKeyboardPress(DIK_E) == true)//E�L�[���������Ƃ�
			{//����]
				g_player.rot.z -= 0.35f;
			}
			fDate = 0.2f;
		}

		else if (GetKeyboardPress(DIK_S) == true)//S�L�[���������Ƃ�
		{//�����ړ�													
			g_player.move.x += sinf(-D3DX_PI * 0.25f) * 0.7f;			  
			g_player.move.y += cosf(-D3DX_PI * 0.25f) * 0.7f;	
			if (GetKeyboardPress(DIK_Q) == true)//Q�L�[���������Ƃ�
			{//�E��]
				g_player.rot.z += 0.35f;
			}
			else if (GetKeyboardPress(DIK_E) == true)//E�L�[���������Ƃ�
			{//����]
				g_player.rot.z -= 0.35f;
			}
			fDate = 0.2f;
		}
		else//A�L�[���������Ƃ�
		{//�E�ړ�
			g_player.move.x -= 0.7f;
			if (GetKeyboardPress(DIK_Q) == true)//Q�L�[���������Ƃ�
			{//�E��]
				g_player.rot.z += 0.35f;
			}
			else if (GetKeyboardPress(DIK_E) == true)//E�L�[���������Ƃ�
			{//����]
				g_player.rot.z -= 0.35f;
			}
		}
	}
	else if (GetKeyboardPress(DIK_D) == true)
	{
		if (GetKeyboardPress(DIK_W) == true)//W�L�[���������Ƃ�
		{//�E��ړ�
			g_player.move.x += sinf(D3DX_PI * 0.75f) * 0.7f;
			g_player.move.y += cosf(D3DX_PI * 0.75f) * 0.7f;
			if (GetKeyboardPress(DIK_Q) == true)//Q�L�[���������Ƃ�
			{//�E��]
				g_player.rot.z += 0.35f;
			}
			else if (GetKeyboardPress(DIK_E) == true)//E�L�[���������Ƃ�
			{//����]
				g_player.rot.z -= 0.35f;
			}
			fDate = 0.2f;
		}
		else if (GetKeyboardPress(DIK_S) == true)//S�L�[���������Ƃ�
		{//�E���ړ�
			g_player.move.x += sinf(D3DX_PI * 0.25f) * 0.7f;
			g_player.move.y += cosf(D3DX_PI * 0.25f) * 0.7f;
			if (GetKeyboardPress(DIK_Q) == true)//Q�L�[���������Ƃ�
			{//�E��]
				g_player.rot.z += 0.35f;
			}
			else if (GetKeyboardPress(DIK_E) == true)//E�L�[���������Ƃ�
			{//����]
				g_player.rot.z -= 0.35f;
			}
			fDate = 0.2f;
		}
		else//D�L�[���������Ƃ�
		{//�E�ړ�
			g_player.move.x += 0.7f;
			if (GetKeyboardPress(DIK_Q) == true)//Q�L�[���������Ƃ�
			{//�E��]
				g_player.rot.z += 0.35f;
			}
			else if (GetKeyboardPress(DIK_E) == true)//E�L�[���������Ƃ�
			{//����]
				g_player.rot.z -= 0.35f;
			}
			fDate = -0.2f;
		}
	}
	else if (GetKeyboardPress(DIK_W) == true)//W�L�[���������Ƃ�
	{//��ړ�
		g_player.move.y -= 0.7f;
		if (GetKeyboardPress(DIK_Q) == true)//Q�L�[���������Ƃ�
		{//�E��]
			g_player.rot.z += 0.35f;
		}
		else if (GetKeyboardPress(DIK_E) == true)//E�L�[���������Ƃ�
		{//����]
			g_player.rot.z -= 0.35f;
		}
	}
	else if (GetKeyboardPress(DIK_S) == true)//S�L�[���������Ƃ�
	{//���ړ�
		g_player.move.y -= -0.7f;
		if (GetKeyboardPress(DIK_Q) == true)//Q�L�[���������Ƃ�
		{//�E��]
			g_player.rot.z += 0.35f;
		}
		else if (GetKeyboardPress(DIK_E) == true)//E�L�[���������Ƃ�
		{//����]
			g_player.rot.z -= 0.35f;
		}
	}
	else if (GetKeyboardPress(DIK_Q) == true)//Q�L�[���������Ƃ�
	{//�E��]
		g_player.rot.z += 0.35f;
	}
	else if (GetKeyboardPress(DIK_E) == true)//E�L�[���������Ƃ�
	{//����]
		g_player.rot.z -= 0.35f;
	}
	else if (KeyboardTrigger(DIK_B) == true)//B�L�[���������Ƃ�
	{//�g��
		if (g_player.fLength <= 900.0f)
		{
			g_player.fLength += 100.0f;
		}
		else if (g_player.fLength >= 900.0f)
		{
			g_player.fLength += 0.0f;
		}
		
	}
	else if (KeyboardTrigger(DIK_L) == true)//L�L�[���������Ƃ�
	{//�k��
		if (g_player.fLength <= 100.0f)
		{
			g_player.fLength += 0.0f;
		}
		else if(g_player.fLength >=100.0f)
		{
			g_player.fLength -= 100.0f;
		}
	}
	else if (KeyboardTrigger(DIK_P) == true)//P�L�[���������Ƃ�
	{//�E�X�O�x
		g_player.rot.z += 1.57f;
	}
	else if (KeyboardTrigger(DIK_O) == true)//O�L�[���������Ƃ�
	{//���X�O�x
		g_player.rot.z -= 1.57f;
	}
	else if (KeyboardTrigger(DIK_I) == true)//I�L�[���������Ƃ�
	{//���̈ʒu�ɖ߂�
		g_player.rot.z += 0.0f;
	}
	else if (KeyboardTrigger(DIK_N) == true)//I�L�[���������Ƃ�
	{//���̃T�C�Y�ɖ߂�
		g_player.fLength = sqrtf(PLAYER_WIDTH * PLAYER_WIDTH + PLAYER_HEIGHT * PLAYER_HEIGHT) / 2.0f;
	}
	if (KeyboardTrigger(DIK_SPACE) == true)//SPACE�L�[���������Ƃ�
	{
		SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI *0.5) * 20.0f, cosf(g_player.rot.z + D3DX_PI*0.5) * 10.0f, 0.0f),100,BULLETTYPE_PLAYER);
	}
	if (GetJoypadPress(JOYKEY_UP) == true)
	{
		g_player.pos.y -= 1.0f;
	}
	//�ʒu���X�V
	g_player.pos.x += g_player.move.x;
	g_player.pos.y += g_player.move.y;
	//�ړ��ʂ��X�V
	g_player.move.x += (0.0f - g_player.move.x) * 0.05f;
	g_player.move.y += (0.0f - g_player.move.y) * 0.05f;
	//pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - 25.0f, g_player.pos.y - 25.0f, 0.0f);
	//pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + 25.0f, g_player.pos.y - 25.0f, 0.0f);
	//pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - 25.0f, g_player.pos.y + 25.0f, 0.0f);
	//pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + 25.0f, g_player.pos.y + 25.0f, 0.0f);
	pVtx[0].pos.x = g_player.pos.x + sinf(g_player.rot.z + (-D3DX_PI + g_player.fAngle)) * g_player.fLength;
	pVtx[0].pos.y = g_player.pos.y + cosf(g_player.rot.z + (-D3DX_PI + g_player.fAngle)) * g_player.fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_player.pos.x + sinf(g_player.rot.z + (D3DX_PI - g_player.fAngle)) * g_player.fLength;
	pVtx[1].pos.y = g_player.pos.y + cosf(g_player.rot.z + (D3DX_PI - g_player.fAngle)) * g_player.fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_player.pos.x + sinf(g_player.rot.z + (0.0f - g_player.fAngle)) * g_player.fLength;
	pVtx[2].pos.y = g_player.pos.y + cosf(g_player.rot.z + (0.0f - g_player.fAngle)) * g_player.fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_player.pos.x + sinf(g_player.rot.z + (0.0f + g_player.fAngle)) * g_player.fLength;
	pVtx[3].pos.y = g_player.pos.y + cosf(g_player.rot.z + (0.0f + g_player.fAngle)) * g_player.fLength;
	pVtx[3].pos.z = 0.0f;
	
	if ((g_player.nCounterAnim % 5) == 0)
	{
		g_player.nCounterAnim = 0;
		g_player.nPatternAnim = (g_player.nPatternAnim + 1) % 4;
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(g_player.nPatternAnim * 0.25f,0.0f);
		pVtx[1].tex = D3DXVECTOR2(g_player.nPatternAnim * 0.25f+0.25f,0.0f);
		pVtx[2].tex = D3DXVECTOR2(g_player.nPatternAnim * 0.25f,1.0f);
		pVtx[3].tex = D3DXVECTOR2(g_player.nPatternAnim * 0.25f + 0.25f,1.0f);
	}
	//�A�����b�N
	g_pVtebuffPlayer->Unlock();
}
//�|���S���̕`�揈��
void DrawPlayer(void)
{
	VERTEX_2D* pVtx;
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtebuffPlayer, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePlayer);
	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
		0,
		2); //���_���\���̂̃T�C�Y
}
//�v���C���[�̎擾
Player* GetPlayer(void)
{
	return &g_player;
}
