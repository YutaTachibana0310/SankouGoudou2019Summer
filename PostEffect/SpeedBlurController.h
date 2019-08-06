//=====================================
//
//スピードブラーコントローラヘッダ[SpeedBlurController.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _SPEEDBLURCONROLLER_H_
#define _SPEEDBLURCONROLLER_H_

#include "../main.h"
#include "../Framework/BaseSingleton.h"

/**************************************
マクロ定義
***************************************/

/**************************************
前方宣言
***************************************/
class SpeedBlur;

/**************************************
クラス定義
***************************************/
class SpeedBlurController : public BaseSingleton<SpeedBlurController>
{
public:
	friend class BaseSingleton<SpeedBlurController>;

	void Update();
	void Draw();
	void SetPower(float power);

private:
	SpeedBlurController();
	~SpeedBlurController();

	SpeedBlur *speedBlur;
	LPDIRECT3DTEXTURE9 texture;
	LPDIRECT3DSURFACE9 surface;

	float startPower, endPower;
	int cntPower;
};

#endif