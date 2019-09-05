//=====================================
//
//Viewer3D.cpp
//�@�\:2D�I�u�W�F�N�g��3D�\��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "Viewer3D.h"

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
Viewer3D::Viewer3D(DWORD sizeX, DWORD sizeY, const D3DXVECTOR2& worldSize) :
	transform(new Transform())
{
	//�����_�[�^�[�Q�b�g�쐬
	MakeRenderTarget(sizeX, sizeY);

	//���_�o�b�t�@�쐬
	MakeVertexBuffer(worldSize);
}

/**************************************
�f�X�g���N�^
***************************************/
Viewer3D::~Viewer3D()
{
	SAFE_RELEASE(vtxBuff);
	SAFE_RELEASE(renderSurface);
	SAFE_RELEASE(renderTarget);

	SAFE_DELETE(transform);
}

/**************************************
2D�`��J�n����
***************************************/
void Viewer3D::Begin2D()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�����_�[�^�[�Q�b�g�؂�ւ�
	pDevice->GetRenderTarget(0, &defaultSurface);
	pDevice->SetRenderTarget(0, renderSurface);

	//�����_�[�^�[�Q�b�g�N���A
	pDevice->Clear(0, 0, D3DCLEAR_TARGET, 0, 0.0f, 0);
}

/**************************************
2D�`��I������
***************************************/
void Viewer3D::End2D()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�����_�[�^�[�Q�b�g�����ɖ߂�
	pDevice->SetRenderTarget(0, defaultSurface);

	//�Q�Ƃ����
	SAFE_RELEASE(defaultSurface);
}

/**************************************
3D�`�揈��
***************************************/
void Viewer3D::Draw3D()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���݂̃����_�[�X�e�[�g��ۑ�
	DWORD flgLighting, flgEnableZ, flgWriteenableZ;
	pDevice->GetRenderState(D3DRS_LIGHTING, &flgLighting);
	pDevice->GetRenderState(D3DRS_ZENABLE, &flgEnableZ);
	pDevice->GetRenderState(D3DRS_ZWRITEENABLE, &flgWriteenableZ);

	//�����_�[�X�e�[�g�؂�ւ�
	pDevice->SetRenderState(D3DRS_LIGHTING, false);
	pDevice->SetRenderState(D3DRS_ZENABLE, false);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);

	//FVF�ۑ����؂�ւ�
	DWORD fvf;
	pDevice->GetFVF(&fvf);
	pDevice->SetFVF(FVF_VERTEX_3D);

	//���_�o�b�t�@���Z�b�g
	pDevice->SetStreamSource(0, vtxBuff, 0, sizeof(VERTEX_3D));

	//UI��`�悵���e�N�X�`�����Z�b�g
	pDevice->SetTexture(0, renderTarget);

	//���[���h�s����v�Z���Z�b�g
	D3DXMATRIX mtxWorld;
	mtxWorld = transform->GetMatrix();
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	//�`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	//�����_�[�X�e�[�g�����ɖ߂�
	pDevice->SetRenderState(D3DRS_LIGHTING, flgLighting);
	pDevice->SetRenderState(D3DRS_ZENABLE, flgEnableZ);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, flgWriteenableZ);

	//FVF�����ɖ߂�
	pDevice->SetFVF(FVF_VERTEX_2D);
}

/**************************************
���W�ݒ菈��
***************************************/
void Viewer3D::SetPosition(const D3DXVECTOR3 & position)
{
	transform->pos = position;
}

/**************************************
��]�ݒ菈��
***************************************/
void Viewer3D::SetRotation(float x, float y, float z)
{
	transform->IdentifyRotation();
	transform->Rotate(x, y, z);
}

/**************************************
���_�o�b�t�@�쐬����
***************************************/
void Viewer3D::MakeVertexBuffer(const D3DXVECTOR2& size)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&vtxBuff,
		0);

	VERTEX_3D *pVtx;
	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].vtx = D3DXVECTOR3(-size.x, size.y, 0.0f);
	pVtx[1].vtx = D3DXVECTOR3(size.x, size.y, 0.0f);
	pVtx[2].vtx = D3DXVECTOR3(-size.x, -size.y, 0.0f);
	pVtx[3].vtx = D3DXVECTOR3(size.x, -size.y, 0.0f);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	vtxBuff->Unlock();
}

/**************************************
�����_�[�^�[�Q�b�g�쐬����
***************************************/
void Viewer3D::MakeRenderTarget(DWORD sizeX, DWORD sizeY)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�����_�[�^�[�Q�b�g�ƂȂ�e�N�X�`�����쐬
	pDevice->CreateTexture(
		sizeX,		//�e�N�X�`���̉���
		sizeY,		//�e�N�X�`���̏c��
		1,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_X8R8G8B8,
		D3DPOOL_DEFAULT,
		&renderTarget,				//���ʂ��i�[����C���^�[�t�F�[�X
		0);

	//�쐬�����e�N�X�`������T�[�t�F�C�X���擾
	renderTarget->GetSurfaceLevel(0, &renderSurface);
}
