//=====================================
//
//TutorialBG.cpp
//機能:
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "TutorialBG.h"
#include "Framework\Polygon2D.h"

/**************************************
グローバル変数
***************************************/
const D3DXVECTOR3 TutorialBG::BoxSize = D3DXVECTOR3(5000.0f, 50000.0f, 5000.0f);
const D3DXVECTOR2 TutorialBG::BoxUV = D3DXVECTOR2(5.0f, 5.0f);

/**************************************
コンストラクタ
***************************************/
TutorialBG::TutorialBG() :
	SkyBox(BoxSize, BoxUV),
	polygon(new Polygon2D((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT))
{
	transform->Rotate(90.0f, 0.0f, 0.0f);

	//テクスチャロード
	const char* textureName = "data/TEXTURE/BG/TutorialBG.jpg";
	LoadTexture(textureName);

	//板ポリの色を黒に設定
	polygon->SetColor(D3DXCOLOR(0.00f, 0.00f, 0.00f, 1.0f));
}

/**************************************
更新処理
***************************************/
void TutorialBG::Update()
{
	VERTEX_BILLBOARD *pVtx = NULL;
	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//スクロール処理
	const float ScrollSpeed = -0.01f;
	for (int i = 0; i < Const::FieldNum * NUM_VERTEX; i++)
	{
		pVtx[i].tex.y += ScrollSpeed;
	}

	vtxBuff->Unlock();
}


/**************************************
描画処理
***************************************/
void TutorialBG::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
	polygon->Draw();
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);

	SkyBox::Draw();
}