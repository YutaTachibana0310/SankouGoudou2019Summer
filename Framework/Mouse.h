//=====================================
//
//�e���v���[�g�w�b�_[Template.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _TEMPLATE_H_
#define _TEMPLATE_H_

#include "../main.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/

/**************************************
�v���g�^�C�v�錾
***************************************/
HRESULT InitializeMouse(HINSTANCE hInst, HWND hWindow, LPDIRECTINPUT8 inputInterface); // �}�E�X�̏�����
void UninitMouse();						// �}�E�X�̏I������
HRESULT UpdateMouse();					// �}�E�X�̍X�V����

//---------------------------- mouse
BOOL IsMouseLeftPressed(void);      // ���N���b�N�������
BOOL IsMouseLeftTriggered(void);    // ���N���b�N�����u��
BOOL IsMouseRightPressed(void);     // �E�N���b�N�������
BOOL IsMouseRightTriggered(void);   // �E�N���b�N�����u��
BOOL IsMouseCenterPressed(void);    // ���N���b�N�������
BOOL IsMouseCenterTriggered(void);  // ���N���b�N�����u��
float GetMouseX(void);               // �}�E�X��X�����ɓ��������Βl
float GetMouseY(void);               // �}�E�X��Y�����ɓ��������Βl
float GetMouseZ(void);               // �}�E�X�z�C�[�������������Βl

D3DXVECTOR3 GetMousePosition(HWND hWnd);

#endif