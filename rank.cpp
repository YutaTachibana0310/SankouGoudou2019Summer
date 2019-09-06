#include "rank.h"
#include "starButtonUI.h"
#include "scoreUI.h"
#include "savefile.h"
#include "UIdrawerC.h"
#include "ScoreManager.h"

SCORERANK scorerank[ARRAY_MAX];
OBJECT rank[RANK_MAX];
OBJECT rankBGParts[RANK_MAX];
//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
int	tmp;	//�\�[�g�p�̕ϐ�

			//�����̈ړ�����
D3DXVECTOR3 acceleration;
D3DXVECTOR3 attraction;
bool rankactive[RANK_MAX];
D3DXVECTOR3 dir;
D3DXVECTOR3 target;
float length;

//=============================================================================
// �����L���O����������
//=============================================================================
HRESULT InitRank(void) {

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�����L���O�������̏���
	for (int i = 0; i < RANK_MAX; i++) {

		LoadTexture(pDevice, ADRESS_TEXTURE_NUMBER_RANK, &rank[i]);
		InitialTexture(&rank[i]);
		MakeVertexObject(&rank[i]);
		rank[i].rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		rank[i].size = SIZE_RANK;

	}

	// ���W
	rank[TOP].position = POSITION_RANK_TOP;
	rank[MIDDLE_LEFT].position = POSITION_RANK_MIDDLE_LEFT;
	rank[LOWER_LEFT].position = POSITION_RANK_MIDDLE_RIGHT;
	rank[LOWER_RIGHT].position = POSITION_RANK_LOWER_LEFT;
	rank[MIDDLE_RIGHT].position = POSITION_RANK_LOWER_RIGHT;
	rank[CENTER].position = POSITION_RANK_CENTER;

	//�@�F�ݒ�
	SetColorObject(&rank[TOP], SET_COLOR_RED);
	SetColorObject(&rank[MIDDLE_LEFT], SET_COLOR_PINK);
	SetColorObject(&rank[LOWER_LEFT], SET_COLOR_RIGHTBLUE);
	SetColorObject(&rank[LOWER_RIGHT], SET_COLOR_NOT_COLORED);
	SetColorObject(&rank[MIDDLE_RIGHT], SET_COLOR_NOT_COLORED);
	SetColorObject(&rank[CENTER], SET_COLOR_ORANGE);

	//�����L���OBG�̏���
	LoadTexture(pDevice, ADRESS_TEXTURE_BG_RANK1, &rankBGParts[0]);
	LoadTexture(pDevice, ADRESS_TEXTURE_BG_RANK2, &rankBGParts[1]);
	LoadTexture(pDevice, ADRESS_TEXTURE_BG_RANK3, &rankBGParts[2]);
	LoadTexture(pDevice, ADRESS_TEXTURE_BG_RANK4, &rankBGParts[3]);
	LoadTexture(pDevice, ADRESS_TEXTURE_BG_RANK5, &rankBGParts[4]);
	LoadTexture(pDevice, ADRESS_TEXTURE_BG_RANK6, &rankBGParts[5]);

	for (int i = 0; i < RANK_MAX; i++) {
		InitialTexture(&rankBGParts[i]);
		MakeVertexObject(&rankBGParts[i]);
		rankBGParts[i].rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		rankBGParts[i].size = SIZE_BG_RANK;

		SetColorObject(&rankBGParts[i], SET_COLOR_NOT_COLORED);

	}

	rankBGParts[TOP].position = POSITION_BG_RANK_TOP;
	rankBGParts[MIDDLE_LEFT].position = POSITION_BG_RANK_MIDDLE_LEFT;
	rankBGParts[LOWER_LEFT].position = POSITION_BG_RANK_MIDDLE_RIGHT;
	rankBGParts[LOWER_RIGHT].position = POSITION_BG_RANK_LOWER_LEFT;
	rankBGParts[MIDDLE_RIGHT].position = POSITION_BG_RANK_LOWER_RIGHT;
	rankBGParts[CENTER].position = POSITION_BG_RANK_CENTER;

	acceleration = { 0,0,0 };
	attraction = { 0,0,0 };
	dir = { 0,0,0 };
	target = { 0,0,0 };
	length = 0.0f;

	rankactive[0] = false;
	rankactive[1] = false;
	rankactive[2] = false;
	rankactive[3] = false;
	rankactive[4] = false;
	rankactive[5] = true;

	//�o�C�i���t�@�C���̓ǂݍ���
	LoadData();

	//�����L���O�\�[�g���s
	RankSort();

	//�\�[�g��̃����L���O��ۑ�
	SaveData();



	return S_OK;
}

//=============================================================================
// �����L���O�I������
//=============================================================================
void UninitRank(void) {

	for (int i = 0; i < RANK_MAX; i++)
	{
		ReleaseTexture(&rank[i]);
		ReleaseTexture(&rankBGParts[i]);
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateRank(void) {

	for (int i = RANK_MAX; i >= 0; i--) {
		if (rankactive[i]) {
			dir = (rankBGParts[i].position - D3DXVECTOR3(80, -10, 0)) - rank[i].position;
			//���K��
			D3DXVec3Normalize(&dir, &dir);
			//�^�[�Q�b�g�����Z�o
			target = (rankBGParts[i].position - D3DXVECTOR3(80, -10, 0)) - rank[i].position;
			length = D3DXVec3Length(&target);
			//�^�[�Q�b�g�ֈړ�
			attraction = dir * 10;
			attraction += acceleration * (1 - length);

			rank[i].position += attraction;

			if (length <= 1.0f) {
				attraction = D3DXVECTOR3(0, 0, 0);
				rankactive[i] = false;
				if (i > 0) {
					rankactive[i - 1] = true;
				}
			}

		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawRank(void) {

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < RANK_MAX; i++) {
		DrawObject(pDevice, rankBGParts[i]);
		SetVertexObject(&rankBGParts[i]);
		for (int nCntPlace = 0; nCntPlace < PLACE_MAX; nCntPlace++)
		{
			int number;

			number = scorerank[i].g_scorerank % (int)(powf(BASE_NUMBER, (float)(PLACE_MAX - nCntPlace))) / (int)(powf(BASE_NUMBER, (float)(PLACE_MAX - nCntPlace - 1)));

			DrawObject(pDevice, rank[i]);
			SetVertexCounter(&rank[i], nCntPlace, INTERVAL_RANKING_NUMBER);
			SetTextureCounter(&rank[i], number, INTERVAL_NUMBER_TEXTURE);
		}

	}
}

void RankSort(void) {

	//�O�񕪂̃}�C�X�R�A��������
	scorerank[MYSCORE].g_scorerank = NULL;

	//����̕��̃X�R�A��z��̍Ō�ɑ��
	scorerank[RANK_MAX].g_scorerank = GetCurrentGameScore();

	for (int i = 0; i <= RANK_MAX; i++) {

		//���̔z��̒l���擾
		for (int j = i + 1; j <= RANK_MAX; j++) {

			//�O��̔z���r
			if (scorerank[i].g_scorerank < scorerank[j].g_scorerank) {

				//�O�̔z��̐��l���傫���ꍇ����ւ��Atmp�Ɉ��ޔ�
				tmp = scorerank[i].g_scorerank;

				//�O�̔z��̐��l�����̐��l�ɑ��
				scorerank[i].g_scorerank = scorerank[j].g_scorerank;

				//���̔z��ɑޔ������O�̐��l����
				scorerank[j].g_scorerank = tmp;

			}
		}
	}

	//����̕��̃}�C�X�R�A�𒆐S��
	scorerank[MYSCORE].g_scorerank = GetCurrentGameScore();


}

SCORERANK *GetRank() {
	return &scorerank[0];
}