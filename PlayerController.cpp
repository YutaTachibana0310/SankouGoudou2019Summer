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

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//��莞�ԓ��͂��Ȃ��ꍇ�ɏ����|�W�V�����ɖ߂�ׂ̃^�C�}�[
int resetcount;

//����p�̔z��
int judgment[JUDG_LEN] = { TOP,LOWER_LEFT,MIDDLE_RIGHT,MIDDLE_LEFT,LOWER_RIGHT };

//����p�z��̌��݈ʒu
int judg_current;
int judg_current2;

//���݂̈ʒu
int current;
int current2;

//�ړ���̔ԍ��ۊǔz��
int move_stack[MAX_LENGTH];
int move_stack2[MAX_LENGTH];

// ���ԂɈړ����邩��ۊ�
int	movenum;

//����z��̓��e�ƍ����Ă��邩�̔���
bool matching;
bool matching2;

//�{�������e�X�g�p�t���O
bool flag;
int flagtimer;

HRESULT InitPlayerController(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < MAX_LENGTH; i++) {
		move_stack[i] = 0;
		move_stack2[i] = 0;
	}
	current = 0;
	current2 = 0;

	judg_current = 0;
	judg_current2 = 0;
	matching = false;
	matching2 = false;

	movenum = CENTER;

	resetcount = 0;

	flag = false;
	flagtimer = 0;

	return S_OK;
}

//update�����̒ǉ�
void UpdatePlayerController(HWND hWnd)
{

	resetcount++;
	
	if (flag == true) {
		flagtimer++;
		if (flagtimer > 120) {
			flag = false;
			flagtimer = 0;
		}
	}

	for (int i = 0; i < STAR_MAX; i++) {
		if (IsEntered(i, hWnd)) {
			movenum = i;
			push();
			resetcount = 0;
		}
	}

	if (resetcount >= 120) {
		movenum = 5;
		push();
		resetcount = 0;
	}
	DebugText("move_stack:%d,%d,%d,%d,%d,%d\n", move_stack[0], move_stack[1], move_stack[2], move_stack[3], move_stack[4], move_stack[5]);
	DebugText("move_stack2:%d,%d,%d,%d,%d,%d\n", move_stack2[0], move_stack2[1], move_stack2[2], move_stack2[3], move_stack2[4], move_stack2[5]);
	
}

void SetPlayerTargetPosition(int *n) {

	*n = movenum;

}

void push() {

	//�ړ��ۊǔz��ɓ��͂��ꂽ�L�[�̔ԍ���ۊ�
	if (current < MAX_LENGTH) {
		move_stack[current] = movenum;
		move_stack2[current2] = movenum;

	}
	//����ɔ���p�z��̉��Ԗڂɓ����������i�[����Ă��邩�m�F
	//�����p
	if (matching == false) {
		for (judg_current = 0; judg_current < JUDG_LEN; judg_current++) {

			//��v�����ꍇ
			if (move_stack[current] == judgment[judg_current]) {
				matching = true;
			}
			if (matching == true) {
				//�ړ��ۊǔz��Ɣ���p�z�񂪈�v�����ꍇ������ijudgment_current�̒l���m�ہj
				break;
			}

		}
	}
	//�E���p
	if (matching2 == false) {
		for (judg_current2 = 0; judg_current2 < JUDG_LEN; judg_current2++) {

			//��v�����ꍇ
			if (move_stack2[current2] == judgment[judg_current2]) {

				matching2 = true;

			}
			if (matching2 == true) {
				//�ړ��ۊǔz��Ɣ���p�z�񂪈�v�����ꍇ������ijudgment_current�̒l���m�ہj
				break;
			}

		}
	}
	//����p�z��̍ő�l�܂Ői�񂾏ꍇ�A�ŏ��ɖ߂�
	if (judg_current >= JUDG_LEN) {
		judg_current = 0;
	}
	if (judg_current2 < 0) {
		judg_current2 = JUDG_LEN - 1;
	}

	//�ړ��ۊǔz��Ɣ���p�z��ƈႤ�ꍇ�i�����j
	if (move_stack[current] != judgment[judg_current]) {

		matching = false;
		current = 0;
		//�ړ��ۊǔz���������
		for (int i = 0; i < MAX_LENGTH; i++) {
			move_stack[i] = 0;
		}

	}
	else {
		//�������ꍇ
		matching = true;
		judg_current++;
		current++;

		//�ړ��ۊǔz��̍ő�l�܂ŒB�����ꍇ�{����������
		if (matching == true && current == MAX_LENGTH) {
			current = 0;
			judg_current = 0;
			matching = false;
			flag = true;

			//�z��̏�����
			for (int i = 0; i < MAX_LENGTH; i++) {
				move_stack[i] = 0;
			}

			move_stack[current] = movenum;
			current++;
		}
	}
	//�ړ��ۊǔz��Ɣ���p�z��ƈႤ�ꍇ�i�E���j
	if (move_stack2[current2] != judgment[judg_current2]) {

		matching2 = false;
		current2 = 0;
		//�ړ��ۊǔz���������
		for (int i = 0; i < MAX_LENGTH; i++) {
			move_stack2[i] = 0;
		}
	}
	else {
		//�������ꍇ
		matching2 = true;
		judg_current2--;
		current2++;

		//�ړ��ۊǔz��̍ő�l�܂ŒB�����ꍇ�{����������
		if (matching2 == true && current2 == MAX_LENGTH) {
			current2 = 0;
			judg_current2 = 0;
			matching2 = false;
			flag = true;

			//�z��̏�����
			for (int i = 0; i < MAX_LENGTH; i++) {
				move_stack2[i] = 0;
			}

			move_stack2[current2] = movenum;
			current2++;
		}

	}

}

bool SetBomb() {
	if (flag == true) {
		return true;
	}
	return false;
}

