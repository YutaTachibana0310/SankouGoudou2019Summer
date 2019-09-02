//=====================================
//
//�G�l�~�[��ǔ�����{���o�[����[PlayerBomberEnemy.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "PlayerBomberEnemy.h"
#include "enemy.h"
#include "Framework\CameraShakePlugin.h"

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�X�V����
***************************************/
void PlayerBomberEnemy::Update()
{
	if (!active)
		return;

	std::shared_ptr<Enemy> ptr = target.lock();

	//�Q�Ɛ悪�L���ł���΃^�[�Q�b�g���W���X�V
	if (ptr)
	{
		targetPos = ptr->m_Pos;
	}

	//�ǔ�����
	Homing();

	//���e�^�C�~���O�̔���
	if (cntFrame == 0)
	{
		//���e����
		if (ptr)
		{
			const D3DXVECTOR3 ShakeAmplitude = D3DXVECTOR3(10.0f, 10.0f, 10.0f);
			const int ShakeDuration = 60;

			//�J������h�炷
			Camera::ShakePlugin::Instance()->Set(ShakeAmplitude, ShakeDuration);
			ptr->OnHitBomber();
		}

		Uninit();
	}
}

/**************************************
�Z�b�g����
***************************************/
void PlayerBomberEnemy::Set(std::shared_ptr<Enemy>& target, D3DXVECTOR3 initPos)
{
	this->target = target;
	PlayerBomber::Set(initPos);
}
