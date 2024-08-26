#include "fade.h"


//�O���[�o���ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffFade = NULL;
FADE g_fade;
MODE g_modeNext;									//���̉��
D3DXCOLOR g_colorFade;								//�|���S��(�t�F�[�h)�̐F

//�t�F�[�h�̏���������
void InitFade(MODE modeNext)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	VERTEX_2D* pVtx = 0;
	g_fade = FADE_IN;								//�t�F�[�h�C����Ԃ�
	g_modeNext = modeNext;							//���̉��(���[�h)��ݒ�
	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);//�����|���S��(�s����)�ɂ��Ă���

	//���_�o�b�t�@�̐����E���_���̐ݒ�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffFade,
		NULL);

	g_pVtxbuffFade->Lock(0, 0, (void**)&pVtx, 0);
	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(0, 0, 0, 255);
	pVtx[1].col = D3DCOLOR_RGBA(0, 0, 0, 255);
	pVtx[2].col = D3DCOLOR_RGBA(0, 0, 0, 255);
	pVtx[3].col = D3DCOLOR_RGBA(0, 0, 0, 255);
	g_pVtxbuffFade->Unlock();
	//���[�h�̐ݒ�
	SetMode(g_modeNext);
}
//�t�F�[�h�̔j������
void UninitFade(void)
{
	if (g_pVtxbuffFade != NULL)
	{
		g_pVtxbuffFade->Release();
		g_pVtxbuffFade = NULL;
	}
}

//�t�F�[�h�̍X�V����
void UpdateFade(void)
{
	VERTEX_2D* pVtx;

	if (g_fade != FADE_NONE)
	{
		if (g_fade == FADE_IN)
		{//�t�F�[�h�C�����
			g_colorFade.a -= 0.02f;	//�|���S���𓧖��ɂ��Ă���

			if (g_colorFade.a <= 0.0f)
			{
				g_colorFade.a = 0.0f;
				g_fade = FADE_NONE;	//�������Ă��Ȃ���Ԃ�
			}
		}
		else if (g_fade == FADE_OUT)
		{//�t�F�[�h�A�E�g���
			g_colorFade.a += 0.02f;	//�|���S����s�����ɂ��Ă���
			if (g_colorFade.a >= 1.0f)
			{
				SetMode(g_modeNext);
				g_colorFade.a = 1.0f;
				g_fade = FADE_IN;	//�t�F�[�h�C����Ԃ�
			}
		}
		g_pVtxbuffFade->Lock(0, 0, (void**)&pVtx, 0);
		//���_�J���[�̐ݒ�
		pVtx[0].col = g_colorFade;
		pVtx[1].col = g_colorFade;
		pVtx[2].col = g_colorFade;
		pVtx[3].col = g_colorFade;
		g_pVtxbuffFade->Unlock();

	}
}
//�t�F�[�h�̕`�揈��
void DrawFade(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxbuffFade, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	//�e�N�X�`����ݒ�
	pDevice->SetTexture(0, NULL);//�e�N�X�`�����g�p���Ȃ��Ƃ��͕K��NULL���w�肷��
	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
		0,
		2); //���_���\���̂̃T�C�Y
}
//�t�F�[�h�̐ݒ菈��
void SetFade(MODE modeNext)
{
	g_fade = FADE_OUT;									//�t�F�[�h�A�E�g��Ԃ�
	g_modeNext = modeNext;								//���̉��(���[�h)��ݒ�
	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	//�����|���S��(����)�ɂ��Ă���
}
//�t�F�[�h�̎擾����
FADE GetFade(void)
{
	return g_fade;
}