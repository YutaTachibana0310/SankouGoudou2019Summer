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
static�����o
***************************************/
LPDIRECT3DVERTEXDECLARATION9 BaseParticleController<BaseParticle, BaseEmitter>::declare;
LPD3DXEFFECT BaseParticleController<BaseParticle, BaseEmitter>::effect;
LPDIRECT3DINDEXBUFFER9 BaseParticleController<BaseParticle, BaseEmitter>::indexBuff;
LPDIRECT3DVERTEXBUFFER9 BaseParticleController<BaseParticle, BaseEmitter>::transformBuff;
LPDIRECT3DVERTEXBUFFER9 BaseParticleController<BaseParticle, BaseEmitter>::uvBuff;
UINT BaseParticleController<BaseParticle, BaseEmitter>::instanceCount;
D3DXHANDLE BaseParticleController<BaseParticle, BaseEmitter>::hMtxView;
D3DXHANDLE BaseParticleController<BaseParticle, BaseEmitter>::hMtxProj;
D3DXHANDLE BaseParticleController<BaseParticle, BaseEmitter>::hMtxInvView;

/**************************************
�R���X�g���N�^
***************************************/
template<>
BaseParticleController<BaseParticle, BaseEmitter>::BaseParticleController()
{
	if (instanceCount == 0)
	{
		MakeVertexDeclaration();
		MakeTransformBuffer();
		MakeUVBuffer();
		MakeIndexBuffer();
		LoadEffect();
	}
	instanceCount++;
}

/**************************************
�f�X�g���N�^
***************************************/
template<>
BaseParticleController<BaseParticle, BaseEmitter>::~BaseParticleController()
{
	SAFE_RELEASE(unitBuff);
	SAFE_RELEASE(texture);

	vector<BaseParticle> tmpParticle;
	tmpParticle.swap(particleContainer);

	vector<BaseEmitter> tmpEmitter;
	tmpEmitter.swap(emitterContainer);

	instanceCount--;
	if (instanceCount == 0)
	{
		SAFE_RELEASE(declare);
		SAFE_RELEASE(transformBuff);
		SAFE_RELEASE(uvBuff);
		SAFE_RELEASE(indexBuff);
		SAFE_RELEASE(effect);
	}
}

/**************************************
����������
***************************************/
template<>
void BaseParticleController<BaseParticle, BaseEmitter>::Init()
{
	for (auto itr = particleContainer.begin(); itr != particleContainer.end(); itr++)
	{
		itr->Init();
	}

	for (auto itr = emitterContainer.begin(); itr != emitterContainer.end(); itr++)
	{
		itr->Init();
	}
}

/**************************************
�I������
***************************************/
template<>
void BaseParticleController<BaseParticle, BaseEmitter>::Uninit()
{
	for (auto itr = particleContainer.begin(); itr != particleContainer.end(); itr++)
	{
		itr->Uninit();
	}

	for (auto itr = emitterContainer.begin(); itr != emitterContainer.end(); itr++)
	{
		itr->Uninit();
	}
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
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e�p�[�e�B�N���̃p�����[�^�𒸓_�o�b�t�@�ɃZ�b�g
	UINT particleCount = 0;
	particleCount = EmbedParameterTransform();
	EmbedParameterUV();

	if (particleCount == 0)
		return;

	//�X�g���[���\�[�X�ݒ�
	pDevice->SetStreamSource(0, unitBuff, 0, sizeof(ParticleUnit));
	pDevice->SetStreamSourceFreq(0, D3DSTREAMSOURCE_INDEXEDDATA | particleCount);
	pDevice->SetStreamSourceFreq(1, D3DSTREAMSOURCE_INSTANCEDATA | 1);
	pDevice->SetStreamSourceFreq(2, D3DSTREAMSOURCE_INSTANCEDATA | 1);

	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, texture);

	//�`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, NUM_VERTEX, 0, NUM_POLYGON);

	//�X�g���[���\�[�X����
	pDevice->SetStreamSourceFreq(0, 1);
	pDevice->SetStreamSourceFreq(1, 1);
	pDevice->SetStreamSourceFreq(2, 1);
}

/**************************************
�p�[�e�B�N���P�ʃo�b�t�@�쐬����
***************************************/
template<>
void BaseParticleController<BaseParticle, BaseEmitter>::MakeUnitBuffer(D3DXVECTOR2 *size, D3DXVECTOR2 *texDiv)
{
	if (unitBuff != NULL)
		return;

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
void BaseParticleController<BaseParticle, BaseEmitter>::MakeTransformBuffer()
{
	if (transformBuff != NULL)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->CreateVertexBuffer(sizeof(Transform) * PARTICLE_NUM_MAX, 0, 0, D3DPOOL_MANAGED, &transformBuff, 0);
}

/**************************************
UV�o�b�t�@�쐬����
***************************************/
template<>
void BaseParticleController<BaseParticle, BaseEmitter>::MakeUVBuffer()
{
	if (uvBuff != NULL)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->CreateVertexBuffer(sizeof(ParticleUV) * PARTICLE_NUM_MAX, 0, 0, D3DPOOL_MANAGED, &uvBuff, 0);
}

/**************************************
���_�錾�쐬����
***************************************/
template<>
void BaseParticleController<BaseParticle, BaseEmitter>::MakeVertexDeclaration()
{
	if (declare != NULL)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DVERTEXELEMENT9 elems[] =
	{
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },	//�P�ʒ��_�i���_���W�j
		{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },	//�P�ʒ��_�i�e�N�X�`�����W�j
		{ 1, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 1 },	//���[���h�ϊ����i�|�W�V�����j
		{ 1, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 2 },	//���[���h�ϊ����i���[�e�[�V�����j
		{ 1, 24, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 3 },	//���[���h�ϊ����i�X�P�[���j
		{ 2, 0, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 4 },	//�ʂ̃e�N�X�`��
		D3DDECL_END()
	};
	pDevice->CreateVertexDeclaration(elems, &declare);
}

/**************************************
�G�t�F�N�g�ǂݍ��ݏ���
***************************************/
template<>
void BaseParticleController<BaseParticle, BaseEmitter>::LoadEffect()
{
	if (effect != NULL)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXCreateEffectFromFile(pDevice, "data/EFFECT/particle3D.fx", 0, 0, D3DXSHADER_SKIPVALIDATION, 0, &effect, 0);

	hMtxView = effect->GetParameterByName(NULL, "mtxView");
	hMtxProj = effect->GetParameterByName(NULL, "mtxProj");
	hMtxInvView = effect->GetParameterByName(NULL, "mtxInvView");
}

/**************************************
�C���f�b�N�o�b�t�@�쐬����
***************************************/
template<>
void BaseParticleController<BaseParticle, BaseEmitter>::MakeIndexBuffer()
{
	if (indexBuff != NULL)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	WORD index[] = { 0, 1, 2, 2, 1, 3 };
	pDevice->CreateIndexBuffer(sizeof(index), 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &indexBuff, 0);

	void* p;
	indexBuff->Lock(0, 0, &p, 0);
	memcpy(p, index, sizeof(index));
	indexBuff->Unlock();
}

/**************************************
�e�N�X�`���ǂݍ��ݏ���
***************************************/
template<>
void BaseParticleController<BaseParticle, BaseEmitter>::LoadTexture(const char* filePath)
{
	if (texture != NULL)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	CreateTextureFromFile((LPSTR)filePath, pDevice);
}

/**************************************
Transform���Z�b�g����
***************************************/
template<>
UINT BaseParticleController<BaseParticle, BaseEmitter>::EmbedParameterTransform()
{
	Transform *pTr;
	transformBuff->Lock(0, 0, (void**)&pTr, 0);
	UINT particleCount = 0;
	for (auto itr = particleContainer.begin(); itr != particleContainer.end() && particleCount < PARTICLE_NUM_MAX; itr++)
	{
		if (!itr->IsActive())
			continue;

		*pTr = itr->transform;
		pTr++;
		particleCount++;
	}
	transformBuff->Unlock();

	return particleCount;
}

/**************************************
UV���Z�b�g����
***************************************/
template<>
UINT BaseParticleController<BaseParticle, BaseEmitter>::EmbedParameterUV()
{
	ParticleUV *pUV;
	uvBuff->Lock(0, 0, (void**)&pUV, 0);
	UINT particleCount = 0;
	for (auto itr = particleContainer.begin(); itr != particleContainer.end() && particleCount < PARTICLE_NUM_MAX; itr++)
	{
		if (!itr->IsActive())
			continue;

		*pUV = itr->uv;
		*pUV++;
		particleCount++;
	}
	uvBuff->Unlock();

	return particleCount;
}

/**************************************
�`��J�n����
***************************************/
template<>
void BaseParticleController<BaseParticle, BaseEmitter>::BeginDraw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�����_�[�X�e�[�g�؂�ւ�
	pDevice->SetRenderState(D3DRS_LIGHTING, false);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);

	//�r���[�s��A�v���W�F�N�V�����s��A�r���[�t�s����擾
	D3DXMATRIX view, proj, invView;
	pDevice->GetTransform(D3DTS_VIEW, &view);
	pDevice->GetTransform(D3DTS_PROJECTION, &proj);
	D3DXMatrixInverse(&invView, NULL, &view);
	invView._41 = invView._42 = invView._43 = 0.0f;

	//�V�F�[�_�Ɋe�s���ݒ�
	effect->SetMatrix(hMtxView, &view);
	effect->SetMatrix(hMtxProj, &proj);
	effect->SetMatrix(hMtxInvView, &invView);

	//�e���_�o�b�t�@��ݒ�
	pDevice->SetStreamSource(1, transformBuff, 0, sizeof(Transform));
	pDevice->SetStreamSource(2, uvBuff, 0, sizeof(ParticleUV));
	pDevice->SetIndices(indexBuff);
	pDevice->SetVertexDeclaration(declare);
	
	//�V�F�[�_�ɂ��`��J�n
	effect->Begin(0, 0);
	effect->BeginPass(0);
}

/**************************************
�`��I������
***************************************/
template<>
void BaseParticleController<BaseParticle, BaseEmitter>::EndDraw()
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�V�F�[�_�ɂ��`��I��
	effect->EndPass();
	effect->End();

	//�����_�[�X�e�[�g����
	pDevice->SetRenderState(D3DRS_LIGHTING, true);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
}

template BaseParticleController<BaseParticle, BaseEmitter>;