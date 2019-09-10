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
#include "sound.h"
#include "camera.h"
#include "Framework\CameraShakePlugin.h"

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

//���Z�X�R�A�̑f�_
const int EnemyModel::BaseScorePoint = 50;

/**************************************
�R���X�g���N�^
***************************************/
EnemyModel::EnemyModel() :
	explosionScale(1.0f)
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
		enemy.reset();
	}
	enemyList.clear();

	for (auto& emitter : chageEffectList)
	{
		if (emitter != NULL)
			emitter->active = false;
	}
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
		GameParticleManager::Instance()->SetEnemyExplosion(&enemy->m_Pos, explosionScale);

		//�X�R�A�E�R���{���Z
		SetAddCombo(1);
		SetAddScore(BaseScorePoint);

		//����SE
		Sound::GetInstance()->SetPlaySE(ENEMYDOWN1, true, (Sound::GetInstance()->changevol / 100.0f));

		//�J�����h�炷
		const D3DXVECTOR3 ShakeAmplitude = D3DXVECTOR3(0.75f, 0.75f, 0.0f);
		const int ShakeDuration = 120;
		Camera::ShakePlugin::Instance()->Set(ShakeAmplitude, ShakeDuration);

		enemy.reset();
	}

	//����
	auto itrNewEnd = remove_if(enemyList.begin(), enemyList.end(), [](auto&& enemy)
	{
		return !enemy;
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
void EnemyModel::GetShotPos(std::vector<D3DXVECTOR3>& out)
{
	for (auto&& enemy : enemyList)
	{
		out.push_back(enemy->m_Pos + ShotPosOffset);
	}
}

/**************************************
�G�l�~�[���W�擾����
***************************************/
void EnemyModel::GetEnemy(list<shared_ptr<Enemy>>& out)
{
	for (auto& enemy : enemyList)
	{
		//Z���W�����Ȃ�ǉ����Ȃ�
		if (enemy->m_Pos.z < 0.0f)
			continue;

		//�G�l�~�[�̃��[���h���W���X�N���[�����W�֕ϊ�
		D3DXVECTOR3 screenPos;
		Camera::Instance()->Projection(screenPos, enemy->m_Pos);

		//�X�N���[���O�ɂ�����ǉ����Ȃ�
		if (screenPos.x < 0.0f || screenPos.x > SCREEN_WIDTH * 1.0f)
			continue;

		if (screenPos.y < 0.0f || screenPos.z > SCREEN_HEIGHT * 1.0f)
			continue;

		out.push_back(enemy);
	}
}