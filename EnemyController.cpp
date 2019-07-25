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
#include "SnakeEnemyModel.h"
#include "EnemyBullet.h"

#include "Framework\ResourceManager.h"
#include "picojson\picojson.h"
#include "debugWindow.h"

#include <algorithm>
#include <fstream>

using namespace std;

/**************************************
�}�N����`
***************************************/
#define USE_DEBUG_TESTENEMY (1)

#define ENEMY_NUM_OUTERLINE		(3)		//�܊p�`�̊O���ɐ�������G�l�~�[�̐�
#define ENEMY_NUM_INNNERLINE	(5)		//�܊p�`�̓����ɐ�������G�l�~�[�̐�

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
//�܊p�`�̊O�����\������LineModel
const vector<LineTrailModel> EnemyController::OuterLineModel = {
	LineTrailModel(0, 1),
	LineTrailModel(1, 2),
	LineTrailModel(2, 3),
	LineTrailModel(3, 4),
	LineTrailModel(4, 0)
};

/**************************************
�R���X�g���N�^
***************************************/
EnemyController::EnemyController()
{
	//���\�[�X�ǂݍ���
	//����̓V�[���I������Game.cpp�ňꊇ���ĊJ������
	ResourceManager::Instance()->LoadMesh("Enemy", "data/MODEL/Enemy/drone.x");

	//�o���b�g�R���g���[���쐬
	bulletController = new EnemyBulletController();

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
	
	//�o���b�g�R���g���[���폜
	SAFE_DELETE(bulletController);

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

	bulletController->Uninit();

	//�V�������Enemy�̏I���e�X�g�͂����ɏ���
#if USE_DEBUG_TESTENEMY

#endif
}

/**************************************
�X�V����
***************************************/
void EnemyController::Update()
{
	//�V�������Enemy�̍X�V�e�X�g�͂����ɏ���
#if USE_DEBUG_TESTENEMY
	BeginDebugWindow("Console");
	if (DebugButton("EnemyBullet"))
	{
		vector<D3DXVECTOR3> tmpVector;
		tmpVector.resize(5, D3DXVECTOR3(0.0f, 0.0f, 300.0f));
		bulletController->SetEnemyBullet(tmpVector, LineTrailModel(0, 1));
	}
	EndDebugWindow("Console");
#endif

	//���f���X�V����
	for (auto &model : modelList)
	{
		model->Update();
	}

	//�o���b�g�X�V����
	bulletController->Update();

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

	//�o���b�g�`��
	bulletController->Draw();

	//�V�������Enemy�̕`��e�X�g�͂����ɏ���
#if USE_DEBUG_TESTENEMY

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

		//type�ɉ����Đ����������f�B�X�p�b�`
		if (stageModelList[i].type == "Change")
			_SetEnemyChange(stageModelList[i].data);

		else if (stageModelList[i].type == "Straight")
			_SetEnemyStraight(stageModelList[i].data);

		else if (stageModelList[i].type == "Snake")
			_SetEnemySnake(stageModelList[i].data);

		currentIndex++;
	}
}

/**************************************
�G�l�~�[���������iChange�^�C�v�j
***************************************/
void EnemyController::_SetEnemyChange(picojson::object& data)
{
	//�C���X�^���X����
	ChangeEnemyModel *model = new ChangeEnemyModel();

	//�f�[�^���p�[�X
	int start = static_cast<int>(data["start"].get<double>());
	int end = static_cast<int>(data["end"].get<double>());
	LineTrailModel lineModel = LineTrailModel(start, end);

	//��������G�l�~�[�̐�������(�܊p�`�̊O���Ȃ�3�́A����ȊO��5��)
	auto itr = find(OuterLineModel.begin(), OuterLineModel.end(), lineModel);
	int enemyNum = itr != OuterLineModel.end() ? ENEMY_NUM_OUTERLINE : ENEMY_NUM_INNNERLINE;

	//������
	model->Init(lineModel, enemyNum);

	modelList.push_back(model);
}

/**************************************
�G�l�~�[���������iStraight�^�C�v�j
***************************************/
void EnemyController::_SetEnemyStraight(picojson::object& data)
{
	//�C���X�^���X����
	StraightEnemyModel *model = new StraightEnemyModel();

	//�f�[�^���p�[�X
	int start = static_cast<int>(data["start"].get<double>());
	int end = static_cast<int>(data["end"].get<double>());
	LineTrailModel lineModel = LineTrailModel(start, end);

	//��������G�l�~�[�̐�������(�܊p�`�̊O���Ȃ�3�́A����ȊO��5��)
	auto itr = find(OuterLineModel.begin(), OuterLineModel.end(), lineModel);
	int enemyNum = itr != OuterLineModel.end() ? ENEMY_NUM_OUTERLINE : ENEMY_NUM_INNNERLINE;

	//������
	model->Init(lineModel, enemyNum);

	modelList.push_back(model);
}

/**************************************
�G�l�~�[���������iSnake�^�C�v�j
***************************************/
void EnemyController::_SetEnemySnake(picojson::object& data)
{
	//�C���X�^���X����
	SnakeEnemyModel *model = new SnakeEnemyModel();

	//�z��f�[�^���p�[�X
	picojson::array dataList = data["destList"].get<picojson::array>();

	//�e�f�[�^�����ꂼ��p�[�X
	vector<int> destList;
	destList.resize(dataList.size());
	for (UINT i = 0; i < dataList.size(); i++)
	{
		destList[i] = static_cast<int>(dataList[i].get<picojson::object>()["dest"].get<double>());
	}

	//������
	model->Init(destList);

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