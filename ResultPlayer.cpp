//=====================================
//
//���U���g�v���C���[����[ResultPlayer.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "ResultPlayer.h"
#include "Framework\AnimContainer.h"

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
ResultPlayer::ResultPlayer(bool isClear)
{
	//�A�j���[�V����������
	animation = new AnimContainer();
	animation->LoadXFile("data/MODEL/ResultPlayer.x", "ResultPlayer");
	animation->SetupCallbackKeyFrames("ResultClear");
	animation->SetupCallbackKeyFrames("ResultFailed");
	animation->LoadAnimation("ResultClear", AnimID::Clear);
	animation->LoadAnimation("ResultFailed", AnimID::Failed);
	animation->SetShiftTime(AnimID::Clear, 0.2f);
	animation->SetShiftTime(AnimID::Failed, 0.2f);

	//�g�����X�t�H�[���쐬
	transform = new Transform();
	transform->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�A�j���[�V�����J��
	AnimID state = isClear ? AnimID::Clear : AnimID::Failed;
	animation->ChangeAnim(state, 1.0f, true);
}

/**************************************
�f�X�g���N�^
***************************************/
ResultPlayer::~ResultPlayer()
{
	SAFE_DELETE(animation);
	SAFE_DELETE(transform);
}

/**************************************
�X�V����
***************************************/
void ResultPlayer::Update()
{
	animation->Update(1.0f / 60);
}

/**************************************
�`�揈��
***************************************/
void ResultPlayer::Draw()
{
	transform->SetWorld();
	
	D3DXMATRIX mtxWorld = transform->GetMatrix();
	animation->Draw(&mtxWorld);
}
