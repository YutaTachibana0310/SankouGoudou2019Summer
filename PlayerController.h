#pragma once
//=============================================================================
//
// �v���C���[�R���g���[���[���� [PlayerController.cpp]
// Author : �n糗Ǒ�
//
//=============================================================================
#ifndef _PLAYERCONTROLLER_H_
#define _PLAYERCONTROLLER_H_

#define JUDG_LEN (5)
#define RESETTIME (120)
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPlayerController(void);
void UpdatePlayerController(HWND hWnd);
void SetPlayerTargetPosition(int *n);

void CheckCW();
void CheckCCW();
bool SetBomb();


#endif
