//=====================================
//
//スカイボックス処理[SkyBox.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "SkyBox.h"
#include "Framework\ResourceManager.h"

/**************************************
マクロ定義
***************************************/

/**************************************
コンストラクタ
***************************************/
SkyBox::SkyBox(D3DXVECTOR3 vtxSize, D3DXVECTOR2 texSize) :
	transform(new Transform())
{
	MakeVertexBuffer(vtxSize.x, vtxSize.y, vtxSize.z);
	SetUV(texSize.x, texSize.y);
}

/**************************************
デストラクタ
***************************************/
SkyBox::~SkyBox()
{
	SAFE_DELETE(transform);
	SAFE_RELEASE(vtxBuff);
	SAFE_RELEASE(texture);
}

/**************************************
描画処理
***************************************/
void SkyBox::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetFVF(FVF_VERTEX_BILLBOARD);

	D3DXMATRIX mtxWorld;
	transform->SetWorld();

	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
	pDevice->SetRenderState(D3DRS_LIGHTING, false);

	pDevice->SetTexture(0, texture);

	pDevice->SetStreamSource(0, vtxBuff, 0, sizeof(VERTEX_BILLBOARD));

	for (int i = 0; i < Const::FieldNum; i++)
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, NUM_VERTEX * i, NUM_POLYGON);

	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
	pDevice->SetRenderState(D3DRS_LIGHTING, true);
}

/**************************************
テクスチャ読み込み設定
***************************************/
void SkyBox::LoadTexture(const char* fileName)
{
	SAFE_RELEASE(texture);
	ResourceManager::Instance()->GetTexture(fileName, texture);
}

/**************************************
UV座標設定処理
***************************************/
void SkyBox::SetUV(float texU, float texV)
{
	VERTEX_BILLBOARD *pVtx;
	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < Const::FieldNum; i++, pVtx += 4)
	{
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(texU, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, texV);
		pVtx[3].tex = D3DXVECTOR2(texU, texV);
	}

	vtxBuff->Unlock();
}

/**************************************
頂点バッファ作成処理
***************************************/
void SkyBox::MakeVertexBuffer(float width, float height, float depth)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->CreateVertexBuffer(sizeof(VERTEX_BILLBOARD) * NUM_VERTEX * Const::FieldNum,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_BILLBOARD,
		D3DPOOL_MANAGED,
		&vtxBuff,
		0);

	VERTEX_BILLBOARD *pVtx;
	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//左面
	pVtx[0].vtx = D3DXVECTOR3(-width, height, -depth);
	pVtx[1].vtx = D3DXVECTOR3(-width, height, depth);
	pVtx[2].vtx = D3DXVECTOR3(-width, -height, -depth);
	pVtx[3].vtx = D3DXVECTOR3(-width, -height, depth);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx[0].diffuse =
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].diffuse =
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//右面
	pVtx += 4;
	pVtx[0].vtx = D3DXVECTOR3(width, height, depth);
	pVtx[1].vtx = D3DXVECTOR3(width, height, -depth);
	pVtx[2].vtx = D3DXVECTOR3(width, -height, depth);
	pVtx[3].vtx = D3DXVECTOR3(width, -height, -depth);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx[0].diffuse =
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].diffuse =
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//前面
	pVtx += 4;
	pVtx[0].vtx = D3DXVECTOR3(-width, height, depth);
	pVtx[1].vtx = D3DXVECTOR3(width, height, depth);
	pVtx[2].vtx = D3DXVECTOR3(-width, -height, depth);
	pVtx[3].vtx = D3DXVECTOR3(width, -height, depth);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx[0].diffuse =
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].diffuse =
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//後面
	pVtx += 4;
	pVtx[0].vtx = D3DXVECTOR3(width, height, -depth);
	pVtx[1].vtx = D3DXVECTOR3(-width, height, -depth);
	pVtx[2].vtx = D3DXVECTOR3(width, -height, -depth);
	pVtx[3].vtx = D3DXVECTOR3(-width, -height, -depth);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx[0].diffuse =
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].diffuse =
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	vtxBuff->Unlock();

}
