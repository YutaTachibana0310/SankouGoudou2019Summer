//=====================================
//
//���C���g���C�����f������[LineTrailModel.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "LineTrailModel.h"
#include "starUI.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/

/**************************************
static�����o
***************************************/
D3DXVECTOR3 LineTrailModel::edgePosition[TrailIndexMax];

/**************************************
�R���X�g���N�^
***************************************/
LineTrailModel::LineTrailModel()
{
	start = end = Top;
}

/**************************************
�R���X�g���N�^
***************************************/
LineTrailModel::LineTrailModel(int start, int end)
{
	this->start = start;
	this->end = end;
}

/**************************************
�f�X�g���N�^
***************************************/
LineTrailModel::~LineTrailModel()
{

}

/**************************************
==���Z�q
***************************************/
bool LineTrailModel::operator==(const LineTrailModel& obj) const
{
	if (this->start == obj.start && this->end == obj.end)
		return true;

	if (this->start == obj.end && this->end == obj.start)
		return true;

	return false;
}

/**************************************
!=���Z�q
***************************************/
bool LineTrailModel::operator!=(const LineTrailModel& obj) const
{
	if (this->start == obj.start && this->end == obj.end)
		return false;

	if (this->start == obj.end && this->end == obj.start)
		return false;

	return true;
}

/**************************************
�[�_���W�擾����
***************************************/
void LineTrailModel::GetEdgePos(D3DXVECTOR3 *right, D3DXVECTOR3 *left)
{
	if (right != NULL)
		*right = edgePosition[start];
	if (left != NULL)
		*left = edgePosition[end];
}

/**************************************
�[�_���W�擾����
***************************************/
D3DXVECTOR3 LineTrailModel::GetEdgePos(int i)
{
	return edgePosition[i];
}

/**************************************
�[�_���W�ݒ菈��
***************************************/
void LineTrailModel::CalcEdgePosition(D3DXVECTOR3 *starPos)
{
	const float PositionDistance = 150.0f;
	for (int i = 0; i < STAR_MAX; i++)
	{
		//�X�^�[�̈ʒu��Near�ʂ�Far�ʂ����ԃ��C���v�Z���Đ��K��
		D3DXVECTOR3 nearPos, farPos;
		CalcScreenToWorld(&nearPos, &starPos[i], 0.0f);
		CalcScreenToWorld(&farPos, &starPos[i], 1.0f);

		D3DXVECTOR3 ray = farPos - nearPos;
		D3DXVec3Normalize(&ray, &ray);

		//�ڕW���W���v�Z
		D3DXVECTOR3 pos = nearPos + ray * PositionDistance;
		edgePosition[i] = pos;
	}
}