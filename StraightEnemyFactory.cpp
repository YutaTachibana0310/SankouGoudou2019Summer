//=====================================
//
//�X�g���[�g�G�l�~�[�t�@�N�g���[����[StraightEnemyFactory.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "StraightEnemyFactory.h"
#include "StraightEnemyModel.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�G�l�~�[��������
***************************************/
EnemyModel* StraightEnemyFactory::Create(picojson::object& data)
{
	//�C���X�^���X����
	StraightEnemyModel *model = new StraightEnemyModel();

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
void StraightEnemyFactory::CreateGuide(picojson::object& data, EnemyGuideArrowController* controller)
{
	//�f�[�^���p�[�X
	int start = static_cast<int>(data["start"].get<double>());
	int end = static_cast<int>(data["end"].get<double>());

	controller->SetEmitter(LineTrailModel(start, end));
}
