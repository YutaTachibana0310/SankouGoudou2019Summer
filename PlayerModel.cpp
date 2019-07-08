//=====================================
//
//�v���C���[���f������[PlayerModel.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "PlayerModel.h"
#include "starUI.h"

using namespace std;

/**************************************
�}�N����`
***************************************/
#define PLAYERMODEL_JUDGSTACK_LENGTH	(5)
#define PLAYERMODEL_MOVEQUEUE_LENGTH	(6)		//�ړ������̍ő�ۑ�����

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
PlayerModel::PlayerModel()
{
	//��M�����̐�����ݒ�
	Judgement.resize(PLAYERMODEL_JUDGSTACK_LENGTH);
	Judgement[0] = TOP;
	Judgement[1] = LOWER_LEFT;
	Judgement[2] = MIDDLE_RIGHT;
	Judgement[3] = MIDDLE_LEFT;
	Judgement[4] = LOWER_RIGHT;
}

/**************************************
�f�X�g���N�^
***************************************/
PlayerModel::~PlayerModel()
{
	Judgement.clear();
	inputHistory.clear();
	queue<int>().swap(inputQueue);
}

/**************************************
��s���͂̕ۑ�
***************************************/
void PlayerModel::PushInput(int num)
{
	inputQueue.push(num);
}

/**************************************
�ړ������̃v�b�V��
***************************************/
void PlayerModel::PushMoveStack(int num)
{
	//�ő吔�ł���Έ�ԌÂ��������폜
	if (inputHistory.size() == PLAYERMODEL_MOVEQUEUE_LENGTH)
		inputHistory.pop_front();

	//�v�b�V��
	inputHistory.push_back(num);
}

/**************************************
��s���͂̊m�F
***************************************/
bool PlayerModel::IsExistPrecedInput(int *res)
{
	if (inputQueue.size() == 0)
		return false;

	*res = inputQueue.front();
	inputQueue.pop();
	return true;
}

/**************************************
��M�����̔���
***************************************/
bool PlayerModel::CheckOneStroke()
{
	//��M�����̉搔�ɑ���Ă��Ȃ���΃��^�[��
	if (inputHistory.size() < PLAYERMODEL_MOVEQUEUE_LENGTH)
		return false;

	//��M�����̊J�n�ʒu�̃C���f�b�N�X������
	auto itrStart = find(Judgement.begin(), Judgement.end(), inputHistory.back());
	size_t startIndex = distance(Judgement.begin(), itrStart);

	//�����v���Ō���
	bool res = _CheckOneStroke(startIndex);

	//�������Ă����烊�^�[��
	if (res)
		return true;

	//����p�z����t�]�����J�n�ʒu������
	reverse(Judgement.begin(), Judgement.end());
	itrStart = find(Judgement.begin(), Judgement.end(), inputHistory.back());
	startIndex = distance(Judgement.begin(), itrStart);

	//���v���Ō���
	res = _CheckOneStroke(startIndex);

	//����p�z������ɖ߂��ă��^�[��	
	reverse(Judgement.begin(), Judgement.end());
	return res;
}

/**************************************
�����N���A
***************************************/
void PlayerModel::Clear()
{
	inputHistory.clear();
	queue<int>().swap(inputQueue);
}

/**************************************
��M��������i�����j
***************************************/
bool PlayerModel::_CheckOneStroke(size_t start)
{
	for (int i = 0; i < PLAYERMODEL_MOVEQUEUE_LENGTH; i++)
	{
		//�Ώۂ̃C���f�b�N�X���v�Z
		int checkIndex = WrapAround(0, PLAYERMODEL_JUDGSTACK_LENGTH, start + i);

		//����p�z��ƈړ��������������Ă����return false
		if (Judgement[checkIndex] != inputHistory[i])
			return false;
	}

	//��M�����ƈ�v����̂ŗ������N���A����return true
	//���̔���p�ɍŌ�̗����̓v�b�V�����Ă���
	int lastMove = inputHistory.back();
	inputHistory.clear();
	inputHistory.push_back(lastMove);
	return true;
}

/**************************************
����1���̋O�Ղ̎擾
***************************************/
bool PlayerModel::GetPlayerTrail(LineTrailModel *pOut)
{
	int queSize = inputHistory.size();
	if (queSize < 2)
		return false;
	
	*pOut = LineTrailModel(inputHistory[queSize - 1], inputHistory[queSize - 2]);
	return true;
}

/**************************************
�S�O�Ղ̎擾
***************************************/
size_t PlayerModel::GetAllPlayerTrail(vector<LineTrailModel> *container)
{
	if (inputHistory.size() < 2)
		return 0;

	int modelCount = inputHistory.size() - 1;
	container->clear();
	container->resize(modelCount);

	for (int i = 0; i < modelCount; i++)
	{
		container->push_back(LineTrailModel(inputHistory[i + 1], inputHistory[i]));
	}

	return modelCount;
}