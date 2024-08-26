//=============================================
//
// athor chikada shouya
//
//=============================================
#include"main.h"
#include"player.h"
#include"bkg.h"
#include"input.h"
#include "bullet.h"
#include "explosion.h"
#include "enemy.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "fade.h"
#include "sound.h"
//�O���[�o���ϐ�
LPDIRECT3D9 g_pD3D = NULL;//Direct3D�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;//Direct3D�f�o�C�X�ւ̃|�C���^

LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

MODE g_mode = MODE_TITLE;//���݂̃��[�h
//===========================
//���C���֐�
//===========================
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hInstancePrev, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)//�ǉ�����(SAL:�\�[�X�R�[�h���ߌ���)
{
	DWORD dwCurrentTime;
	DWORD dwExeclastTime;
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WindowProc,
		0,
		0,
		hInstance,
		LoadIcon(NULL,IDI_APPLICATION),
		LoadCursor(NULL,IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		LoadIcon(NULL,IDI_APPLICATION)
	};

	HWND hWnd;//�E�B���h�E�n���h��(���ʎq)
	MSG msg;//���b�Z�[�W���i�[����ϐ�

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	//�E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);
	//�N���C�A���g�̈���w��̃T�C�Y�ɒ���
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
	//�E�B���h�E����
	hWnd = CreateWindowEx(0,//�g���E�B���h�E�X�^�C��
		CLASS_NAME,//�E�B���h�E�N���X�̖��O
		WINDOW_NAME,//�E�B���h�E�̖��O
		WS_OVERLAPPEDWINDOW,//�E�B���h�E�X�^�C��
		CW_USEDEFAULT,//�E�B���h�E�̍���X���W
		CW_USEDEFAULT,//�E�B���h�E�̍���Y���W
		(rect.right - rect.left),//�E�B���h�E�̕�
		(rect.bottom - rect.top),//�E�B���h�E�̍���
		NULL,//�e�E�B���h�E�̃n���h��
		NULL,//���j���[�n���h���܂��͎q�E�B���h�EID
		hInstance,//�C���X�^���X�n���h��
		NULL);//�E�B���h�E�쐬�f�[�^
	//����������
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{//���������������s�����ꍇ
		return-1;
	}
	timeBeginPeriod(1);
	dwCurrentTime = 0;
	dwExeclastTime = timeGetTime();
	//�E�B���h�E��\��
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	//���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//windows�̏���
			if (msg.message == WM_QUIT)
			{//WM_QUIT���b�Z�[�W���󂯎�����烁�b�Z�[�W���[�v�𔲂���
				break;
			}
			else
			{//���b�Z�[�W�̐ݒ�
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{//DirectX�̏���
			dwCurrentTime = timeGetTime();
			if((dwCurrentTime-dwExeclastTime) >=(1000/60))
			{
				dwExeclastTime = dwCurrentTime;
				//�X�V����
				Update();
				//�`�揈��
				Draw();
			}
		}
	}
	//�I������
	Uninit();
	timeEndPeriod(1);
	//�E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);
	return(int)msg.wParam;
}
//�E�B���h�E�v���V�[�W��
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;
	HWND hWndButtonFinish;//�I���{�^���̃E�B���h�E�n���h��(���ʎq)
	HWND hWndButtonCopy; //�R�s�[�{�^���̃E�C���h�E�n���h��(���ʎq)
	static HWND hWndEditInput;//���̓E�B���h�E�n���h��(���ʎq)
	static HWND hWndEditOutput;//�o�̓E�C���h�E�n���h��(���ʎq)
	char aStringInput[256]; //�R�s�[���̃e�L�X�g���i�[����ϐ�
	char aStringOutput[256]; //�R�s�[��̃e�L�X�g���i�[����ϐ�
	HDC hDC; //�f�o�C�X�R���e�L�X�g(GDI�I�u�W�F�N�g)�̃n���h��
	PAINTSTRUCT ps; //�N���C�A���g�̈�̕`��ɕK�v�ȏ��
	HBRUSH hBrush, hBrushOld;//�u���V�̃n���h��
	HPEN hPen, hPenOld;//�y���̃n���h��
	static int nMoveX = 4;//�����̎n�_(X���W)�̈ړ���
	static int nMoveY = 5;//�����̎n�_(Y���W)�̈ړ���
	static POINT pos = { 100,100 };//�����̎n�_{X���W,Y���W}
	static POINT ros = { 100,200 };//�����̎n�_{X���W,Y���W}
	static POINT las = { 200,200 };//�����̎n�_{X���W,Y���W}
	static POINT res = { 200,100 };//�����̎n�_{X���W,Y���W}
	static POINT rus = { 100,100 };//�����̎n�_{X���W,Y���W}
	//�ϐ��̌^�̑O��const���w�肷���
	//���̕ϐ��͏��������s�̒萔�ƂȂ�
	const RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };//�E�B���h�E�̗̈�(��`)
	char aString[256] = "test";//�`�悷��
	switch (uMsg)
	{
	case WM_DESTROY://�E�B���h�E�j��
	//WM_QUIT���b�Z�[�W�𑗂�
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN://�L�[�����̃��b�Z�[�W

		switch (wParam)
		{
		case VK_ESCAPE://ESC�L�[�������ꂽ
			nID = MessageBox(hWnd, "�I�����܂���", "�m�F", MB_YESNO | MB_ICONEXCLAMATION);
			if (nID == IDYES)
			{
				MessageBox(NULL, "�I�����܂�", "��", MB_YESNO | MB_ICONHAND);
				//�E�B���h�E��j������(WM_DESTROY���b�Z�[�W�𑗂�)
				DestroyWindow(hWnd);
				break;
			}
			else if (nID == IDNO)
			{
				MessageBox(NULL, "�L�����Z�����܂���", "��", MB_YESNO | MB_ICONASTERISK);
			}
			break;
		}
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);//����̏�����Ԃ�
}
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;
	D3DPRESENT_PARAMETERS d3dpp;
	//Direct3D
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}
	//���݂̃f�B�X�v���C
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}
	//�f�o�C�X�̐���
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.Windowed = bWindow;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	//Direct3D
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_HARDWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}
	//�����^�[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//�T���v���[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	//�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	if (FAILED(InitKeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}
	//�W���C�p�b�h�̏���������
	if (FAILED(InitJoypad()))
	{
		return E_FAIL;
	}
	//InitSound(hWnd);
	//return S_OK;
	InitFade(g_mode);
	//InitBkg();
	//InitPlayer();
	//InitBullet();
	//InitExplosion();
	////�G�̏���������
	//InitEnemy();
	//SetEnemy(D3DXVECTOR3(800.0f,360.0f,0.0f),2);//�C�ӂ̐������ݒ�
	// 
	//�t�F�[�h�̐ݒ�
	SetFade(g_mode);
	return S_OK;
}
//�I������
void Uninit(void)
{
	//UninitBullet();
	//UninitExplosion();
	//UninitBkg();
	//UninitPlayer();
	//UninitSound();
	
	UninitKeyboard();

	//�W���C�p�b�h�̍X�V����
	UninitJoypad();

	//�t�F�[�h�̏I������
	UninitFade();

	//�^�C�g����ʂ̏I������
	UninitTitle();

	//�Q�[����ʂ̏I������
	UninitGame();

	//���U���g��ʂ̏I������
	UninitResult();
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}
//�X�V����
void Update(void)
{
	UpdateJoypad();

	UpdateKeyboard();

	switch (g_mode)
	{
	case MODE_TITLE:
		UpdateTitle();
		break;
	case MODE_GAME:
		UpdateGame();
		break;
	case MODE_RESULT:
		UpdateResult();
		break;
	}

	//�t�F�[�h�̍X�V����
	UpdateFade();

	//UpdatePlayer();
	//UpdateBkg();
	//UpdateBullet();
	//UpdateExplosion();
}
//�`�揈��
void Draw(void)
{
	
	g_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{//�`��J�n���������ꂽ�Ƃ�
		//DrawBkg();
		//DrawBullet();
		//DrawExplosion();
		//DrawPlayer();

		switch (g_mode)
		{
		case MODE_TITLE:	//�^�C�g�����
			DrawTitle();
			break;
		case MODE_GAME:		//�Q�[�����
			DrawGame();
			break;
		case MODE_RESULT:	//���U���g���
			DrawResult();
			break;
		}

		//�t�F�[�h�̕`�揈��
		DrawFade();

		//�`��I��
		g_pD3DDevice->EndScene();
	}
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);

}	

//���[�h�̐ݒ�
void SetMode(MODE mode)
{
	//���݂̉��(���[�h)�̏I������
	switch (g_mode)
	{
	case MODE_TITLE:
		UninitTitle();
		break;
	case MODE_GAME:
		UninitGame();
		break;
	case MODE_RESULT:
		UninitResult();
		break;
	}
	//�V�������(���[�h)�̏���������
	switch (mode)
	{
	case MODE_TITLE:	//�^�C�g�����
		InitTitle();
		break;
	case MODE_GAME:		//�Q�[�����
		InitGame();
		break;
	case MODE_RESULT:	//���U���g���
		InitResult();
		break;
	}
	g_mode = mode;//���݂̉��(���[�h)��؂�ւ���
	
}
//���[�h�̎擾
MODE GetMode(void)
{
	return g_mode;
}
