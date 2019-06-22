//=====================================
//
//ベースパーティクルコントローラヘッダ[BaseParticleController.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _BASEPARTICLECONTROLLER_H_
#define _BASEPARTICLECONTROLLER_H_

#include "../main.h"
#include "BaseParticle.h"
#include "BaseEmitter.h"
#include <vector>

/**************************************
マクロ定義
***************************************/
#define PARTICLE_NUM_MAX	(4096)

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class BaseParticleController
{
public:
	//コンストラクタ、デストラクタ
	BaseParticleController();
	virtual ~BaseParticleController();

	//初期化と放出処理は継承先に実装する
	virtual void Init() = 0;
	virtual void Emit() = 0;

	virtual void SetEmitter(D3DXVECTOR3 *pos);	//エミッタセット処理
	virtual void Uninit();						//終了処理
	void Update();						//更新処理
	void Draw();						//描画処理

	//描画開始・終了処理
	static void BeginDraw();		
	static void EndDraw();			

protected:
	LPDIRECT3DVERTEXBUFFER9 unitBuff;				//単位頂点バッファ
	LPDIRECT3DTEXTURE9 texture;						//テクスチャ
	std::vector<BaseParticle*> particleContainer;	//パーティクルコンテナ
	std::vector<BaseEmitter*> emitterContainer;		//エミッタコンテナ

	void MakeUnitBuffer(D3DXVECTOR2* size, D3DXVECTOR2* texDix);	//単位頂点バッファ作成処理
	void LoadTexture(const char* filePath);			//テクスチャ読み込み処理

private:
	//インスタンシングに必要な静的メンバ
	static LPDIRECT3DVERTEXDECLARATION9 declare;
	static LPD3DXEFFECT effect;
	static LPDIRECT3DINDEXBUFFER9 indexBuff;	
	static LPDIRECT3DVERTEXBUFFER9 transformBuff, uvBuff;
	static UINT instanceCount;
	static D3DXHANDLE hMtxView, hMtxProj, hMtxInvView;

	//頂点バッファへの各情報セット処理
	UINT EmbedParameterUV();
	UINT EmbedParameterTransform();

	//静的メンバ準備処理
	static void LoadEffect();
	static void MakeVertexDeclaration();
	static void MakeTransformBuffer();
	static void MakeUVBuffer();
	static void MakeIndexBuffer();
};

#endif