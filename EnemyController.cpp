//=====================================
//
//�G�l�~�[�R���g���[���[����[EnemyController.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "EnemyController.h"
#include "TestEnemyModel.h"
#include "ChangeEnemyModel.h"

#include "Framework\ResourceManager.h"
#include "picojson\picojson.h"

#include <algorithm>
#include <fstream>

using namespace std;

/**************************************
�}�N����`
***************************************/

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
}

/**************************************
����������
***************************************/
void EnemyController::Init()
{
	cntFrame = 0;
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
}

/**************************************
�X�V����
***************************************/
void EnemyController::Update()
{
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

		if(stageModelList[i].type == "Change")
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
	EnemyModel *model = new ChangeEnemyModel();

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