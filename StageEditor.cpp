//=====================================
//
//�X�e�[�W�G�f�B�^����[StageEditor.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "StageEditor.h"
#include "debugWindow.h"

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
�R���X�g���N�^
***************************************/
StageEditor::StageEditor()
{
	windowContainer.resize(5);
	for (auto& window : windowContainer)
	{
		window = new BaseEditWindow();
	}
}

/**************************************
�f�X�g���N�^
***************************************/
StageEditor::~StageEditor()
{
	for (auto& window : windowContainer)
	{
		SAFE_DELETE(window)
	}
	windowContainer.clear();
}

/**************************************
����������
***************************************/
void StageEditor::Init()
{

}

/**************************************
�I������
***************************************/
void StageEditor::Uninit()
{

}

/**************************************
�X�V����
***************************************/
void StageEditor::Update()
{

}

/**************************************
�`�揈��
***************************************/
void StageEditor::Draw()
{
	BeginDebugWindow("StageEditor");
	for (auto& window : windowContainer)
	{
		window->Draw();
		DebugNewLine();
	}
	EndDebugWindow("SageEditor");
}