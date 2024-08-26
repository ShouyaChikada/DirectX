#include "Effect.h"
#include "main.h"
#include "player.h"
#include "explosion.h"
#include "enemy.h"
#include "effect.h"
//�}�N����`
#define MAX_EFFECT (4096)//�e�̍ő吔
//�e�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	D3DXCOLOR col;//�ړ���
	float fRadius;
	int nLife;//����
	bool bUse;//�g�p���Ă��邩�ǂ���
}Effect;
//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureEffect = NULL;//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;
Effect g_aEffect[MAX_EFFECT];//arry(�A���C)
//�e�̏���������
void InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEffect;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\effect000.jpg",
		&g_pTextureEffect);
	//�e�̏���������
	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		g_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].col = D3DXCOLOR(255,255,255,255);
		g_aEffect[nCntEffect].fRadius = 0;
		g_aEffect[nCntEffect].nLife = 100;
		g_aEffect[nCntEffect].bUse = false;
	}
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EFFECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL);
	VERTEX_2D* pVtx;
	//���b�N
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
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
	g_pVtxBuffEffect->Unlock();
}
//�e�̏I������
void UninitEffect(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureEffect != NULL)
	{
		g_pTextureEffect->Release();
		g_pTextureEffect = NULL;
	}
	//�e�N�X�`���̔j��
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}
//�e�̍X�V����
void UpdateEffect(void)
{
	int nCntEffect;
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	VERTEX_2D* pVtx;
	
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{//�e���g�p����Ă���

			int nCntEnemy;
			if (g_aEffect[nCntEffect].bUse == true)
			{
				//�G�̎擾
				Enemy* pEnemy;//�G�̏��ւ̃|�C���^
				pEnemy = GetEnemy();//�G�̏��̐擪�A�h���X����������
				for (nCntEnemy = 0; nCntEnemy <= MAX_ENEMY; nCntEnemy++)
				{
					if (pEnemy->bUse == true)
					{
						if (g_aEffect[nCntEffect].pos.x >= pEnemy->pos.x - 50 && g_aEffect[nCntEffect].pos.x >= pEnemy->pos.x + 50
							&& g_aEffect[nCntEffect].pos.y >= pEnemy->pos.x - 50 && g_aEffect[nCntEffect].pos.x >= pEnemy->pos.x + 50)
						{
							HitEnemy(nCntEnemy, 1);
							g_aEffect[nCntEffect].bUse = false;
						}
					}
					pEnemy++;
				}
			}
			pVtx[0].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].pos.y - g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].pos.y - g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].fRadius, 0.0f);
			g_aEffect[nCntEffect].nLife--;
			g_aEffect[nCntEffect].fRadius -= 1.5f;
			pVtx[0].col = D3DXCOLOR(0,255, 255, 255);
			pVtx[1].col = D3DXCOLOR(0,255, 255, 255);
			pVtx[2].col = D3DXCOLOR(0,255, 255, 255);
			pVtx[3].col = D3DXCOLOR(0,255, 255, 255);
			if (0 >= g_aEffect[nCntEffect].pos.x >= SCREEN_HEIGHT || 0 >= g_aEffect[nCntEffect].pos.y >= SCREEN_WIDTH)
			{
				g_aEffect[nCntEffect].bUse = false;
			}
			if (g_aEffect[nCntEffect].nLife == 0)
			{
				//�����̐ݒ�
				//SetExplosion(g_aEffect[nCntEffect].pos,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				g_aEffect[nCntEffect].bUse = false;
			}
		}
		pVtx += 4;
	}
	g_pVtxBuffEffect->Unlock();
}
//�e�̕`�揈��
void DrawEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEffect;
	//�f�o�C�X�擾
	pDevice = GetDevice();
	pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	//���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//�e�N�X�`���̐ݒ�
	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{//�e���g�p����Ă���
			pDevice->SetTexture(0, g_pTextureEffect);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntEffect * 4, 2);
		}
	}

	//���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}
//�e�̐ݒ菈��
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadius, int nLife)
{
	int nCntEffect;
	VERTEX_2D* pVtx;

	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == false)
		{
			pVtx[0].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].pos.y - g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].pos.y - g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].fRadius, 0.0f);

			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			g_aEffect[nCntEffect].pos = pos;
			g_aEffect[nCntEffect].col = col;
			g_aEffect[nCntEffect].fRadius = fRadius;
			g_aEffect[nCntEffect].nLife = nLife;
			g_aEffect[nCntEffect].bUse = true;
			break;
		}
		pVtx += 4;
	}
	g_pVtxBuffEffect->Unlock();
}
