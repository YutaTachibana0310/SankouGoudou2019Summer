//=====================================
//
//GameOver.cpp
//�@�\:�Q�[���I�[�o�[�\��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "GameOver.h"

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
GameOver::GameOver() :
	cntFrame(0)
{
	LoadTexture("data/TEXTURE/UI/gameOver.png");
	transform.pos = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f);
	SetSize(550.0f, 100.0f);
	SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
}

/**************************************
�X�V����
***************************************/
void GameOver::Update()
{
	cntFrame++;
	float t = 1.0f * cntFrame / Duration;

	SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, t));
}

/**************************************
�O���[�o���ϐ�
***************************************/
void GameOver::Draw()
{
	Polygon2D::Draw();
}