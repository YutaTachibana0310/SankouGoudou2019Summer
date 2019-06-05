//=============================================================================
//
// �v���C���[�R���g���[���[���� [player_controller.cpp]
// Author : �n糗Ǒ�
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "star.h"
#include "input.h"
#include "player_controller.h"
#include "InputController.h"
#include "UIdrawer.h"

PLAYER_CONTROLLER player_controller;

PLAYER* pplayer;

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


HRESULT InitPlayerController(void)
{

	for (int i = 0; i < MAX_LENGTH; i++) {
		move_stack[i] = 0;
		move_stack2[i] = 0;
	}
	current = 0;
	current2 = 0;

	judg_current = 0;
	judg_current2 = 0;
	player_controller.matching = false;
	player_controller.matching2 = false;
	player_controller.flag = false;
	player_controller.flag_count = 0;

	movenum = CENTER;

	return S_OK;
}

//update�����̒ǉ�
void UpdatePlayerController(HWND hWnd)
{
	pplayer = GetPlayer();


	if (pplayer->move_wait == true) {
		
		for (int i = 0; i < STAR_MAX; i++) {
			if (IsEntered(i,hWnd)) {
				movenum = i;
				push();
			}
		}

	}

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
	if (player_controller.matching == false) {
		for (judg_current = 0; judg_current < JUDG_LEN; judg_current++) {

			//��v�����ꍇ
			if (move_stack[current] == judgment[judg_current]) {
				player_controller.matching = true;
			}
			if (player_controller.matching == true) {
				//�ړ��ۊǔz��Ɣ���p�z�񂪈�v�����ꍇ������ijudgment_current�̒l���m�ہj
				break;
			}

		}
	}
	//�E���p
	if (player_controller.matching2 == false) {
		for (judg_current2 = 0; judg_current2 < JUDG_LEN; judg_current2++) {

			//��v�����ꍇ
			if (move_stack2[current2] == judgment[judg_current2]) {

				player_controller.matching2 = true;

			}
			if (player_controller.matching2 == true) {
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

		player_controller.matching = false;
		current = 0;
		//�ړ��ۊǔz���������
		for (int i = 0; i < MAX_LENGTH; i++) {
			move_stack[i] = 0;
		}

	}
	else {
		//�������ꍇ
		player_controller.matching = true;
		judg_current++;
		current++;

		//�ړ��ۊǔz��̍ő�l�܂ŒB�����ꍇ�{����������
		if (player_controller.matching == true && current == MAX_LENGTH) {
			current = 0;
			judg_current = 0;
			player_controller.matching = false;
			player_controller.flag = true;

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

		player_controller.matching2 = false;
		current2 = 0;
		//�ړ��ۊǔz���������
		for (int i = 0; i < MAX_LENGTH; i++) {
			move_stack2[i] = 0;
		}
	}
	else {
		//�������ꍇ
		player_controller.matching2 = true;
		judg_current2--;
		current2++;

		//�ړ��ۊǔz��̍ő�l�܂ŒB�����ꍇ�{����������
		if (player_controller.matching2 == true && current2 == MAX_LENGTH) {
			current2 = 0;
			judg_current2 = 0;
			player_controller.matching2 = false;
			player_controller.flag = true;

			//�z��̏�����
			for (int i = 0; i < MAX_LENGTH; i++) {
				move_stack2[i] = 0;
			}

			move_stack2[current2] = movenum;
			current2++;
		}

	}

}


PLAYER_CONTROLLER* GetPlayerController() {
	return &player_controller;
}