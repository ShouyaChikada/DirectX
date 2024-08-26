#include "bullet.h"
#include "main.h"
#include "player.h"
#include "explosion.h"
//�}�N����`
#define MAX_EXPLOSION (128)//�e�̍ő吔
//�e�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	D3DXVECTOR3 col;//�ړ���
	int nCounterAnim;//�A�j���[�V�����J�E���^�[
	int nPatternAnim;//�A�j���[�V�����p�^�[��No.
	bool bUse;//�g�p���Ă��邩�ǂ���
}Explosion;
//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureExplosion = NULL;//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;//���_�o�b�t�@�ւ̃|�C���^
Explosion g_aExplosion[MAX_EXPLOSION];//�����̏��
//�e�̏���������
void InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntExplosion;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\explosion000.png",
		&g_pTextureExplosion);
	//�e�̏���������
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		g_aExplosion[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].col = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].nCounterAnim = 0;
		g_aExplosion[nCntExplosion].nPatternAnim = 0;
		g_aExplosion[nCntExplosion].bUse = false;
	}
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EXPLOSION,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion,
		NULL);
	VERTEX_2D* pVtx;
	//���b�N
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
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
	g_pVtxBuffExplosion->Unlock();
}
//�e�̏I������
void UninitExplosion(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}
	//�e�N�X�`���̔j��
	if (g_pVtxBuffExplosion != NULL)
	{			  
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}
}
//�e�̍X�V����
void UpdateExplosion(void)
{
	int nCntExplosion;
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	VERTEX_2D* pVtx;

	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{//�������g�p����Ă���
			/*g_aExplosion[nCntExplosion].pos.x += g_aExplosion[nCntExplosion].move.x;
			g_aExplosion[nCntExplosion].pos.y += g_aExplosion[nCntExplosion].move.y;*/

			pVtx[0].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - 50.0f, g_aExplosion[nCntExplosion].pos.y - 50.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + 50.0f, g_aExplosion[nCntExplosion].pos.y - 50.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - 50.0f, g_aExplosion[nCntExplosion].pos.y + 50.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + 50.0f, g_aExplosion[nCntExplosion].pos.y + 50.0f, 0.0f);

			if (0>=g_aExplosion[nCntExplosion].pos.x >=SCREEN_HEIGHT||0>=g_aExplosion[nCntExplosion].pos.y>=SCREEN_WIDTH)
			{
				g_aExplosion[nCntExplosion].bUse = false;
			}
		}
		pVtx += 4;
	}
	g_pVtxBuffExplosion->Unlock();
}
//�e�̕`�揈��
void DrawExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntExplosion;
	//�f�o�C�X�擾
	pDevice = GetDevice();

	pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	//�e�N�X�`���̐ݒ�
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{//�e���g�p����Ă���
			pDevice->SetTexture(0, g_pTextureExplosion);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntExplosion * 4, 2);
		}
	}
}
//�e�̐ݒ菈��
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	int nCntExplosion;
	VERTEX_2D* pVtx;

	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == false)
		{//�������g�p����Ă��Ȃ�
			g_aExplosion[nCntExplosion].pos = pos;
			g_aExplosion[nCntExplosion].col = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aExplosion[nCntExplosion].nCounterAnim = 0;
			g_aExplosion[nCntExplosion].nPatternAnim = 0;
			g_aExplosion[nCntExplosion].bUse = true;

			pVtx[0].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - 50.0f, g_aExplosion[nCntExplosion].pos.y - 50.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + 50.0f, g_aExplosion[nCntExplosion].pos.y - 50.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - 50.0f, g_aExplosion[nCntExplosion].pos.y + 50.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + 50.0f, g_aExplosion[nCntExplosion].pos.y + 50.0f, 0.0f);

			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			//�e�N�X�`�����W
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 0.125f);
			pVtx[3].tex = D3DXVECTOR2(0.125f, 0.25f);
			break;
		}
		pVtx += 4;
	}
	g_pVtxBuffExplosion->Unlock();
}