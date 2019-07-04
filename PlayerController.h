#pragma once
//=============================================================================
//
// �v���C���[�R���g���[���[���� [PlayerController.cpp]
// Author : �n糗Ǒ�
//
//=============================================================================
#ifndef _PLAYERCONTROLLER_H_
#define _PLAYERCONTROLLER_H_

#include <vector>

#define JUDG_LEN (5)

#define PLAYER_CENTER		D3DXVECTOR3(0.0f ,-25.0f, 0.0f)

#define MOVESTACK_LENGTH (6)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPlayerController(void);
void UninitPlayerController(void);
void UpdatePlayerController(HWND hWnd);
void DrawPlayerController();
void GetPlayerMoveHistory(std::vector<int> *pOut);		//�ړ������擾����

#endif
