//=====================================
//
//�e���v���[�g����[BackGroundCity.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "BackGroundCity.h"
#include "Framework\MeshContainer.h"
#include "SkyBox.h"

/**************************************
�}�N����`
***************************************/
#define BACKGROUNDCITY_MODEL_FILE		"data/MODEL/City/city01.x"
#define BACKGROUNDCITY_NUM_MAX			(100)
#define BACKGROUNDCITY_KIND_MAX			(2)

#define BACKGROUNDCITY_BASEPOS_X_INNER	(300.0f)
#define BACKGROUNDCITY_BASEPOS_X_OUTER	(500.0f)
#define BACKGROUNDCITY_BASEPOS_Y		(0.0f)
#define BACKGROUNDCITY_BASEPOS_Z		(0.0f)

#define BACKGROUNDCITY_POS_RANGE_X		(200.0f)
#define BACKGROUNDCITY_POS_RANGE_Y		(100.0f)
#define BACKGROUNDCITY_POS_RANGE_Z		(50.0f)

#define BACKGROUNDCITY_OFFSET_Z			(300.0f)

#define BACKGROUNDCITY_MOVE_SPEED		(-25.0f)

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
static D3DXVECTOR3 cityPos[BACKGROUNDCITY_NUM_MAX];

static MeshContainer* meshContainer;

/**************************************
�v���g�^�C�v�錾
***************************************/

/**************************************
����������
***************************************/
void InitBackGroundCity(int num)
{
	meshContainer = new MeshContainer();
	meshContainer->Load(BACKGROUNDCITY_MODEL_FILE);

	//Y���W�AZ���W�ɂ��ď�����
	for (int i = 0; i < BACKGROUNDCITY_NUM_MAX; i += BACKGROUNDCITY_KIND_MAX)
	{
		cityPos[i].y = BACKGROUNDCITY_BASEPOS_Y + RandomRangef(-BACKGROUNDCITY_POS_RANGE_Y, BACKGROUNDCITY_POS_RANGE_Y);

		for (int j = 0; j < BACKGROUNDCITY_KIND_MAX; j++)
		{
			cityPos[i+j].z = BACKGROUNDCITY_BASEPOS_Z + BACKGROUNDCITY_OFFSET_Z * (i / 2) + RandomRangef(-BACKGROUNDCITY_POS_RANGE_Z, BACKGROUNDCITY_POS_RANGE_Z);
		}
	}

	//X���W�ɂ��ď�����
	for (int i = 0; i < BACKGROUNDCITY_NUM_MAX; i += BACKGROUNDCITY_KIND_MAX)
	{
		cityPos[i].x = BACKGROUNDCITY_BASEPOS_X_INNER + RandomRangef(0.0f, BACKGROUNDCITY_POS_RANGE_X);
		cityPos[i + 1].x = -BACKGROUNDCITY_BASEPOS_X_INNER - RandomRangef(0.0f, BACKGROUNDCITY_POS_RANGE_X);
		//cityPos[i + 2].x = BACKGROUNDCITY_BASEPOS_X_OUTER + RandomRangef(0.0f, BACKGROUNDCITY_POS_RANGE_X);
		//cityPos[i + 3].x = -BACKGROUNDCITY_BASEPOS_X_OUTER - RandomRangef(0.0f, BACKGROUNDCITY_POS_RANGE_X);
	}
}

/**************************************
�I������
***************************************/
void UninitBackGroundCity(int num)
{
	delete meshContainer;
}
#include "input.h"
/**************************************
�X�V����
***************************************/
void UpdateBackGroundCity(void)
{
	for (int i = 0; i < BACKGROUNDCITY_NUM_MAX; i++)
	{
		//�ړ�����
		cityPos[i].z += BACKGROUNDCITY_MOVE_SPEED;

		//�������ɉ������Ă�����őO��ֈړ�
		if (cityPos[i].z <= -100.0f)
			cityPos[i].z += 15000.0f;
	}
}

/**************************************
�`�揈��
***************************************/
void DrawBackGroundCity(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxWorld, mtxTranslate;
	D3DMATERIAL9 matDef;

	pDevice->GetMaterial(&matDef);

	for (int i = 0; i < BACKGROUNDCITY_NUM_MAX; i++)
	{
		D3DXMatrixIdentity(&mtxWorld);

		//Translate
		D3DXMatrixTranslation(&mtxTranslate, cityPos[i].x, cityPos[i].y, cityPos[i].z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

		pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
		meshContainer->Draw();

		pDevice->SetMaterial(&matDef);
	}
}