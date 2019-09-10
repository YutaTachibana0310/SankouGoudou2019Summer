//=====================================
//
//リザルトプレイヤー処理[ResultPlayer.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "ResultPlayer.h"
#include "Framework\AnimContainer.h"

/**************************************
グローバル変数
***************************************/

/**************************************
コンストラクタ
***************************************/
ResultPlayer::ResultPlayer(bool isClear)
{
	//アニメーション初期化
	animation = new AnimContainer();
	animation->LoadXFile("data/MODEL/ResultPlayer.x", "ResultPlayer");
	animation->SetupCallbackKeyFrames("ResultClear");
	animation->SetupCallbackKeyFrames("ResultFailed");
	animation->LoadAnimation("ResultClear", AnimID::Clear);
	animation->LoadAnimation("ResultFailed", AnimID::Failed);
	animation->SetShiftTime(AnimID::Clear, 0.2f);
	animation->SetShiftTime(AnimID::Failed, 0.2f);

	//トランスフォーム作成
	transform = new Transform();
	transform->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//アニメーション遷移
	AnimID state = isClear ? AnimID::Clear : AnimID::Failed;
	animation->ChangeAnim(state, 1.0f, true);
}

/**************************************
デストラクタ
***************************************/
ResultPlayer::~ResultPlayer()
{
	SAFE_DELETE(animation);
	SAFE_DELETE(transform);
}

/**************************************
更新処理
***************************************/
void ResultPlayer::Update()
{
	animation->Update(1.0f / 60);
}

/**************************************
描画処理
***************************************/
void ResultPlayer::Draw()
{
	transform->SetWorld();
	
	D3DXMATRIX mtxWorld = transform->GetMatrix();
	animation->Draw(&mtxWorld);
}
