//=====================================
//
//ステンシル処理[Stencil.h]
//Author:GP12B332 45　渡邉良則
//
//=====================================
#ifndef _STENCIL_H_
#define _STENCIL_H_

#include <d3d9.h>
/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
namespace Clip {
	class Stencil
	{
	public:

		//マスク色
		enum MaskColor {
			MaskColor_Trans = 0x00, //透明色
			MaskColor_Fill = 0x01, //塗りつぶし
			MaskColor_None = 0xff //無効カラー
		};

		//モード
		enum StencilMode {
			Mode_Masking, //マスク書き込みモード中
			Mode_Draw //描画モード中
		};

		Stencil(void);
		virtual ~Stencil();


		//クリッピング領域作成開始
		virtual bool regionBegin(MaskColor clearColor = MaskColor_Trans);

		//クリッピング領域作成終了
		virtual bool regionEnd();

		//クリッピング描画開始
		virtual bool drawBegin();

		//クリッピング描画終了
		virtual bool drawEnd(MaskColor clearColor = MaskColor_Trans);

		//書き込み時のマスクカラーの設定
		void setWriteMaskColor(MaskColor color);

		//描画時のマスクカラーの指定
		void setRefMaskColor(MaskColor color);

	protected:
		StencilMode			mode_;			//モード
		MaskColor			writeColor_;	//マスク書き込み時の色
		MaskColor			refColor_;		//描画時のマスキング色
		IDirect3DDevice9*	device_;		//描画時のマスキング色
		DWORD				curZTest_;		//既存のZテストの有無
		DWORD				curZFunc_;		//既存のZテスト比較関数

	};
}

#endif