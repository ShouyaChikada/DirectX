#include "fade.h"


//グローバル変数
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffFade = NULL;
FADE g_fade;
MODE g_modeNext;									//次の画面
D3DXCOLOR g_colorFade;								//ポリゴン(フェード)の色

//フェードの初期化処理
void InitFade(MODE modeNext)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	VERTEX_2D* pVtx = 0;
	g_fade = FADE_IN;								//フェードイン状態に
	g_modeNext = modeNext;							//次の画面(モード)を設定
	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);//黒いポリゴン(不透明)にしておく

	//頂点バッファの生成・頂点情報の設定
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffFade,
		NULL);

	g_pVtxbuffFade->Lock(0, 0, (void**)&pVtx, 0);
	//頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(0, 0, 0, 255);
	pVtx[1].col = D3DCOLOR_RGBA(0, 0, 0, 255);
	pVtx[2].col = D3DCOLOR_RGBA(0, 0, 0, 255);
	pVtx[3].col = D3DCOLOR_RGBA(0, 0, 0, 255);
	g_pVtxbuffFade->Unlock();
	//モードの設定
	SetMode(g_modeNext);
}
//フェードの破棄処理
void UninitFade(void)
{
	if (g_pVtxbuffFade != NULL)
	{
		g_pVtxbuffFade->Release();
		g_pVtxbuffFade = NULL;
	}
}

//フェードの更新処理
void UpdateFade(void)
{
	VERTEX_2D* pVtx;

	if (g_fade != FADE_NONE)
	{
		if (g_fade == FADE_IN)
		{//フェードイン状態
			g_colorFade.a -= 0.02f;	//ポリゴンを透明にしていく

			if (g_colorFade.a <= 0.0f)
			{
				g_colorFade.a = 0.0f;
				g_fade = FADE_NONE;	//何もしていない状態に
			}
		}
		else if (g_fade == FADE_OUT)
		{//フェードアウト状態
			g_colorFade.a += 0.02f;	//ポリゴンを不透明にしていく
			if (g_colorFade.a >= 1.0f)
			{
				SetMode(g_modeNext);
				g_colorFade.a = 1.0f;
				g_fade = FADE_IN;	//フェードイン状態に
			}
		}
		g_pVtxbuffFade->Lock(0, 0, (void**)&pVtx, 0);
		//頂点カラーの設定
		pVtx[0].col = g_colorFade;
		pVtx[1].col = g_colorFade;
		pVtx[2].col = g_colorFade;
		pVtx[3].col = g_colorFade;
		g_pVtxbuffFade->Unlock();

	}
}
//フェードの描画処理
void DrawFade(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxbuffFade, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	//テクスチャを設定
	pDevice->SetTexture(0, NULL);//テクスチャを使用しないときは必ずNULLを指定する
	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類
		0,
		2); //頂点情報構造体のサイズ
}
//フェードの設定処理
void SetFade(MODE modeNext)
{
	g_fade = FADE_OUT;									//フェードアウト状態に
	g_modeNext = modeNext;								//次の画面(モード)を設定
	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	//黒いポリゴン(透明)にしておく
}
//フェードの取得処理
FADE GetFade(void)
{
	return g_fade;
}