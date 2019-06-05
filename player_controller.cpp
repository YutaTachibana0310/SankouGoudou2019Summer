//=============================================================================
//
// プレイヤーコントローラー処理 [player_controller.cpp]
// Author : 渡邉良則
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

//判定用の配列
int judgment[JUDG_LEN] = { TOP,LOWER_LEFT,MIDDLE_RIGHT,MIDDLE_LEFT,LOWER_RIGHT };

//判定用配列の現在位置
int judg_current;
int judg_current2;

//現在の位置
int current;
int current2;

//移動先の番号保管配列
int move_stack[MAX_LENGTH];
int move_stack2[MAX_LENGTH];

// 何番に移動するかを保管
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

//update処理の追加
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

	//移動保管配列に入力されたキーの番号を保管
	if (current < MAX_LENGTH) {
		move_stack[current] = movenum;
		move_stack2[current2] = movenum;

	}
	//初回に判定用配列の何番目に同じ数字が格納されているか確認
	//左回り用
	if (player_controller.matching == false) {
		for (judg_current = 0; judg_current < JUDG_LEN; judg_current++) {

			//一致した場合
			if (move_stack[current] == judgment[judg_current]) {
				player_controller.matching = true;
			}
			if (player_controller.matching == true) {
				//移動保管配列と判定用配列が一致した場合抜ける（judgment_currentの値を確保）
				break;
			}

		}
	}
	//右回り用
	if (player_controller.matching2 == false) {
		for (judg_current2 = 0; judg_current2 < JUDG_LEN; judg_current2++) {

			//一致した場合
			if (move_stack2[current2] == judgment[judg_current2]) {

				player_controller.matching2 = true;

			}
			if (player_controller.matching2 == true) {
				//移動保管配列と判定用配列が一致した場合抜ける（judgment_currentの値を確保）
				break;
			}

		}
	}
	//判定用配列の最大値まで進んだ場合、最初に戻す
	if (judg_current >= JUDG_LEN) {
		judg_current = 0;
	}
	if (judg_current2 < 0) {
		judg_current2 = JUDG_LEN - 1;
	}

	//移動保管配列と判定用配列と違う場合（左回り）
	if (move_stack[current] != judgment[judg_current]) {

		player_controller.matching = false;
		current = 0;
		//移動保管配列を初期化
		for (int i = 0; i < MAX_LENGTH; i++) {
			move_stack[i] = 0;
		}

	}
	else {
		//正しい場合
		player_controller.matching = true;
		judg_current++;
		current++;

		//移動保管配列の最大値まで達した場合ボム発生処理
		if (player_controller.matching == true && current == MAX_LENGTH) {
			current = 0;
			judg_current = 0;
			player_controller.matching = false;
			player_controller.flag = true;

			//配列の初期化
			for (int i = 0; i < MAX_LENGTH; i++) {
				move_stack[i] = 0;
			}

			move_stack[current] = movenum;
			current++;
		}
	}
	//移動保管配列と判定用配列と違う場合（右回り）
	if (move_stack2[current2] != judgment[judg_current2]) {

		player_controller.matching2 = false;
		current2 = 0;
		//移動保管配列を初期化
		for (int i = 0; i < MAX_LENGTH; i++) {
			move_stack2[i] = 0;
		}
	}
	else {
		//正しい場合
		player_controller.matching2 = true;
		judg_current2--;
		current2++;

		//移動保管配列の最大値まで達した場合ボム発生処理
		if (player_controller.matching2 == true && current2 == MAX_LENGTH) {
			current2 = 0;
			judg_current2 = 0;
			player_controller.matching2 = false;
			player_controller.flag = true;

			//配列の初期化
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