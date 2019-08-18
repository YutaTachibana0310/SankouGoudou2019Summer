//=============================================================================
//
// ���f������ [player.cpp]
// Author : �����̎���
//
//	�����L�����N�^�Ή���
//
//=============================================================================
#include "RebarOb.h"
#include "Framework\ResourceManager.h"
#include "Framework\Vector3.h"

/**************************************
�}�N����`
***************************************/


/**************************************
�R���X�g���N�^
***************************************/
RebarObstacle::RebarObstacle(const D3DXVECTOR3& pos, LineTrailModel& model)
{
	//�C���X�^���X�쐬
	transform = new Transform();
	collider = new TrailCollider(TrailColliderTag::EnemyBullet);

	//�R���C�_�[������
	collider->SetTrailIndex(model);
	collider->SetAddressZ(&transform->pos.z);
	collider->active = true;

	//���b�V���擾
	ResourceManager::Instance()->GetMesh("RebarObstacle", &mesh);

	//�g�����X�t�H�[��������
	transform->pos = pos;

	D3DXVECTOR3 right, left;
	model.GetEdgePos(&right, &left);
	float angle = Vector3::Angle(Vector3::Right, right - left);
	D3DXVECTOR3 axis = Vector3::Axis(Vector3::Right, right - left);
	transform->RotateByAxis(angle, axis);

	////��]������
	rotateAxis = Vector3::Axis(Vector3::Forward, right - left);

	//�t���O������
	isDestroyed = false;
	inMoving = false;
}

/**************************************
�f�X�g���N�^
***************************************/
RebarObstacle::~RebarObstacle()
{
	SAFE_DELETE(transform);
	SAFE_DELETE(collider);

	mesh = NULL;
}

/**************************************
�X�V����
***************************************/
void RebarObstacle::Update()
{
	//�ړ�����
	_Move();

	//��]����
	transform->RotateByAxis(5.0f, rotateAxis);
}

/**************************************
�`�揈��
***************************************/
void RebarObstacle::Draw()
{
	transform->SetWorld();
	mesh->Draw();

	TrailCollider::DrawCollider(collider);
}

/**************************************
�ړ�����
***************************************/
void RebarObstacle::Move(const D3DXVECTOR3& offset, int duration, EaseType type)
{
	startPos = transform->pos;
	endPos = transform->pos + offset;
	moveDuration = duration;
	cntFrame = 0;
	moveEaseType = type;
	inMoving = true;
}

/**************************************
�ړ���������
***************************************/
void RebarObstacle::_Move()
{
	if (!inMoving)
		return;

	cntFrame++;

	float t = (float)cntFrame / moveDuration;
	transform->pos = Easing::EaseValue(t, startPos, endPos, moveEaseType);

	if (cntFrame == moveDuration)
	{
		inMoving = false;
	}
}

/**************************************
���j����
***************************************/
bool RebarObstacle::IsDestroyed()
{
	return isDestroyed;
}