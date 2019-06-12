//=====================================
//
//�o�b�N�O���E���h�V�e�B����[BackGroundCity.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "BackGroundCity.h"
#include "Framework\InstancingMeshContainer.h"
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

#define BACKGROUNDCITY_LIGHT_AMPLIFIER	(2.2f)

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
static Transform cityTransform[BACKGROUNDCITY_NUM_MAX];
static InstancingMeshContainer* meshContainer;
static LPDIRECT3DVERTEXBUFFER9 transformBuffer;

/**************************************
�v���g�^�C�v�錾
***************************************/

/**************************************
����������
***************************************/
void InitBackGroundCity(int num)
{
	//�C���X�^���V���O�p�Ƀ��b�V�������[�h���ď�����
	meshContainer = new InstancingMeshContainer();
	meshContainer->Load(BACKGROUNDCITY_MODEL_FILE);
	meshContainer->SetLightAmplifier(BACKGROUNDCITY_LIGHT_AMPLIFIER);

	//Y���W�AZ���W�ɂ��ď�����
	for (int i = 0; i < BACKGROUNDCITY_NUM_MAX; i += BACKGROUNDCITY_KIND_MAX)
	{
		cityTransform[i].pos.y = BACKGROUNDCITY_BASEPOS_Y + RandomRangef(-BACKGROUNDCITY_POS_RANGE_Y, BACKGROUNDCITY_POS_RANGE_Y);

		for (int j = 0; j < BACKGROUNDCITY_KIND_MAX; j++)
		{
			cityTransform[i+j].pos.z = BACKGROUNDCITY_BASEPOS_Z + BACKGROUNDCITY_OFFSET_Z * (i / 2) + RandomRangef(-BACKGROUNDCITY_POS_RANGE_Z, BACKGROUNDCITY_POS_RANGE_Z);
		}
	}

	//X���W�ɂ��ď�����
	for (int i = 0; i < BACKGROUNDCITY_NUM_MAX; i += BACKGROUNDCITY_KIND_MAX)
	{
		cityTransform[i].pos.x = BACKGROUNDCITY_BASEPOS_X_INNER + RandomRangef(0.0f, BACKGROUNDCITY_POS_RANGE_X);
		cityTransform[i + 1].pos.x = -BACKGROUNDCITY_BASEPOS_X_INNER - RandomRangef(0.0f, BACKGROUNDCITY_POS_RANGE_X);
	}

	//�X�P�[���A��]����������
	Transform *ptr = cityTransform;
	for (int i = 0; i < BACKGROUNDCITY_NUM_MAX; i++, ptr++)
	{
		ptr->scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		ptr->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	//SRT���o�b�t�@���쐬
	MakeTransformBuffer(BACKGROUNDCITY_NUM_MAX, &transformBuffer);
}

/**************************************
�I������
***************************************/
void UninitBackGroundCity(int num)
{
	SAFE_RELEASE(transformBuffer);
	delete meshContainer;
}
/**************************************
�X�V����
***************************************/
void UpdateBackGroundCity(void)
{
	for (int i = 0; i < BACKGROUNDCITY_NUM_MAX; i++)
	{
		//�ړ�����
		cityTransform[i].pos.z += BACKGROUNDCITY_MOVE_SPEED;

		//�������ɉ������Ă�����őO��ֈړ�
		if (cityTransform[i].pos.z <= -100.0f)
			cityTransform[i].pos.z += 15000.0f;
	}

	//SRT�����o�b�t�@�փZ�b�g
	CopyVtxBuff(sizeof(cityTransform), cityTransform, transformBuffer);
}

/**************************************
�`�揈��
***************************************/
void DrawBackGroundCity(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	
	//�X�g���[���\�[�X�ݒ�
	meshContainer->SetStreamSource(transformBuffer, BACKGROUNDCITY_NUM_MAX);

	//�`��
	meshContainer->Draw();
}