//=====================================
//
//�x�[�X�G�l�~�[���f������[EnemyModel.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "EnemyModel.h"
#include "GameParticleManager.h"

using namespace std;

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
	pos.z = 250.0f;
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
	//�G�l�~�[���X�g�N���A
	enemyList.clear();

	collider->active = false;
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

#ifdef TRAILCOLLIDER_USE_DEBUG
	TrailCollider::DrawCollider(collider);
#endif
}

/**************************************
�Փ˔���ʒm���V�[�o�[
***************************************/
void EnemyModel::OnNotified(ObserveSubject *notifier)
{
	//�������邷�ׂẴG�l�~�[�Ƀ_���[�W����
	for (auto& enemy : enemyList)
	{
		enemy->Uninit();
		Singleton<GameParticleManager>::GetInstance()->SetEnemyExplosion(&enemy->pos);
	}

	//��A�N�e�B�u��
	Uninit();
}

/**************************************
��ԑJ�ڏ���
***************************************/
void EnemyModel::ChangeState(IStateMachine<EnemyModel> *next)
{
	state = next;
	state->OnStart(this);
}

/**************************************
�G�l�~�[�ǉ�����
***************************************/
void EnemyModel::AddEnemy(Enemy* enemy)
{
	enemyList.push_back(enemy);
}