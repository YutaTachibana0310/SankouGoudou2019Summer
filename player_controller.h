#pragma once
//=============================================================================
//
// �v���C���[�R���g���[���[���� [player_controller.cpp]
// Author : �n糗Ǒ�
//
//=============================================================================
#ifndef _PLAYER_CONTROLLER_H_
#define _PLAYER_CONTROLLER_H_


typedef struct
{

	//����z��̓��e�ƍ����Ă��邩�̔���
	bool matching;
	bool matching2;

	//��M�����ł������p�̃e�X�g�t���O
	bool flag;
	int flag_count;

						
	

}PLAYER_CONTROLLER;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPlayerController(void);
void UpdatePlayerController(HWND hWnd);
void SetPlayerTargetPosition(int *n);
void push(void);

PLAYER_CONTROLLER* GetPlayerController();


#endif
