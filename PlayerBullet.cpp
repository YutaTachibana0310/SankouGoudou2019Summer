//=====================================
//
//�v���C���[�o���b�g����[PlayerBullet.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "PlayerBullet.h"
#include "Framework/Easing.h"
#include "GameParticleManager.h"

/**************************************
�}�N����`
***************************************/
#define PLAYERBULLET_LIFE_COUNT		(60)
#define PLAYERBULLET_FADE_FRAME		(30)
#define PLAYERBULLET_FADE_START		(PLAYERBULLET_LIFE_COUNT-PLAYERBULLET_FADE_FRAME)
#define PLAYERBULLET_VTX_LENGTH		(2.0f)
#define PLAYERBLLET_VTX_DELTA		(PLAYERBULLET_VTX_LENGTH / PLAYERBULLET_FADE_FRAME)
#define PLAYERBULLET_COLLIDER_SIZE	(D3DXVECTOR3(5.0f, 5.0f, 5.0f))

/**************************************
�\���̒�`
***************************************/

/**************************************
static�����o
***************************************/

/****************************************
����������
****************************************/
void PlayerBullet::Init(LineTrailModel model)
{
	cntFrame = 0;
	collider->SetTrailIndex(model);
	SetEdgePos(model);
	collider->active = true;
	colliderR->active = true;
	colliderL->active = true;
	active = true;
}

/****************************************
�I������
*****************************************/
void PlayerBullet::Uninit()
{
	collider->active = false;
	colliderL->active = false;
	colliderR->active = false;
	isDestroyed = false;
	active = false;
}

/****************************************
�X�V����
*****************************************/
void PlayerBullet::Update()
{
	if (!active)
		return;

	//�ړ�����
	const float Speed = 30.0f;
	pos.z += Speed;
	edgeL.z += Speed;
	edgeR.z += Speed;

	cntFrame++;

	//�k������
	if (cntFrame > PLAYERBULLET_FADE_START)
	{
		VERTEX_3D *pVtx;
		vtxBuff->Lock(0, 0, (void**)&pVtx, 0);
		pVtx[0].vtx -= vtxUp * PLAYERBLLET_VTX_DELTA;
		pVtx[1].vtx -= vtxUp * PLAYERBLLET_VTX_DELTA;
		pVtx[2].vtx += vtxUp * PLAYERBLLET_VTX_DELTA;
		pVtx[3].vtx += vtxUp * PLAYERBLLET_VTX_DELTA;
		vtxBuff->Unlock();
	}

	//��������
	if (cntFrame > PLAYERBULLET_LIFE_COUNT)
	{
		Uninit();
	}
}

/****************************************
�`�揈��
*****************************************/
void PlayerBullet::Draw()
{
	if (!active)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetStreamSource(0, vtxBuff, 0, sizeof(VERTEX_3D));

	D3DXMATRIX mtxWorld;
	D3DXMatrixIdentity(&mtxWorld);
	D3DXMatrixTranslation(&mtxWorld, pos.x, pos.y, pos.z);

	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	BoxCollider3D::DrawCollider(colliderL);
	BoxCollider3D::DrawCollider(colliderR);
}

/****************************************
�R���X�g���N�^
****************************************/
PlayerBullet::PlayerBullet()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	
	//���_�o�b�t�@�쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &vtxBuff, 0);

	//���_���W�ȊO�̏��𖄂߂�
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

	//�R���C�_�[�C���X�^���X�쐬
	collider = new TrailCollider(TrailColliderTag::PlayerBullet);

	//TrailCollider��Z���W�A�h���X��ݒ�
	collider->SetAddressZ(&pos.z);

	//�R���C�_�[�̊ϑ��҂Ɏ��g��ǉ�
	collider->AddObserver(this);

	//�[�_�̃R���C�_�[�C���X�^���X�쐬
	colliderR = new BoxCollider3D(BoxCollider3DTag::PlayerBullet, &edgeR, PLAYERBULLET_COLLIDER_SIZE);
	colliderL = new BoxCollider3D(BoxCollider3DTag::PlayerBullet, &edgeL, PLAYERBULLET_COLLIDER_SIZE);
	colliderR->AddObserver(this);
	colliderL->AddObserver(this);
}

/****************************************
�f�X�g���N�^
****************************************/
PlayerBullet::~PlayerBullet()
{
	SAFE_RELEASE(vtxBuff);
}

/****************************************
�[�_�Z�b�g����
*****************************************/
void PlayerBullet::SetEdgePos(LineTrailModel model)
{
	//�n�_�ƏI�_�����Ԑ������v�Z���A�����𔼕��ɂ���
	model.GetEdgePos(&edgeR, &edgeL);
	D3DXVECTOR3 diff = edgeR - edgeL;
	diff /= 2.0f;

	//�����ɐ����ȃx�N�g�������߂�
	D3DXVec3Cross(&vtxUp, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &diff);
	D3DXVec3Normalize(&vtxUp, &vtxUp);

	//���߂��x�N�g�����璸�_���W���v�Z
	VERTEX_3D *pVtx;
	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	pVtx[0].vtx = -diff + vtxUp * PLAYERBULLET_VTX_LENGTH;
	pVtx[1].vtx = diff + vtxUp * PLAYERBULLET_VTX_LENGTH;
	pVtx[2].vtx = -diff - vtxUp * PLAYERBULLET_VTX_LENGTH;
	pVtx[3].vtx = diff - vtxUp * PLAYERBULLET_VTX_LENGTH;
	vtxBuff->Unlock();

	//���[���h���W���n�_�ƏI�_�̐^�񒆂ɐݒ�
	pos = edgeL + diff;

	//�p�[�e�B�N���Z�b�g
	GameParticleManager::Instance()->SetPlayerBulletParticle(&pos, &active, &edgeR, &edgeL);
}

/****************************************
�Փ˔���ʒm���V�[�o�[
*****************************************/
void PlayerBullet::OnNotified(ObserveSubject *notifier)
{
	isDestroyed = true;
}

void PlayerBullet::OnNotified(BoxCollider3DTag other)
{
	isDestroyed = true;
}