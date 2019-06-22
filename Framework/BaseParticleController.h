//=====================================
//
//�x�[�X�p�[�e�B�N���R���g���[���w�b�_[BaseParticleController.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _BASEPARTICLECONTROLLER_H_
#define _BASEPARTICLECONTROLLER_H_

#include "../main.h"
#include "BaseParticle.h"
#include "BaseEmitter.h"
#include <vector>
#include <memory>

/**************************************
�}�N����`
***************************************/
#define PARTICLE_NUM_MAX	(4096)

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class BaseParticleController
{
public:
	BaseParticleController();
	virtual ~BaseParticleController();

	virtual void Init() = 0;
	virtual void Emit() = 0;

	virtual void SetEmitter(D3DXVECTOR3 *pos);
	virtual void Uninit();
	void Update();
	void Draw();

	static void BeginDraw();
	static void EndDraw();

protected:
	static LPDIRECT3DVERTEXDECLARATION9 declare;
	static LPD3DXEFFECT effect;
	static LPDIRECT3DINDEXBUFFER9 indexBuff;	
	static LPDIRECT3DVERTEXBUFFER9 transformBuff, uvBuff;
	static UINT instanceCount;
	static D3DXHANDLE hMtxView, hMtxProj, hMtxInvView;

	LPDIRECT3DVERTEXBUFFER9 unitBuff;
	LPDIRECT3DTEXTURE9 texture;
	std::vector<BaseParticle*> particleContainer;
	std::vector<BaseEmitter*> emitterContainer;

	UINT EmbedParameterTransform();
	UINT EmbedParameterUV();

	void MakeUnitBuffer(D3DXVECTOR2* size, D3DXVECTOR2* texDix);
	void LoadTexture(const char* filePath);

	static void LoadEffect();
	static void MakeVertexDeclaration();
	static void MakeTransformBuffer();
	static void MakeUVBuffer();
	static void MakeIndexBuffer();
};

#endif