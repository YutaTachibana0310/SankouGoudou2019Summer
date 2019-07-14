//=====================================
//
//�G�f�B�^BG����[EditorBG.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "EditorBG.h"

/**************************************
�}�N����`
***************************************/
#define EDITORBG_WIDTH		(600.0f)
#define EDITORBG_LEFT		(100.0f)
/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
EditorBG::EditorBG()
{
	vtxWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vtxWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vtxWk[2].tex = D3DXVECTOR2(0.0f, 5.0f);
	vtxWk[3].tex = D3DXVECTOR2(1.0f, 5.0f);

	vtxWk[0].vtx = D3DXVECTOR3(EDITORBG_LEFT, 0.0f, 0.0f);
	vtxWk[1].vtx = D3DXVECTOR3(EDITORBG_LEFT + EDITORBG_WIDTH, 0.0f, 0.0f);
	vtxWk[2].vtx = D3DXVECTOR3(EDITORBG_LEFT, SCREEN_HEIGHT, 0.0f);
	vtxWk[3].vtx = D3DXVECTOR3(EDITORBG_LEFT + EDITORBG_WIDTH, SCREEN_HEIGHT, 0.0f);
	
	vtxWk[0].diffuse =
		vtxWk[1].diffuse =
		vtxWk[2].diffuse =
		vtxWk[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	vtxWk[0].rhw =
		vtxWk[1].rhw =
		vtxWk[2].rhw =
		vtxWk[3].rhw = 1.0f;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Editor/grid.png", &texture);
}

/**************************************
�f�X�g���N�^
***************************************/
EditorBG::~EditorBG()
{
	SAFE_RELEASE(texture);
}

/**************************************
����������
***************************************/
void EditorBG::Init()
{

}

/**************************************
�I������
***************************************/
void EditorBG::Uninit()
{

}

/**************************************
�X�V����
***************************************/
void EditorBG::Update()
{

}

/**************************************
�`�揈��
***************************************/
void EditorBG::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetTexture(0, texture);
	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vtxWk, sizeof(VERTEX_2D));
}