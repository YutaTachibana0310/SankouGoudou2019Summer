//=====================================
//
//�v���C���[���f���w�b�_[PlayerModel.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _PLAYERMODEL_H_
#define _PLAYERMODEL_H_

#include "main.h"
#include "LineTrailModel.h"

#include <queue>
#include <vector>
#include <deque>
#include <map>

/**************************************
�}�N����`
***************************************/

/**************************************
PlayerModel�N���X
���͗�����ړ��������܂Ƃ߂�
***************************************/
class PlayerModel
{
public:
	PlayerModel();
	~PlayerModel();

	void PushInput(int num);						//��s���͂̕ۑ�
	void PushMoveStack(int num, bool canUpdate);	//�ړ������̃v�b�V��
	bool IsExistPrecedInput(int *pres);				//��s���͂̊m�F
	bool CheckOneStroke();							//��M�����̔���
	void Clear();									//��s���́A�ړ������̃N���A

	bool GetPlayerTrail(LineTrailModel *pOut);						//�v���C���[�̒���1���̋O�Ղ̎擾
	size_t GetAllPlayerTrail(std::vector<LineTrailModel> *contaier);	//�v���C���[�̑S�O�Ղ��擾
	bool Empty();									//���������邩�ǂ���

private:
	std::queue<int> inputQueue;						//��s���͂�ۑ�����L���[
	std::deque<int> inputHistory;					//���͗���
	std::deque<LineTrailModel> moveHistory;			//�ړ�����

	void UpdateMoveHistory();						//�ړ������̍X�V

	static const LineTrailModel OneStrokePatrs[];	//��M�������\�����郉�C���̏W��

};

#endif