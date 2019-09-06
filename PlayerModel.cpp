//=====================================
//
//�v���C���[���f������[PlayerModel.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "PlayerModel.h"
#include "starButtonUI.h"
#include "ScoreManager.h"

using namespace std;

/**************************************
�}�N����`
***************************************/
#define PLAYERMODEL_INPUTHISTORY_MAX	(15)		//���͗����̍ő�ۑ�����
#define PLAYERMODEL_MOVEHISTORY_MAX		(PLAYERMODEL_INPUTHISTORY_MAX-1)	//�ړ������̍ő�ۑ�����

//��M�����̃p�[�c��\���񋓎q
enum OneStrokeParts
{
	TopToLowerleft,
	LowerleftToMiddleright,
	MiddlerightToMiddleleft,
	MiddleleftToLowerright,
	LowerrightToTop,
	PartsMax
};

/**************************************
�\���̒�`
***************************************/

/**************************************
static�ϐ�
***************************************/
//��M�������\�����郉�C���̏W��
const LineTrailModel PlayerModel::OneStrokePatrs[OneStrokeParts::PartsMax] = {
	LineTrailModel(TOP, LOWER_LEFT),
	LineTrailModel(LOWER_LEFT, MIDDLE_RIGHT),
	LineTrailModel(MIDDLE_RIGHT, MIDDLE_LEFT),
	LineTrailModel(MIDDLE_LEFT, LOWER_RIGHT),
	LineTrailModel(LOWER_RIGHT, TOP)
};

/**************************************
�R���X�g���N�^
***************************************/
PlayerModel::PlayerModel()
{

}

/**************************************
�f�X�g���N�^
***************************************/
PlayerModel::~PlayerModel()
{
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
���͗����̃v�b�V��
***************************************/
void PlayerModel::PushMoveStack(int num, bool canUpdate)
{
	//�ő吔�ł���Έ�ԌÂ��������폜
	if (inputHistory.size() == PLAYERMODEL_INPUTHISTORY_MAX)
		inputHistory.pop_front();

	//�v�b�V��
	inputHistory.push_back(num);

	//�ړ������̍X�V
	if(canUpdate)
		UpdateMoveHistory();
}

/**************************************
�ړ������̊m�F
***************************************/
void PlayerModel::UpdateMoveHistory()
{
	//���͗�����2���ȏ㖳���ƈړ��������\�z�ł��Ȃ����߃��^�[��
	if (inputHistory.size() < 2)
		return;
	
	//�ő�ۑ������ł���Έ�ԌÂ��������폜
	if (moveHistory.size() == PLAYERMODEL_MOVEHISTORY_MAX)
		moveHistory.pop_front();

	//�V�����ړ��������v�b�V��
	auto lastHistory = inputHistory.end() - 1;
	int current = *lastHistory;
	int prev = *(lastHistory - 1);
	moveHistory.push_back(LineTrailModel(current, prev));
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
	//����p���[�N
	int checkWork[OneStrokeParts::PartsMax];
	ZeroMemory(checkWork, sizeof(checkWork));

	//�ړ��������ׂĂɑ΂��Ĉ�M�������\������p�[�c���ǂ�������
	for (auto& model : moveHistory)
	{
		for (int i = 0; i < OneStrokeParts::PartsMax; i++)
		{
			//��M�������\������p�[�c�ł���΃J�E���g����break
			if (model == OneStrokePatrs[i])
			{
				checkWork[i]++;
				break;
			}
		}
	}

	//��M�������\������p�[�c����ł������Ă����return false
	for (int i = 0; i < OneStrokeParts::PartsMax; i++)
	{
		if (checkWork[i] == 0)
			return false;
	}

	//��M�������������Ă���̂ŗ������N���A����return true
	//�ŐV�̗��������̓v�b�V�����Ă���
	int lastInput = inputHistory.back();
	inputHistory.clear();
	moveHistory.clear();
	inputHistory.push_back(lastInput);
	return true;
}

/**************************************
�����N���A
***************************************/
void PlayerModel::Clear()
{
	inputHistory.clear();
	moveHistory.clear();
	queue<int>().swap(inputQueue);
	//ClearCombo();
}

/**************************************
����1���̋O�Ղ̎擾
***************************************/
bool PlayerModel::GetPlayerTrail(LineTrailModel *pOut)
{
	if (inputHistory.size() < 2)
		return false;
	
	int start = *(inputHistory.end() - 1);
	int end = *(inputHistory.end() - 2);
	*pOut = LineTrailModel(start, end);
	return true;
}

/**************************************
�S�O�Ղ̎擾
***************************************/
size_t PlayerModel::GetAllPlayerTrail(vector<LineTrailModel> *container)
{
	if (moveHistory.size() == 0)
		return 0;

	container->clear();
	container->resize(moveHistory.size());

	for (auto& model : moveHistory)
	{
		container->push_back(model);
	}

	return moveHistory.size();
}