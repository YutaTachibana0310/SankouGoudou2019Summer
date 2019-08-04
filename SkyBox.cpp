//=====================================
//
//�X�J�C�{�b�N�X����[SkyBox.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "SkyBox.h"

/**************************************
�}�N����`
***************************************/
#define SKYBOX_FIELD_NUM		(4)
#define SKYBOX_TEXTURE_NAME		"data/TEXTURE/BG/img_post152_07.jpg"
#define SKYBOX_SCROLL_SPEED		(0.0002f)

/**************************************
�R���X�g���N�^
***************************************/
SkyBox::SkyBox(D3DXVECTOR3 vtxSize, D3DXVECTOR2 texSize)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->CreateVertexBuffer(sizeof(VERTEX_BILLBOARD) * NUM_VERTEX * SKYBOX_FIELD_NUM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_BILLBOARD,
		D3DPOOL_MANAGED,
		&vtxBuff,
		0);

	VERTEX_BILLBOARD *pVtx;
	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//����
	pVtx[0].vtx = D3DXVECTOR3(-vtxSize.x, vtxSize.y, -vtxSize.z);
	pVtx[1].vtx = D3DXVECTOR3(-vtxSize.x, vtxSize.y, vtxSize.z);
	pVtx[2].vtx = D3DXVECTOR3(-vtxSize.x, -vtxSize.y, -vtxSize.z);
	pVtx[3].vtx = D3DXVECTOR3(-vtxSize.x, -vtxSize.y, vtxSize.z);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(texSize.x, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, texSize.y);
	pVtx[3].tex = D3DXVECTOR2(texSize.x, texSize.y);

	pVtx[0].diffuse =
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].diffuse =
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�E��
	pVtx += 4;
	pVtx[0].vtx = D3DXVECTOR3(vtxSize.x, vtxSize.y, vtxSize.x);
	pVtx[1].vtx = D3DXVECTOR3(vtxSize.x, vtxSize.y, -vtxSize.x);
	pVtx[2].vtx = D3DXVECTOR3(vtxSize.x, -vtxSize.y, vtxSize.x);
	pVtx[3].vtx = D3DXVECTOR3(vtxSize.x, -vtxSize.y, -vtxSize.x);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(texSize.x, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, texSize.y);
	pVtx[3].tex = D3DXVECTOR2(texSize.x, texSize.y);

	pVtx[0].diffuse =
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].diffuse =
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�O��
	pVtx += 4;
	pVtx[0].vtx = D3DXVECTOR3(-vtxSize.x, vtxSize.y, vtxSize.z);
	pVtx[1].vtx = D3DXVECTOR3(vtxSize.x, vtxSize.y, vtxSize.z);
	pVtx[2].vtx = D3DXVECTOR3(-vtxSize.x, -vtxSize.y, vtxSize.z);
	pVtx[3].vtx = D3DXVECTOR3(vtxSize.x, -vtxSize.y, vtxSize.z);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(texSize.x, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, texSize.y);
	pVtx[3].tex = D3DXVECTOR2(texSize.x, texSize.y);

	pVtx[0].diffuse =
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].diffuse =
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//���
	pVtx += 4;
	pVtx[0].vtx = D3DXVECTOR3(vtxSize.x, vtxSize.y, -vtxSize.z);
	pVtx[1].vtx = D3DXVECTOR3(-vtxSize.x, vtxSize.y, -vtxSize.z);
	pVtx[2].vtx = D3DXVECTOR3(vtxSize.x, -vtxSize.y, -vtxSize.z);
	pVtx[3].vtx = D3DXVECTOR3(-vtxSize.x, -vtxSize.y, -vtxSize.z);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(texSize.x, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, texSize.y);
	pVtx[3].tex = D3DXVECTOR2(texSize.x, texSize.y);

	pVtx[0].diffuse =
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].diffuse =
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	vtxBuff->Unlock();
}

/**************************************
�f�X�g���N�^
***************************************/
SkyBox::~SkyBox()
{
	SAFE_RELEASE(vtxBuff);
	SAFE_RELEASE(texture);
}

/**************************************
�X�V����
***************************************/
void SkyBox::Update()
{
	VERTEX_BILLBOARD *pVtx;
	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < NUM_VERTEX * SKYBOX_FIELD_NUM; i++)
	{
		pVtx[i].tex.x += SKYBOX_SCROLL_SPEED;
		pVtx[i].tex.y += SKYBOX_SCROLL_SPEED;
	}

	vtxBuff->Unlock();
}

/**************************************
�`�揈��
***************************************/
void SkyBox::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetFVF(FVF_VERTEX_BILLBOARD);

	D3DXMATRIX mtxWorld;
	transform.SetWorld();

	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
	pDevice->SetRenderState(D3DRS_LIGHTING, false);

	pDevice->SetTexture(0, texture);

	pDevice->SetStreamSource(0, vtxBuff, 0, sizeof(VERTEX_BILLBOARD));

	for (int i = 0; i < SKYBOX_FIELD_NUM; i++)
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

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXCreateTextureFromFile(pDevice, fileName, &texture);
}
