//=====================================
//
//�G�l�~�[�R���g���[���[����[EnemyController.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "EnemyController.h"
#include "TestEnemyModel.h"
#include "ChangeEnemyFactory.h"
#include "StraightEnemyFactory.h"
#include "SnakeEnemyFactory.h"
#include "EnemyBullet.h"
#include "GameParticleManager.h"

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

#define ENEMY_SHOTPOS_OFFSET	(D3DXVECTOR3(0.0f, 0.0f, -50.0f))
#define ENEMY_GUIDE_TIMING		(10)

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
	ResourceManager::Instance()->LoadMesh("Enemy", "data/MODEL/Enemy/drone.x");

	//�e�R���g���[���쐬
	bulletController = new EnemyBulletController();
	guideController = new EnemyGuideArrowController();

	//�e�t�@�N�g���[�쐬
	factoryContainer["Change"] = new ChangeEnemyFactory();
	factoryContainer["Straight"] = new StraightEnemyFactory();
	factoryContainer["Snake"] = new SnakeEnemyFactory();

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
	
	//�e�R���g���[���폜
	SAFE_DELETE(bulletController);
	SAFE_DELETE(guideController);

	//�e�t�@�N�g���[�폜
	for (auto& pair : factoryContainer)
	{
		SAFE_DELETE(pair.second);
	}
	factoryContainer.clear();

	//�X�e�[�W�f�[�^�N���A
	stageModelList.clear();
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

#endif

	//���f���X�V����
	for (auto &model : modelList)
	{
		int updateResult = model->Update();

		if (updateResult == AttackTiming)
			EnemyAttack(model);
		else if (updateResult == ChargeTiming)
			SetChageEffect(model);
	}

	//�o���b�g�X�V����
	bulletController->Update();

	//�K�C�h�X�V����
	guideController->Update();

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
�K�C�h�`�揈��
***************************************/
void EnemyController::DrawGuide()
{
	guideController->Draw();
}

/**************************************
�G�l�~�[�����C���^�[�t�F�[�X
***************************************/
void EnemyController::SetEnemy()
{
	cntFrame++;

	//�K�C�h����
	SetGuide();

	//���݂̃C���f�b�N�X����X�e�[�W�f�[�^���m�F���Ă���
	for (UINT i = currentIndex; i < stageModelList.size(); i++)
	{
		//�����^�C�~���O�O�ł����break
		if (cntFrame < stageModelList[i].frame)
			break;

		//type�ɉ����Đ����������f�B�X�p�b�`
		string type = stageModelList[i].type;
		EnemyModel* model = factoryContainer[type]->Create(stageModelList[i].data);
		modelList.push_back(model);

		currentIndex++;
	}
}

/**************************************
�K�C�h��������
***************************************/
void EnemyController::SetGuide()
{
	//���݂̃C���f�b�N�X����f�[�^���m�F���Ă���
	for (UINT i = currentIndex; i < stageModelList.size(); i++)
	{
		//�K�C�h�^�C�~���O�łȂ����Continue
		if (cntFrame + ENEMY_GUIDE_TIMING != stageModelList[i].frame)
			continue;

		//�K�C�h�^�C�~���O���x���f�[�^��������break
		if (cntFrame + ENEMY_GUIDE_TIMING < stageModelList[i].frame)
			break;

		//�K�C�h����
		string type = stageModelList[i].type;
		factoryContainer[type]->CreateGuide(stageModelList[i].data, guideController);
	}
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

/**************************************
�G�l�~�[�U������
***************************************/
void EnemyController::EnemyAttack(EnemyModel *enermyModel)
{
	vector<D3DXVECTOR3> emitPos;
	emitPos.reserve(enermyModel->enemyList.size());

	for (auto& enemy : enermyModel->enemyList)
	{
		emitPos.push_back(enemy->m_Pos + ENEMY_SHOTPOS_OFFSET);
	}

	bulletController->SetEnemyBullet(emitPos, enermyModel->model);
}

/**************************************
�G�l�~�[�U���`���[�W�J�n����
***************************************/
void EnemyController::SetChageEffect(EnemyModel *model)
{
	model->chageEffectList.clear();
	model->chageEffectList.resize(model->enemyList.size());

	UINT cntSet = 0;
	for (auto& enemey : model->enemyList)
	{
		BaseEmitter* emitter = GameParticleManager::Instance()->SetEnemyBulletCharge(&(enemey->m_Pos + ENEMY_SHOTPOS_OFFSET));
		model->chageEffectList[cntSet] = emitter;
		cntSet++;
	}
}

/**************************************
�G�l�~�[���W�擾����
***************************************/
void EnemyController::GetEnemyPositionList(vector<D3DXVECTOR3>& out)
{
	for (auto& model : modelList)
	{
		model->GetEnemyPosition(out);
	}
}

/**************************************
�{���o�[�V�[�P���X�R�[���o�b�N
***************************************/
void EnemyController::OnFinishBombSequence()
{
	bulletController->DisableAll();
}