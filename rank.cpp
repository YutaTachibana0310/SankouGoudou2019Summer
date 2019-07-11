#include "rank.h"
#include "starUI.h"
#include "scoreUI.h"
#include "savefile.h"
#include "ScoreManager.h"

OBJECT rank[RANK_MAX];
//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
int g_scorerank[RANK_MAX]; //����


//=============================================================================
// �����L���O����������
//=============================================================================
HRESULT InitRank(void) {

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < RANK_MAX; i++) {

		LoadTexture(pDevice, ADRESS_TEXTURE_NUMBER_RANK, &rank[i]);
		InitialTexture(&rank[i]);
		MakeVertexObject(&rank[i]);
		rank[i].rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		rank[i].size = SIZE_RANK;

	}

	// ���W
	rank[TOP].position = POSITION_STAR_TOP;
	rank[MIDDLE_LEFT].position = POSITION_STAR_MIDDLE_LEFT;
	rank[LOWER_LEFT].position = POSITION_STAR_LOWER_LEFT;
	rank[LOWER_RIGHT].position = POSITION_STAR_LOWER_RIGHT;
	rank[MIDDLE_RIGHT].position = POSITION_STAR_MIDDLE_RIGHT;
	rank[CENTER].position = POSITION_STAR_CENTER;

	//�@�F�ݒ�
	SetColorObject(&rank[TOP], SET_COLOR_YELLOW);
	SetColorObject(&rank[MIDDLE_LEFT], SET_COLOR_PINK);
	SetColorObject(&rank[LOWER_LEFT], SET_COLOR_RIGHTBLUE);
	SetColorObject(&rank[LOWER_RIGHT], SET_COLOR_NOT_COLORED);
	SetColorObject(&rank[MIDDLE_RIGHT], SET_COLOR_NOT_COLORED);
	SetColorObject(&rank[CENTER], SET_COLOR_ORANGE);

	//����̕��̃X�R�A��z��̍Ō�ɑ��
	g_scorerank[RANK_MAX] = GetHiScore();

	LoadData();

	



	return S_OK;
}

//=============================================================================
// �����L���O�I������
//=============================================================================
void UninitRank(void) {

	for (int i = 0; i < RANK_MAX; i++)
	{
		ReleaseTexture(&rank[i]);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawRank(void) {

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < RANK_MAX; i++) {
		for (int nCntPlace = 0; nCntPlace < PLACE_MAX; nCntPlace++)
		{
			int number;

			number = g_scorerank[0] % (int)(powf(BASE_NUMBER, (float)(PLACE_MAX - nCntPlace))) / (int)(powf(BASE_NUMBER, (float)(PLACE_MAX - nCntPlace - 1)));

			DrawObject(pDevice, rank[i]);
			SetVertexCounter(&rank[i], nCntPlace, INTERVAL_NUMBER);
			SetTextureCounter(&rank[i], number, INTERVAL_NUMBER_TEXTURE);
		}
	}
}

OBJECT *GetRank() {
	return &rank[0];
}





