//=============================================================================
//
// �v���C���[�R���g���[���[���� [PlayerController.cpp]
// Author : �n糗Ǒ�
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "starUI.h"
#include "PlayerController.h"
#include "InputController.h"
#include "debugWindow.h"
#include "IStateMachine.h"
#include <map>
#include "PlayerMove.h"
#include "PlayerReturn.h"
#include "PlayerWait.h"
#include "PlayerBullet.h"
#include <vector>
#include "GameParticleManager.h"

using namespace std;

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MOVETARGET_LENGTH				(6)
#define PLAYER_DISTANCE_FROM_CAMERA		(150.0f)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void push(void);				//�ړ������X�^�b�N�ւ̃v�b�V������
void CheckInput(HWND hWnd);		//���͔���
void CheckComboReset(void);		//���Z�b�g�m�F
void CalcPlayerMoveTargetPos();	//�ړ��ڕW���W�v�Z����

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
int move_stackCCW[MOVESTACK_LENGTH];
int move_stackCW[MOVESTACK_LENGTH];

// ���ԂɈړ����邩��ۊ�
int	movenum;

//����z��̓��e�ƍ����Ă��邩�̔���
bool matchingCCW;
bool matchingCW;

//�{�������e�X�g�p�t���O
bool flag;
int flagtimer;

//�v���C���[�X�e�[�g�}�V��
static map<PlayerState, IStateMachine<Player>*> fsm;

//�v���C���[
Player player;

//�ړ�����W
D3DXVECTOR3 MovePos[MOVETARGET_LENGTH];

//�o���b�g�R���e�i
vector<PlayerBullet*> bulletContainer;

//*****************************************************************************
// ����������
//*****************************************************************************
HRESULT InitPlayerController(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�X�e�[�g�}�V��������
	fsm[PlayerState::Move] = new PlayerMove();
	fsm[PlayerState::Wait] = new PlayerWait();
	fsm[PlayerState::Return] = new PlayerReturn();

	//�v���C���[������
	player.Init();

	//�ړ������X�^�b�N��������
	for (int i = 0; i < MOVESTACK_LENGTH; i++) {
		move_stackCCW[i] = INITIAL_ARRAY_NUMBER;
		move_stackCW[i] = INITIAL_ARRAY_NUMBER;
	}

	//�ړ��ڕW������
	MovePos[CENTER] = PLAYER_CENTER;
	CalcPlayerMoveTargetPos();

	//��M��������p�ϐ���������
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

	//�v���C���[��Wait��ԂɑJ��
	player.currentState = PlayerState::Wait;
	player.active = true;

	//PlayerTrailParticle���Z�b�g
	SetPlayerTrailParticle(&player.pos, &player.active);

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
	BeginDebugWindow("PlayerController");
	if (DebugButton("BUllet"))
	{
		int start = RandomRange(0, 5);
		int end = WrapAround(0, 5, start + RandomRange(1, 4));
		FirePlayerBullet((TrailIndex)start, (TrailIndex)end);
	}
	DebugText("PlayerBulletCnt : %d", bulletContainer.size());
	DebugText("PlayerState:%d", (int)player.currentState);
	EndDebugWindow("PlayerController");

	resetcount++;

	//�{�������p�̃t���O�A�J�E���^
	if (flag == true) {
		flagtimer++;
		if (flagtimer > RESETTIME) {
			flag = false;
			flagtimer = 0;
		}
	}

	//�ړ��̓��͊m�F
	CheckInput(hWnd);

	//�R���{���Z�b�g�m�F
	CheckComboReset();

	//�v���C���[���A�b�v�f�[�g
	player.Update();
	fsm[player.currentState]->OnUpdate(&player);

	//�v���C���[�o���b�g���A�b�v�f�[�g
	for (auto itr = bulletContainer.begin(); itr != bulletContainer.end(); itr++)
	{
		(*itr)->Update();
	}
}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void DrawPlayerController()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�v���C���[�`��
	player.Draw();
}

//*****************************************************************************
//�@�v���C���[�o���b�g�`�揈��
//*****************************************************************************
void DrawPlayerBullet()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	pDevice->SetRenderState(D3DRS_LIGHTING, false);
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);

	//�v���C���[�o���b�g�`��
	for (auto itr = bulletContainer.begin(); itr != bulletContainer.end(); itr++)
	{
		(*itr)->Draw();
	}

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	pDevice->SetRenderState(D3DRS_LIGHTING, true);
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
}

//*****************************************************************************
// ���͊m�F
//*****************************************************************************
void CheckInput(HWND hWnd)
{
	//Wait��ԈȊO�͓��͂��󂯕t���Ȃ�
	if (player.currentState != PlayerState::Wait)
		return;

	//�e�{�^���ɂ��Ċm�F
	for (int i = 0; i < STAR_MAX; i++)
	{
		if (!IsEntered(i))
			continue;

		movenum = i;
		push();
		player.goalpos = MovePos[i];
		ChangeState(&player, PlayerState::Move);

		CheckCW();
		CheckCCW();
		resetcount = 0;
	}
}

//*****************************************************************************
// ���Z�b�g�m�F
//*****************************************************************************
void CheckComboReset(void)
{
	//���Ԍo�߂��Ă��Ȃ���Ή������Ȃ�
	if (resetcount < RESETTIME)
		return;

	
	//�����֖߂�
	movenum = 5;
	push();
	ChangeState(&player, PlayerState::Return);

	CheckCW();
	CheckCCW();
	resetcount = 0;

}

//*****************************************************************************
// ����p�X�^�b�N�ւ̈ړ������v�b�V������
//*****************************************************************************
void push()
{
	//�ړ��ۊǔz��ɓ��͂��ꂽ�L�[�̔ԍ���ۊ�
	if (currentCCW < MOVESTACK_LENGTH) {
		move_stackCCW[currentCCW] = movenum;
		move_stackCW[currentCW] = movenum;
	}
}

//*****************************************************************************
// ���^��M��������i�E���j
//*****************************************************************************
void CheckCW()
{
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
	if (move_stackCW[currentCW] != judgment[judg_currentCW])
	{

		matchingCW = false;
		currentCW = 0;
		//�ړ��ۊǔz���������
		for (int i = 0; i < MOVESTACK_LENGTH; i++) {
			move_stackCW[i] = INITIAL_ARRAY_NUMBER;
		}
	}
	else
	{
		//�������ꍇ
		matchingCW = true;
		judg_currentCW--;
		currentCW++;

		//�ړ��ۊǔz��̍ő�l�܂ŒB�����ꍇ�{����������
		if (matchingCW == true && currentCW == MOVESTACK_LENGTH) {
			currentCW = 0;
			judg_currentCW = 0;
			matchingCW = false;
			flag = true;

			//�z��̏�����
			for (int i = 0; i < MOVESTACK_LENGTH; i++) {
				move_stackCW[i] = INITIAL_ARRAY_NUMBER;
			}

			move_stackCW[currentCW] = movenum;
			currentCW++;
		}
	}
}

//*****************************************************************************
// ���^��M��������i�����j
//*****************************************************************************
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
		for (int i = 0; i < MOVESTACK_LENGTH; i++) {
			move_stackCCW[i] = INITIAL_ARRAY_NUMBER;
		}

	}
	else {
		//�������ꍇ
		matchingCCW = true;
		judg_currentCCW++;
		currentCCW++;

		//�ړ��ۊǔz��̍ő�l�܂ŒB�����ꍇ�{����������
		if (matchingCCW == true && currentCCW == MOVESTACK_LENGTH) {
			currentCCW = 0;
			judg_currentCCW = 0;
			matchingCCW = false;
			flag = true;

			//�z��̏�����
			for (int i = 0; i < MOVESTACK_LENGTH; i++) {
				move_stackCCW[i] = INITIAL_ARRAY_NUMBER;
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

//=============================================================================
// �v���C���[�o���b�g�R���e�i�擾����
//=============================================================================
vector<PlayerBullet*>* GetPlayerBulletContainer(void)
{
	return &bulletContainer;
}

//=============================================================================
// Player��ԑJ�ڏ���
//=============================================================================
void ChangeState(Player *player, PlayerState next)
{
	fsm[player->currentState]->OnExit(player);
	player->currentState = next;
	fsm[player->currentState]->OnStart(player);
}

//=============================================================================
// �ړ��ڕW���W�v�Z����
//=============================================================================
void CalcPlayerMoveTargetPos()
{
	//�X�^�[�̃X�N���[�����W���擾
	D3DXVECTOR3 starPos[5];
	GetStarPosition(starPos);

	for (int i = 0; i < STAR_MAX; i++)
	{
		//�X�^�[�̈ʒu��Near�ʂ�Far�ʂ����ԃ��C���v�Z���Đ��K��
		D3DXVECTOR3 nearPos, farPos;
		CalcScreenToWorld(&nearPos, &starPos[i], 0.0f);
		CalcScreenToWorld(&farPos, &starPos[i], 1.0f);

		D3DXVECTOR3 ray = farPos - nearPos;
		D3DXVec3Normalize(&ray, &ray);

		//�ڕW���W���v�Z
		MovePos[i] = nearPos + ray * PLAYER_DISTANCE_FROM_CAMERA;
	}
}

//=============================================================================
//�@�v���C���[�o���b�g���ˏ���
//=============================================================================
void FirePlayerBullet(TrailIndex start, TrailIndex end)
{
	for (auto itr = bulletContainer.begin(); itr != bulletContainer.end(); itr++)
	{
		if ((*itr)->IsActive())
			continue;
		
		//�Z�b�g���ă��^�[��
		(*itr)->SetTrailIndex(start, end);
		(*itr)->SetEdgePos(&MovePos[(int)start], &MovePos[(int)end]);
		(*itr)->Init();
		return;

	}

	//�V�����������Ēǉ�
	PlayerBullet *bullet = new PlayerBullet();
	bullet->SetTrailIndex(start, end);
	bullet->SetEdgePos(&MovePos[(int)start], &MovePos[(int)end]);
	bullet->Init();
	bulletContainer.push_back(bullet);
	return;
}

//=============================================================================
//�@�v���C���[�o���b�g���ˏ���
//=============================================================================
void FirePlayerBullet(D3DXVECTOR3 *rightPos, D3DXVECTOR3 *leftPos)
{
	int start = 0, end = 0;
	for (int i = 0; i < STAR_MAX; i++)
	{
		if (MovePos[i] == *rightPos)
			start = i;

		if (MovePos[i] == *leftPos)
			end = i;
	}

	for (auto itr = bulletContainer.begin(); itr != bulletContainer.end(); itr++)
	{
		if ((*itr)->IsActive())
			continue;

		//�Z�b�g���ă��^�[��
		(*itr)->SetTrailIndex((TrailIndex)start, (TrailIndex)end);
		(*itr)->SetEdgePos(&MovePos[(int)start], &MovePos[(int)end]);
		(*itr)->Init();
		return;

	}

	//�V�����������Ēǉ�
	PlayerBullet *bullet = new PlayerBullet();
	bullet->SetTrailIndex((TrailIndex)start, (TrailIndex)end);
	bullet->SetEdgePos(&MovePos[(int)start], &MovePos[(int)end]);
	bullet->Init();
	bulletContainer.push_back(bullet);
	return;
}

//=============================================================================
// CCW�z��擾���� (���[�͂ܒǋL)
//=============================================================================
void GetMove_StackCCW(int trailHistoryCCW[MOVESTACK_LENGTH]) {
	for (int i = 0; i < MOVESTACK_LENGTH; i++) {
		trailHistoryCCW[i] = move_stackCCW[i];
	}
}

//=============================================================================
// CW�z��擾���� (���[�͂ܒǋL)
//=============================================================================
void GetMove_StackCW(int trailHistoryCW[MOVESTACK_LENGTH]) {
	for (int i = 0; i < MOVESTACK_LENGTH; i++) {
		trailHistoryCW[i] = move_stackCW[i];
	}
}
