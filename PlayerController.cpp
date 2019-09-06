//=============================================================================
//
// プレイヤーコントローラー処理 [PlayerController.cpp]
// Author : 渡邉良則
//
//=============================================================================
#include "main.h"
#include "starButtonUI.h"
#include "PlayerController.h"
#include "PlayerObserver.h"
#include "trailUI.h"

using namespace std;

//*****************************************************************************
// グローバル変数
//*****************************************************************************
PlayerObserver *observer;

//=============================================================================
// MoveHistory取得処理
//=============================================================================
void GetPlayerMoveHistory(vector<int> *pOut)
{
	//移動履歴を取得
	vector<LineTrailModel> moveHistory;
	observer->model->GetAllPlayerTrail(&moveHistory);

	//UI用データに変換
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

//*****************************************************************************
// PlayerObserverセット処理
//*****************************************************************************
void SetPlayerObserverAdr(PlayerObserver *adr)
{
	observer = adr;
}