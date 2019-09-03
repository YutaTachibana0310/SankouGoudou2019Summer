//=====================================
//
//TutorialBG.cpp
//�@�\:
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "TutorialBG.h"
#include "Framework\Polygon2D.h"

/**************************************
�O���[�o���ϐ�
***************************************/
const D3DXVECTOR3 TutorialBG::BoxSize = D3DXVECTOR3(5000.0f, 50000.0f, 5000.0f);
const D3DXVECTOR2 TutorialBG::BoxUV = D3DXVECTOR2(5.0f, 5.0f);

/**************************************
�R���X�g���N�^
***************************************/
TutorialBG::TutorialBG() :
	SkyBox(BoxSize, BoxUV),
	polygon(new Polygon2D((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT))
{
	transform->Rotate(90.0f, 0.0f, 0.0f);

	//�e�N�X�`�����[�h
	const char* textureName = "data/TEXTURE/BG/TutorialBG.jpg";
	LoadTexture(textureName);

	//�|���̐F�����ɐݒ�
	polygon->SetColor(D3DXCOLOR(0.00f, 0.00f, 0.00f, 1.0f));
}

/**************************************
�X�V����
***************************************/
void TutorialBG::Update()
{
	VERTEX_BILLBOARD *pVtx = NULL;
	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�X�N���[������
	const float ScrollSpeed = -0.01f;
	for (int i = 0; i < Const::FieldNum * NUM_VERTEX; i++)
	{
		pVtx[i].tex.y += ScrollSpeed;
	}

	vtxBuff->Unlock();
}


/**************************************
�`�揈��
***************************************/
void TutorialBG::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
	polygon->Draw();
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);

	SkyBox::Draw();
}