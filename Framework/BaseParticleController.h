//=====================================
//
//ベースパーティクルコントローラヘッダ[BaseParticleController.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _BASEPARTICLECONTROLLER_H_
#define _BASEPARTICLECONTROLLER_H_

#include "../main.h"
#include <vector>

/**************************************
マクロ定義
***************************************/
class BaseParticle;
class BaseEmitter;

/**************************************
クラス定義
***************************************/
template<class Tparticle, class Temitter>
class BaseParticleController
{
public:
	BaseParticleController();
	virtual ~BaseParticleController();

	virtual void Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();

protected:
	LPDIRECT3DVERTEXDECLARATION9 declare;
	LPDIRECT3DVERTEXBUFFER9 unitBuff;
	LPDIRECT3DVERTEXBUFFER9 transformBuff, uvBuff;
	LPDIRECT3DTEXTURE9 texture;

	std::vector<Tparticle> particleContainer;
	std::vector<Temitter> emitterContainer;
	
	LPDIRECT3DINDEXBUFFER9 indexBuff;
	LPD3DXEFFECT effect;

	void MakeUnitBuffer(D3DXVECTOR2 *size, D3DXVECTOR2 *texDiv);
	void MakeTransformBuffer(UINT particleNumMax);
	void MakeUVBuffer(UINT paritlceNumMax);
};

#endif