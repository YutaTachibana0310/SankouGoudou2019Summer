//=====================================
//
//テンプレート処理[Template.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "WarningUI.h"
#include "WarningBelt.h"

/**************************************
マクロ定義
***************************************/

/**************************************
WarningUIコンストラクタ
***************************************/
WarningUI::WarningUI() :
	active(false)
{
	upperBelt = new WarningBelt(1.0f);
	upperBelt->transform.pos = D3DXVECTOR3(SCREEN_CENTER_X, 0.0f, 0.0f);

	lowerBelt = new WarningBelt(-1.0f);
	lowerBelt->transform.pos = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_HEIGHT, 0.0f);
}

/**************************************
WarningUIデストラクタ
***************************************/
WarningUI::~WarningUI()
{
	SAFE_DELETE(upperBelt);
	SAFE_DELETE(lowerBelt);
}

/**************************************
WarningUI更新処理
***************************************/
void WarningUI::Update()
{
	if (!active)
		return;

	upperBelt->Update();
	lowerBelt->Update();
}

/**************************************
WarningUI描画処理
***************************************/
void WarningUI::Draw()
{
	if (!active)
		return;

	cntFrame++;
	const float Duration = 300;
	if (cntFrame == Duration - 30)
	{
		upperBelt->SetFade(false);
		lowerBelt->SetFade(false);
	}
	if (cntFrame == Duration)
	{
		active = false;
	}

	upperBelt->Draw();
	lowerBelt->Draw();
}

/**************************************
WarningUIフェード処理
***************************************/
void WarningUI::StartFade(bool isFadein)
{
	upperBelt->SetFade(isFadein);
	lowerBelt->SetFade(isFadein);

	cntFrame = 0;

	if (isFadein)
		active = true;
}
