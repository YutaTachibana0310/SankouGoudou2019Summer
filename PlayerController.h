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

#define PLAYER_CENTER		D3DXVECTOR3(0.0f ,-25.0f, 150.0f)
#define PLAYER_TOP			D3DXVECTOR3(0.0f, 25.0f, 150.0f)
#define PLAYER_MIDDLE_LEFT	D3DXVECTOR3(-50.0f, -10.0f, 150.0f)
#define PLAYER_LOWER_LEFT	D3DXVECTOR3(-30.0f, -50.0f, 150.0f)
#define PLAYER_LOWER_RIGHT	D3DXVECTOR3(30.0f, -50.0f, 150.0f)
#define PLAYER_MIDDLE_RIGHT	D3DXVECTOR3(50.0f, -10.0f, 150.0f)

#define PLAYER_MOVE_TIME	(20)
#define PLAYER_RETURN_TIME	(60)


enum class PlayerState 
{
	Move,
	Wait,
	Return,
};

class Player;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPlayerController(void);
void UninitPlayerController(void);
void UpdatePlayerController(HWND hWnd);
void DrawPlayerController();
void SetPlayerTargetPosition(int *n);

void CheckCW();
void CheckCCW();
bool SetBomb();

void ChangeState(Player *player, PlayerState next);


#endif
