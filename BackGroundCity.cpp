//=====================================
//
//�o�b�N�O���E���h�V�e�B����[BackGroundCity.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "BackGroundCity.h"
#include "Framework\InstancingMeshContainer.h"
#include "SkyBox.h"

#include <vector>
#include <map>
#include <array>

using namespace std;

/**************************************
�}�N����`
***************************************/
#define BACKGROUNDCITY_KIND_MAX			(3)

#define BACKGROUNDCITY_Z_MAX			(24)
#define BACKGROUNDCITY_X_MAX			(16)
#define BACKGROUNDCITY_NUM_MAX			(BACKGROUNDCITY_Z_MAX*BACKGROUNDCITY_X_MAX)

#define BACKGROUNDCITY_MOVE_SPEED		(-25.0f)

#define BACKGROUNDCITY_LIGHT_AMPLIFIER	(2.2f)

#define BACKGROUNDCITY_OFFSET_X			(-600.0f)
#define BACKGROUNDCITY_OFFSET_Z			(-600.0f)

//�ǂݍ���X�t�@�C���ւ̃p�X
static const char* fileName[] = {
	"data/MODEL/City/city01.x",
	"data/MODEL/City/city02.x",
	"data/MODEL/City/city03.x"
};

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
static InstancingMeshContainer* meshContainer[BACKGROUNDCITY_KIND_MAX];
static Transform* transformList[BACKGROUNDCITY_KIND_MAX];
static int cityTypeCount[BACKGROUNDCITY_KIND_MAX];
static LPDIRECT3DVERTEXBUFFER9 transformBuffer[BACKGROUNDCITY_KIND_MAX];

/**************************************
�v���g�^�C�v�錾
***************************************/
void MakeCityPositionMap(void);

/**************************************
����������
***************************************/
void InitBackGroundCity(int num)
{
	//�C���X�^���V���O�p�Ƀ��b�V�������[�h���ď�����
	for (int i = 0; i < BACKGROUNDCITY_KIND_MAX; i++)
	{
		meshContainer[i] = new InstancingMeshContainer();
		meshContainer[i]->Load(fileName[i]);
		meshContainer[i]->SetLightAmplifier(BACKGROUNDCITY_LIGHT_AMPLIFIER);
	}

	//���W�}�b�v�쐬
	MakeCityPositionMap();

	//SRT���o�b�t�@���쐬
	for (int i = 0; i < BACKGROUNDCITY_KIND_MAX; i++)
	{
		MakeTransformBuffer(cityTypeCount[i], &transformBuffer[i]);
	}
}

/**************************************
�I������
***************************************/
void UninitBackGroundCity(int num)
{
	for (int i = 0; i < BACKGROUNDCITY_KIND_MAX; i++)
	{
		SAFE_DELETE_ARRAY(transformList[i]);
		SAFE_RELEASE(transformBuffer[i]);
		delete meshContainer[i];
	}
}

/**************************************
�X�V����
***************************************/
void UpdateBackGroundCity(void)
{
	for (int i = 0; i < BACKGROUNDCITY_KIND_MAX; i++)
	{
		for (int j = 0; j < cityTypeCount[i]; j++)
		{
			//�ړ�����
			transformList[i][j].pos.z += BACKGROUNDCITY_MOVE_SPEED;

			//�������ɉ������Ă�����őO��ֈړ�
			if (transformList[i][j].pos.z <= -100.0f)
				transformList[i][j].pos.z += -BACKGROUNDCITY_OFFSET_Z * BACKGROUNDCITY_Z_MAX;
		}

		//SRT�����o�b�t�@�փZ�b�g
		CopyVtxBuff(sizeof(Transform) * cityTypeCount[i], &transformList[i][0], transformBuffer[i]);
	}

}

/**************************************
�`�揈��
***************************************/
void DrawBackGroundCity(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int i = 0; i < BACKGROUNDCITY_KIND_MAX; i++)
	{
		//�X�g���[���\�[�X�ݒ�
		meshContainer[i]->SetStreamSource(transformBuffer[i], cityTypeCount[i]);

		//�`��
		meshContainer[i]->Draw();
	}
}

/**************************************
���W�}�b�v�쐬����
***************************************/
void MakeCityPositionMap(void)
{
	array<D3DXVECTOR3, BACKGROUNDCITY_NUM_MAX> posMap;

	int maxX = BACKGROUNDCITY_X_MAX;
	int maxZ = BACKGROUNDCITY_Z_MAX;

	//��Տ�ɍ��W�}�b�v�쐬
	float offsetZ = BACKGROUNDCITY_OFFSET_Z, offsetX = BACKGROUNDCITY_OFFSET_X;
	float basePosX = -offsetX * maxX / 2;
	float basePosZ = -offsetZ * maxZ;
	for (int z = 0; z < maxZ; z++)
	{
		for (int x = 0; x < maxX; x++)
		{
			posMap[z * maxX + x].x = basePosX + offsetX * x;
			posMap[z * maxX + x].z = basePosZ + offsetZ * z;
		}
	}

	//���W�}�b�v�Ƀ����_���Ƀr���^�C�v�����蓖��
	ZeroMemory(cityTypeCount, sizeof(cityTypeCount));
	for (auto itr = posMap.begin(); itr != posMap.end(); itr++)
	{
		//���S�����͋󂯂�
		if (fabsf(itr->x) < 500.0f)
		{
			itr->y = (float)BACKGROUNDCITY_KIND_MAX;
			continue;
		}

		int type = RandomRange(0, BACKGROUNDCITY_KIND_MAX);
		itr->y = (float)type;
		cityTypeCount[type]++;
	}

	//�e�^�C�v��posList�փR�s�[
	for (int i = 0; i < BACKGROUNDCITY_KIND_MAX; i++)
	{
		transformList[i] = new Transform[cityTypeCount[i]];
	}
	int index[BACKGROUNDCITY_KIND_MAX] = {};
	for (auto itr = posMap.begin(); itr != posMap.end(); itr++)
	{
		if (itr->y == (float)BACKGROUNDCITY_KIND_MAX)
			continue;

		Transform tr = { D3DXVECTOR3(itr->x, 0.0f, itr->z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f) };
		int type = (int)itr->y;
		transformList[type][index[type]] = tr;
		index[type]++;
	}
}