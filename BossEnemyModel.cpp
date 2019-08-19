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

#include "Framework\ResourceManager.h"
#include "GameParticleManager.h"

using namespace std;
/**************************************
�}�N����`
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
BossEnemyModel::BossEnemyModel()
{
	actor = new BossEnemyActor();

	//�X�e�[�g�}�V���쐬
	fsm[State::Init] = new BossInit();
	fsm[State::RebarAttack] = new BossRebarAttack();
	fsm[State::HomingAttack] = new BossHomingAttack();

	//�S�؂̃��f�������[�h
	ResourceManager::Instance()->LoadMesh("RebarObstacle", "data/MODEL/rebar.x");

	//Init�X�e�[�g�֑J��
	ChangeState(State::Init);
 }

/**************************************
�f�X�g���N�^
***************************************/
BossEnemyModel::~BossEnemyModel()
{
	SAFE_DELETE(actor);
}

/**************************************
�X�V����
***************************************/
int BossEnemyModel::Update()
{
	updateResult = StateContinuous;

	state->OnUpdate(this);

	for (auto&& rebar : rebarList)
	{
		rebar->Update();
	}

	actor->Update();

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
	//for (int i = 0; i < 5; i++)
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

		rebarList.push_back(rebar);

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
		rebar->Move(D3DXVECTOR3(0.0f, 0.0f, -2000.0f), 300, EaseType::InOutCubic);
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