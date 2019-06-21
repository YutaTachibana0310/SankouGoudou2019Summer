//=====================================
//
//�x�[�X�p�[�e�B�N���R���g���[������[BaseParticleController.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "BaseParticleController.h"
#include "BaseParticle.h"
#include "BaseEmitter.h"

using namespace std;

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
template<>
BaseParticleController<BaseParticle, BaseEmitter>::BaseParticleController()
{

}

/**************************************
�f�X�g���N�^
***************************************/
template<>
BaseParticleController<BaseParticle, BaseEmitter>::~BaseParticleController()
{

}

/**************************************
����������
***************************************/
template<>
void BaseParticleController<BaseParticle, BaseEmitter>::Init()
{

}

/**************************************
�I������
***************************************/
template<>
void BaseParticleController<BaseParticle, BaseEmitter>::Uninit()
{

}

/**************************************
�X�V����
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
�`�揈��
***************************************/
template<>
void BaseParticleController<BaseParticle, BaseEmitter>::Draw()
{

}

/**************************************
�p�[�e�B�N���P�ʃo�b�t�@�쐬����
***************************************/
template<>
void BaseParticleController<BaseParticle, BaseEmitter>::MakeUnitBuffer(D3DXVECTOR2 *size, D3DXVECTOR2 *texDiv)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->CreateVertexBuffer(sizeof(ParticleUnit) * NUM_VERTEX, 0, 0, D3DPOOL_MANAGED, &unitBuff, 0);

	ParticleUnit *p;
	unitBuff->Lock(0, 0, (void**)&p, 0);

	//�P�ʃT�C�Y�ݒ�
	p[0].vtx = D3DXVECTOR3(-size->x / 2.0f, size->y / 2.0f, 0.0f);
	p[1].vtx = D3DXVECTOR3(size->x / 2.0f, size->y / 2.0f, 0.0f);
	p[2].vtx = D3DXVECTOR3(-size->x / 2.0f, -size->y / 2.0f, 0.0f);
	p[3].vtx = D3DXVECTOR3(size->x / 2.0f, -size->y / 2.0f, 0.0f);

	//�P��UV�ݒ�
	float u = 1.0f / texDiv->x;
	float v = 1.0f / texDiv->y;
	p[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	p[1].tex = D3DXVECTOR2(u, 0.0f);
	p[2].tex = D3DXVECTOR2(0.0f, v);
	p[3].tex = D3DXVECTOR2(u, v);

	unitBuff->Unlock();
}

/**************************************
�g�����X�t�H�[���o�b�t�@�쐬����
***************************************/
template<>
void BaseParticleController<BaseParticle, BaseEmitter>::MakeTransformBuffer(UINT particleNumMax)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->CreateVertexBuffer(sizeof(Transform) * particleNumMax, 0, 0, D3DPOOL_MANAGED, &transformBuff, 0);
}

/**************************************
UV�o�b�t�@�쐬����
***************************************/
template<>
void BaseParticleController<BaseParticle, BaseEmitter>::MakeUVBuffer(UINT particleNumMax)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->CreateVertexBuffer(sizeof(ParticleUV) * particleNumMax, 0, 0, D3DPOOL_MANAGED, &uvBuff, 0);
}

template BaseParticleController<BaseParticle, BaseEmitter>;