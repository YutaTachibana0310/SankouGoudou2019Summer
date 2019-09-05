//=====================================
//
//Viewer3D.h
//�@�\:2D�I�u�W�F�N�g��3D�\��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _VIEWER3D_H_
#define _VIEWER3D_H_

#include "main.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class Viewer3D
{
public:
	//�R���X�g���N�^
	//��1���� DWORD 2DUI�̕����w��
	//��2���� DWORD 2DUI�̍������w��
	//��3���� D3DXVECTOR2 ���[���h��Ԃł̃T�C�Y���w��
	Viewer3D(DWORD sizeX, DWORD sizeY, const D3DXVECTOR2& worldSize);
	
	//�f�X�g���N�^
	virtual ~Viewer3D();

	//2D�`��J�n����
	virtual void Begin2D();

	//2D�`��I������
	virtual void End2D();

	//3D�`�揈��
	virtual void Draw3D();

	//���[���h���W�ݒ菈��
	virtual void SetPosition(const D3DXVECTOR3& position);

	//��]�ݒ菈��
	virtual void SetRotation(float x, float y, float z);

protected:
	//�����_�[�^�[�Q�b�g�֘A�̃����o
	LPDIRECT3DTEXTURE9 renderTarget;
	LPDIRECT3DSURFACE9 renderSurface;

	//���̃����_�[�^�[�Q�b�g�ۑ��p�����o
	LPDIRECT3DSURFACE9 defaultSurface;

	//���_�o�b�t�@
	LPDIRECT3DVERTEXBUFFER9 vtxBuff;

	//SRT���
	Transform* transform;

	//���_�o�b�t�@�쐬����
	virtual void MakeVertexBuffer(const D3DXVECTOR2& size);

	//�����_�[�^�[�Q�b�g�쐬����
	virtual void MakeRenderTarget(DWORD sizeX, DWORD sizeY);

};
#endif