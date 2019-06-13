//=====================================
//
//プレイヤーバレット処理[PlayerBullet.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================

#include "PlayerBullet.h"
/**************************************
マクロ定義
***************************************/

/**************************************
構造体定義
***************************************/

/**************************************
プロトタイプ宣言
***************************************/

/****************************************
初期化処理
****************************************/
void PlayerBullet::Init()
{

}

/****************************************
終了処理
*****************************************/
void PlayerBullet::Uninit()
{

}


/****************************************
更新処理
*****************************************/
void PlayerBullet::Update()
{
	if (!active)
		return;

	//移動処理
	const float Speed = 10.0f;
	pos.z += Speed;
}

/****************************************
描画処理
*****************************************/
void PlayerBullet::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	VERTEX_3D* p;
	vtxBuff->Lock(0, 0, (void**)&p, 0);
	vtxBuff->Unlock();

	pDevice->SetFVF(FVF_VERTEX_3D);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	pDevice->SetRenderState(D3DRS_LIGHTING, false);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	pDevice->SetTexture(0, texture);

	pDevice->SetStreamSource(0, vtxBuff, 0, sizeof(VERTEX_3D));

	D3DXMATRIX mtxWorld;
	D3DXMatrixIdentity(&mtxWorld);
	D3DXMatrixTranslation(&mtxWorld, pos.x, pos.y, pos.z);

	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	pDevice->SetRenderState(D3DRS_LIGHTING, true);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

/****************************************
コンストラクタ
****************************************/
PlayerBullet::PlayerBullet()
{
	//頂点バッファ作成
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &vtxBuff, 0);

	//頂点座標以外の情報を埋める
	VERTEX_3D *pVtx;

	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	
	const float texSize = 1.0f;
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(texSize, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(texSize, 1.0f);

	pVtx[0].diffuse =
		pVtx[1].diffuse =
		pVtx[2].diffuse =
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	pVtx[0].nor =
		pVtx[1].nor =
		pVtx[2].nor =
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	vtxBuff->Unlock();

	texture = CreateTextureFromFile((LPSTR)"data/TEXTURE/Player/PlayerBullet.png", pDevice);

	//TrailColliderのZ座標アドレスを設定
	collider.SetAddressZ(&pos.z);
}

/****************************************
デストラクタ
****************************************/
PlayerBullet::~PlayerBullet()
{
	SAFE_RELEASE(vtxBuff);
}

/****************************************
セット処理
*****************************************/
void PlayerBullet::Set(TrailIndex start, TrailIndex end)
{

}

/****************************************
セット処理(テスト用)
*****************************************/
void PlayerBullet::Set(D3DXVECTOR3 start, D3DXVECTOR3 end)
{

	D3DXVECTOR3 diff = end - start;
	diff /= 2.0f;

	D3DXVECTOR3 up;
	D3DXVec3Cross(&up, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &diff);
	D3DXVec3Normalize(&up, &up);

	VERTEX_3D *pVtx;
	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	const float length = 15.0f;

	pVtx[0].vtx = -diff + up * length;
	pVtx[1].vtx = diff + up * length;
	pVtx[2].vtx = -diff - up * length;
	pVtx[3].vtx = diff - up * length;

	vtxBuff->Unlock();

	pos = start + diff;

	active = true;

}

/****************************************
コライダー取得処理
*****************************************/
TrailCollider PlayerBullet::GetCollider()
{
	return collider;
}

/****************************************
アクティブ判定
*****************************************/
bool PlayerBullet::IsActive()
{
	return active;
}
