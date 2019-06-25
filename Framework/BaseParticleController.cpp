//=====================================
//
//�x�[�X�p�[�e�B�N���R���g���[������[BaseParticleController.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "BaseParticleController.h"
#include <algorithm>

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
LPDIRECT3DVERTEXDECLARATION9 BaseParticleController::declare;	//���_�錾
LPD3DXEFFECT BaseParticleController::effect;					//�G�t�F�N�g
LPDIRECT3DINDEXBUFFER9 BaseParticleController::indexBuff;		//�C���f�b�N�o�b�t�@
LPDIRECT3DVERTEXBUFFER9 BaseParticleController::transformBuff;	//�g�����X�t�H�[�����_�o�b�t�@
LPDIRECT3DVERTEXBUFFER9 BaseParticleController::uvBuff;			//UV��񒸓_�o�b�t�@
UINT BaseParticleController::instanceCount;						//�C���X�^���X��
D3DXHANDLE BaseParticleController::hMtxView;					//�G�t�F�N�g�̃r���[�s��ւ̃n���h��
D3DXHANDLE BaseParticleController::hMtxProj;					//�G�t�F�N�g�̃v���W�F�N�V�����s��ւ̃n���h��
D3DXHANDLE BaseParticleController::hMtxInvView;					//�G�t�F�N�g�̃r���[�t�s��ւ̃n���h��

/**************************************
�R���X�g���N�^
***************************************/
BaseParticleController::BaseParticleController()
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
BaseParticleController::~BaseParticleController()
{
	SAFE_RELEASE(unitBuff);
	SAFE_RELEASE(texture);

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
�I������
***************************************/
void BaseParticleController::Uninit()
{
	vector<BaseParticle*>().swap(particleContainer);

	vector<BaseEmitter*>().swap(emitterContainer);

}

/**************************************
�X�V����
***************************************/
void BaseParticleController::Update()
{
	//�G�~�b�^�X�V
	for (BaseEmitter *emitter : emitterContainer)
	{
		if (!emitter->active)
			continue;

		emitter->Update();
	}

	//�p�[�e�B�N�����o
	Emit();

	//�p�[�e�B�N���X�V
	for (BaseParticle *particle : particleContainer)
	{
		if (!particle->active)
			continue;

		particle->Update();
	}
}

/**************************************
�`�揈��
***************************************/
bool BaseParticleController::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e�p�[�e�B�N���̃p�����[�^�𒸓_�o�b�t�@�ɃZ�b�g
	UINT particleCount = 0;
	particleCount = EmbedParameterTransform();
	EmbedParameterUV();

	if (particleCount == 0)
		return false;

	//�X�g���[���\�[�X�ݒ�
	pDevice->SetStreamSource(0, unitBuff, 0, sizeof(ParticleUnit));
	pDevice->SetStreamSourceFreq(0, D3DSTREAMSOURCE_INDEXEDDATA | particleCount);

	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, texture);

	//�`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, NUM_VERTEX, 0, NUM_POLYGON);

	return true;
}

/**************************************
�p�[�e�B�N���P�ʃo�b�t�@�쐬����
***************************************/
void BaseParticleController::MakeUnitBuffer(const D3DXVECTOR2 *size, const D3DXVECTOR2 *texDiv)
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
void BaseParticleController::MakeTransformBuffer()
{
	if (transformBuff != NULL)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->CreateVertexBuffer(sizeof(Transform) * PARTICLE_NUM_MAX, 0, 0, D3DPOOL_MANAGED, &transformBuff, 0);
}

/**************************************
UV�o�b�t�@�쐬����
***************************************/
void BaseParticleController::MakeUVBuffer()
{
	if (uvBuff != NULL)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->CreateVertexBuffer(sizeof(ParticleUV) * PARTICLE_NUM_MAX, 0, 0, D3DPOOL_MANAGED, &uvBuff, 0);
}

/**************************************
���_�錾�쐬����
***************************************/
void BaseParticleController::MakeVertexDeclaration()
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
void BaseParticleController::LoadEffect()
{
	if (effect != NULL)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXCreateEffectFromFile(pDevice, "data/EFFECT/particle3D.cfx", 0, 0, D3DXSHADER_SKIPVALIDATION, 0, &effect, 0);

	hMtxView = effect->GetParameterByName(NULL, "mtxView");
	hMtxProj = effect->GetParameterByName(NULL, "mtxProj");
	hMtxInvView = effect->GetParameterByName(NULL, "mtxInvView");
}

/**************************************
�C���f�b�N�o�b�t�@�쐬����
***************************************/
void BaseParticleController::MakeIndexBuffer()
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
void BaseParticleController::LoadTexture(const char* filePath)
{
	if (texture != NULL)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	texture = CreateTextureFromFile((LPSTR)filePath, pDevice);
}

/**************************************
�`��J�n����
***************************************/
void BaseParticleController::BeginDraw()
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

	//�X�g���[�����g���ݒ�
	pDevice->SetStreamSourceFreq(1, D3DSTREAMSOURCE_INSTANCEDATA | 1);
	pDevice->SetStreamSourceFreq(2, D3DSTREAMSOURCE_INSTANCEDATA | 1);
	
	//�V�F�[�_�ɂ��`��J�n
	effect->Begin(0, 0);
	effect->BeginPass(0);
}

/**************************************
�`��I������
***************************************/
void BaseParticleController::EndDraw()
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�V�F�[�_�ɂ��`��I��
	effect->EndPass();
	effect->End();

	//�����_�[�X�e�[�g����
	pDevice->SetRenderState(D3DRS_LIGHTING, true);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);

	//�X�g���[�����g������
	pDevice->SetStreamSourceFreq(0, 1);
	pDevice->SetStreamSourceFreq(1, 1);
	pDevice->SetStreamSourceFreq(2, 1);
}

/**************************************
�g�����X�t�H�[����񖄂ߍ��ݏ���
***************************************/
UINT BaseParticleController::EmbedParameterTransform()
{
	if (particleContainer.size() > PARTICLE_NUM_MAX)
		return 0;

	UINT count = 0;
	Transform *pTr;
	transformBuff->Lock(0, 0, (void**)&pTr, 0);
	for (BaseParticle *particle : particleContainer)
	{
		if (!particle->active)
			continue;

		*pTr = particle->transform;
		pTr++;
		count++;
	}

	return count;
}

/**************************************
UV��񖄂ߍ��ݏ���
***************************************/
UINT BaseParticleController::EmbedParameterUV()
{
	if (particleContainer.size() > PARTICLE_NUM_MAX)
		return 0;

	UINT count = 0;
	ParticleUV *pUV;
	uvBuff->Lock(0, 0, (void**)&pUV, 0);
	for (BaseParticle *particle : particleContainer)
	{
		if (!particle->active)
			continue;

		*pUV = particle->uv;
		pUV++;
		count++;
	}

	return count;
}

/**************************************
�G�~�b�^�Z�b�g����
***************************************/
void BaseParticleController::SetEmitter(D3DXVECTOR3 *pos)
{
	auto emitter = find_if(emitterContainer.begin(), emitterContainer.end(), [](BaseEmitter* emitter)
	{
		return !emitter->active;
	});

	if (emitter == emitterContainer.end())
		return;

	(*emitter)->transform.pos = *pos;
	(*emitter)->Init();

}