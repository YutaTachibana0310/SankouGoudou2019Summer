//=====================================
//
//MidiumeEnemyFactory.cpp
//�@�\:���^�G�l�~�[���쐬����t�@�N�g���N���X
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "MidiumEnemyFactory.h"
#include "MidiumEnemyModel.h"

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�G�l�~�[�쐬�֐�
***************************************/
EnemyModel * MidiumEnemyFactory::Create(picojson::object & data)
{
	//�C���X�^���X����
	MidiumEnemyModel *model = new MidiumEnemyModel();

	//�z��f�[�^���p�[�X
	picojson::array dataList = data["dataList"].get<picojson::array>();

	//�e�f�[�^�����ꂼ��p�[�X
	vector<LineTrailModel> modelList;
	modelList.resize(dataList.size());
	for (UINT i = 0; i < dataList.size(); i++)
	{
		int start = static_cast<int>(dataList[i].get<picojson::object>()["start"].get<double>());
		int end = static_cast<int>(dataList[i].get < picojson::object>()["end"].get<double>());
		modelList.push_back(LineTrailModel(start, end));
	}

	//������
	model->Init(modelList);

	return model;
}

/**************************************
�K�C�h�쐬�֐�
***************************************/
void MidiumEnemyFactory::CreateGuide(picojson::object & data, EnemyGuideArrowController * container)
{
	//�z��f�[�^���p�[�X
	picojson::array dataList = data["dataList"].get<picojson::array>();

	//�ŏ��̃��C���ɃK�C�h����
	int start = static_cast<int>(dataList[0].get<picojson::object>()["start"].get<double>());
	int end = static_cast<int>(dataList[0].get < picojson::object>()["end"].get<double>());
	container->SetEmitter(LineTrailModel(start, end));
}
