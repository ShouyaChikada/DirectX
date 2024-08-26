#include "score.h"

//�O���[�o��
LPDIRECT3DTEXTURE9 g_TextureScore = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;	//���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posScore;							//�X�R�A�̈ʒu
int g_nScore;									//�X�R�A�̒l

//�X�R�A�̏���������
void InitScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\number000.png",
		&g_TextureScore);
	g_posScore = D3DXVECTOR3(0.0f,0.0f,0.0f);
	g_nScore = 0;
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL);
	VERTEX_2D* pVtx;
	//���b�N
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(900.0f, 50.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1200.0f, 50.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(900.0f, 300.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1200.0f, 300.0f, 0.0f);

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
	g_pVtxBuffScore->Unlock();
}

//�X�R�A�̏I������
void UninitScore(void)
{
	//�e�N�X�`���̔j��
	if (g_TextureScore != NULL)
	{
		g_TextureScore->Release();
		g_TextureScore = NULL;
	}
	//�e�N�X�`���̔j��
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}
}

//�X�R�A�̍X�V����
void UpdateScore(void)
{
	//�����ڂɕω��E���o������������������
}

//�X�R�A�̕`�揈��
void DrawScore(void)
{//�K�v�������̕`��

}

//�X�R�A�̐ݒ菈��
void SetScore(int nScore)
{
	int aPosTexU[8],nCount,nDate=10000000,aDate=1000000;	//�e���̐������i�[
	g_nScore = nScore;
	for (nCount = 0; nCount < 8; nCount++)
	{
		//�����Ƃɕ�������
		if (aPosTexU[nCount] == aPosTexU[0])
		{
			aPosTexU[nCount] = g_nScore / 10000000;//8����
		}
		else
		{
			aPosTexU[nCount] = g_nScore % nDate / aDate;//7����
			nDate = nDate / 10;
			aDate = aDate / 10;
		}
	}
	//�e�N�X�`�����W�̐ݒ�

}

//�X�R�A�̉��Z����
void AddScore(int nValue)
{
	int aPosTexU[8], nCount, nDate = 10000000, aDate = 1000000;	//�e���̐������i�[
	g_nScore += nValue;
	for (nCount = 0; nCount < 8; nCount++)
	{
		//�����Ƃɕ�������
		if (aPosTexU[nCount] == aPosTexU[0])
		{
			aPosTexU[nCount] = g_nScore / 10000000;//8����
		}
		else
		{
			aPosTexU[nCount] = g_nScore % nDate / aDate;//7����
			nDate = nDate / 10;
			aDate = aDate / 10;
		}
	}
	//�e�N�X�`�����W�̐ݒ�

}