//=====================================
//
//TutorialScene.cpp
//�@�\:�`���[�g���A���V�[��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "TutorialScene.h"
#include "TutorialBG.h"

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
����������
***************************************/
void TutorialScene::Init()
{
	//�C���X�^���X�쐬
	bg = new TutorialBG();

	//�t�H�O��L����
	FLOAT StartPos = 10000;
	FLOAT EndPos = 50000;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->SetRenderState(D3DRS_FOGENABLE, true);
	pDevice->SetRenderState(D3DRS_FOGCOLOR, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	pDevice->SetRenderState(D3DRS_FOGVERTEXMODE, D3DFOG_NONE);
	pDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_LINEAR);
	pDevice->SetRenderState(D3DRS_FOGSTART, *(DWORD*)(&StartPos));
	pDevice->SetRenderState(D3DRS_FOGEND, *(DWORD*)(&EndPos));
}

/**************************************
�I������
***************************************/
void TutorialScene::Uninit()
{
	//�C���X�^���X�폜
	SAFE_DELETE(bg);

	//�t�H�O�𖳌���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->SetRenderState(D3DRS_FOGENABLE, false);
}

/**************************************
�X�V����
***************************************/
void TutorialScene::Update(HWND hWnd)
{
	bg->Update();
}

/**************************************
�`�揈��
***************************************/
void TutorialScene::Draw()
{
	bg->Draw();
}
