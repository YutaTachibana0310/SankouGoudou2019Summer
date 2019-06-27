//=====================================
//
//�^�C�g���V�[������[TitleScene.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "TitleScene.h"
#include "debugWindow.h"
#include "Game.h"
#include "InputController.h"
#include "masktex.h"

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
void TitleScene::Init()
{


	InitMask();
}

/**************************************
�I������
***************************************/
void TitleScene::Uninit()
{
	UninitMask();
}

/**************************************
�X�V����
***************************************/
void TitleScene::Update(HWND hWnd)
{
	UpdateMask();
}

/**************************************
�`�揈��
***************************************/
void TitleScene::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	DrawMaskTEX();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
}