//=====================================
//
//�x�[�X�G�l�~�[���f������[EnemyModel.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "EnemyModel.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
EnemyModel::EnemyModel()
{
	collider = new TrailCollider(TrailColliderTag::Enemy);
	collider->AddObserver(this);
	pos.z = 500.0f;
	collider->SetAddressZ(&pos.z);
	active = false;
}

/**************************************
�f�X�g���N�^
***************************************/
EnemyModel::~EnemyModel()
{
	SAFE_DELETE(collider);
}

/**************************************
����������
***************************************/
void EnemyModel::Init(LineTrailModel model)
{
	this->model = model;
	collider->SetTrailIndex(model);
	cntFrame = 0;
	active = true;
}

/**************************************
�I������
***************************************/
void EnemyModel::Uninit()
{
	collider->RemoveFromCheckList();
	active = false;
}

/**************************************
�X�V����
***************************************/
int EnemyModel::Update()
{
	return state->OnUpdate(this);
}

/**************************************
�`�揈��
***************************************/
void EnemyModel::Draw()
{

}

/**************************************
�Փ˔���ʒm���V�[�o�[
***************************************/
void EnemyModel::OnNotified(ObserveSubject *notifier)
{

}

/**************************************
��ԑJ�ڏ���
***************************************/
void EnemyModel::ChangeState(IStateMachine<EnemyModel> *next)
{
	state = next;
	state->OnStart(this);
}