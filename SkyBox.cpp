//=====================================
//
//�X�J�C�{�b�N�X����[SkyBox.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "SkyBox.h"
#include "Framework\ResourceManager.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
SkyBox::SkyBox(D3DXVECTOR3 vtxSize, D3DXVECTOR2 texSize) :
	transform(new Transform())
{
	MakeVertexBuffer(vtxSize.x, vtxSize.y, vtxSize.z);
	SetUV(texSize.x, texSize.y);
}

/**************************************
�f�X�g���N�^
***************************************/
SkyBox::~SkyBox()
{
	SAFE_DELETE(transform);
	SAFE_RELEASE(vtxBuff);
	SAFE_RELEASE(texture);
}

/**************************************
�`�揈��
***************************************/
void SkyBox::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetFVF(FVF_VERTEX_BILLBOARD);

	D3DXMATRIX mtxWorld;
	transform->SetWorld();

	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
	pDevice->SetRenderState(D3DRS_LIGHTING, false);

	pDevice->SetTexture(0, texture);

	pDevice->SetStreamSource(0, vtxBuff, 0, sizeof(VERTEX_BILLBOARD));

	for (int i = 0; i < Const::FieldNum; i++)
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, NUM_VERTEX * i, NUM_POLYGON);

	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
	pDevice->SetRenderState(D3DRS_LIGHTING, true);
}

/**************************************
�e�N�X�`���ǂݍ��ݐݒ�
***************************************/
void SkyBox::LoadTexture(const char* fileName)
{
	SAFE_RELEASE(texture);
	ResourceManager::Instance()->GetTexture(fileName, texture);
}

/**************************************
UV���W�ݒ菈��
***************************************/
void SkyBox::SetUV(float texU, float texV)
{
	VERTEX_BILLBOARD *pVtx;
	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < Const::FieldNum; i++, pVtx += 4)
	{
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(texU, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, texV);
		pVtx[3].tex = D3DXVECTOR2(texU, texV);
	}

	vtxBuff->Unlock();
}

/**************************************
���_�o�b�t�@�쐬����
***************************************/
void SkyBox::MakeVertexBuffer(float width, float height, float depth)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->CreateVertexBuffer(sizeof(VERTEX_BILLBOARD) * NUM_VERTEX * Const::FieldNum,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_BILLBOARD,
		D3DPOOL_MANAGED,
		&vtxBuff,
		0);

	VERTEX_BILLBOARD *pVtx;
	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//����
	pVtx[0].vtx = D3DXVECTOR3(-width, height, -depth);
	pVtx[1].vtx = D3DXVECTOR3(-width, height, depth);
	pVtx[2].vtx = D3DXVECTOR3(-width, -height, -depth);
	pVtx[3].vtx = D3DXVECTOR3(-width, -height, depth);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx[0].diffuse =
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].diffuse =
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�E��
	pVtx += 4;
	pVtx[0].vtx = D3DXVECTOR3(width, height, depth);
	pVtx[1].vtx = D3DXVECTOR3(width, height, -depth);
	pVtx[2].vtx = D3DXVECTOR3(width, -height, depth);
	pVtx[3].vtx = D3DXVECTOR3(width, -height, -depth);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx[0].diffuse =
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].diffuse =
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�O��
	pVtx += 4;
	pVtx[0].vtx = D3DXVECTOR3(-width, height, depth);
	pVtx[1].vtx = D3DXVECTOR3(width, height, depth);
	pVtx[2].vtx = D3DXVECTOR3(-width, -height, depth);
	pVtx[3].vtx = D3DXVECTOR3(width, -height, depth);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx[0].diffuse =
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].diffuse =
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//���
	pVtx += 4;
	pVtx[0].vtx = D3DXVECTOR3(width, height, -depth);
	pVtx[1].vtx = D3DXVECTOR3(-width, height, -depth);
	pVtx[2].vtx = D3DXVECTOR3(width, -height, -depth);
	pVtx[3].vtx = D3DXVECTOR3(-width, -height, -depth);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx[0].diffuse =
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].diffuse =
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	vtxBuff->Unlock();

}
