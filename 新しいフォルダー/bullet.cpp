#include "bullet.h"
#include "main.h"
#include "player.h"
#include "explosion.h"
#include "enemy.h"
#include "effect.h"
//マクロ定義
#define MAX_BULLET (128)//弾の最大数
//弾構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;//位置
	D3DXVECTOR3 move;//移動量
	int nLife;//寿命
	BULLETTYPE type;//弾の種類
	bool bUse;//使用しているかどうか
}Bullet;
//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;
Bullet g_aBullet[MAX_BULLET];
//弾の初期化処理
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;
	//デバイスの取得
	pDevice = GetDevice();
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\korokke2.png",
		&g_pTextureBullet);
	//弾の情報を初期化
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].nLife = 100;
		g_aBullet[nCntBullet].bUse = false;
	}
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);
	VERTEX_2D* pVtx;
	//ロック
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
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
	g_pVtxBuffBullet->Unlock();
}
//弾の終了処理
void UninitBullet(void)
{
	//テクスチャの破棄
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}
	//テクスチャの破棄
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}
//弾の更新処理
void UpdateBullet(void)
{
	int nCntBullet;
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	VERTEX_2D* pVtx;

	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{//弾が使用されている
			
			int nCntEnemy;
			if (g_aBullet[nCntBullet].type == BULLETTYPE_PLAYER)
			{
				//敵の取得
				Enemy* pEnemy;//敵の情報へのポインタ
				pEnemy = GetEnemy();//敵の情報の先頭アドレスが代入される
				for (nCntEnemy = 0; nCntEnemy <= MAX_ENEMY; nCntEnemy++)
				{
					if (pEnemy->bUse == true)
					{
						if (g_aBullet[nCntBullet].pos.x >= pEnemy->pos.x - 50 && g_aBullet[nCntBullet].pos.x >= pEnemy->pos.x + 50
							&& g_aBullet[nCntBullet].pos.y >= pEnemy->pos.x - 50 && g_aBullet[nCntBullet].pos.x >= pEnemy->pos.x + 50)
						{
							HitEnemy(nCntEnemy, 1);
							g_aBullet[nCntBullet].bUse = false;
						}
					}
					pEnemy++;
				}
			}
			else if (g_aBullet[nCntBullet].type == BULLETTYPE_ENEMY)
			{
				int nCntPlayer;
				Player* pPlayer;
				pPlayer = GetPlayer();
				for (nCntPlayer = 0; nCntPlayer < MAX_ENEMY; nCntPlayer++)
				{
					if (pPlayer->bUse == true)
					{
						if (g_aBullet[nCntBullet].pos.x >= pPlayer->pos.x - 50 && g_aBullet[nCntBullet].pos.x >= pPlayer->pos.x + 50
							&& g_aBullet[nCntBullet].pos.y >= pPlayer->pos.x - 50 && g_aBullet[nCntBullet].pos.x >= pPlayer->pos.x + 50)
						{
							
							g_aBullet[nCntBullet].bUse = false;
						}
					}
				}
			}
			g_aBullet[nCntBullet].pos.x += g_aBullet[nCntBullet].move.x;
			g_aBullet[nCntBullet].pos.y += g_aBullet[nCntBullet].move.y;

			SetEffect(g_aBullet[nCntBullet].pos,40, 80, 40);
			pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 25.0f, g_aBullet[nCntBullet].pos.y - 25.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 25.0f, g_aBullet[nCntBullet].pos.y - 25.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 25.0f, g_aBullet[nCntBullet].pos.y + 25.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 25.0f, g_aBullet[nCntBullet].pos.y + 25.0f, 0.0f);
			g_aBullet[nCntBullet].nLife--;
			pVtx[0].col = D3DXCOLOR(155, 0, 155, 255);
			pVtx[1].col = D3DXCOLOR(155, 0, 155, 255);
			pVtx[2].col = D3DXCOLOR(155, 0, 155, 255);
			pVtx[3].col = D3DXCOLOR(155, 0, 155, 255);
			if (0 >= g_aBullet[nCntBullet].pos.x >= SCREEN_HEIGHT || 0 >= g_aBullet[nCntBullet].pos.y >= SCREEN_WIDTH)
			{
				g_aBullet[nCntBullet].bUse = false;
			}
			if (g_aBullet[nCntBullet].nLife == 0)
			{
				//爆発の設定
				//SetExplosion(g_aBullet[nCntBullet].pos,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				g_aBullet[nCntBullet].bUse = false;
			}
		}
		pVtx += 4;
	}
	g_pVtxBuffBullet->Unlock();
}
//弾の描画処理
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;
	//デバイス取得
	pDevice = GetDevice();

	pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	//テクスチャの設定
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{//弾が使用されている
			pDevice->SetTexture(0, g_pTextureBullet);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntBullet * 4, 2);
		}
	}
}
//弾の設定処理
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, BULLETTYPE type)
{
	int nCntBullet;
	VERTEX_2D* pVtx;

	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{

			pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 25.0f, g_aBullet[nCntBullet].pos.y - 25.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 25.0f, g_aBullet[nCntBullet].pos.y - 25.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 25.0f, g_aBullet[nCntBullet].pos.y + 25.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 25.0f, g_aBullet[nCntBullet].pos.y + 25.0f, 0.0f);

			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			g_aBullet[nCntBullet].pos = pos;
			g_aBullet[nCntBullet].move = move;
			g_aBullet[nCntBullet].nLife = 100;
			g_aBullet[nCntBullet].bUse = true;
			break;
		}
		pVtx += 4;
	}
	g_pVtxBuffBullet->Unlock();
}
