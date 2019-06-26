//=============================================================================
//
// �v���C���[�R���g���[���[���� [PlayerController.cpp]
// Author : �n糗Ǒ�
//
//=============================================================================
#include "main.h"
#include "starUI.h"
#include "PlayerController.h"
#include "InputController.h"
#include "debugWindow.h"
#include "GameParticleManager.h"
#include "PlayerObserver.h"

using namespace std;

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MOVETARGET_LENGTH				(6)
#define PLAYER_DISTANCE_FROM_CAMERA		(150.0f)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void CalcPlayerMoveTargetPos();
void CheckInput(HWND hWnd);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
PlayerObserver *observer;

//*****************************************************************************
// ����������
//*****************************************************************************
HRESULT InitPlayerController(void)
{
	observer = new PlayerObserver();
	observer->Init();

	//�ړ��ڕW������
	CalcPlayerMoveTargetPos();

	return S_OK;
}
//*****************************************************************************
// �I������
//*****************************************************************************
void UninitPlayerController()
{
	observer->Uninit();
	delete observer;
}

//*****************************************************************************
// �X�V����
//*****************************************************************************
void UpdatePlayerController(HWND hWnd)
{
	//�ړ��̓��͊m�F
	CheckInput(hWnd);

	observer->Update();
}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void DrawPlayerController()
{
	observer->Draw();
}

//*****************************************************************************
// ���͊m�F
//*****************************************************************************
void CheckInput(HWND hWnd)
{
	//�e�{�^���ɂ��Ċm�F
	for (int i = 0; i < STAR_MAX; i++)
	{
		if (!IsEntered(i))
			continue;

		observer->PushInput(i);
		return;
	}
}


//=============================================================================
// �ړ��ڕW���W�v�Z����
//=============================================================================
void CalcPlayerMoveTargetPos()
{
	//�X�^�[�̃X�N���[�����W���擾
	D3DXVECTOR3 starPos[5];
	GetStarPosition(starPos);

	for (int i = 0; i < STAR_MAX; i++)
	{
		//�X�^�[�̈ʒu��Near�ʂ�Far�ʂ����ԃ��C���v�Z���Đ��K��
		D3DXVECTOR3 nearPos, farPos;
		CalcScreenToWorld(&nearPos, &starPos[i], 0.0f);
		CalcScreenToWorld(&farPos, &starPos[i], 1.0f);

		D3DXVECTOR3 ray = farPos - nearPos;
		D3DXVec3Normalize(&ray, &ray);

		//�ڕW���W���v�Z
		D3DXVECTOR3 pos = nearPos + ray * PLAYER_DISTANCE_FROM_CAMERA;
		observer->SetMoveTargetPosition(i, pos);
	}
}

//���t�@�N�^�����O�����̂ŃG���[�΍�ɉ���
bool SetBomb()
{
	return true;
}

//=============================================================================
// CCW�z��擾���� (���[�͂ܒǋL)
// �ǋL�i���ԁj�F���t�@�N�^�����O�Ńf�[�^�\�����ς�����̂ŗv���k
//=============================================================================
void GetMove_StackCCW(int trailHistoryCCW[MOVESTACK_LENGTH]) {

	for (int i = 0; i < MOVESTACK_LENGTH; i++) {
		trailHistoryCCW[i] = INITIAL_ARRAY_NUMBER;
	}
}

//=============================================================================
// CW�z��擾���� (���[�͂ܒǋL)
// �ǋL�i���ԁj�F���t�@�N�^�����O�Ńf�[�^�\�����ς�����̂ŗv���k
//=============================================================================
void GetMove_StackCW(int trailHistoryCW[MOVESTACK_LENGTH]) {
	for (int i = 0; i < MOVESTACK_LENGTH; i++) {
		trailHistoryCW[i] = INITIAL_ARRAY_NUMBER;
	}
}