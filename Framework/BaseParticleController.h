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
#include <functional>

/**************************************
�}�N����`
***************************************/
#define PARTICLE_NUM_MAX	(1024)

/**************************************
�O���錾
***************************************/

/**************************************
BasePartlceController�N���X
���p�����Init(), Emit(), SetEmitter()����������
***************************************/
class BaseParticleController
{
public:
	//�R���X�g���N�^�A�f�X�g���N�^
	BaseParticleController();
	virtual ~BaseParticleController();

	//�������ƕ��o�����͌p����Ɏ�������
	virtual void Init() = 0;
	virtual void Emit() = 0;

	virtual BaseEmitter* SetEmitter(D3DXVECTOR3 *pos);	//�G�~�b�^�Z�b�g����
	virtual void Uninit();						//�I������
	void Update();								//�X�V����
	virtual bool Draw();						//�`�揈��

	//�`��J�n�E�I������
	static void BeginDraw();		
	static void EndDraw();			

protected:
	LPDIRECT3DVERTEXBUFFER9 unitBuff;				//�P�ʒ��_�o�b�t�@
	LPDIRECT3DTEXTURE9 texture;						//�e�N�X�`��
	std::vector<BaseParticle*> particleContainer;	//�p�[�e�B�N���R���e�i
	std::vector<BaseEmitter*> emitterContainer;		//�G�~�b�^�R���e�i

	void MakeUnitBuffer(const D3DXVECTOR2* size, const D3DXVECTOR2* texDix);	//�P�ʒ��_�o�b�t�@�쐬����
	void LoadTexture(const char* filePath);			//�e�N�X�`���ǂݍ��ݏ���

	//�S�G�~�b�^�ɑ΂�����o����
	void ForEachEmitter(UINT emitNum, std::function<void(BaseEmitter *emitter, BaseParticle *particle)> func);

private:
	//�C���X�^���V���O�ɕK�v�ȐÓI�����o
	static LPDIRECT3DVERTEXDECLARATION9 declare;
	static LPD3DXEFFECT effect;
	static LPDIRECT3DINDEXBUFFER9 indexBuff;	
	static LPDIRECT3DVERTEXBUFFER9 transformBuff, uvBuff;
	static UINT instanceCount;
	static D3DXHANDLE hMtxView, hMtxProj, hMtxInvView;

	//���_�o�b�t�@�ւ̊e���Z�b�g����
	UINT EmbedParameterUV();
	UINT EmbedParameterTransform();

	//�ÓI�����o��������
	static void LoadEffect();
	static void MakeVertexDeclaration();
	static void MakeTransformBuffer();
	static void MakeUVBuffer();
	static void MakeIndexBuffer();
};

#endif