#pragma once
//=============================================================================
//
// �v���C���[�R���g���[���[���� [PlayerController.cpp]
// Author : �n糗Ǒ�
//
//=============================================================================
#ifndef _PLAYERCONTROLLER_H_
#define _PLAYERCONTROLLER_H_


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPlayerController(void);
void UpdatePlayerController(HWND hWnd);
void SetPlayerTargetPosition(int *n);
void push(void);
bool SetBomb();


#endif
