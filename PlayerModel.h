//=====================================
//
//�v���C���[���f���w�b�_[PlayerModel.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _PLAYERMODEL_H_
#define _PLAYERMODEL_H_

#include "main.h"
#include <queue>
#include <vector>
#include <deque>
#include "PlayerTrailModel.h"

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

	void PushInput(int num);				//��s���͂̕ۑ�
	void PushMoveStack(int num);			//�ړ������̃v�b�V��
	bool IsExistPrecedInput(int *pres);		//��s���͂̊m�F
	bool CheckOneStroke();					//��M�����̔���
	void Clear();							//��s���́A�ړ������̃N���A

	bool GetPlayerTrail(PlayerTrailModel *pOut);						//�v���C���[�̒���1���̋O�Ղ̎擾
	size_t GetAllPlayerTrail(std::vector<PlayerTrailModel> *contaier);	//�v���C���[�̑S�O�Ղ��擾

private:
	std::vector<int> Judgement;				//��M�����̐���z��
	std::queue<int> inputQueue;				//��s���͂�ۑ�����L���[
	std::deque<int> moveQueue;				//�ړ�����

	bool _CheckOneStroke(size_t start);		//�����ł̈�M��������
};


#endif