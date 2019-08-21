//=====================================
//
//�{�X�G�l�~�[���f������[BossEnemyModel.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "BossEnemyModel.h"
#include "BossEnemyActor.h"
#include "BossInit.h"
#include "BossRebarAttack.h"
#include "BossHomingAttack.h"
#include "BossDamageable.h"
#include "BossLargeDamage.h"

#include "EnemyBulletController.h"

#include "Framework\ResourceManager.h"
#include "GameParticleManager.h"

using namespace std;
/**************************************
�}�N����`
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
BossEnemyModel::BossEnemyModel(const Transform& player) : player(player)
{
	actor = new BossEnemyActor();
	bulletController = new EnemyBulletController();
	colliderController = new BossColliderController(*this);

	//�X�e�[�g�}�V���쐬
	fsm[State::Init] = new BossInit();
	fsm[State::RebarAttack] = new BossRebarAttack();
	fsm[State::HomingAttack] = new BossHomingAttack();
	fsm[State::Damageable] = new BossDamageable();
	fsm[State::LargeDamage] = new BossLargeDamage();

	//�S�؂̃��f�������[�h
	ResourceManager::Instance()->LoadMesh("RebarObstacle", "data/MODEL/rebar.x");

	//���x��������
	level = 0;

	//Init�X�e�[�g�֑J��
	ChangeState(State::Init);
 }

/**************************************
�f�X�g���N�^
***************************************/
BossEnemyModel::~BossEnemyModel()
{
	SAFE_DELETE(actor);
	SAFE_DELETE(bulletController);

	for (auto&& pair : fsm)
	{
		SAFE_DELETE(pair.second);
	}
	fsm.clear();

	
	for (auto&& rebar : rebarList)
	{
		rebar.reset();
	}
	rebarList.clear();
}

/**************************************
�X�V����
***************************************/
int BossEnemyModel::Update()
{
	int nextState = state->OnUpdate(this);
	if (nextState != currentState)
	{
		ChangeState((State)nextState);
	}

	for (auto&& rebar : rebarList)
	{
		rebar->Update();
	}

	actor->Update();


	bulletController->Update();

	colliderController->Update();

	rebarList.remove_if([](auto&& rebar)
	{
		return rebar->IsDestroyed();
	});

	return 0;
}

/**************************************
�`�揈��
***************************************/
void BossEnemyModel::Draw()
{
	for (auto&& rebar : rebarList)
	{
		rebar->Draw();
	}

	actor->Draw();

	bulletController->Draw();

	colliderController->Draw();
}

/**************************************
��ԑJ�ڏ���
***************************************/
void BossEnemyModel::ChangeState(State next)
{
	state = fsm[next];
	state->OnStart(this);

	prevState = currentState;
	currentState = next;
	cntAttack = 0;
}

/**************************************
�S�؃Z�b�g����
***************************************/
void BossEnemyModel::SetRebar()
{
	float z = 300.0f;
	const int LoopMax[] = { 2, 3, 5 };
	for (int i = 0; i < LoopMax[level]; i++)
	{
		int start = Math::RandomRange(0, 5);
		int end = Math::WrapAround(0, 5, start + Math::RandomRange(1, 4));

		LineTrailModel model = LineTrailModel(start, end);
		D3DXVECTOR3 right, left;
		model.GetEdgePos(&right, &left);

		D3DXVECTOR3 pos = right + (left - right) / 2.0f;
		pos.z = z;
		pos.y -= 500.0f;

		RebarObstacle *rebar = new RebarObstacle(pos, model);
		rebar->Move(D3DXVECTOR3(0.0f, 500.0f, 0.0f), 120, EaseType::OutCubic);

		rebarList.push_back(unique_ptr<RebarObstacle>(rebar));

		z += 100.0f;
	}
}

/**************************************
�S�ؓ�������
***************************************/
void BossEnemyModel::ThrowRebar()
{
	for (auto&& rebar : rebarList)
	{
		rebar->Move(player, 2500.0f, 180, EaseType::InSine);
	}
}

/**************************************
�`���[�W�J�n����
***************************************/
void BossEnemyModel::StartBulletCharge()
{
	D3DXVECTOR3 SetPos = D3DXVECTOR3(0.0f, 0.0f, 500.0f);

	GameParticleManager::Instance()->SetBossCharge(&SetPos);
}

/**************************************
�o���b�g���ˏ���
**************************************/
void BossEnemyModel::FireBullet()
{
	static std::vector<D3DXVECTOR3> Emitter = { D3DXVECTOR3(0.0f, 0.0f, 500.0f),  D3DXVECTOR3(0.0f, 0.0f, 500.0f), D3DXVECTOR3(0.0f, 0.0f, 500.0f) };
	static const int LoopMax[] = { 1, 2, 3 };

	for (int i = 0; i < LoopMax[level]; i++)
	{
		int start = RandomRange(0, 5);
		int end = WrapAround(0, 5, start + RandomRange(1, 5));
		bulletController->Set(Emitter, LineTrailModel(start, end), 60, D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	}
}

/**************************************
�R���C�_�[�Z�b�g����
**************************************/
void BossEnemyModel::SetCollider()
{
	const UINT EdgeMax = 3;
	int prevStart = 5;
	int prevEnd = RandomRange(0, 5);

	std::vector<int> edgeList;
	edgeList.reserve(EdgeMax);

	for (UINT i = 0; i < EdgeMax; i++)
	{
		int start = prevEnd;
		edgeList.push_back(start);

		int end = prevStart;
		while (end == prevStart)
		{
			end = WrapAround(0, 5, start + RandomRange(1, 5));
		}
		prevEnd = end;
		prevStart = start;
	}

	colliderController->SetCollider(edgeList);
}

/**************************************
�_���[�W����
**************************************/
void BossEnemyModel::OnDamage()
{
	actor->ChangeAnimation(BossEnemyActor::AnimID::Damage);
}