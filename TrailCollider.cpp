//=====================================
//
//�g���C���R���C�_�[����[TrailCollider.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "TrailCollider.h"
#include <algorithm>

using namespace std;

/**************************************
�}�N����`
***************************************/
#define TRAILCOLLIDER_HIT_LENGTH		(20.0f)

/**************************************
�\���̒�`
***************************************/

/**************************************
static�ϐ�
***************************************/
map<TrailColliderTag, list<TrailCollider*>> TrailCollider::checkDictionary;

#ifdef _DEBUG
LineRenderer* TrailCollider::renderer;
UINT TrailCollider::instanceCount;
#endif

/**************************************
�Փ˔���
***************************************/
bool TrailCollider::CheckCollision(TrailCollider *other)
{
	//�n�_�ƏI�_�̈�v����
	if(this->model != other->model)
		return false;

	//Z��������
	float dist = fabsf(*posZ - *(other->posZ));

	if (dist < TRAILCOLLIDER_HIT_LENGTH)
	{
		//���g�Ƒ���̊ϑ��҂ɏՓ˂�ʒm
		ObserveSubject::NotifyObservers();
		other->NotifyObservers();

		return true;
	}
	else
	{
		return false;
	}
	
}

/**************************************
�R���X�g���N�^
***************************************/
TrailCollider::TrailCollider(TrailColliderTag tag)
{
	this->tag = tag;

#ifdef _DEBUG
	instanceCount++;
	if (renderer == NULL)
		renderer = new LineRenderer();
	renderer->SetColor(D3DXCOLOR(1.0f, 0.4f, 0.4f, 0.5f));
#endif
}

/**************************************
�f�X�g���N�^
***************************************/
TrailCollider::~TrailCollider()
{
	list<TrailCollider*> *checkList = &checkDictionary[tag];
	auto itr = find(checkList->begin(), checkList->end(), this);
	if (itr != checkList->end())
	{
		checkList->erase(itr);
	}

#ifdef _DEBUG
	instanceCount--;
	if (instanceCount == 0)
		SAFE_DELETE(renderer);
#endif
}

/**************************************
�g���C���C���f�b�N�X�Z�b�g����
***************************************/
void TrailCollider::SetTrailIndex(LineTrailModel model)
{
	this->model = model;
}

/**************************************
Z���W�|�C���^�Z�b�g����
***************************************/
void TrailCollider::SetAddressZ(float* adrPosZ)
{
	this->posZ = adrPosZ;
}

/**************************************
�Փ˔���
***************************************/
void TrailCollider::UpdateCollision()
{
	//�v���C���[�o���b�g�ƃG�l�~�[�̏Փ˔���
	for (TrailCollider* bullet : checkDictionary[TrailColliderTag::PlayerBullet])
	{
		for (TrailCollider *enemy : checkDictionary[TrailColliderTag::Enemy])
		{
			bullet->CheckCollision(enemy);
		}
	}
}

/**************************************
�`�F�b�N���X�g�o�^����
***************************************/
void TrailCollider::RegisterToCheckList()
{
	list<TrailCollider*> *checkList = &checkDictionary[tag];

	//���d�o�^����
	auto itr = find(checkList->begin(), checkList->end(), this);
	if (itr != checkList->end())
		return;

	//�o�^
	checkList->push_back(this);
}

/**************************************
�`�F�b�N���X�g���E����
***************************************/
void TrailCollider::RemoveFromCheckList()
{
	list<TrailCollider*> *checkList = &checkDictionary[tag];

	//�o�^�m�F
	auto itr = find(checkList->begin(), checkList->end(), this);
	if (itr == checkList->end())
		return;

	//���E
	checkList->erase(itr);
}

/**************************************
Collider�`�揈��
***************************************/
void TrailCollider::DrawCollider(TrailCollider *collider)
{
#ifdef _DEBUG
	D3DXVECTOR3 right, left, center;
	collider->model.GetEdgePos(&right, &left);
	center = (right - left) / 2.0f + left;
	center.z = *collider->posZ;

	renderer->Init(&right, &left, 5.0f);

	D3DXMATRIX mtxWorld;
	D3DXMatrixTranslation(&mtxWorld, center.x, center.y, center.z);
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
	pDevice->SetTexture(0, NULL);

	renderer->Draw();
#endif
}