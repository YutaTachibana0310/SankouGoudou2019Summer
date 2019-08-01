//=====================================
//
//�e���v���[�g����[SnakeEnemyFactory.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "SnakeEnemyFactory.h"
#include "SnakeEnemyModel.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�G�l�~�[��������
***************************************/
EnemyModel * SnakeEnemyFactory::Create(picojson::object & data)
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

	return model;
}

/**************************************
�K�C�h��������
***************************************/
void SnakeEnemyFactory::CreateGuide(picojson::object & data, EnemyGuideArrowController * controller)
{
	//�z��f�[�^���p�[�X
	picojson::array dataList = data["destList"].get<picojson::array>();

	//�e�f�[�^�����ꂼ��p�[�X
	vector<int> destList;
	destList.resize(dataList.size());
	for (UINT i = 0; i < dataList.size(); i++)
	{
		destList[i] = static_cast<int>(dataList[i].get<picojson::object>()["dest"].get<double>());
	}

	//destList����K�C�h�̐�����\��
	for (UINT i = 0; i < destList.size() - 1; i++)
	{
		controller->Reserve(i * ENEMYGUIDEARROW_DURATION, LineTrailModel(destList[i], destList[i + 1]));
	}
}
