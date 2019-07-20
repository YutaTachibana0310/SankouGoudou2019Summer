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
コンストラクタ
***************************************/
SkyBox::SkyBox(D3DXVECTOR3 vtxSize, D3DXVECTOR2 texSize)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->CreateVertexBuffer(sizeof(VERTEX_BILLBOARD) * NUM_VERTEX * SKYBOX_FIELD_NUM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_BILLBOARD,
		D3DPOOL_MANAGED,
		&vtxBuff,
		0);

	VERTEX_BILLBOARD *pVtx;
	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//左面
	pVtx[0].vtx = D3DXVECTOR3(-vtxSize.x, vtxSize.y, -vtxSize.z);
	pVtx[1].vtx = D3DXVECTOR3(-vtxSize.x, vtxSize.y, vtxSize.z);
	pVtx[2].vtx = D3DXVECTOR3(-vtxSize.x, -vtxSize.y, -vtxSize.z);
	pVtx[3].vtx = D3DXVECTOR3(-vtxSize.x, -vtxSize.y, vtxSize.z);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(texSize.x, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, texSize.y);
	pVtx[3].tex = D3DXVECTOR2(texSize.x, texSize.y);

	pVtx[0].diffuse =
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].diffuse =
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//右面
	pVtx += 4;
	pVtx[0].vtx = D3DXVECTOR3(vtxSize.x, vtxSize.y, vtxSize.x);
	pVtx[1].vtx = D3DXVECTOR3(vtxSize.x, vtxSize.y, -vtxSize.x);
	pVtx[2].vtx = D3DXVECTOR3(vtxSize.x, -vtxSize.y, vtxSize.x);
	pVtx[3].vtx = D3DXVECTOR3(vtxSize.x, -vtxSize.y, -vtxSize.x);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(texSize.x, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, texSize.y);
	pVtx[3].tex = D3DXVECTOR2(texSize.x, texSize.y);

	pVtx[0].diffuse =
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].diffuse =
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//前面
	pVtx += 4;
	pVtx[0].vtx = D3DXVECTOR3(-vtxSize.x, vtxSize.y, vtxSize.z);
	pVtx[1].vtx = D3DXVECTOR3(vtxSize.x, vtxSize.y, vtxSize.z);
	pVtx[2].vtx = D3DXVECTOR3(-vtxSize.x, -vtxSize.y, vtxSize.z);
	pVtx[3].vtx = D3DXVECTOR3(vtxSize.x, -vtxSize.y, vtxSize.z);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(texSize.x, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, texSize.y);
	pVtx[3].tex = D3DXVECTOR2(texSize.x, texSize.y);

	pVtx[0].diffuse =
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].diffuse =
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//後面
	pVtx += 4;
	pVtx[0].vtx = D3DXVECTOR3(vtxSize.x, vtxSize.y, -vtxSize.z);
	pVtx[1].vtx = D3DXVECTOR3(-vtxSize.x, vtxSize.y, -vtxSize.z);
	pVtx[2].vtx = D3DXVECTOR3(vtxSize.x, -vtxSize.y, -vtxSize.z);
	pVtx[3].vtx = D3DXVECTOR3(-vtxSize.x, -vtxSize.y, -vtxSize.z);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(texSize.x, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, texSize.y);
	pVtx[3].tex = D3DXVECTOR2(texSize.x, texSize.y);

	pVtx[0].diffuse =
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].diffuse =
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	vtxBuff->Unlock();
}

/**************************************
デストラクタ
***************************************/
SkyBox::~SkyBox()
{
	SAFE_RELEASE(vtxBuff);
	SAFE_RELEASE(texture);
}

/**************************************
更新処理
***************************************/
void SkyBox::Update()
{

}

/**************************************
描画処理
***************************************/
void SkyBox::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetFVF(FVF_VERTEX_BILLBOARD);

	D3DXMATRIX mtxWorld;
	transform.CalcWorldMtx(&mtxWorld);
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
}

/**************************************
テクスチャ読み込み設定
***************************************/
void SkyBox::LoadTexture(const char* fileName)
{
	SAFE_RELEASE(texture);

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXCreateTextureFromFile(pDevice, fileName, &texture);
}
