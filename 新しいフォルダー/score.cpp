#include "score.h"

//グローバル
LPDIRECT3DTEXTURE9 g_TextureScore = NULL;		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;	//頂点バッファへのポインタ
D3DXVECTOR3 g_posScore;							//スコアの位置
int g_nScore;									//スコアの値

//スコアの初期化処理
void InitScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\number000.png",
		&g_TextureScore);
	g_posScore = D3DXVECTOR3(0.0f,0.0f,0.0f);
	g_nScore = 0;
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL);
	VERTEX_2D* pVtx;
	//ロック
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);
	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(900.0f, 50.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1200.0f, 50.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(900.0f, 300.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1200.0f, 300.0f, 0.0f);

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
	pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.25f);
	pVtx[3].tex = D3DXVECTOR2(0.5f, 0.25f);
	//アンロック
	g_pVtxBuffScore->Unlock();
}

//スコアの終了処理
void UninitScore(void)
{
	//テクスチャの破棄
	if (g_TextureScore != NULL)
	{
		g_TextureScore->Release();
		g_TextureScore = NULL;
	}
	//テクスチャの破棄
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}
}

//スコアの更新処理
void UpdateScore(void)
{
	//見た目に変化・演出を加えたかったらやる
}

//スコアの描画処理
void DrawScore(void)
{//必要桁数分の描画

}

//スコアの設定処理
void SetScore(int nScore)
{
	int aPosTexU[8],nCount,nDate=10000000,aDate=1000000;	//各桁の数字を格納
	g_nScore = nScore;
	for (nCount = 0; nCount < 8; nCount++)
	{
		//桁ごとに分割する
		if (aPosTexU[nCount] == aPosTexU[0])
		{
			aPosTexU[nCount] = g_nScore / 10000000;//8桁目
		}
		else
		{
			aPosTexU[nCount] = g_nScore % nDate / aDate;//7桁目
			nDate = nDate / 10;
			aDate = aDate / 10;
		}
	}
	//テクスチャ座標の設定

}

//スコアの加算処理
void AddScore(int nValue)
{
	int aPosTexU[8], nCount, nDate = 10000000, aDate = 1000000;	//各桁の数字を格納
	g_nScore += nValue;
	for (nCount = 0; nCount < 8; nCount++)
	{
		//桁ごとに分割する
		if (aPosTexU[nCount] == aPosTexU[0])
		{
			aPosTexU[nCount] = g_nScore / 10000000;//8桁目
		}
		else
		{
			aPosTexU[nCount] = g_nScore % nDate / aDate;//7桁目
			nDate = nDate / 10;
			aDate = aDate / 10;
		}
	}
	//テクスチャ座標の設定

}