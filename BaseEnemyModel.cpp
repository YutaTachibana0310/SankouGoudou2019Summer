//=====================================
//
//�x�[�X�G�l�~�[���f������[BaseEnemyModel.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "BaseEnemyModel.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
BaseEnemyModel::BaseEnemyModel()
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
BaseEnemyModel::~BaseEnemyModel()
{
	SAFE_DELETE(collider);
}

/**************************************
����������
***************************************/
void BaseEnemyModel::Init(LineTrailModel model)
{
	this->model = model;
	collider->SetTrailIndex(model);
	cntFrame = 0;
	active = true;
}

/**************************************
�I������
***************************************/
void BaseEnemyModel::Uninit()
{
	collider->RemoveFromCheckList();
	active = false;
}

/**************************************
�X�V����
***************************************/
int BaseEnemyModel::Update()
{
	return state->OnUpdate(this);
}

/**************************************
�`�揈��
***************************************/
void BaseEnemyModel::Draw()
{

}

/**************************************
�Փ˔���ʒm���V�[�o�[
***************************************/
void BaseEnemyModel::OnNotified(ObserveSubject *notifier)
{

}

/**************************************
��ԑJ��
***************************************/
void BaseEnemyModel::ChangeState(IStateMachine<BaseEnemyModel> *next)
{
	state = next;
	state->OnStart(this);
}