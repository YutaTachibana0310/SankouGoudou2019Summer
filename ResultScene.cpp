//=====================================
//
//���U���g�V�[������[ResultScene.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "ResultScene.h"
#include "debugWindow.h"
#include "Game.h"
#include "ResultSceneUIManager.h"
#include "ResultPlayer.h"
#include "Framework\PlayerPrefs.h"
#include "sound.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
����������
***************************************/
void ResultScene::Init()
{
	bool gameresult = PlayerPrefs::GetBool("GameResult");
	player = new ResultPlayer(gameresult);

	InitResultSceneUI();

	if (gameresult) {
		Sound::GetInstance()->SetPlaySE(RESULTCLEAR, true, (Sound::GetInstance()->changevol / 10.0f));
	}
	else {
		Sound::GetInstance()->SetPlaySE(RESULTFAILED, true, (Sound::GetInstance()->changevol / 10.0f));
	}

}

/**************************************
�I������
***************************************/
void ResultScene::Uninit()
{
	UninitResultSceneUI();

	SAFE_DELETE(player);
}

/**************************************
�X�V����
***************************************/
void ResultScene::Update(HWND hWnd)
{
	player->Update();
	UpdateResultSceneUI(hWnd);
}

/**************************************
�`�揈��
***************************************/
void ResultScene::Draw()
{
	DrawResultSceneBG();
	player->Draw();
	DrawResultSceneUI();
}