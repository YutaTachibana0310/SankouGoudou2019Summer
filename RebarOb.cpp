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
RebarObstacle::RebarObstacle(const D3DXVECTOR3& pos, LineTrailModel& model, const Transform& player) :
	player(player)
{
	//�C���X�^���X�쐬
	transform = new Transform();
	collider = new BoxCollider3D(BoxCollider3DTag::Rebar, &transform->pos);

	//�R���C�_�[������
	const float colliderSize = 10.0f;
	collider->SetSize(D3DXVECTOR3(colliderSize, colliderSize, colliderSize));
	collider->active = true;

	//���b�V���擾
	ResourceManager::Instance()->GetMesh("RebarObstacle", mesh);

	//�g�����X�t�H�[��������
	transform->pos = pos;

	D3DXVECTOR3 right, left;
	model.GetEdgePos(&right, &left);
	D3DXVECTOR3 diff = right - left;
	float angle = Vector3::Angle(Vector3::Right, diff);
	D3DXVECTOR3 axis = Vector3::Axis(Vector3::Right, diff);
	transform->RotateByAxis(angle, axis);

	////��]������
	rotateAxis = Vector3::Axis(Vector3::Forward, diff);

	//�t���O������
	isDestroyed = false;
	inMoving = false;
	reserveDestroy = false;
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

	if (cntFrame == delay)
	{
		inMoving = true;
		if (reserveDestroy)
		{
			D3DXVECTOR3 noise = D3DXVECTOR3(RandomRangef(-20.0f, 20.0f), RandomRangef(-20.0f, 20.0f), RandomRangef(-20.0f, 20.0f));
			D3DXVECTOR3 diff = player.pos + noise - transform->pos;
			D3DXVec3Normalize(&diff, &diff);
			endPos = transform->pos + diff * moveLength;
		}
	}

	cntFrame++;

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

	BoxCollider3D::DrawCollider(collider);
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
	delay = 0;
}

/**************************************
�ړ���������
***************************************/
void RebarObstacle::_Move()
{
	if (!inMoving)
		return;

	float t = (float)(cntFrame - delay) / moveDuration;
	transform->pos = Easing::EaseValue(t, startPos, endPos, moveEaseType);

	if (cntFrame == moveDuration)
	{
		inMoving = false;

		if (reserveDestroy)
			isDestroyed = true;
	}
}

/**************************************
���j����
***************************************/
bool RebarObstacle::IsDestroyed()
{
	return isDestroyed;
}

/**************************************
Move����
***************************************/
void RebarObstacle::Move(float length, int duration, EaseType type, int delay)
{
	startPos = transform->pos;
	moveLength = length;
	moveDuration = duration;
	cntFrame = 0;
	moveEaseType = type;
	inMoving = false;
	reserveDestroy = true;
	this->delay = delay;
}