//=============================================================================
//
// ゲージ画面処理 [guage.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _GUAGE_H_
#define _GUAGE_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	ADRESS_TEXTURE_GUAGEBAR		("data/TEXTURE/UI/guage/guageBar_vertical.png")		
#define	ADRESS_TEXTURE_GUAGEFLAME	("data/TEXTURE/UI/guage/guageFrame_vertical.png")		
#define	ADRESS_TEXTURE_GUAGETEXT	("data/TEXTURE/UI/guage/guageText_fever_vertical.png")		

enum GUARGE_PARTS
{
	GUAGEBAR_DAMAGE,  // ダメージ表現ゲージバー
	GUAGEBAR_TRUE,	  // 実際のゲージバー
	GUAGEFLAME,
	GUAGETEXT,
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitGuageParts	(void);
void	UninitGuageParts(void);
void	UpdateGuageParts(void);
void	DrawGuageParts	(void);
void	ChangeGuage		(float value);

#endif

