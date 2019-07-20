//=====================================
//
//�o�b�N�O���E���h�R���g���[������[BackGroundController.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "BackGroundController.h"
#include "BackGroundCity.h"

#include "Framework\ResourceManager.h"

using namespace std;

/**************************************
�}�N����`
***************************************/
#define BACKGROUND_CITY_KIND_MAX		(3)		//�w�i���f���̎��
#define BACKGROUND_CITY_NUMMAX_X		(6)		//
#define BACKGROUND_CITY_NUMMAX_Z		(16)	//

//�ǂݍ���X�t�@�C��
static const char* MeshFileName[] = {
	"data/MODEL/City/city01.x",
	"data/MODEL/City/city02.x",
	"data/MODEL/City/city03.x"
};

//�w�i���b�V���̃^�O
static const char* MeshTag[] = {
	"city01",
	"city02",
	"city03"
};

/**************************************
�R���X�g���N�^
***************************************/
BackGroundController::BackGroundController()
{
	//�w�i���f���ǂݍ���
	for (int i = 0; i < BACKGROUND_CITY_KIND_MAX; i++)
	{
		ResourceManager::Instance()->LoadMesh(MeshTag[i], MeshFileName[i]);
	}

	//CityContainer�쐬
	CreateCityContainer();
}

/**************************************
�f�X�g���N�^
***************************************/
BackGroundController::~BackGroundController()
{
	for (auto& city : cityContainer)
	{
		SAFE_DELETE(city);
	}
	cityContainer.clear();
}

/**************************************
����������
***************************************/
void BackGroundController::Init()
{
	for (auto& city : cityContainer)
	{
		city->Init();
	}
}

/**************************************
�I������
***************************************/
void BackGroundController::Uninit()
{
	for (auto& city : cityContainer)
	{
		city->Uninit();
	}
}

/**************************************
�X�V����
***************************************/
void BackGroundController::Update()
{
	for (auto& city : cityContainer)
	{
		city->Update();
	}
}

/**************************************
�`�揈��
***************************************/
void BackGroundController::Draw()
{
	for (auto& city : cityContainer)
	{
		city->Draw();
	}
}

/**************************************
�V�e�B�R���e�i�쐬����
***************************************/
void BackGroundController::CreateCityContainer()
{
	const float BasePosX = 1000.0f;
	const float OffsetX = 1200.0f;
	const float OffsetZ = 3000.0f;

	//�w�i��City���쐬
	cityContainer.resize(BACKGROUND_CITY_NUMMAX_X * BACKGROUND_CITY_NUMMAX_Z);
	for (auto& city : cityContainer)
	{
		int index = RandomRange(0, BACKGROUND_CITY_KIND_MAX);
		city = new BackGroundCity(MeshTag[index]);
	}

	//���葤��City���쐬
	int cityIndex = 0;
	for (int i = 0; i < BACKGROUND_CITY_NUMMAX_Z; i++)
	{
		for (int j = 0; j < BACKGROUND_CITY_NUMMAX_X / 2; j++)
		{
			cityContainer[cityIndex]->transform.pos.x = BasePosX + OffsetX * j;
			cityContainer[cityIndex]->transform.pos.z = OffsetZ * i;
			cityIndex++;
		}
	}

	//�E�葤��City���쐬
	for (int i = 0; i < BACKGROUND_CITY_NUMMAX_Z; i++)
	{
		for (int j = 0; j < BACKGROUND_CITY_NUMMAX_X / 2; j++)
		{
			cityContainer[cityIndex]->transform.pos.x = -BasePosX - OffsetX * j;
			cityContainer[cityIndex]->transform.pos.z = OffsetZ * i;
			cityIndex++;
		}
	}

	//City�̉��s���ő�l��ݒ�
	BackGroundCity::depthMaxZ = BACKGROUND_CITY_NUMMAX_Z * OffsetZ;
}