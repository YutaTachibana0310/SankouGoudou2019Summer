//=====================================
//
//�X�s�[�h�u���[�t�B���^�[�w�b�_[SpeedBlurFilter.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _SPEEDBLURFILTER_H_
#define _SPEEDBLURFILTER_H_

#include "../main.h"
#include "ScreenObject.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
class SpeedBlur : public ScreenObject
{
public:
	SpeedBlur();
	~SpeedBlur();
	void DrawEffect();
	void SetPower(float power);
	void SetCenterPos(D3DXVECTOR3 pos);
	void SetSurfaceSize(float width, float height);
	void SetStartLength(float length);

private:
	LPD3DXEFFECT effect;
	D3DXHANDLE hPower, hCenter;
	D3DXHANDLE hTU, hTV;
	D3DXHANDLE hStartLength;
};

#endif