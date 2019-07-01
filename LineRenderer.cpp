//=====================================
//
//���C�������_���[����[LineRenderer.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "LineRenderer.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
LineRenderer::LineRenderer()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_�o�b�t�@�쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&vtxBuff,
		0);
	VERTEX_3D *pVtx;
	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//UV���W�ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//�F������
	pVtx[0].diffuse =
		pVtx[1].diffuse =
		pVtx[2].diffuse =
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	vtxBuff->Unlock();
}

/**************************************
�f�X�g���N�^
***************************************/
LineRenderer::~LineRenderer()
{
	SAFE_RELEASE(vtxBuff);
}

/**************************************
����������
***************************************/
void LineRenderer::Init(D3DXVECTOR3 *right, D3DXVECTOR3 *left, float width)
{
	//������ۑ�
	this->width = width;

	//�n�_�ƏI�_�����Ԑ������v�Z���A�����𔼕��ɂ���
	D3DXVECTOR3 diff = *left - *right;
	diff /= 2.0f;

	//�����ɐ����ȃx�N�g�������߂�
	D3DXVec3Cross(&vtxUp, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &diff);
	D3DXVec3Normalize(&vtxUp, &vtxUp);

	//���߂��x�N�g�����璸�_���W���v�Z
	VERTEX_3D *pVtx;
	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	pVtx[0].vtx = -diff + vtxUp * width;
	pVtx[1].vtx = diff + vtxUp * width;
	pVtx[2].vtx = -diff - vtxUp * width;
	pVtx[3].vtx = diff - vtxUp * width;
	vtxBuff->Unlock();
}

/**************************************
�`�揈��
***************************************/
void LineRenderer::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�����`�悳��Ȃ������J�����O���I�t�ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, false);

	pDevice->SetStreamSource(0, vtxBuff, 0, sizeof(VERTEX_3D));
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

/**************************************
�E�[�ݒ菈��
***************************************/
void LineRenderer::SetRightPos(D3DXVECTOR3 *pos)
{
	VERTEX_3D *pVtx;
	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	pVtx[1].vtx = *pos + vtxUp * width;
	pVtx[3].vtx = *pos - vtxUp * width;
	vtxBuff->Unlock();
}

/**************************************
���[�ݒ菈��
***************************************/
void LineRenderer::SetLeftPos(D3DXVECTOR3 *pos)
{
	VERTEX_3D *pVtx;
	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	pVtx[0].vtx = *pos + vtxUp * width;
	pVtx[2].vtx = *pos - vtxUp * width;
	vtxBuff->Unlock();
}

/**************************************
�F�ݒ菈��
***************************************/
void LineRenderer::SetColor(D3DXCOLOR color)
{
	VERTEX_3D *pVtx;
	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	pVtx[0].diffuse =
		pVtx[1].diffuse =
		pVtx[2].diffuse =
		pVtx[3].diffuse = color;
	vtxBuff->Unlock();
}