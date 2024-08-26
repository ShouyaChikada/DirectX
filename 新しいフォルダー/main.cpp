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
//グローバル変数
LPDIRECT3D9 g_pD3D = NULL;//Direct3Dオブジェクトへのポインタ
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;//Direct3Dデバイスへのポインタ

LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

MODE g_mode = MODE_TITLE;//現在のモード
//===========================
//メイン関数
//===========================
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hInstancePrev, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)//追加する(SAL:ソースコード注釈言語)
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

	HWND hWnd;//ウィンドウハンドル(識別子)
	MSG msg;//メッセージを格納する変数

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	//ウィンドウクラスの登録
	RegisterClassEx(&wcex);
	//クライアント領域を指定のサイズに調整
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
	//ウィンドウ生成
	hWnd = CreateWindowEx(0,//拡張ウィンドウスタイル
		CLASS_NAME,//ウィンドウクラスの名前
		WINDOW_NAME,//ウィンドウの名前
		WS_OVERLAPPEDWINDOW,//ウィンドウスタイル
		CW_USEDEFAULT,//ウィンドウの左上X座標
		CW_USEDEFAULT,//ウィンドウの左上Y座標
		(rect.right - rect.left),//ウィンドウの幅
		(rect.bottom - rect.top),//ウィンドウの高さ
		NULL,//親ウィンドウのハンドル
		NULL,//メニューハンドルまたは子ウィンドウID
		hInstance,//インスタンスハンドル
		NULL);//ウィンドウ作成データ
	//初期化処理
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{//初期化処理が失敗した場合
		return-1;
	}
	timeBeginPeriod(1);
	dwCurrentTime = 0;
	dwExeclastTime = timeGetTime();
	//ウィンドウを表示
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	//メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//windowsの処理
			if (msg.message == WM_QUIT)
			{//WM_QUITメッセージを受け取ったらメッセージループを抜ける
				break;
			}
			else
			{//メッセージの設定
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{//DirectXの処理
			dwCurrentTime = timeGetTime();
			if((dwCurrentTime-dwExeclastTime) >=(1000/60))
			{
				dwExeclastTime = dwCurrentTime;
				//更新処理
				Update();
				//描画処理
				Draw();
			}
		}
	}
	//終了処理
	Uninit();
	timeEndPeriod(1);
	//ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);
	return(int)msg.wParam;
}
//ウィンドウプロシージャ
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;
	HWND hWndButtonFinish;//終了ボタンのウィンドウハンドル(識別子)
	HWND hWndButtonCopy; //コピーボタンのウインドウハンドル(識別子)
	static HWND hWndEditInput;//入力ウィンドウハンドル(識別子)
	static HWND hWndEditOutput;//出力ウインドウハンドル(識別子)
	char aStringInput[256]; //コピー元のテキストを格納する変数
	char aStringOutput[256]; //コピー先のテキストを格納する変数
	HDC hDC; //デバイスコンテキスト(GDIオブジェクト)のハンドル
	PAINTSTRUCT ps; //クライアント領域の描画に必要な情報
	HBRUSH hBrush, hBrushOld;//ブラシのハンドル
	HPEN hPen, hPenOld;//ペンのハンドル
	static int nMoveX = 4;//線分の始点(X座標)の移動量
	static int nMoveY = 5;//線分の始点(Y座標)の移動量
	static POINT pos = { 100,100 };//線分の始点{X座標,Y座標}
	static POINT ros = { 100,200 };//線分の始点{X座標,Y座標}
	static POINT las = { 200,200 };//線分の始点{X座標,Y座標}
	static POINT res = { 200,100 };//線分の始点{X座標,Y座標}
	static POINT rus = { 100,100 };//線分の始点{X座標,Y座標}
	//変数の型の前にconstを指定すると
	//その変数は書き換え不可の定数となる
	const RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };//ウィンドウの領域(矩形)
	char aString[256] = "test";//描画する
	switch (uMsg)
	{
	case WM_DESTROY://ウィンドウ破棄
	//WM_QUITメッセージを送る
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN://キー押下のメッセージ

		switch (wParam)
		{
		case VK_ESCAPE://ESCキーが押された
			nID = MessageBox(hWnd, "終了しますか", "確認", MB_YESNO | MB_ICONEXCLAMATION);
			if (nID == IDYES)
			{
				MessageBox(NULL, "終了します", "解答", MB_YESNO | MB_ICONHAND);
				//ウィンドウを破棄する(WM_DESTROYメッセージを送る)
				DestroyWindow(hWnd);
				break;
			}
			else if (nID == IDNO)
			{
				MessageBox(NULL, "キャンセルしました", "解答", MB_YESNO | MB_ICONASTERISK);
			}
			break;
		}
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);//既定の処理を返す
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
	//現在のディスプレイ
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}
	//デバイスの生成
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
	//レンターステートの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//サンプラーステートの設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	//テクスチャステージステートの設定
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	if (FAILED(InitKeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}
	//ジョイパッドの初期化処理
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
	////敵の初期化処理
	//InitEnemy();
	//SetEnemy(D3DXVECTOR3(800.0f,360.0f,0.0f),2);//任意の数だけ設定
	// 
	//フェードの設定
	SetFade(g_mode);
	return S_OK;
}
//終了処理
void Uninit(void)
{
	//UninitBullet();
	//UninitExplosion();
	//UninitBkg();
	//UninitPlayer();
	//UninitSound();
	
	UninitKeyboard();

	//ジョイパッドの更新処理
	UninitJoypad();

	//フェードの終了処理
	UninitFade();

	//タイトル画面の終了処理
	UninitTitle();

	//ゲーム画面の終了処理
	UninitGame();

	//リザルト画面の終了処理
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
//更新処理
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

	//フェードの更新処理
	UpdateFade();

	//UpdatePlayer();
	//UpdateBkg();
	//UpdateBullet();
	//UpdateExplosion();
}
//描画処理
void Draw(void)
{
	
	g_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{//描画開始が成功されたとき
		//DrawBkg();
		//DrawBullet();
		//DrawExplosion();
		//DrawPlayer();

		switch (g_mode)
		{
		case MODE_TITLE:	//タイトル画面
			DrawTitle();
			break;
		case MODE_GAME:		//ゲーム画面
			DrawGame();
			break;
		case MODE_RESULT:	//リザルト画面
			DrawResult();
			break;
		}

		//フェードの描画処理
		DrawFade();

		//描画終了
		g_pD3DDevice->EndScene();
	}
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);

}	

//モードの設定
void SetMode(MODE mode)
{
	//現在の画面(モード)の終了処理
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
	//新しい画面(モード)の初期化処理
	switch (mode)
	{
	case MODE_TITLE:	//タイトル画面
		InitTitle();
		break;
	case MODE_GAME:		//ゲーム画面
		InitGame();
		break;
	case MODE_RESULT:	//リザルト画面
		InitResult();
		break;
	}
	g_mode = mode;//現在の画面(モード)を切り替える
	
}
//モードの取得
MODE GetMode(void)
{
	return g_mode;
}
