//=====================================
//
//�G�l�~�[�R���g���[���[����[EnemyController.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "EnemyController.h"
#include "TestEnemyModel.h"
#include "ChangeEnemyModel.h"
#include "StraightEnemyModel.h"

#include "Framework\ResourceManager.h"
#include "picojson\picojson.h"

#include <algorithm>
#include <fstream>

using namespace std;

/**************************************
�}�N����`
***************************************/
#define USE_DEBUG_TESTENEMY (0)

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
EnemyController::EnemyController()
{
	//���\�[�X�ǂݍ���
	//����̓V�[���I������Game.cpp�ňꊇ���ĊJ������
	ResourceManager::Instance()->LoadMesh("Enemy", "data/MODEL/airplane000.x");

	//�X�e�[�W�f�[�^�ǂݍ���
	LoadStageData();
}

/**************************************
�f�X�g���N�^
***************************************/
EnemyController::~EnemyController()
{
	//���f���R���e�i�N���A
	for (auto &model : modelList)
	{
		SAFE_DELETE(model);
	}
	modelList.clear();

	//�X�e�[�W�f�[�^�N���A
	stageModelList.clear();

	//�e�X�g�p�G�l�~�[��delete����
	SAFE_DELETE(test);
}

/**************************************
����������
***************************************/
void EnemyController::Init()
{
	cntFrame = 0;

	//�V�������Enemy�̏������e�X�g�͂����ɏ���
#if USE_DEBUG_TESTENEMY
	//test
	test = new EnemySnake;
	std::vector<D3DXVECTOR3> posDestList;
	posDestList.push_back(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	posDestList.push_back(D3DXVECTOR3(50.0f, 0.0f, 0.0f));
	posDestList.push_back(D3DXVECTOR3(0.0f, 50.0f, 0.0f));
	posDestList.push_back(D3DXVECTOR3(0.0f, 0.0f, 50.0f));
	posDestList.push_back(D3DXVECTOR3(50.0f, 0.0f, 0.0f));
	posDestList.push_back(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	vector<float> frameDestList;
	frameDestList.push_back(50.0f);
	frameDestList.push_back(100.0f);
	frameDestList.push_back(200.0f);
	frameDestList.push_back(300.0f);
	frameDestList.push_back(400.0f);
	test->VInit();
	test->Set(posDestList, frameDestList, 50.0f);
#endif
}

/**************************************
�I������
***************************************/
void EnemyController::Uninit()
{
	for (auto &model : modelList)
	{
		model->Uninit();
	}

	//�V�������Enemy�̏I���e�X�g�͂����ɏ���
#if USE_DEBUG_TESTENEMY
	test->VUninit();
#endif
}

/**************************************
�X�V����
***************************************/
void EnemyController::Update()
{
	//�V�������Enemy�̍X�V�e�X�g�͂����ɏ���
#if USE_DEBUG_TESTENEMY
	test->VUpdate();
#endif

	//���f���X�V����
	for (auto &model : modelList)
	{
		model->Update();
	}

	//�I���������f�����폜����
	for (auto& model : modelList)
	{
		if (!model->active)
			SAFE_DELETE(model);
	}

	//�폜�������f�������X�g����폜
	modelList.remove_if([](EnemyModel* model)
	{
		return model == nullptr;
	});
}

/**************************************
�`�揈��
***************************************/
void EnemyController::Draw()
{
	//�G�l�~�[���f���`��
	for (auto &model : modelList)
	{
		model->Draw();
	}

	//�V�������Enemy�̕`��e�X�g�͂����ɏ���
#if USE_DEBUG_TESTENEMY
	test->VDraw();
#endif
}

/**************************************
�G�l�~�[�����C���^�[�t�F�[�X
***************************************/
void EnemyController::SetEnemy()
{
	cntFrame++;

	//���݂̃C���f�b�N�X����X�e�[�W�f�[�^���m�F���Ă���
	for (UINT i = currentIndex; i < stageModelList.size(); i++)
	{
		//�����^�C�~���O�O�ł����break
		if (cntFrame < stageModelList[i].frame)
			break;

		if (stageModelList[i].type == "Change")
			_SetEnemyChange(stageModelList[i].data);

		currentIndex++;
	}
}

/**************************************
�G�l�~�[���������i���f���Łj
***************************************/
void EnemyController::_SetEnemyChange(picojson::object& data)
{
	//�C���X�^���X����
	EnemyModel *model = new StraightEnemyModel();

	//�f�[�^���p�[�X
	int start = static_cast<int>(data["start"].get<double>());
	int end = static_cast<int>(data["end"].get<double>());

	//������
	model->Init(LineTrailModel(start, end));

	modelList.push_back(model);
}

/**************************************
�X�e�[�W�f�[�^�ǂݍ��ݏ���
***************************************/
bool EnemyController::LoadStageData()
{
	//JSON�t�@�C�����J��
	ifstream ifs;
	ifs.open("data/JSON/test.json", std::ios::binary);

	//�����m�F
	if (!ifs.is_open())
		return false;

	//JSON�f�[�^��ǂݍ���
	picojson::value val;
	ifs >> val;
	ifs.close();

	//�f�[�^�z����p�[�X����
	picojson::array& dataList = val.get<picojson::object>()["StageData"].get<picojson::array>();

	//�f�[�^��1��1�p�[�X����StageModel���쐬����
	stageModelList.resize(dataList.size());
	for (UINT i = 0; i < dataList.size(); i++)
	{
		int frame = static_cast<int>(dataList[i].get<picojson::object>()["frame"].get<double>());
		string type = dataList[i].get<picojson::object>()["type"].get<string>();
		picojson::object data = dataList[i].get<picojson::object>()["data"].get<picojson::object>();

		stageModelList[i] = StageModel(frame, type, data);
	}

	//�C���f�b�N�X������
	currentIndex = 0;

	return true;
}