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
#define PARTICLE_NUM_MAX	(4096)

/**************************************
前方宣言
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
	static LPDIRECT3DVERTEXDECLARATION9 declare;
	static LPD3DXEFFECT effect;
	static LPDIRECT3DINDEXBUFFER9 indexBuff;	
	static LPDIRECT3DVERTEXBUFFER9 transformBuff, uvBuff;
	static UINT instanceCount;
	static D3DXHANDLE hMtxView, hMtxProj, hMtxInvView;

	LPDIRECT3DVERTEXBUFFER9 unitBuff;
	LPDIRECT3DTEXTURE9 texture;

	std::vector<Tparticle> particleContainer;
	std::vector<Temitter> emitterContainer;
	
	virtual void MakeUnitBuffer(D3DXVECTOR2* size, D3DXVECTOR2* texDix);

	static void MakeVertexDeclaration();
	static void MakeTransformBuffer();
	static void MakeUVBuffer();
	static void MakeIndexBuffer();
	static void LoadEffect();
	static void BeginDraw();
	static void EndDraw();

	UINT EmbedParameterTransform();
	UINT EmbedParameterUV();
	void LoadTexture(const char* filePath);
};

#endif