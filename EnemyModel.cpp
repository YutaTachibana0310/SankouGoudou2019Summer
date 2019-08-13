//=====================================
//
//�x�[�X�G�l�~�[���f������[EnemyModel.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "EnemyModel.h"
#include "GameParticleManager.h"
#include "ScoreManager.h"
#include "Framework\BaseEmitter.h"
#include <algorithm>

using namespace std;

/**************************************
�}�N����`
***************************************/

/**************************************
static�ϐ�
***************************************/
//�܊p�`�̊O�����\������LineModel
const vector<LineTrailModel> EnemyModel::OuterLineModel = {
	LineTrailModel(0, 1),
	LineTrailModel(1, 2),
	LineTrailModel(2, 3),
	LineTrailModel(3, 4),
	LineTrailModel(4, 0)
};


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

	for (auto& enemy : enemyList)
	{
		SAFE_DELETE(enemy);
	}
	enemyList.clear();
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
	collider->active = false;
	active = false;
}

/**************************************
�`�揈��
***************************************/
void EnemyModel::Draw()
{
	for (auto& enemy : enemyList)
	{
		enemy->VDraw();
	}

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
		enemy->m_FlgDestroyed = true;
	}

	//�`���[�W�G�t�F�N�g��\��
	for (auto& emitter : chageEffectList)
	{
		if(emitter != NULL)
			emitter->active = false;
	}
}

/**************************************
���j�ς݃G�l�~�[�m�F����
***************************************/
void EnemyModel::CheckDestroied()
{
	for (auto& enemy : enemyList)
	{
		if (!enemy->m_FlgDestroyed)
			continue;

		enemy->VUninit();
		GameParticleManager::Instance()->SetEnemyExplosion(&enemy->m_Pos);

		//�X�R�A�E�R���{���Z
		SetAddScore(100);
		SetAddCombo(1);

		SAFE_DELETE(enemy);
	}

	//����
	auto itrNewEnd = remove_if(enemyList.begin(), enemyList.end(), [](Enemy* enemy)
	{
		return enemy == NULL;
	});
	enemyList.erase(itrNewEnd, enemyList.end());

	if (enemyList.empty())
	{
		Uninit();
	}
}

/**************************************
�G�l�~�[���W�擾����
***************************************/
void EnemyModel::GetEnemy(list<Enemy*>& out)
{
	for (auto& enemy : enemyList)
	{
		out.push_back(enemy);
	}
}