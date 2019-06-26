//=====================================
//
//�R���W�����}�l�[�W������[CollisionManager.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "CollisionManager.h"

#include "PlayerController.h"
#include "PlayerBullet.h"

#include <vector>
#include "debugWindow.h"

using namespace std;

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�v���g�^�C�v�錾
***************************************/
void CheckCollisionPlayerBullet();

/**************************************
�X�V����
***************************************/
void UpdateCollisionManager(void)
{
	CheckCollisionPlayerBullet();
}

/**************************************
�v���C���[�o���b�g�̏Փ˔���
***************************************/
void CheckCollisionPlayerBullet()
{
#if 0
	vector<PlayerBullet*>* bulletContainer = GetPlayerBulletContainer();

	//�G�l�~�[�ƃo���b�g�̑�������
	for (auto itrBullet = bulletContainer->begin(); itrBullet != bulletContainer->end(); itrBullet++)
	{

	}

//#ifdef _DEBUG
	//�e�X�g�p
	static TrailCollider testCollider;
	static int start, end;
	static float posZ = 500.0f;
	BeginDebugWindow("Collider");

	DebugInputInt("Start", &start);
	DebugInputInt("End", &end);
	DebugSliderFloat("Z", &posZ, 0.0f, 1000.0f);
	
	testCollider.SetAddressZ(&posZ);
	testCollider.SetTrailIndex((TrailIndex)start, (TrailIndex)end);

	for (auto itr = bulletContainer->begin(); itr != bulletContainer->end(); itr++)
	{
		if (!(*itr)->IsActive())
			continue;

		if ((*itr)->GetCollider().CheckCollision(&testCollider))
		{
			DebugText("hit!");
		}
	}

	EndDebugWindow("Begin");
#endif
}