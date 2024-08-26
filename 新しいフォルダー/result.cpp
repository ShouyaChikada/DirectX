#include "result.h"
#include "input.h"
#include "main.h"

//ぐろーばる
LPDIRECT3DTEXTURE9 g_apTextureResult = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;

//タイトル画面の初期化処理
void InitResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\result000.png",
		&g_apTextureResult);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL);
	VERTEX_2D* pVtx;
	//ロック
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);
	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	//アンロック
	g_pVtxBuffResult->Unlock();
}
//リザルトの終了処理
void UninitResult(void)
{
	//入力デバイス
	if (g_apTextureResult != NULL)
	{		  
		g_apTextureResult->Release();
		g_apTextureResult = NULL;
	}
	//Direct
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}
}
//タイトル画面の更新処理
void UpdateResult(void)
{
	if (KeyboardTrigger(DIK_RETURN) == true)
	{//決定キー(ENTERキー)が押された
		//モード設定(ゲーム画面に移行)
		SetMode(MODE_RESULT);
	}
}//タイトル画面の描画処理
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	//テクスチャの設定
	pDevice->SetTexture(0, g_apTextureResult);
	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類
		0,
		2); //頂点情報構造体のサイズ
}
