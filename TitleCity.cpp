//=====================================
//
//�e���v���[�g����[TitleCity.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "TitleCity.h"

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
Title::CityBG::CityBG()
{
	const char* TextureName = "data/TEXTURE/UI/logobg.png";
	LoadTexture(TextureName);

	SetSize(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f);
	
	transform.pos = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f);
}

/**************************************
�X�V����
***************************************/
void Title::CityBG::Update()
{
	const float ScrollSpeed = 0.02f;
	//offsetU = WrapAroundf(0.0f, 1.0f, offsetU + ScrollSpeed);

	vtxWk[0].tex.x = offsetU;
	vtxWk[1].tex.x = offsetU + 1.0f;
	vtxWk[2].tex.x = offsetU;
	vtxWk[3].tex.x = offsetU + 1.0f;
}
