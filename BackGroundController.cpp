//=====================================
//
//�o�b�N�O���E���h�R���g���[������[BackGroundController.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "BackGroundController.h"
#include "BackGroundCity.h"
#include "SkyBox.h"

#include "Framework\ResourceManager.h"
#include "Framework\Easing.h"

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

#define BACKGROUND_SCROOLSPEED_INIT			(-75.0f)
#define BACKGROUND_ACCEL_DURATION			(30)
#define BACKGROUND_DAMPER_DURATION			(120)
#define BACKGROUND_ACCEL_MAGNI				(5.0f)

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

	//�X�J�C�{�b�N�X�쐬
	skyBoxies.push_back(new SkyBox(D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f), D3DXVECTOR2(6.0f, 6.0f)));
	skyBoxies[0]->LoadTexture("data/TEXTURE/BG/img_post152_07.jpg");

	//Transform������
	transform.Rotate(3.0f, 0.0f, 0.0f);

	//�X�N���[�����x������
	scroolSpeed = BACKGROUND_SCROOLSPEED_INIT;
	startSpeed = endSpeed = scroolSpeed;
	cntChangeSpeed = 0;
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

	for (auto& skybox : skyBoxies)
	{
		SAFE_DELETE(skybox);
	}
	skyBoxies.clear();
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
#include "debugWindow.h"
/**************************************
�X�V����
***************************************/
void BackGroundController::Update()
{
	DebugLog("speed : %f", scroolSpeed);
	//�X�N���[���X�s�[�h���C�[�W���O
	if (cntChangeSpeed > 0)
	{
		if (cntChangeSpeed > BACKGROUND_DAMPER_DURATION)
			AccelScrollSpeed();
		else
			DampScrollSpeed();
	}

	//�������X�V
	for (auto& city : cityContainer)
	{
		city->Update(scroolSpeed);
	}
}

/**************************************
�`�揈��
***************************************/
void BackGroundController::Draw()
{
	for (auto& box : skyBoxies)
	{
		box->Draw();
	}

	D3DXMATRIX mtxWorld = transform.GetMatrix();
	for (auto& city : cityContainer)
	{
		city->Draw(mtxWorld);
	}
}

/**************************************
�V�e�B�R���e�i�쐬����
***************************************/
void BackGroundController::CreateCityContainer()
{
	const float BasePosX = 2000.0f;
	const float OffsetX = 3000.0f;
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

/**************************************
�X�N���[���X�s�[�h�ω�����
***************************************/
void BackGroundController::AddScrollSpeed(float add)
{
	endSpeed += add;

	if (cntChangeSpeed > BACKGROUND_DAMPER_DURATION)
		return;

	startSpeed = scroolSpeed;
	cntChangeSpeed = BACKGROUND_ACCEL_DURATION + BACKGROUND_DAMPER_DURATION;
}

/**************************************
�X�N���[���X�s�[�h����������
***************************************/
void BackGroundController::InitScroolSpeed()
{
	endSpeed = BACKGROUND_SCROOLSPEED_INIT;

	if (cntChangeSpeed != 0)
		return;

	startSpeed = scroolSpeed;
	cntChangeSpeed = BACKGROUND_DAMPER_DURATION;
}

/**************************************
�X�N���[���X�s�[�h��������
***************************************/
void BackGroundController::AccelScrollSpeed()
{
	cntChangeSpeed--;
	float t = 1.0f - (float)(cntChangeSpeed - BACKGROUND_DAMPER_DURATION) / BACKGROUND_ACCEL_DURATION;
	scroolSpeed = Easing::EaseValue(t, startSpeed, BACKGROUND_ACCEL_MAGNI * endSpeed, EaseType::OutCubic);

	if (cntChangeSpeed == BACKGROUND_DAMPER_DURATION)
		startSpeed = BACKGROUND_ACCEL_MAGNI * endSpeed;
}

/**************************************
�X�N���[���X�s�[�h��������
***************************************/
void BackGroundController::DampScrollSpeed()
{
	cntChangeSpeed--;
	float t = 1.0f - (float)(cntChangeSpeed - BACKGROUND_ACCEL_DURATION) / BACKGROUND_DAMPER_DURATION;
	scroolSpeed = Easing::EaseValue(t, startSpeed, endSpeed, EaseType::InOutExpo);

	if (cntChangeSpeed == 0)
		startSpeed = endSpeed;
}