//=====================================
//
//�e���v���[�g����[Template.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "WarningUI.h"
#include "WarningBelt.h"

/**************************************
�}�N����`
***************************************/

/**************************************
WarningUI�R���X�g���N�^
***************************************/
WarningUI::WarningUI() :
	active(false)
{
	upperBelt = new WarningBelt(1.0f);
	upperBelt->transform.pos = D3DXVECTOR3(SCREEN_CENTER_X, 0.0f, 0.0f);

	lowerBelt = new WarningBelt(-1.0f);
	lowerBelt->transform.pos = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_HEIGHT, 0.0f);
}

/**************************************
WarningUI�f�X�g���N�^
***************************************/
WarningUI::~WarningUI()
{
	SAFE_DELETE(upperBelt);
	SAFE_DELETE(lowerBelt);
}

/**************************************
WarningUI�X�V����
***************************************/
void WarningUI::Update()
{
	if (!active)
		return;

	upperBelt->Update();
	lowerBelt->Update();
}

/**************************************
WarningUI�`�揈��
***************************************/
void WarningUI::Draw()
{
	if (!active)
		return;

	cntFrame++;
	const float Duration = 300;
	if (cntFrame == Duration - 30)
	{
		upperBelt->SetFade(false);
		lowerBelt->SetFade(false);
	}
	if (cntFrame == Duration)
	{
		active = false;
	}

	upperBelt->Draw();
	lowerBelt->Draw();
}

/**************************************
WarningUI�t�F�[�h����
***************************************/
void WarningUI::StartFade(bool isFadein)
{
	upperBelt->SetFade(isFadein);
	lowerBelt->SetFade(isFadein);

	cntFrame = 0;

	if (isFadein)
		active = true;
}
