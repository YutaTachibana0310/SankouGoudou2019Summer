//=====================================
//
//�X�p�C�N�m�C�Y�w�b�_[SpikeNoiise.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _SPIKENOISE_H_
#define _SPIKENOISE_H_

#include "../main.h"
#include "ScreenObject.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
class SpikeNoise :public ScreenObject
{
public:
	SpikeNoise();
	~SpikeNoise();
	void DrawEffect();
	void SetLength(float length);
	void SetBaseY(float f);

private:
	LPD3DXEFFECT effect;
	D3DXHANDLE hndlLength;
	D3DXHANDLE hBaseY;
};


#endif