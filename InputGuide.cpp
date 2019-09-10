//=====================================
//
//InputGuide.cpp
//�@�\:���̓K�C�h�\��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "InputGuide.h"
#include "LineTrailModel.h"
#include "camera.h"
#include "Framework\Vector3.h"

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
InputGuide::InputGuide()
{
	LoadTexture("data/TEXTURE/UI/inputGuide.png");
	SetSize(100.0f, 100.0f);
}

/**************************************
�`�揈��
***************************************/
void InputGuide::Draw()
{
	if (!active)
		return;

	Polygon2D::Draw();
	active = false;
}

/**************************************
�Z�b�g����
***************************************/
void InputGuide::Set(LineTrailModel & model)
{
	//���f������[�_�̃��[���h���W
	D3DXVECTOR3 start, end;
	model.GetEdgePos(&start, &end);

	//���K�����C���x�N�g�����v�Z
	D3DXVECTOR3 diff = end - start;
	D3DXVec3Normalize(&diff, &diff);

	//���[���h���W���X�N���[�����W�ɕϊ�
	D3DXVECTOR3 worldPos = start + diff * 30.0f;
	Camera::Instance()->Projection(transform.pos, worldPos);

	//��]
	float angle = Vector3::Angle(Vector3::Up, diff);
	D3DXVECTOR3 axis = Vector3::Axis(Vector3::Up, diff);
	transform.IdentifyRotation();
	transform.RotateByAxis(-angle, axis);

	//�A�N�e�B�x�C�g
	active = true;
}
