//=====================================
//
//テンプレート処理[Template.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "WarningUI.h"
#include "WarningBelt.h"
#include "WarningText.h"

/**************************************
マクロ定義
***************************************/

/**************************************
WarningUIコンストラクタ
***************************************/
WarningUI::WarningUI() :
	active(false),
	TextSetInterval(5),
	Duration(300)
{
	upperBelt = new WarningBelt(1.0f);
	upperBelt->transform.pos = D3DXVECTOR3(SCREEN_CENTER_X, 0.0f, 0.0f);

	lowerBelt = new WarningBelt(-1.0f);
	lowerBelt->transform.pos = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_HEIGHT, 0.0f);

	const WarningText::Index index[] = {
		WarningText::Index::W,
		WarningText::Index::A,
		WarningText::Index::R,
		WarningText::Index::N,
		WarningText::Index::I,
		WarningText::Index::N,
		WarningText::Index::G,
		WarningText::Index::EXCLAMATION,
		WarningText::Index::EXCLAMATION };

	textContainer.resize(sizeof(index) / sizeof(WarningText::Index));
	for (UINT i = 0; i < textContainer.size(); i++)
	{
		textContainer[i] = new WarningText(index[i]);

		const float Offset = 150.0f;
		const float InitX = SCREEN_CENTER_X - Offset * (textContainer.size() - 1) / 2;
		textContainer[i]->transform.pos = D3DXVECTOR3(InitX + Offset * i, SCREEN_CENTER_Y, 0.0f);
	}
}

/**************************************
WarningUIデストラクタ
***************************************/
WarningUI::~WarningUI()
{
	SAFE_DELETE(upperBelt);
	SAFE_DELETE(lowerBelt);

	for (auto&& text : textContainer)
	{
		SAFE_DELETE(text);
	}
	textContainer.clear();
}

/**************************************
WarningUI更新処理
***************************************/
void WarningUI::Update()
{
	if (!active)
		return;


	CheckFinish();
	SetTextIn();

	upperBelt->Update();
	lowerBelt->Update();

	for (auto&& text : textContainer)
	{
		text->Update();
	}

	cntFrame++;
}

/**************************************
WarningUI描画処理
***************************************/
void WarningUI::Draw()
{
	if (!active)
		return;

	upperBelt->Draw();
	lowerBelt->Draw();

	for (auto&& text : textContainer)
	{
		text->Draw();
	}
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

	itrText = textContainer.begin();
}

/**************************************
終了確認
***************************************/
void WarningUI::CheckFinish()
{
	if (cntFrame == Duration - 30)
	{
		upperBelt->SetFade(false);
		lowerBelt->SetFade(false);
	}
	if (cntFrame == Duration)
	{
		active = false;
	}
}

/**************************************
テキストイン
***************************************/
void WarningUI::SetTextIn()
{
	if (cntFrame >= (int)textContainer.size() * TextSetInterval)
		return;

	if (cntFrame % TextSetInterval != 0)
		return;

	(*itrText)->StartAnimation(true);
	itrText++;

	if (itrText == textContainer.end())
		itrText = textContainer.begin();
}
