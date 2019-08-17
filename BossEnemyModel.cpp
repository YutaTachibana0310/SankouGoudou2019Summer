//=====================================
//
//�{�X�G�l�~�[���f������[BossEnemyModel.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "BossEnemyModel.h"
#include "BossEnemyActor.h"
#include "BossInit.h"

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
	state->OnUpdate(this);

	actor->Update();
	return 0;
}

/**************************************
�`�揈��
***************************************/
void BossEnemyModel::Draw()
{
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
}