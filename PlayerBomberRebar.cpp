//=====================================
//
//PlayerBomberRebar.cpp
//�@�\:�S����ǔ�����{���o�[
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "PlayerBomberRebar.h"
#include "Framework\CameraShakePlugin.h"

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�X�V����
***************************************/
void PlayerBomberRebar::Update()
{
	if (!active)
		return;

	std::shared_ptr<RebarObstacle> ptr = target.lock();

	//�Q�Ɛ悪�L���ł���΃^�[�Q�b�g���W���X�V
	if (ptr)
	{
		targetPos = ptr->GetPos();
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
void PlayerBomberRebar::Set(std::shared_ptr<RebarObstacle>& target, D3DXVECTOR3 initPos)
{
	const int ReachFrame = 40;

	this->target = target;
	transform.pos = initPos;
	cntFrame = reachFrame = ReachFrame;
}
