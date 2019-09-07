//=====================================
//
//タイトルロゴ処理[Logo.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "TitleLogo.h"
#include "Framework\Easing.h"

/**************************************
グローバル変数
***************************************/
const D3DXVECTOR2 Title::LogoParts::Size[] =
{
	D3DXVECTOR2(190.0f, 100.0f) * 1.5f,
	D3DXVECTOR2(190.0f, 100.0f) * 1.5f,
	D3DXVECTOR2(180.0f, 98.0f) * 1.5f
};

/**************************************
Logoコンストラクタ
***************************************/
Title::Logo::Logo() :
	cntFrame(0)
{
	//ロゴインスタンス作成
	logoContainer.reserve(LogoParts::ID::Max);
	logoContainer.push_back(new LogoParts(LogoParts::ID::City));
	logoContainer.push_back(new LogoParts(LogoParts::ID::Star));
	logoContainer.push_back(new LogoParts(LogoParts::ID::Liner));

	//座標決定
	const float InitOffsetX = 1000.0f;
	const float InitPositionY = 400.0f;
	const D3DXVECTOR3 LogoPosition[] =
	{
		D3DXVECTOR3(
			SCREEN_CENTER_X - (LogoParts::Size[1].x + LogoParts::Size[0].x) / 1.1f - InitOffsetX,
			InitPositionY,
			0.0f),
		D3DXVECTOR3(
			SCREEN_CENTER_X,
			InitPositionY,
			0.0f),
		D3DXVECTOR3(SCREEN_CENTER_X + (LogoParts::Size[1].x + LogoParts::Size[2].x) / 1.1f + InitOffsetX,
			InitPositionY,
			0.0f)
	};
	logoContainer[LogoParts::ID::City]->transform.pos = LogoPosition[LogoParts::ID::City];
	logoContainer[LogoParts::ID::Star]->transform.pos = LogoPosition[LogoParts::ID::Star];
	logoContainer[LogoParts::ID::Liner]->transform.pos = LogoPosition[LogoParts::ID::Liner];

	//移動開始
	logoContainer[LogoParts::ID::City]->Move(D3DXVECTOR3(InitOffsetX, 0.0f, 0.0f), MoveDuration);
	logoContainer[LogoParts::ID::Liner]->Move(D3DXVECTOR3(-InitOffsetX, 0.0f, 0.0f), MoveDuration);

	//BG作成
	bg = new Polygon2D();
	bg->LoadTexture("data/TEXTURE/UI/citybg.png");
	bg->transform.pos = D3DXVECTOR3(SCREEN_CENTER_X, InitPositionY, 0.0f);
	bg->SetSize(SCREEN_WIDTH / 2.0f, 200.0f);
}

/**************************************
デストラクタ
***************************************/
Title::Logo::~Logo()
{
	for (auto&& parts : logoContainer)
	{
		SAFE_DELETE(parts);
	}
	logoContainer.clear();

	SAFE_DELETE(bg);
}

/**************************************
更新処理
***************************************/
void Title::Logo::Update()
{
	cntFrame++;

	if (cntFrame == MoveDuration)
	{
		const D3DXVECTOR3 MoveOffset = D3DXVECTOR3(0.0f, 50.0f, 0.0f);
		logoContainer[LogoParts::ID::City]->Move(-MoveOffset, MoveDuration);
		logoContainer[LogoParts::ID::Liner]->Move(MoveOffset, MoveDuration);
	}

	for (auto&& parts : logoContainer)
	{
		parts->Update();
	}
}

/**************************************
描画処理
***************************************/
void Title::Logo::Draw()
{
	bg->Draw();

	for (auto&& parts : logoContainer)
	{
		parts->Draw();
	}
}

/**************************************
LogoPartsコンストラクタ
***************************************/
Title::LogoParts::LogoParts(ID id) :
	cntFrame(0),
	moveDuration(0),
	moveTarget(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	startPos(D3DXVECTOR3(0.0f ,0.0f, 0.0f))
{
	const char* TextureName[] = {
		"data/TEXTURE/UI/city.png",
		"data/TEXTURE/UI/star.png",
		"data/TEXTURE/UI/liner.png"
	};
	LoadTexture(TextureName[id]);


	SetSize(Size[id].x, Size[id].y);
}

/**************************************
LogoParts更新処理
***************************************/
void Title::LogoParts::Update()
{
	if (cntFrame >= moveDuration)
		return;

	cntFrame++;
	float t = 1.0f * cntFrame / moveDuration;
	D3DXVECTOR3 position = Easing::EaseValue(t, startPos, moveTarget, EaseType::OutCubic);
	transform.pos = position;
}

/**************************************
LogoParts移動処理
***************************************/
void Title::LogoParts::Move(D3DXVECTOR3 offset, int duration)
{
	moveTarget = transform.pos + offset;
	startPos = transform.pos;
	moveDuration = duration;
	cntFrame = 0;

}
