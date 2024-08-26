#include "bullet.h"
#include "main.h"
#include "player.h"
#include "explosion.h"
#include "enemy.h"
#include "effect.h"
//�}�N����`
#define MAX_BULLET (128)//�e�̍ő吔
//�e�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	D3DXVECTOR3 move;//�ړ���
	int nLife;//����
	BULLETTYPE type;//�e�̎��
	bool bUse;//�g�p���Ă��邩�ǂ���
}Bullet;
//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;
Bullet g_aBullet[MAX_BULLET];
//�e�̏���������
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\korokke2.png",
		&g_pTextureBullet);
	//�e�̏���������
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].nLife = 100;
		g_aBullet[nCntBullet].bUse = false;
	}
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);
	VERTEX_2D* pVtx;
	//���b�N
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	g_pVtxBuffBullet->Unlock();
}
//�e�̏I������
void UninitBullet(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}
	//�e�N�X�`���̔j��
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}
//�e�̍X�V����
void UpdateBullet(void)
{
	int nCntBullet;
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	VERTEX_2D* pVtx;

	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{//�e���g�p����Ă���
			
			int nCntEnemy;
			if (g_aBullet[nCntBullet].type == BULLETTYPE_PLAYER)
			{
				//�G�̎擾
				Enemy* pEnemy;//�G�̏��ւ̃|�C���^
				pEnemy = GetEnemy();//�G�̏��̐擪�A�h���X����������
				for (nCntEnemy = 0; nCntEnemy <= MAX_ENEMY; nCntEnemy++)
				{
					if (pEnemy->bUse == true)
					{
						if (g_aBullet[nCntBullet].pos.x >= pEnemy->pos.x - 50 && g_aBullet[nCntBullet].pos.x >= pEnemy->pos.x + 50
							&& g_aBullet[nCntBullet].pos.y >= pEnemy->pos.x - 50 && g_aBullet[nCntBullet].pos.x >= pEnemy->pos.x + 50)
						{
							HitEnemy(nCntEnemy, 1);
							g_aBullet[nCntBullet].bUse = false;
						}
					}
					pEnemy++;
				}
			}
			else if (g_aBullet[nCntBullet].type == BULLETTYPE_ENEMY)
			{
				int nCntPlayer;
				Player* pPlayer;
				pPlayer = GetPlayer();
				for (nCntPlayer = 0; nCntPlayer < MAX_ENEMY; nCntPlayer++)
				{
					if (pPlayer->bUse == true)
					{
						if (g_aBullet[nCntBullet].pos.x >= pPlayer->pos.x - 50 && g_aBullet[nCntBullet].pos.x >= pPlayer->pos.x + 50
							&& g_aBullet[nCntBullet].pos.y >= pPlayer->pos.x - 50 && g_aBullet[nCntBullet].pos.x >= pPlayer->pos.x + 50)
						{
							
							g_aBullet[nCntBullet].bUse = false;
						}
					}
				}
			}
			g_aBullet[nCntBullet].pos.x += g_aBullet[nCntBullet].move.x;
			g_aBullet[nCntBullet].pos.y += g_aBullet[nCntBullet].move.y;

			SetEffect(g_aBullet[nCntBullet].pos,40, 80, 40);
			pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 25.0f, g_aBullet[nCntBullet].pos.y - 25.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 25.0f, g_aBullet[nCntBullet].pos.y - 25.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 25.0f, g_aBullet[nCntBullet].pos.y + 25.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 25.0f, g_aBullet[nCntBullet].pos.y + 25.0f, 0.0f);
			g_aBullet[nCntBullet].nLife--;
			pVtx[0].col = D3DXCOLOR(155, 0, 155, 255);
			pVtx[1].col = D3DXCOLOR(155, 0, 155, 255);
			pVtx[2].col = D3DXCOLOR(155, 0, 155, 255);
			pVtx[3].col = D3DXCOLOR(155, 0, 155, 255);
			if (0 >= g_aBullet[nCntBullet].pos.x >= SCREEN_HEIGHT || 0 >= g_aBullet[nCntBullet].pos.y >= SCREEN_WIDTH)
			{
				g_aBullet[nCntBullet].bUse = false;
			}
			if (g_aBullet[nCntBullet].nLife == 0)
			{
				//�����̐ݒ�
				//SetExplosion(g_aBullet[nCntBullet].pos,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				g_aBullet[nCntBullet].bUse = false;
			}
		}
		pVtx += 4;
	}
	g_pVtxBuffBullet->Unlock();
}
//�e�̕`�揈��
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;
	//�f�o�C�X�擾
	pDevice = GetDevice();

	pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	//�e�N�X�`���̐ݒ�
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{//�e���g�p����Ă���
			pDevice->SetTexture(0, g_pTextureBullet);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntBullet * 4, 2);
		}
	}
}
//�e�̐ݒ菈��
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, BULLETTYPE type)
{
	int nCntBullet;
	VERTEX_2D* pVtx;

	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{

			pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 25.0f, g_aBullet[nCntBullet].pos.y - 25.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 25.0f, g_aBullet[nCntBullet].pos.y - 25.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 25.0f, g_aBullet[nCntBullet].pos.y + 25.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 25.0f, g_aBullet[nCntBullet].pos.y + 25.0f, 0.0f);

			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			g_aBullet[nCntBullet].pos = pos;
			g_aBullet[nCntBullet].move = move;
			g_aBullet[nCntBullet].nLife = 100;
			g_aBullet[nCntBullet].bUse = true;
			break;
		}
		pVtx += 4;
	}
	g_pVtxBuffBullet->Unlock();
}
