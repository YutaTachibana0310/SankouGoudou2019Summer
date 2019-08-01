//=====================================
//
//�|���S������[BoardPolygon.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "BoardPolygon.h"

/**************************************
�}�N����`
***************************************/
#define BILLBOARD_DEFAULT_SIZE		(10.0f)

/**************************************
�R���X�g���N�^
***************************************/
BoardPolygon::BoardPolygon()
{
	pDevice = GetDevice();

	pDevice->CreateVertexBuffer(sizeof(VERTEX_BILLBOARD) * NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_BILLBOARD,
		D3DPOOL_MANAGED,
		&vtxBuff,
		0);

	VERTEX_BILLBOARD *pVtx;
	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].vtx = D3DXVECTOR3(-BILLBOARD_DEFAULT_SIZE, BILLBOARD_DEFAULT_SIZE, 0.0f);
	pVtx[1].vtx = D3DXVECTOR3( BILLBOARD_DEFAULT_SIZE, BILLBOARD_DEFAULT_SIZE, 0.0f);
	pVtx[2].vtx = D3DXVECTOR3(-BILLBOARD_DEFAULT_SIZE, -BILLBOARD_DEFAULT_SIZE, 0.0f);
	pVtx[3].vtx = D3DXVECTOR3( BILLBOARD_DEFAULT_SIZE, -BILLBOARD_DEFAULT_SIZE, 0.0f);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx[0].diffuse =
		pVtx[1].diffuse =
		pVtx[2].diffuse =
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	vtxBuff->Unlock();
}

/**************************************
�f�X�g���N�^
***************************************/
BoardPolygon::~BoardPolygon()
{
	SAFE_RELEASE(vtxBuff);
	SAFE_RELEASE(texture);
}

/**************************************
�`�揈��
***************************************/
void BoardPolygon::Draw()
{
	pDevice->SetTexture(0, texture);

	pDevice->SetStreamSource(0, vtxBuff, 0, sizeof(VERTEX_BILLBOARD));

	pDevice->SetFVF(FVF_VERTEX_BILLBOARD);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

/**************************************
�e�N�X�`���ǂݍ��ݏ���
***************************************/
void BoardPolygon::LoadTexture(const char* path)
{
	SAFE_RELEASE(texture);

	D3DXCreateTextureFromFile(pDevice, path, &texture);
}

/**************************************
�T�C�Y�ݒ菈��
***************************************/
void BoardPolygon::SetSize(D3DXVECTOR2 size)
{
	VERTEX_BILLBOARD *pVtx;
	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].vtx = D3DXVECTOR3(-size.x, size.y, 0.0f);
	pVtx[1].vtx = D3DXVECTOR3( size.x, size.y, 0.0f);
	pVtx[2].vtx = D3DXVECTOR3(-size.x, -size.y, 0.0f);
	pVtx[3].vtx = D3DXVECTOR3( size.x, -size.y, 0.0f);

	vtxBuff->Unlock();
}

/**************************************
UV�����ݒ菈��
***************************************/
void BoardPolygon::SetTexDiv(D3DXVECTOR2 div)
{
	texDiv = div;
	texSize.x = 1.0f / div.x;
	texSize.y = 1.0f / div.y;

	VERTEX_BILLBOARD *pVtx;
	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(texSize.x, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, texSize.y);
	pVtx[3].tex = D3DXVECTOR2(texSize.x, texSize.y);

	vtxBuff->Unlock();
}

/**************************************
UV�C���f�b�N�X�ݒ菈��
***************************************/
void BoardPolygon::SetTextureIndex(int index)
{
	int x = index % (int)texDiv.x;
	int y = index / (int)texDiv.x;

	VERTEX_BILLBOARD *pVtx;
	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(x * texSize.x, y * texSize.y);
	pVtx[1].tex = D3DXVECTOR2((x + 1) * texSize.x, y * texSize.y);
	pVtx[2].tex = D3DXVECTOR2(x * texSize.x, (y + 1) * texSize.y);
	pVtx[3].tex = D3DXVECTOR2((x + 1) * texSize.x, (y + 1) * texSize.y);

	vtxBuff->Unlock();
}