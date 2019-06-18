//=====================================
//
//スカイボックス処理[SkyBox.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "SkyBox.h"

/**************************************
マクロ定義
***************************************/
#define SKYBOX_FIELD_NUM		(4)
#define SKYBOX_TEXTURE_NAME		"data/TEXTURE/BG/img_post152_07.jpg"
#define SKYBOX_SCROLL_SPEED		(0.0002f)

/**************************************
構造体定義
***************************************/

/**************************************
グローバル変数
***************************************/
static LPDIRECT3DVERTEXBUFFER9 vtxBuff;
static LPDIRECT3DTEXTURE9 texture;

/**************************************
プロトタイプ宣言
***************************************/
void MakeVertexBufferSkyBox(void);

/**************************************
初期化処理
***************************************/
void InitSkyBox(int num)
{
	MakeVertexBufferSkyBox();

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	texture = CreateTextureFromFile((LPSTR)SKYBOX_TEXTURE_NAME, pDevice);
}

/**************************************
終了処理
***************************************/
void UninitSkyBox(int num)
{
	SAFE_RELEASE(texture);
	SAFE_RELEASE(vtxBuff);
}

/**************************************
更新処理
***************************************/
void UpdateSkyBox(void)
{
	//スカイボックスをスクロール
	VERTEX_3D *pVtx;
	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < NUM_VERTEX * SKYBOX_FIELD_NUM; i++)
	{
		pVtx[i].tex.x += SKYBOX_SCROLL_SPEED;
		pVtx[i].tex.y += SKYBOX_SCROLL_SPEED;
	}

	vtxBuff->Unlock();
}

/**************************************
描画処理
***************************************/
void DrawSkyBox(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxWorld;

	//フォグをオフ
	pDevice->SetRenderState(D3DRS_FOGENABLE, false);

	//ワールド変換行列設定
	D3DXMatrixIdentity(&mtxWorld);
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	//レンダーステート設定
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
	pDevice->SetRenderState(D3DRS_LIGHTING, false);

	//FVF設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャ設定
	pDevice->SetTexture(0, texture);

	//ストリームソース設定
	pDevice->SetStreamSource(0, vtxBuff, 0, sizeof(VERTEX_3D));

	//描画
	for (int i = 0; i < SKYBOX_FIELD_NUM; i++)
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, NUM_VERTEX * i, NUM_POLYGON);

	//レンダーステート復元
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
	pDevice->SetRenderState(D3DRS_LIGHTING, true);

	//フォグをオン
	pDevice->SetRenderState(D3DRS_FOGENABLE, true);
}

/**************************************
頂点バッファ作成処理
***************************************/
void MakeVertexBufferSkyBox(void)
{
	const float Bottom = -750.0f;
	const float BoxSize = 5000.0f;
	const float TexLoop = 3.0f;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * SKYBOX_FIELD_NUM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&vtxBuff,
		0);

	VERTEX_3D *pVtx;
	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//左面
	pVtx[0].vtx = D3DXVECTOR3(-BoxSize, BoxSize * 2, -BoxSize);
	pVtx[1].vtx = D3DXVECTOR3(-BoxSize, BoxSize * 2, BoxSize);
	pVtx[2].vtx = D3DXVECTOR3(-BoxSize, Bottom, -BoxSize);
	pVtx[3].vtx = D3DXVECTOR3(-BoxSize, Bottom, BoxSize);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(TexLoop, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, TexLoop * 2);
	pVtx[3].tex = D3DXVECTOR2(TexLoop, TexLoop * 2);

	pVtx[0].diffuse =
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].diffuse =
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//右面
	pVtx += 4;
	pVtx[0].vtx = D3DXVECTOR3(BoxSize, BoxSize * 2, BoxSize);
	pVtx[1].vtx = D3DXVECTOR3(BoxSize, BoxSize * 2, -BoxSize);
	pVtx[2].vtx = D3DXVECTOR3(BoxSize, Bottom, BoxSize);
	pVtx[3].vtx = D3DXVECTOR3(BoxSize, Bottom, -BoxSize);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(TexLoop, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, TexLoop * 2);
	pVtx[3].tex = D3DXVECTOR2(TexLoop, TexLoop * 2);

	pVtx[0].diffuse =
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].diffuse =
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//前面
	pVtx += 4;
	pVtx[0].vtx = D3DXVECTOR3(-BoxSize, BoxSize * 2, BoxSize);
	pVtx[1].vtx = D3DXVECTOR3(BoxSize, BoxSize * 2, BoxSize);
	pVtx[2].vtx = D3DXVECTOR3(-BoxSize, Bottom, BoxSize);
	pVtx[3].vtx = D3DXVECTOR3(BoxSize, Bottom, BoxSize);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(TexLoop, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, TexLoop * 2);
	pVtx[3].tex = D3DXVECTOR2(TexLoop, TexLoop * 2);

	pVtx[0].diffuse =
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].diffuse =
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//後面
	pVtx += 4;
	pVtx[0].vtx = D3DXVECTOR3(BoxSize, BoxSize * 2, -BoxSize);
	pVtx[1].vtx = D3DXVECTOR3(-BoxSize, BoxSize * 2, -BoxSize);
	pVtx[2].vtx = D3DXVECTOR3(BoxSize, Bottom, -BoxSize);
	pVtx[3].vtx = D3DXVECTOR3(-BoxSize, Bottom, -BoxSize);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(TexLoop, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, TexLoop * 2);
	pVtx[3].tex = D3DXVECTOR2(TexLoop, TexLoop * 2);

	pVtx[0].diffuse =
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].diffuse =
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	vtxBuff->Unlock();
}