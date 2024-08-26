#include "main.h"
#include "player.h"
#include "input.h"
#include "bullet.h"
#include "effect.h"
//グローバル宣言
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;//テクスチャへのポインタ
LPDIRECT3DTEXTURE9 g_pTexturePlayer1 = NULL;//テクスチャへのポインタ

LPDIRECT3DVERTEXBUFFER9 g_pVtebuffPlayer;
LPDIRECT3DVERTEXBUFFER9 g_pVtebuffPlayer1;

Player g_player;
//ポリゴンの初期化処理
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\maxresdefault1.png",
		&g_pTexturePlayer);
	//初期化
	g_player.nCounterAnim=0;
	g_player.nPatternAnim = 0;
	g_player.pos = D3DXVECTOR3(200.0f, 100.0f,0.0f);//位置を初期化する
	g_player.move = D3DXVECTOR3(0.0f,0.0f,0.0f);//動きを初期化する
	g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//向きを初期化する

	//対角線の長さを算出する
	g_player.fLength = sqrtf(PLAYER_WIDTH * PLAYER_WIDTH + PLAYER_HEIGHT * PLAYER_HEIGHT) / 2.0f;
	//対角線の角度を算出する
	g_player.fAngle = atan2f(PLAYER_WIDTH,PLAYER_HEIGHT);
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtebuffPlayer,
		NULL);
	VERTEX_2D* pVtx;
	//ロック
	g_pVtebuffPlayer->Lock(0, 0, (void**)&pVtx, 0);
	//頂点座標の設定
	pVtx[0].pos.x = g_player.pos.x + sinf(g_player.rot.z + (-D3DX_PI + g_player.fAngle)) * g_player.fLength;
	pVtx[0].pos.y = g_player.pos.y + cosf(g_player.rot.z + (-D3DX_PI + g_player.fAngle)) * g_player.fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_player.pos.x + sinf(g_player.rot.z + (D3DX_PI - g_player.fAngle)) * g_player.fLength;
	pVtx[1].pos.y = g_player.pos.y + cosf(g_player.rot.z + (D3DX_PI - g_player.fAngle)) * g_player.fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_player.pos.x + sinf(g_player.rot.z + (0.0f - g_player.fAngle)) * g_player.fLength;
	pVtx[2].pos.y = g_player.pos.y + cosf(g_player.rot.z + (0.0f - g_player.fAngle)) * g_player.fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_player.pos.x + sinf(g_player.rot.z + (0.0f + g_player.fAngle)) * g_player.fLength;
	pVtx[3].pos.y = g_player.pos.y + cosf(g_player.rot.z + (0.0f + g_player.fAngle)) * g_player.fLength;
	pVtx[3].pos.z = 0.0f;

	//rhwの設定
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
	g_pVtebuffPlayer->Unlock();
}

//ポリゴンの終了処理
void UninitPlayer(void)
{
	//テクスチャの破棄
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}
	//テクスチャの破棄
	if (g_pVtebuffPlayer != NULL)
	{
		g_pVtebuffPlayer->Release();
		g_pVtebuffPlayer = NULL;
	}
}
//ポリゴンの更新処理
void UpdatePlayer(void)
{
	VERTEX_2D* pVtx;
	static float fDate=0.2f;
	
	//ロック
	g_pVtebuffPlayer->Lock(0, 0, (void**)&pVtx, 0);
	g_player.nCounterAnim++;


	//頂点座標の設定
	if (GetKeyboardPress(DIK_A) == true)
	{
		if (GetKeyboardPress(DIK_W) == true)//Wキーを押したとき
		{//左上移動

			g_player.move.x += sinf(-D3DX_PI * 0.75f) * 0.7f;
			g_player.move.y += cosf(-D3DX_PI * 0.75f) * 0.7f;
			if (GetKeyboardPress(DIK_Q) == true)//Qキーを押したとき
			{//右回転
				g_player.rot.z += 0.35f;
			}
			else if (GetKeyboardPress(DIK_E) == true)//Eキーを押したとき
			{//左回転
				g_player.rot.z -= 0.35f;
			}
			fDate = 0.2f;
		}

		else if (GetKeyboardPress(DIK_S) == true)//Sキーを押したとき
		{//左下移動													
			g_player.move.x += sinf(-D3DX_PI * 0.25f) * 0.7f;			  
			g_player.move.y += cosf(-D3DX_PI * 0.25f) * 0.7f;	
			if (GetKeyboardPress(DIK_Q) == true)//Qキーを押したとき
			{//右回転
				g_player.rot.z += 0.35f;
			}
			else if (GetKeyboardPress(DIK_E) == true)//Eキーを押したとき
			{//左回転
				g_player.rot.z -= 0.35f;
			}
			fDate = 0.2f;
		}
		else//Aキーを押したとき
		{//右移動
			g_player.move.x -= 0.7f;
			if (GetKeyboardPress(DIK_Q) == true)//Qキーを押したとき
			{//右回転
				g_player.rot.z += 0.35f;
			}
			else if (GetKeyboardPress(DIK_E) == true)//Eキーを押したとき
			{//左回転
				g_player.rot.z -= 0.35f;
			}
		}
	}
	else if (GetKeyboardPress(DIK_D) == true)
	{
		if (GetKeyboardPress(DIK_W) == true)//Wキーを押したとき
		{//右上移動
			g_player.move.x += sinf(D3DX_PI * 0.75f) * 0.7f;
			g_player.move.y += cosf(D3DX_PI * 0.75f) * 0.7f;
			if (GetKeyboardPress(DIK_Q) == true)//Qキーを押したとき
			{//右回転
				g_player.rot.z += 0.35f;
			}
			else if (GetKeyboardPress(DIK_E) == true)//Eキーを押したとき
			{//左回転
				g_player.rot.z -= 0.35f;
			}
			fDate = 0.2f;
		}
		else if (GetKeyboardPress(DIK_S) == true)//Sキーを押したとき
		{//右下移動
			g_player.move.x += sinf(D3DX_PI * 0.25f) * 0.7f;
			g_player.move.y += cosf(D3DX_PI * 0.25f) * 0.7f;
			if (GetKeyboardPress(DIK_Q) == true)//Qキーを押したとき
			{//右回転
				g_player.rot.z += 0.35f;
			}
			else if (GetKeyboardPress(DIK_E) == true)//Eキーを押したとき
			{//左回転
				g_player.rot.z -= 0.35f;
			}
			fDate = 0.2f;
		}
		else//Dキーを押したとき
		{//右移動
			g_player.move.x += 0.7f;
			if (GetKeyboardPress(DIK_Q) == true)//Qキーを押したとき
			{//右回転
				g_player.rot.z += 0.35f;
			}
			else if (GetKeyboardPress(DIK_E) == true)//Eキーを押したとき
			{//左回転
				g_player.rot.z -= 0.35f;
			}
			fDate = -0.2f;
		}
	}
	else if (GetKeyboardPress(DIK_W) == true)//Wキーを押したとき
	{//上移動
		g_player.move.y -= 0.7f;
		if (GetKeyboardPress(DIK_Q) == true)//Qキーを押したとき
		{//右回転
			g_player.rot.z += 0.35f;
		}
		else if (GetKeyboardPress(DIK_E) == true)//Eキーを押したとき
		{//左回転
			g_player.rot.z -= 0.35f;
		}
	}
	else if (GetKeyboardPress(DIK_S) == true)//Sキーを押したとき
	{//下移動
		g_player.move.y -= -0.7f;
		if (GetKeyboardPress(DIK_Q) == true)//Qキーを押したとき
		{//右回転
			g_player.rot.z += 0.35f;
		}
		else if (GetKeyboardPress(DIK_E) == true)//Eキーを押したとき
		{//左回転
			g_player.rot.z -= 0.35f;
		}
	}
	else if (GetKeyboardPress(DIK_Q) == true)//Qキーを押したとき
	{//右回転
		g_player.rot.z += 0.35f;
	}
	else if (GetKeyboardPress(DIK_E) == true)//Eキーを押したとき
	{//左回転
		g_player.rot.z -= 0.35f;
	}
	else if (KeyboardTrigger(DIK_B) == true)//Bキーを押したとき
	{//拡大
		if (g_player.fLength <= 900.0f)
		{
			g_player.fLength += 100.0f;
		}
		else if (g_player.fLength >= 900.0f)
		{
			g_player.fLength += 0.0f;
		}
		
	}
	else if (KeyboardTrigger(DIK_L) == true)//Lキーを押したとき
	{//縮小
		if (g_player.fLength <= 100.0f)
		{
			g_player.fLength += 0.0f;
		}
		else if(g_player.fLength >=100.0f)
		{
			g_player.fLength -= 100.0f;
		}
	}
	else if (KeyboardTrigger(DIK_P) == true)//Pキーを押したとき
	{//右９０度
		g_player.rot.z += 1.57f;
	}
	else if (KeyboardTrigger(DIK_O) == true)//Oキーを押したとき
	{//左９０度
		g_player.rot.z -= 1.57f;
	}
	else if (KeyboardTrigger(DIK_I) == true)//Iキーを押したとき
	{//元の位置に戻る
		g_player.rot.z += 0.0f;
	}
	else if (KeyboardTrigger(DIK_N) == true)//Iキーを押したとき
	{//元のサイズに戻る
		g_player.fLength = sqrtf(PLAYER_WIDTH * PLAYER_WIDTH + PLAYER_HEIGHT * PLAYER_HEIGHT) / 2.0f;
	}
	if (KeyboardTrigger(DIK_SPACE) == true)//SPACEキーを押したとき
	{
		SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI *0.5) * 20.0f, cosf(g_player.rot.z + D3DX_PI*0.5) * 10.0f, 0.0f),100,BULLETTYPE_PLAYER);
	}
	if (GetJoypadPress(JOYKEY_UP) == true)
	{
		g_player.pos.y -= 1.0f;
	}
	//位置を更新
	g_player.pos.x += g_player.move.x;
	g_player.pos.y += g_player.move.y;
	//移動量を更新
	g_player.move.x += (0.0f - g_player.move.x) * 0.05f;
	g_player.move.y += (0.0f - g_player.move.y) * 0.05f;
	//pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - 25.0f, g_player.pos.y - 25.0f, 0.0f);
	//pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + 25.0f, g_player.pos.y - 25.0f, 0.0f);
	//pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - 25.0f, g_player.pos.y + 25.0f, 0.0f);
	//pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + 25.0f, g_player.pos.y + 25.0f, 0.0f);
	pVtx[0].pos.x = g_player.pos.x + sinf(g_player.rot.z + (-D3DX_PI + g_player.fAngle)) * g_player.fLength;
	pVtx[0].pos.y = g_player.pos.y + cosf(g_player.rot.z + (-D3DX_PI + g_player.fAngle)) * g_player.fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_player.pos.x + sinf(g_player.rot.z + (D3DX_PI - g_player.fAngle)) * g_player.fLength;
	pVtx[1].pos.y = g_player.pos.y + cosf(g_player.rot.z + (D3DX_PI - g_player.fAngle)) * g_player.fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_player.pos.x + sinf(g_player.rot.z + (0.0f - g_player.fAngle)) * g_player.fLength;
	pVtx[2].pos.y = g_player.pos.y + cosf(g_player.rot.z + (0.0f - g_player.fAngle)) * g_player.fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_player.pos.x + sinf(g_player.rot.z + (0.0f + g_player.fAngle)) * g_player.fLength;
	pVtx[3].pos.y = g_player.pos.y + cosf(g_player.rot.z + (0.0f + g_player.fAngle)) * g_player.fLength;
	pVtx[3].pos.z = 0.0f;
	
	if ((g_player.nCounterAnim % 5) == 0)
	{
		g_player.nCounterAnim = 0;
		g_player.nPatternAnim = (g_player.nPatternAnim + 1) % 4;
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(g_player.nPatternAnim * 0.25f,0.0f);
		pVtx[1].tex = D3DXVECTOR2(g_player.nPatternAnim * 0.25f+0.25f,0.0f);
		pVtx[2].tex = D3DXVECTOR2(g_player.nPatternAnim * 0.25f,1.0f);
		pVtx[3].tex = D3DXVECTOR2(g_player.nPatternAnim * 0.25f + 0.25f,1.0f);
	}
	//アンロック
	g_pVtebuffPlayer->Unlock();
}
//ポリゴンの描画処理
void DrawPlayer(void)
{
	VERTEX_2D* pVtx;
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtebuffPlayer, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePlayer);
	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類
		0,
		2); //頂点情報構造体のサイズ
}
//プレイヤーの取得
Player* GetPlayer(void)
{
	return &g_player;
}
