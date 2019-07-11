//=============================================================================
//
// ステンシル処理 [Stencil.cpp]
// Author : 渡邉良則
//
//=============================================================================

#include "Stencil.h"
#include "main.h"

namespace Clip {
	Stencil::Stencil(void):
		device_		(0),
		mode_		(Mode_Masking),
		writeColor_	(MaskColor_Fill),
		refColor_	(MaskColor_Fill),
		curZTest_	(0),
		curZFunc_	(0)
	{

	}

	Stencil::~Stencil() {

	}



	//クリッピング領域作成開始
	bool Stencil::regionBegin(MaskColor initColor) {

		LPDIRECT3DDEVICE9 pDevice = GetDevice();
		device_ = pDevice;

		if (device_ == 0) {
			return false;
		}

		//ステンシルバッファのみ初期値クリア
		pDevice->Clear(0, NULL, D3DCLEAR_STENCIL, 0, 1.0f, static_cast<DWORD>(initColor));

		//既存のZテストパラメータの保存
		pDevice->GetRenderState(D3DRS_ZENABLE, &curZTest_);
		pDevice->GetRenderState(D3DRS_ZFUNC, &curZFunc_);

		//ステンシルバッファの有効化
		pDevice->SetRenderState(D3DRS_ZENABLE, true);
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_NEVER);

		pDevice->SetRenderState(D3DRS_STENCILENABLE, true);
		pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
		pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);
		pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_REPLACE);
		pDevice->SetRenderState(D3DRS_STENCILREF, writeColor_);
		pDevice->SetRenderState(D3DRS_STENCILMASK,0xff);

		mode_ = Mode_Masking;

		return true;
	}

	//クリッピング領域作成終了
	bool Stencil::regionEnd() {
		if (device_ == 0) {
			return false;
		}

		//ステンシルを無効化
		//Zテストを戻す
		device_->SetRenderState(D3DRS_STENCILENABLE, false);
		device_->SetRenderState(D3DRS_ZENABLE,curZTest_);
		device_->SetRenderState(D3DRS_ZFUNC,curZFunc_);

		return true;
	}

	//クリッピング描画開始
	bool Stencil::drawBegin() {
		if (device_ == 0) {
			return false;
		}

		//既に書き込まれているステンシル値に対し
		//マスク色でない部分だけテスト合格する
		device_->SetRenderState(D3DRS_STENCILENABLE,true);
		device_->SetRenderState(D3DRS_STENCILFUNC,D3DCMP_NOTEQUAL);
		device_->SetRenderState(D3DRS_STENCILPASS,D3DSTENCILOP_KEEP);
		device_->SetRenderState(D3DRS_STENCILZFAIL,D3DSTENCILOP_KEEP);
		device_->SetRenderState(D3DRS_STENCILREF,refColor_);
		device_->SetRenderState(D3DRS_STENCILMASK,0xff);

		mode_ = Mode_Draw;

		return true;

	}

	//クリッピング描画終了
	bool Stencil::drawEnd(MaskColor clearColor) {
		if (device_ == 0) {
			return false;
		}

		//ステンシルを無効化しバッファをクリア
		device_->SetRenderState(D3DRS_STENCILENABLE, false);
		device_->Clear(0, NULL, D3DCLEAR_STENCIL, 0, 1.0f, static_cast<DWORD>(clearColor));

		return true;
	}

	//書き込み時マスクカラーの設定
	void Stencil::setWriteMaskColor(MaskColor color) {
		writeColor_ = color;
		if (device_ && mode_ == Mode_Masking) {
			device_->SetRenderState(D3DRS_STENCILREF, writeColor_);
		}
	}


	//描画時のマスクカラーの指定
	void Stencil::setRefMaskColor(MaskColor color) {
		refColor_ = color;
		if (device_ && mode_ == Mode_Draw) {
			device_->SetRenderState(D3DRS_STENCILREF, refColor_);
		}
	}

}

