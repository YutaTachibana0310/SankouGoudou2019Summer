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
#define RESETTIME (120)

#define PLAYER_CENTER		D3DXVECTOR3(0.0f ,-25.0f, 0.0f)
#define PLAYER_TOP			D3DXVECTOR3(0.0f, 25.0f, 150.0f)
#define PLAYER_MIDDLE_LEFT	D3DXVECTOR3(-50.0f, -10.0f, 150.0f)
#define PLAYER_LOWER_LEFT	D3DXVECTOR3(-30.0f, -50.0f, 150.0f)
#define PLAYER_LOWER_RIGHT	D3DXVECTOR3(30.0f, -50.0f, 150.0f)
#define PLAYER_MIDDLE_RIGHT	D3DXVECTOR3(50.0f, -10.0f, 150.0f)

#define PLAYER_MOVE_TIME	(20)
#define PLAYER_RETURN_TIME	(60)

#define MOVESTACK_LENGTH (6)

//�v���C���[�̏�ԗ񋓎q
enum class PlayerState 
{
	Move,
	Wait,
	Return,
};

//�O���錾
class Player;
enum class TrailIndex;
class PlayerBullet;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPlayerController(void);
void UninitPlayerController(void);
void UpdatePlayerController(HWND hWnd);
void DrawPlayerController();
void DrawPlayerBullet();

void CheckCW();
void CheckCCW();
bool SetBomb();

std::vector<PlayerBullet*>* GetPlayerBulletContainer(void);
void ChangeState(Player *player, PlayerState next);
void FirePlayerBullet(TrailIndex start, TrailIndex end);
void FirePlayerBullet(D3DXVECTOR3 *rightPos, D3DXVECTOR3 *leftPos);

//(�ȉ��A���[�͂ܒǋL)
//*****************************************************************************
// �}�N����` (���[�͂ܒǋL)  ��U�ǋL�����Ă��炢�܂����B����GM�ő��k���܂��傤
//*****************************************************************************
#define INITIAL_ARRAY_NUMBER (8) // ���������鐔���i�z��̗v�f�Ɗ֌W�Ȃ��l�ŏ������j

void GetMove_StackCCW(int trailHistoryCCW[MOVESTACK_LENGTH]);
void GetMove_StackCW(int trailHistoryCW[MOVESTACK_LENGTH]);

#endif
