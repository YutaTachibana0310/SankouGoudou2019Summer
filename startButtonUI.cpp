//=============================================================================
//
// �X�^�[�g�{�^����ʏ��� [startButtonPartsUI.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "startButtonUI.h"
#include "UIdrawer.h"
#include "TitleSceneUIManager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define STARTBUTTON_PARTS_MAX		(2)
#define SIZE_STARTBUTTON			(D3DXVECTOR3(SCREEN_WIDTH/10,SCREEN_HEIGHT/10,0.0f))
#define COLLIDER_SIZE_STARTBUTTON	(D3DXVECTOR3(320.0f,100.0f,0.0f))
#define POSITION_STARTBUTTON		(D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT/10*8,0.0f))
#define VOLUME_ZOOM					(30.0f)
#define INCREASE_VOLUME_ALPHA		(0.02f)

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
StartButton::StartButton()
{
	bg = new Object();
	text = new Object();

	bg->LoadTexture("data/TEXTURE/UI/StartButton/startButtonBG.png");
	text->LoadTexture("data/TEXTURE/UI/StartButton/startButtonText.png");

	bg->MakeVertex();
	text->MakeVertex();

	bg->position = POSITION_STARTBUTTON;
	bg->size = SIZE_STARTBUTTON;
	bg->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	bg->colliderSize = COLLIDER_SIZE_STARTBUTTON;

	text->position = POSITION_STARTBUTTON;
	text->size = SIZE_STARTBUTTON;
	text->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	text->colliderSize = COLLIDER_SIZE_STARTBUTTON;

	bg->SetColorObject(SET_COLOR_NOT_COLORED);
	text->SetColorObject(SET_COLOR_NOT_COLORED);
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
StartButton::~StartButton()
{
	delete bg;
	bg = NULL;

	delete text;
	text = NULL;
}

//=============================================================================
// �X�V����
//=============================================================================
void StartButton::Update(HWND hWnd)
{
	if (bg->IsMouseOvered(hWnd,bg->position, 
		bg->colliderSize))
	{
		// �{�^������������Q�[���V�[����
		if (IsMouseLeftTriggered())
		{
			GoGameScene();
		}

		for (int i = 0; i < STARTBUTTON_PARTS_MAX; i++)
		{
			// �I������Ă���Ȃ�g��\��
			bg->size.x = SIZE_STARTBUTTON.x + VOLUME_ZOOM;
			bg->size.y = SIZE_STARTBUTTON.y + VOLUME_ZOOM;

			text->size.x = SIZE_STARTBUTTON.x + VOLUME_ZOOM;
			text->size.y = SIZE_STARTBUTTON.y + VOLUME_ZOOM;
		}
	}
	else
	{	
		for (int i = 0; i < STARTBUTTON_PARTS_MAX; i++)
		{
			// ���ɖ߂�
			bg->size.x = SIZE_STARTBUTTON.x;
			bg->size.y = SIZE_STARTBUTTON.y;

			text->size.x = SIZE_STARTBUTTON.x;
			text->size.y = SIZE_STARTBUTTON.y;
		}
	}

	BlinkStartButtonText();
}

//=============================================================================
// �`�揈��
//=============================================================================
void StartButton::Draw(void)
{
	bg->Draw();
	bg->SetVertex();

	text->Draw();
	text->SetVertex();
}

//=============================================================================
// �X�^�[�g�{�^���e�L�X�g�_�ŏ���
//=============================================================================
void StartButton::BlinkStartButtonText(void)
{
	if (alpha >= 1.0f)
	{
		IsAlphaIncreased = false;
	}
	if (alpha <= 0.0f)
	{
		IsAlphaIncreased = true;
	}

	if (IsAlphaIncreased)
	{
		alpha += INCREASE_VOLUME_ALPHA;
	}
	else
	{
		alpha -= INCREASE_VOLUME_ALPHA;
	}

	text->SetColorObject(D3DXCOLOR(1.0f,1.0f,1.0f,alpha));
}


//=============================================================================
// �Q�[���V�[���ڍs����
//=============================================================================
void StartButton::GoGameScene(void)
{
	SceneChangeFlag(true, SceneGame);
}
