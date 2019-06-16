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
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
static LPDIRECT3DVERTEXBUFFER9 vtxBuff;
static LPDIRECT3DTEXTURE9 texture;

/**************************************
�v���g�^�C�v�錾
***************************************/
void MakeVertexBufferSkyBox(void);

/**************************************
����������
***************************************/
void InitSkyBox(int num)
{
	MakeVertexBufferSkyBox();

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	texture = CreateTextureFromFile((LPSTR)SKYBOX_TEXTURE_NAME, pDevice);
}

/**************************************
�I������
***************************************/
void UninitSkyBox(int num)
{
	SAFE_RELEASE(texture);
	SAFE_RELEASE(vtxBuff);
}

/**************************************
�X�V����
***************************************/
void UpdateSkyBox(void)
{
	//�X�J�C�{�b�N�X���X�N���[��
	VERTEX_3D *pVtx;
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
void DrawSkyBox(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxWorld;

	//�t�H�O���I�t
	pDevice->SetRenderState(D3DRS_FOGENABLE, false);

	//���[���h�ϊ��s��ݒ�
	D3DXMatrixIdentity(&mtxWorld);
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	//�����_�[�X�e�[�g�ݒ�
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
	pDevice->SetRenderState(D3DRS_LIGHTING, false);

	//FVF�ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, texture);

	//�X�g���[���\�[�X�ݒ�
	pDevice->SetStreamSource(0, vtxBuff, 0, sizeof(VERTEX_3D));

	//�`��
	for (int i = 0; i < SKYBOX_FIELD_NUM; i++)
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, NUM_VERTEX * i, NUM_POLYGON);

	//�����_�[�X�e�[�g����
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
	pDevice->SetRenderState(D3DRS_LIGHTING, true);

	//�t�H�O���I��
	pDevice->SetRenderState(D3DRS_FOGENABLE, true);
}

/**************************************
���_�o�b�t�@�쐬����
***************************************/
void MakeVertexBufferSkyBox(void)
{
	const float Bottom = -750.0f;
	const float BoxSize = 5000.0f;
	const float TexLoop = 3.0f;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * SKYBOX_FIELD_NUM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&vtxBuff,
		0);

	VERTEX_3D *pVtx;
	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//����
	pVtx[0].vtx = D3DXVECTOR3(-BoxSize, BoxSize * 2, -BoxSize);
	pVtx[1].vtx = D3DXVECTOR3(-BoxSize, BoxSize * 2, BoxSize);
	pVtx[2].vtx = D3DXVECTOR3(-BoxSize, Bottom, -BoxSize);
	pVtx[3].vtx = D3DXVECTOR3(-BoxSize, Bottom, BoxSize);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(TexLoop, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, TexLoop * 2);
	pVtx[3].tex = D3DXVECTOR2(TexLoop, TexLoop * 2);

	pVtx[0].diffuse =
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].diffuse =
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�E��
	pVtx += 4;
	pVtx[0].vtx = D3DXVECTOR3(BoxSize, BoxSize * 2, BoxSize);
	pVtx[1].vtx = D3DXVECTOR3(BoxSize, BoxSize * 2, -BoxSize);
	pVtx[2].vtx = D3DXVECTOR3(BoxSize, Bottom, BoxSize);
	pVtx[3].vtx = D3DXVECTOR3(BoxSize, Bottom, -BoxSize);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(TexLoop, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, TexLoop * 2);
	pVtx[3].tex = D3DXVECTOR2(TexLoop, TexLoop * 2);

	pVtx[0].diffuse =
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].diffuse =
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�O��
	pVtx += 4;
	pVtx[0].vtx = D3DXVECTOR3(-BoxSize, BoxSize * 2, BoxSize);
	pVtx[1].vtx = D3DXVECTOR3(BoxSize, BoxSize * 2, BoxSize);
	pVtx[2].vtx = D3DXVECTOR3(-BoxSize, Bottom, BoxSize);
	pVtx[3].vtx = D3DXVECTOR3(BoxSize, Bottom, BoxSize);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(TexLoop, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, TexLoop * 2);
	pVtx[3].tex = D3DXVECTOR2(TexLoop, TexLoop * 2);

	pVtx[0].diffuse =
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].diffuse =
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//���
	pVtx += 4;
	pVtx[0].vtx = D3DXVECTOR3(BoxSize, BoxSize * 2, -BoxSize);
	pVtx[1].vtx = D3DXVECTOR3(-BoxSize, BoxSize * 2, -BoxSize);
	pVtx[2].vtx = D3DXVECTOR3(BoxSize, Bottom, -BoxSize);
	pVtx[3].vtx = D3DXVECTOR3(-BoxSize, Bottom, -BoxSize);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(TexLoop, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, TexLoop * 2);
	pVtx[3].tex = D3DXVECTOR2(TexLoop, TexLoop * 2);

	pVtx[0].diffuse =
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].diffuse =
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	vtxBuff->Unlock();
}