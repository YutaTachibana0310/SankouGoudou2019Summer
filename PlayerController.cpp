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
#include "trailUI.h"

using namespace std;

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MOVETARGET_LENGTH				(6)
#define PLAYER_DISTANCE_FROM_CAMERA		(150.0f)

//#define USE_COLLIDER_TEST

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void CheckInput(HWND hWnd);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
PlayerObserver *observer;

#ifdef USE_COLLIDER_TEST
TrailCollider *testCollider;
#endif
//*****************************************************************************
// ����������
//*****************************************************************************
HRESULT InitPlayerController(void)
{
	observer = new PlayerObserver();
	observer->Init();

#ifdef USE_COLLIDER_TEST
	testCollider = new TrailCollider("Enemy");
	testCollider->RegisterToCheckList();
#endif
	return S_OK;
}
//*****************************************************************************
// �I������
//*****************************************************************************
void UninitPlayerController()
{
	observer->Uninit();
	delete observer;

#ifdef USE_COLLIDER_TEST
	testCollider->RemoveFromCheckList();
	delete testCollider;
#endif
}

//*****************************************************************************
// �X�V����
//*****************************************************************************
void UpdatePlayerController(HWND hWnd)
{
	//�ړ��̓��͊m�F
	CheckInput(hWnd);

	observer->Update();

#ifdef USE_COLLIDER_TEST
	static int start, end;
	static float posZ = 500.0f;
	BeginDebugWindow("Collider");

	DebugInputInt("Start", &start);
	DebugInputInt("End", &end);
	DebugSliderFloat("Z", &posZ, 0.0f, 1000.0f);

	testCollider->SetAddressZ(&posZ);
	testCollider->SetTrailIndex(LineTrailModel(start, end));
#endif
	EndDebugWindow("Collider");
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
// MoveHistory�擾����
//=============================================================================
void GetPlayerMoveHistory(vector<int> *pOut)
{
	//�ړ��������擾
	vector<LineTrailModel> moveHistory;
	observer->model->GetAllPlayerTrail(&moveHistory);

	//UI�p�f�[�^�ɕϊ�
	for (LineTrailModel model : moveHistory)
	{
		if (model.start == TOP || model.end == TOP)
		{
			if (model.start == LOWER_RIGHT || model.end == LOWER_RIGHT)
			{
				pOut->push_back(TRAIL_LINE_TOP_TO_LOWERRIGHT);
				continue;
			}
			if (model.start == LOWER_LEFT || model.end == LOWER_LEFT)
			{
				pOut->push_back(TRAIL_LINE_TOP_TO_LOWERLEFT);
				continue;
			}
		}
		else if (model.start == LOWER_LEFT || model.end == LOWER_LEFT)
		{
			if (model.start == MIDDLE_RIGHT || model.end == MIDDLE_RIGHT)
			{
				pOut->push_back(TRAIL_LINE_LOWERLEFT_TO_MIDDLERIGHT);
				continue;
			}
		}
		else if (model.start == LOWER_RIGHT || model.end == LOWER_RIGHT)
		{
			if (model.start == MIDDLE_LEFT || model.end == MIDDLE_LEFT)
			{
				pOut->push_back(TRAIL_LINE_LOWERRIGHT_TO_MIDDLELEFT);
				continue;
			}
		}
		else if (model.start == MIDDLE_LEFT || model.end == MIDDLE_LEFT)
		{
			if (model.start == MIDDLE_RIGHT || model.end == MIDDLE_RIGHT)
			{
				pOut->push_back(TRAIL_LINE_MIDDLELEFT_TO_MIDDLERIGHT);
				continue;
			}
		}
	}

	return;
}