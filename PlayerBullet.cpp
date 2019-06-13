//=====================================
//
//�v���C���[�o���b�g����[PlayerBullet.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================

#include "PlayerBullet.h"
/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/

/**************************************
�v���g�^�C�v�錾
***************************************/

/****************************************
����������
****************************************/
void PlayerBullet::Init()
{

}

/****************************************
�I������
*****************************************/
void PlayerBullet::Uninit()
{

}


/****************************************
�X�V����
*****************************************/
void PlayerBullet::Update()
{
	if (!active)
		return;

	//�ړ�����
	const float Speed = 10.0f;
	pos.z += Speed;
}

/****************************************
�`�揈��
*****************************************/
void PlayerBullet::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	VERTEX_3D* p;
	vtxBuff->Lock(0, 0, (void**)&p, 0);
	vtxBuff->Unlock();

	pDevice->SetFVF(FVF_VERTEX_3D);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	pDevice->SetRenderState(D3DRS_LIGHTING, false);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	pDevice->SetTexture(0, texture);

	pDevice->SetStreamSource(0, vtxBuff, 0, sizeof(VERTEX_3D));

	D3DXMATRIX mtxWorld;
	D3DXMatrixIdentity(&mtxWorld);
	D3DXMatrixTranslation(&mtxWorld, pos.x, pos.y, pos.z);

	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	pDevice->SetRenderState(D3DRS_LIGHTING, true);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

/****************************************
�R���X�g���N�^
****************************************/
PlayerBullet::PlayerBullet()
{
	//���_�o�b�t�@�쐬
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &vtxBuff, 0);

	//���_���W�ȊO�̏��𖄂߂�
	VERTEX_3D *pVtx;

	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	
	const float texSize = 1.0f;
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(texSize, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(texSize, 1.0f);

	pVtx[0].diffuse =
		pVtx[1].diffuse =
		pVtx[2].diffuse =
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	pVtx[0].nor =
		pVtx[1].nor =
		pVtx[2].nor =
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	vtxBuff->Unlock();

	texture = CreateTextureFromFile((LPSTR)"data/TEXTURE/Player/PlayerBullet.png", pDevice);

	//TrailCollider��Z���W�A�h���X��ݒ�
	collider.SetAddressZ(&pos.z);
}

/****************************************
�f�X�g���N�^
****************************************/
PlayerBullet::~PlayerBullet()
{
	SAFE_RELEASE(vtxBuff);
}

/****************************************
�Z�b�g����
*****************************************/
void PlayerBullet::Set(TrailIndex start, TrailIndex end)
{

}

/****************************************
�Z�b�g����(�e�X�g�p)
*****************************************/
void PlayerBullet::Set(D3DXVECTOR3 start, D3DXVECTOR3 end)
{

	D3DXVECTOR3 diff = end - start;
	diff /= 2.0f;

	D3DXVECTOR3 up;
	D3DXVec3Cross(&up, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &diff);
	D3DXVec3Normalize(&up, &up);

	VERTEX_3D *pVtx;
	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	const float length = 15.0f;

	pVtx[0].vtx = -diff + up * length;
	pVtx[1].vtx = diff + up * length;
	pVtx[2].vtx = -diff - up * length;
	pVtx[3].vtx = diff - up * length;

	vtxBuff->Unlock();

	pos = start + diff;

	active = true;

}

/****************************************
�R���C�_�[�擾����
*****************************************/
TrailCollider PlayerBullet::GetCollider()
{
	return collider;
}

/****************************************
�A�N�e�B�u����
*****************************************/
bool PlayerBullet::IsActive()
{
	return active;
}
