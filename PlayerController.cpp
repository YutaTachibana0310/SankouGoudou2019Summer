//=============================================================================
//
// �v���C���[�R���g���[���[���� [PlayerController.cpp]
// Author : �n糗Ǒ�
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "star.h"
#include "PlayerController.h"
#include "InputController.h"
#include "debugWindow.h"
#include "IStateMachine.h"
#include <map>
#include "PlayerMove.h"
#include "PlayerReturn.h"
#include "PlayerWait.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void push(void);

using namespace std;

static map<PlayerState, IStateMachine<Player>*> fsm;

Player player;

D3DXVECTOR3 MovePos[MAX_LENGTH];

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//��莞�ԓ��͂��Ȃ��ꍇ�ɏ����|�W�V�����ɖ߂�ׂ̃^�C�}�[
int resetcount;

//����p�̔z��
int judgment[JUDG_LEN] = { TOP,LOWER_LEFT,MIDDLE_RIGHT,MIDDLE_LEFT,LOWER_RIGHT };

//����p�z��̌��݈ʒu
int judg_currentCCW;
int judg_currentCW;

//���݂̈ʒu
int currentCCW;
int currentCW;

//�ړ���̔ԍ��ۊǔz��
int move_stackCCW[MAX_LENGTH];
int move_stackCW[MAX_LENGTH];

// ���ԂɈړ����邩��ۊ�
int	movenum;

//����z��̓��e�ƍ����Ă��邩�̔���
bool matchingCCW;
bool matchingCW;

//�{�������e�X�g�p�t���O
bool flag;
int flagtimer;
//*****************************************************************************
// ����������
//*****************************************************************************
HRESULT InitPlayerController(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	fsm[PlayerState::Move] = new PlayerMove();
	fsm[PlayerState::Wait] = new PlayerWait();
	fsm[PlayerState::Return] = new PlayerReturn();

	player.Init();
	for (int i = 0; i < MAX_LENGTH; i++) {
		move_stackCCW[i] = 0;
		move_stackCW[i] = 0;
	}

	MovePos[CENTER] = PLAYER_CENTER;
	MovePos[TOP] = PLAYER_TOP;
	MovePos[MIDDLE_LEFT] = PLAYER_MIDDLE_LEFT;
	MovePos[LOWER_LEFT] = PLAYER_LOWER_LEFT;
	MovePos[LOWER_RIGHT] = PLAYER_LOWER_RIGHT;
	MovePos[MIDDLE_RIGHT] = PLAYER_MIDDLE_RIGHT;

	currentCCW = 0;
	currentCW = 0;

	judg_currentCCW = 0;
	judg_currentCW = 0;
	matchingCCW = false;
	matchingCW = false;

	movenum = CENTER;

	resetcount = 0;

	flag = false;
	flagtimer = 0;

	player.CurrentState = PlayerState::Wait;
	return S_OK;
}
//*****************************************************************************
// �I������
//*****************************************************************************
void UninitPlayerController()
{
	fsm.clear();
	player.Uninit();
}
//*****************************************************************************
// �X�V����
//*****************************************************************************
void UpdatePlayerController(HWND hWnd)
{

	resetcount++;


	//�{�������p�̃t���O�A�J�E���^
	if (flag == true) {
		flagtimer++;
		if (flagtimer > RESETTIME) {
			flag = false;
			flagtimer = 0;
		}
	}
	if (player.CurrentState == PlayerState::Wait)
	{
		for (int i = 0; i < STAR_MAX; i++) {
			if (IsEntered(i, hWnd)) {
				movenum = i;
				push();
				player.goalpos = MovePos[i];
				ChangeState(&player, PlayerState::Move);

				CheckCW();
				CheckCCW();
				resetcount = 0;

			}
		}
	}
	//��莞�Ԍ�ɒ����֖߂鏈��
	if (resetcount >= RESETTIME) {
		movenum = 5;
		push();
		CheckCW();
		CheckCCW();
		resetcount = 0;
	}
	DebugText("move_stackCCW:%d,%d,%d,%d,%d,%d\n", move_stackCCW[0], move_stackCCW[1], move_stackCCW[2], move_stackCCW[3], move_stackCCW[4], move_stackCCW[5]);
	DebugText("move_stackCW:%d,%d,%d,%d,%d,%d\n", move_stackCW[0], move_stackCW[1], move_stackCW[2], move_stackCW[3], move_stackCW[4], move_stackCW[5]);
	
	
	player.Update();
	fsm[player.CurrentState]->OnUpdate(&player);

}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void DrawPlayerController()
{
	player.Draw();

}




//*****************************************************************************
// ���ؗp
//*****************************************************************************

void SetPlayerTargetPosition(int *n) {

	*n = movenum;

}

void push() {

	//�ړ��ۊǔz��ɓ��͂��ꂽ�L�[�̔ԍ���ۊ�
	if (currentCCW < MAX_LENGTH) {
		move_stackCCW[currentCCW] = movenum;
		move_stackCW[currentCW] = movenum;

	}

}

//�E���p
void CheckCW() {

	//����ɔ���p�z��̉��Ԗڂɓ����������i�[����Ă��邩�m�F

	if (matchingCW == false) {
		for (judg_currentCW = 0; judg_currentCW < JUDG_LEN; judg_currentCW++) {

			//��v�����ꍇ
			if (move_stackCW[currentCW] == judgment[judg_currentCW]) {

				matchingCW = true;

			}
			if (matchingCW == true) {
				//�ړ��ۊǔz��Ɣ���p�z�񂪈�v�����ꍇ������ijudgment_current�̒l���m�ہj
				break;
			}

		}
	}
	//����p�z��̍ő�l�܂Ői�񂾏ꍇ�A�ŏ��ɖ߂�
	if (judg_currentCW < 0) {
		judg_currentCW = JUDG_LEN - 1;
	}
	//�ړ��ۊǔz��Ɣ���p�z��ƈႤ�ꍇ�i�E���j
	if (move_stackCW[currentCW] != judgment[judg_currentCW]) {

		matchingCW = false;
		currentCW = 0;
		//�ړ��ۊǔz���������
		for (int i = 0; i < MAX_LENGTH; i++) {
			move_stackCW[i] = 0;
		}
	}
	else {
		//�������ꍇ
		matchingCW = true;
		judg_currentCW--;
		currentCW++;

		//�ړ��ۊǔz��̍ő�l�܂ŒB�����ꍇ�{����������
		if (matchingCW == true && currentCW == MAX_LENGTH) {
			currentCW = 0;
			judg_currentCW = 0;
			matchingCW = false;
			flag = true;

			//�z��̏�����
			for (int i = 0; i < MAX_LENGTH; i++) {
				move_stackCW[i] = 0;
			}

			move_stackCW[currentCW] = movenum;
			currentCW++;
		}

	}
}

//�����p
void CheckCCW() {

//����ɔ���p�z��̉��Ԗڂɓ����������i�[����Ă��邩�m�F

	if (matchingCCW == false) {
		for (judg_currentCCW = 0; judg_currentCCW < JUDG_LEN; judg_currentCCW++) {

			//��v�����ꍇ
			if (move_stackCCW[currentCCW] == judgment[judg_currentCCW]) {
				matchingCCW = true;
			}
			if (matchingCCW == true) {
				//�ړ��ۊǔz��Ɣ���p�z�񂪈�v�����ꍇ������ijudgment_current�̒l���m�ہj
				break;
			}

		}
	}

	//����p�z��̍ő�l�܂Ői�񂾏ꍇ�A�ŏ��ɖ߂�
	if (judg_currentCCW >= JUDG_LEN) {
		judg_currentCCW = 0;
	}

	//�ړ��ۊǔz��Ɣ���p�z��ƈႤ�ꍇ�i�����j
	if (move_stackCCW[currentCCW] != judgment[judg_currentCCW]) {

		matchingCCW = false;
		currentCCW = 0;
		//�ړ��ۊǔz���������
		for (int i = 0; i < MAX_LENGTH; i++) {
			move_stackCCW[i] = 0;
		}

	}
	else {
		//�������ꍇ
		matchingCCW = true;
		judg_currentCCW++;
		currentCCW++;

		//�ړ��ۊǔz��̍ő�l�܂ŒB�����ꍇ�{����������
		if (matchingCCW == true && currentCCW == MAX_LENGTH) {
			currentCCW = 0;
			judg_currentCCW = 0;
			matchingCCW = false;
			flag = true;

			//�z��̏�����
			for (int i = 0; i < MAX_LENGTH; i++) {
				move_stackCCW[i] = 0;
			}

			move_stackCCW[currentCCW] = movenum;
			currentCCW++;
		}
	}

}

bool SetBomb() {
	if (flag == true) {
		return true;
	}
	return false;
}

void ChangeState(Player *player,PlayerState next)
{
	fsm[player->CurrentState]->OnExit(player);
	player->CurrentState = next;
	fsm[player->CurrentState]->OnStart(player);
}