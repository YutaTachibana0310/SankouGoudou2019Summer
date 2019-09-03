#include "rank.h"
#include "starUI.h"
#include "scoreUI.h"
#include "savefile.h"
#include "scoreUI.h"
#include "GameSceneUIManager.h"

SCORERANK scorenumber[ARRAY_MAX];

//=============================================================================
// �����L���O����������
//=============================================================================
Rank::Rank()
{
	//�����L���O�������̏���
	for (int i = 0; i < RANK_MAX; i++) {

		number[i] = new CounterObject;

		number[i]->LoadTexture(ADRESS_TEXTURE_NUMBER_RANK);
		number[i]->MakeVertex();
		number[i]->position = numberPosition[i];
		number[i]->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		number[i]->size = SIZE_RANK;
		number[i]->SetColorObject(numberColor[i]);
	}

	//�����L���OBG�̏���
	for (int i = 0; i < RANK_MAX; i++) {

		bg[i] = new Object;

		bg[i]->LoadTexture(bgTexPath[i]);
		bg[i]->MakeVertex();
		bg[i]->position = bgPosition[i];
		bg[i]->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		bg[i]->size = SIZE_BG_RANK;

		bg[i]->SetColorObject(SET_COLOR_NOT_COLORED);
	}

	acceleration = { 0,0,0 };
	attraction = { 0,0,0 };
	dir = { 0,0,0 };
	target = { 0,0,0 };
	length = 0.0f;

	numberactive[0] = false;
	numberactive[1] = false;
	numberactive[2] = false;
	numberactive[3] = false;
	numberactive[4] = false;
	numberactive[5] = true;

	//�o�C�i���t�@�C���̓ǂݍ���
	LoadData();

	//�����L���O�\�[�g���s
	RankSort();

	//�\�[�g��̃����L���O��ۑ�
	SaveData();
}

Rank::~Rank()
{
	for (int i = 0; i < RANK_MAX; i++)
	{
		delete number[i];
		number[i] = NULL;

		delete bg[i];
		bg[i] = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void Rank::Update(void) {

	for (int i = RANK_MAX; i >= 0;i--) {
		if (numberactive[i]) {
			dir = (bg[i]->position - D3DXVECTOR3(80,-10,0)) - number[i]->position;
			//���K��
			D3DXVec3Normalize(&dir, &dir);
			//�^�[�Q�b�g�����Z�o
			target = (bg[i]->position - D3DXVECTOR3(80, -10, 0)) - number[i]->position;
			length = D3DXVec3Length(&target);
			//�^�[�Q�b�g�ֈړ�
			attraction = dir * 10;
			attraction += acceleration * (1 - length);

			number[i]->position += attraction;

			if (length <= 1.0f) {
				attraction = D3DXVECTOR3(0, 0, 0);
				numberactive[i] = false;
				if (i > 0) {
					numberactive[i - 1] = true;
				}
			}

		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void Rank::Draw(void) {

	for (int i = 0; i < RANK_MAX; i++) {
		bg[i]->Draw();
		bg[i]->SetVertex();
		for (int nCntPlace = 0; nCntPlace < PLACE_MAX; nCntPlace++)
		{
			int num;

			num = scorenumber[i].g_scorenumber % (int)(powf(BASE_NUMBER, (float)(PLACE_MAX - nCntPlace))) / (int)(powf(BASE_NUMBER, (float)(PLACE_MAX - nCntPlace - 1)));

			number[i]->Draw();
			number[i]->SetVertex(nCntPlace, INTERVAL_RANKING_NUMBER);
			number[i]->SetTexture(num, INTERVAL_NUMBER_TEXTURE);
		}

	}
}

void Rank::RankSort(void) {

	//�O�񕪂̃}�C�X�R�A��������
	scorenumber[MYSCORE].g_scorenumber = NULL;

	//����̕��̃X�R�A��z��̍Ō�ɑ��
	gameSceneUIManager->SetScore(scorenumber[RANK_MAX].g_scorenumber);

	for (int i = 0; i <= RANK_MAX; i++) {

		//���̔z��̒l���擾
		for (int j = i + 1; j <= RANK_MAX; j++) {

			//�O��̔z���r
			if (scorenumber[i].g_scorenumber < scorenumber[j].g_scorenumber) {

				//�O�̔z��̐��l���傫���ꍇ����ւ��Atmp�Ɉ��ޔ�
				tmp = scorenumber[i].g_scorenumber;

				//�O�̔z��̐��l�����̐��l�ɑ��
				scorenumber[i].g_scorenumber = scorenumber[j].g_scorenumber;

				//���̔z��ɑޔ������O�̐��l����
				scorenumber[j].g_scorenumber = tmp;
			}
		}
	}

	//����̕��̃}�C�X�R�A�𒆐S��
	gameSceneUIManager->SetScore(scorenumber[MYSCORE].g_scorenumber);
}

SCORERANK *GetRank() {
	return &scorenumber[0];
}
