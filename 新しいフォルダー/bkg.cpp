#include"main.h"
#include"bkg.h"
#include"player.h"
//�}�N��
#define NUM_BG (3)//�w�i�̐�
//�O���[�o���錾
LPDIRECT3DTEXTURE9 g_apTextureBG[NUM_BG] = {};//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtebuffBG;
float g_aPosTexU[NUM_BG];

//�|���S���̏���������
void InitBkg(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	int nCntBG;
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bg100.png",
		&g_apTextureBG[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bg101.png",
		&g_apTextureBG[1]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bg102.png",
		&g_apTextureBG[2]);

	
	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		g_aPosTexU[nCntBG] = 0.0f;
	}
	
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_BG,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtebuffBG,
		NULL);
	VERTEX_2D* pVtx;
	g_pVtebuffBG->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
	//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);
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
		pVtx[0].tex = D3DXVECTOR2(g_aPosTexU[nCntBG], 0.0f);
		pVtx[1].tex = D3DXVECTOR2(g_aPosTexU[nCntBG]+1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(g_aPosTexU[nCntBG], 1.0f);
		pVtx[3].tex = D3DXVECTOR2(g_aPosTexU[nCntBG]+1.0f, 1.0f);

		pVtx += 4;
	}
	//�A�����b�N
	g_pVtebuffBG->Unlock();
}

//�|���S���̏I������
void UninitBkg(void)
{
	int nCntBG;
	
	//�e�N�X�`���̔j��
	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		if (g_apTextureBG[nCntBG] != NULL)
		{	
				g_apTextureBG[nCntBG]->Release();
				g_apTextureBG[nCntBG] = NULL;
		}

	}
	if (g_pVtebuffBG != NULL)
	{
		g_pVtebuffBG->Release();
		g_pVtebuffBG = NULL;
	}

	
	
}
//�|���S���̍X�V����
void UpdateBkg(void)
{
	int nCntBG;
	VERTEX_2D* pVtx;
	g_pVtebuffBG->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		g_aPosTexU[nCntBG] += 0.001f * nCntBG + 1;
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

		pVtx[0].tex = D3DXVECTOR2(g_aPosTexU[nCntBG], 0.0f);
		pVtx[1].tex = D3DXVECTOR2(g_aPosTexU[nCntBG] + 1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(g_aPosTexU[nCntBG], 1.0f);
		pVtx[3].tex = D3DXVECTOR2(g_aPosTexU[nCntBG] + 1.0f, 1.0f);
	}
	pVtx += 4;
	g_pVtebuffBG->Unlock();
}
//�|���S���̕`�揈��
void DrawBkg(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBG;
	pDevice = GetDevice();
	pDevice->SetStreamSource(0, g_pVtebuffBG, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTextureBG[0]);
		pDevice->SetTexture(0, g_apTextureBG[1]);
		pDevice->SetTexture(0, g_apTextureBG[2]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
							   0,2); //���_���\���̂̃T�C�Y
	}
}