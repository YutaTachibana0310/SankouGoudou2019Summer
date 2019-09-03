//=====================================
//
//�`�F���W�G�l�~�[�t�@�N�g���[����[ChangeEnemyFactory.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "ChangeEnemyFactory.h"
#include "ChangeEnemyModel.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�G�l�~�[��������
***************************************/
EnemyModel* ChangeEnemyFactory::Create(picojson::object& data)
{
	//�C���X�^���X����
	ChangeEnemyModel *model = new ChangeEnemyModel();

	//�f�[�^���p�[�X
	int start = static_cast<int>(data["start"].get<double>());
	int end = static_cast<int>(data["end"].get<double>());
	LineTrailModel lineModel = LineTrailModel(start, end);

	//��������G�l�~�[�̐�������(�܊p�`�̊O���Ȃ�3�́A����ȊO��5��)
	auto itr = find(EnemyModel::OuterLineModel.begin(), EnemyModel::OuterLineModel.end(), lineModel);
	int enemyNum = itr != EnemyModel::OuterLineModel.end() ? ENEMY_NUM_OUTERLINE : ENEMY_NUM_INNNERLINE;

	//������
	model->Init(lineModel, enemyNum);

	return model;
}

/**************************************
�K�C�h��������
***************************************/
void ChangeEnemyFactory::CreateGuide(picojson::object& data, EnemyGuideArrowController* controller)
{
	//�f�[�^���p�[�X
	int start = static_cast<int>(data["start"].get<double>());
	int end = static_cast<int>(data["end"].get<double>());

	controller->SetEmitter(LineTrailModel(start, end));
}
