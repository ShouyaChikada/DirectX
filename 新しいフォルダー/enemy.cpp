#include "enemy.h"
#include "bullet.h"
#include "explosion.h"
//マクロ
#define NUM_ENEMY (4) //敵の種類
//グローバル変数
LPDIRECT3DTEXTURE9 g_apTextureEnemy[NUM_ENEMY] = { NULL };
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;
Enemy g_aEnemy[MAX_ENEMY];
int g_nNumEnemy = 0;

void InitEnemy(void)
{
	
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEnemy;
	g_nNumEnemy = 1;//敵の総数
	//デバイスの取得
	pDevice = GetDevice();
	//テクスチャ(４枚分)の読み込み
	D3DXCreateTextureFromFile(pDevice,
	"data\\TEXTURE\\chikin.jpg",
		&g_apTextureEnemy[0]);
	VERTEX_2D* pVtx;
	//頂点バッファの生成・頂点情報の設定
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnemy,
		NULL);

	//ロック
	g_pVtxBuffEnemy ->Lock(0, 0, (void**)&pVtx, 0);

	//敵の情報の初期化
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
	
		pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 50.0f, g_aEnemy[nCntEnemy].pos.y - 50.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 50.0f, g_aEnemy[nCntEnemy].pos.y - 50.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 50.0f, g_aEnemy[nCntEnemy].pos.y + 50.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 50.0f, g_aEnemy[nCntEnemy].pos.y + 50.0f, 0.0f);
		/*g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(200.0f, 300.0f, 0.0f);
		g_aEnemy[nCntEnemy].nLife = 5;
		g_aEnemy[nCntEnemy].nType = 0;
		g_aEnemy[nCntEnemy].bUse = false;*/
		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 0.25f);
		pVtx[3].tex = D3DXVECTOR2(0.5f, 0.25f);
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
		pVtx += 4;
	}

	//アンロック
	g_pVtxBuffEnemy ->Unlock();


}	
void UninitEnemy(void)
{
	int nCntEnemy;
	//テクスチャ(４枚分)の破棄
	for (nCntEnemy = 0; nCntEnemy < 1; nCntEnemy++)
	{
		if (g_apTextureEnemy[nCntEnemy] != NULL)
		{
			g_apTextureEnemy[nCntEnemy]->Release();
			g_apTextureEnemy[nCntEnemy] = NULL;
		}
		//テクスチャの破棄
		if (g_pVtxBuffEnemy != NULL)
		{
			g_pVtxBuffEnemy->Release();
			g_pVtxBuffEnemy = NULL;
		}
	}
}
void UpdateEnemy(void)
{
	VERTEX_2D* pVtx;
	int nCnt;
	//ロック
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);
	for (nCnt = 0; nCnt <= MAX_ENEMY; nCnt++)
	{
		if (g_aEnemy[nCnt].bUse == true)
		{
			g_aEnemy[nCnt].nCounterState++;
			switch (g_aEnemy[nCnt].state)
			{
			case ENEMYSTATE_NORMAL:
				if (g_aEnemy[nCnt].nCounterState > 60)
				{
					SetBullet(g_aEnemy[nCnt].pos, D3DXVECTOR3(-10.0f, 0.0f, 0.0f), 10, BULLETTYPE_ENEMY);
					g_aEnemy[nCnt].nCounterState = 0;
				}
				break;
			case ENEMYSTATE_DAMAGE:
				g_aEnemy[nCnt].nCntS--;
				if (g_aEnemy[nCnt].nCntS <= 0)
				{
					g_aEnemy[nCnt].nCntS = ENEMYSTATE_NORMAL;
					//頂点カラー
					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				}
			}
			break;
		}
		pVtx += 4;
	}
	//アンロック
	g_pVtxBuffEnemy->Unlock();
}

void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEnemy;
	//デバイスの取得
	pDevice = GetDevice();
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{//敵が使用している
			//テクスチャ設定
			pDevice->SetTexture(0, g_apTextureEnemy[nCntEnemy]);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntEnemy * 4, 2);
		}
	}
}
//ポリゴンの描画
void SetEnemy(D3DXVECTOR3 pos, int nType)
{
	int nCntEnemy;
	VERTEX_2D* pVtx;

	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)
		{//敵が使用されていない
			//敵の情報の設定
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 50.0f, g_aEnemy[nCntEnemy].pos.y - 50.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 50.0f, g_aEnemy[nCntEnemy].pos.y - 50.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 50.0f, g_aEnemy[nCntEnemy].pos.y + 50.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 50.0f, g_aEnemy[nCntEnemy].pos.y + 50.0f, 0.0f);
			//頂点座標の設定
			g_aEnemy[nCntEnemy].pos = pos;
			g_aEnemy[nCntEnemy].nLife = 5;
			g_aEnemy[nCntEnemy].nType = nType;
			g_aEnemy[nCntEnemy].bUse = true;
			g_nNumEnemy++;	//敵の総数
			//頂点カラー
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			break;

		}
		pVtx += 4;
	}
	g_pVtxBuffEnemy->Unlock();
}
void HitEnemy(int nCntEnemy, int nDamage)
{
	VERTEX_2D* pVtx{};
	g_aEnemy[nCntEnemy].nLife -= nDamage;

	if (g_aEnemy[nCntEnemy].nLife <= 0)
	{
		SetExplosion(g_aEnemy[nCntEnemy].pos,D3DXCOLOR(255,0,0,255));
		g_aEnemy[nCntEnemy].bUse = false; 
		g_nNumEnemy--;
	}
	else
	{
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_DAMAGE;
		g_aEnemy[nCntEnemy].nCounterState = 5;
		pVtx += 4 * nCntEnemy;
		g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);
		pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		g_pVtxBuffEnemy->Unlock();
	}
}
Enemy* GetEnemy(void)
{
	return &g_aEnemy[0];//敵の情報の先頭アドレスを返す
}