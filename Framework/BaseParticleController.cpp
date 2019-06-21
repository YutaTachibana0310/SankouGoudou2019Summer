//=====================================
//
//ベースパーティクルコントローラ処理[BaseParticleController.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "BaseParticleController.h"
#include "BaseParticle.h"
#include "BaseEmitter.h"

using namespace std;

/**************************************
マクロ定義
***************************************/

/**************************************
構造体定義
***************************************/

/**************************************
グローバル変数
***************************************/

/**************************************
コンストラクタ
***************************************/
template<>
BaseParticleController<BaseParticle, BaseEmitter>::BaseParticleController()
{

}

/**************************************
デストラクタ
***************************************/
template<>
BaseParticleController<BaseParticle, BaseEmitter>::~BaseParticleController()
{

}

/**************************************
初期化処理
***************************************/
template<>
void BaseParticleController<BaseParticle, BaseEmitter>::Init()
{

}

/**************************************
終了処理
***************************************/
template<>
void BaseParticleController<BaseParticle, BaseEmitter>::Uninit()
{

}

/**************************************
更新処理
***************************************/
template<>
void BaseParticleController<BaseParticle, BaseEmitter>::Update()
{
	for (auto itr = emitterContainer.begin(); itr != emitterContainer.end(); itr++)
	{
		itr->Update();
		itr->Emit(&particleContainer);
	}

	for (auto itr = particleContainer.begin(); itr != particleContainer.end(); itr++)
	{
		itr->Update();
	}

}

/**************************************
描画処理
***************************************/
template<>
void BaseParticleController<BaseParticle, BaseEmitter>::Draw()
{

}

/**************************************
パーティクル単位バッファ作成処理
***************************************/
template<>
void BaseParticleController<BaseParticle, BaseEmitter>::MakeUnitBuffer(D3DXVECTOR2 *size, D3DXVECTOR2 *texDiv)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->CreateVertexBuffer(sizeof(ParticleUnit) * NUM_VERTEX, 0, 0, D3DPOOL_MANAGED, &unitBuff, 0);

	ParticleUnit *p;
	unitBuff->Lock(0, 0, (void**)&p, 0);

	//単位サイズ設定
	p[0].vtx = D3DXVECTOR3(-size->x / 2.0f, size->y / 2.0f, 0.0f);
	p[1].vtx = D3DXVECTOR3(size->x / 2.0f, size->y / 2.0f, 0.0f);
	p[2].vtx = D3DXVECTOR3(-size->x / 2.0f, -size->y / 2.0f, 0.0f);
	p[3].vtx = D3DXVECTOR3(size->x / 2.0f, -size->y / 2.0f, 0.0f);

	//単位UV設定
	float u = 1.0f / texDiv->x;
	float v = 1.0f / texDiv->y;
	p[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	p[1].tex = D3DXVECTOR2(u, 0.0f);
	p[2].tex = D3DXVECTOR2(0.0f, v);
	p[3].tex = D3DXVECTOR2(u, v);

	unitBuff->Unlock();
}

/**************************************
トランスフォームバッファ作成処理
***************************************/
template<>
void BaseParticleController<BaseParticle, BaseEmitter>::MakeTransformBuffer(UINT particleNumMax)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->CreateVertexBuffer(sizeof(Transform) * particleNumMax, 0, 0, D3DPOOL_MANAGED, &transformBuff, 0);
}

/**************************************
UVバッファ作成処理
***************************************/
template<>
void BaseParticleController<BaseParticle, BaseEmitter>::MakeUVBuffer(UINT particleNumMax)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->CreateVertexBuffer(sizeof(ParticleUV) * particleNumMax, 0, 0, D3DPOOL_MANAGED, &uvBuff, 0);
}

template BaseParticleController<BaseParticle, BaseEmitter>;