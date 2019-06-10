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


//(�ȉ��A���[�͂ܒǋL)

#include "player.h"

//*****************************************************************************
// �}�N����` (���[�͂ܒǋL)  ��U�ǋL�����Ă��炢�܂����B����GM�ő��k���܂��傤
//*****************************************************************************
#define INITIAL_ARRAY_NUMBER (8) // ���������鐔���i�z��̗v�f�Ɗ֌W�Ȃ��l�ŏ������j

void GetMove_StackCCW(int trailHistoryCCW[MAX_LENGTH]);
void GetMove_StackCW(int trailHistoryCW[MAX_LENGTH]);

#endif
