//=====================================
//
//�X�e�[�W���f���w�b�_[StageModel.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _STAGEMODEL_H_
#define _STAGEMODEL_H_

#include "main.h"
#include "picojson\picojson.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
class StageModel
{
public:
	int frame;					//���t���[���ڂɐ�������邩
	std::string type;			//��������G�l�~�[�̃^�C�v
	picojson::object data;		//�G�l�~�[�f�[�^

	StageModel(int frame, std::string type, picojson::object data)
	{
		this->frame = frame;
		this->type = type;
		this->data = data;
	}

	StageModel()
	{

	}

	~StageModel()
	{

	}
};

#endif