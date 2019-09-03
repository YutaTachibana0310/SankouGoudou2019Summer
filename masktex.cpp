//=============================================================================
//
// マスク処理 [masktex->cpp]
// Author : 渡邉良則
//
//=============================================================================
#include "main.h"
#include "masktex.h"
#include "UIdrawer.h"
#include "Stencil.h"
#include "Game.h"

static Clip::Stencil clip;

Mask::Mask(float size_x, float size_y, float size_z)
{
	masktex = new Object;

	masktex->LoadTexture("data/TEXTURE/UI/mask_star.png");
	masktex->MakeVertex();

	masktex->size = D3DXVECTOR3(size_x, size_y, size_z);
	masktex->position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
	masktex->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	masktex->SetColorObject(SET_COLOR_NOT_COLORED);

	active = false;
	sizechange = false;
	isFadeIn = false;
	wait = 0;
}

Mask::~Mask()
{
	delete masktex;
	masktex = NULL;
}

void Mask::Init(void)
{

}

void Mask::Uninit(void)
{

}


void Mask::Update(void) {

	if (active) {
		//isFadeInがtrueの場合にフェードイン
		if (isFadeIn) {
			FadeIn();
		}
		else {
			FadeOut();
		}
	}

}

//マスク用テクスチャ更新処理
void Mask::FadeOut(void) {

	if (sizechange) {
		masktex->size -= D3DXVECTOR3(10.0f, 10.0f, 0.0f);

	}
	//サイズ小さくなるにつれ画面が黒くなる
	if (masktex->size.x <= 0) {
		masktex->size = D3DXVECTOR3(0,0,0);
		SceneChangeFlag(true, nextscene);

		//サイズ0以下でシーン切り替え
		wait++;

		if (wait > 60) {

			ChangeScene(nextscene);
			isFadeIn = true;
			//active = false;
			wait = 0;

		}

	}

}

void Mask::FadeIn(void) {

	if (sizechange) {
		masktex->size += D3DXVECTOR3(10.0f, 10.0f, 0.0f);

	}

	//サイズが大きくなるにつれゲーム画面表示
	if (masktex->size.x >= MASK_SIZE) {

		SceneChangeFlag(false,nextscene);
		active = false;
	}
}

//マスク用テクスチャ描画
void Mask::DrawMaskTexSet(void) {

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//マスク部分
	clip.setWriteMaskColor(Clip::Stencil::MaskColor_Trans);
	clip.regionBegin(Clip::Stencil::MaskColor_Fill);

	masktex->Draw();
	masktex->SetVertex();

	clip.regionEnd();

	clip.setRefMaskColor(Clip::Stencil::MaskColor_Fill);
	clip.drawBegin();

}

void Mask::DrawMaskTexEnd(void) {

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	clip.drawEnd();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);

}

void Mask::SceneChangeFlag(bool fadeflag,Scene next) {

	if (fadeflag) {
		sizechange = true;
		nextscene = next;
		active = true;
		isFadeIn = false;
	}
	else {
		sizechange = false;
		active = false;
	}	
}
