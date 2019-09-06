//=============================================================================
//
// �{���X�g�b�N��ʏ��� [bomberStockUI.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "Viewer3D.h"
#include "UIdrawer.h"
#include "GameSceneUIManager.h"
#include "bomberStockUI.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SIZE_BOMBER_STOCK_BOM		(D3DXVECTOR3(70.0f,70.0f,0.0f))
#define SIZE_BOMBER_STOCK_BG		(D3DXVECTOR3(300.0f,60.0f,0.0f))
#define INTERVAL_STOCKED_BOM		(150.0f)
#define SPEED_ROTATION				(0.10f)
#define COLLIDERSIZE_BOMBER_STOCK	(D3DXVECTOR3(5.0f,5.0f,0.0f))

//���W�ݒ�(3D)
#define POSITION_BOMBER_STOCK_BOM	(D3DXVECTOR3(70.0f,70.0f,0.0f))
#define POSITION_BOMBER_STOCK_BG	(D3DXVECTOR3(300.0f,60.0f,0.0f))

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
BomberStock::BomberStock()
{
	stockedBomNum = 0;

	//�{��
	for (int i = 0; i < MAX_STOCKED_BOM_NUM; i++)
	{
		bom[i] = new RotateObject();
		bom[i]->LoadTexture("data/TEXTURE/UI/BomberStock/bom.png");
		bom[i]->MakeVertex();
		bom[i]->position = (POSITION_BOMBER_STOCK_BOM + D3DXVECTOR3(i* INTERVAL_STOCKED_BOM, 0.0f, 0.0f))/2;
		bom[i]->size = SIZE_BOMBER_STOCK_BOM/2;
		bom[i]->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		bom[i]->colliderSize = COLLIDERSIZE_BOMBER_STOCK / 2;
		bom[i]->SetColorObject(SET_COLOR_NOT_COLORED);
		bom[i]->CreateObjectCircle();
	}

	//�w�i
	bg = new Object();
	bg->LoadTexture("data/TEXTURE/UI/BomberStock/bomberStockBG.png");
	bg->MakeVertex();
	bg->position = POSITION_BOMBER_STOCK_BG/2;
	bg->size = SIZE_BOMBER_STOCK_BG/2;
	bg->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	bg->colliderSize = COLLIDERSIZE_BOMBER_STOCK / 2;
	bg->SetColorObject(SET_COLOR_NOT_COLORED);

	//�r���A�[
	viewer = new Viewer3D(SIZE_BOMBER_STOCK_BG.x, SIZE_BOMBER_STOCK_BG.y, D3DXVECTOR2(20.0f, 15.0f));
	viewer->SetPosition(D3DXVECTOR3((float)SCREEN_WIDTH / 14.5f, -(float)SCREEN_HEIGHT / 100, 0.0f));
	viewer->SetRotation(0.0f, 30.0f, 0.0f);
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
BomberStock::~BomberStock()
{
	for (int i = 0; i < MAX_STOCKED_BOM_NUM; i++)
	{
		SAFE_DELETE(bom[i]);
	}

	SAFE_DELETE(bg);
	SAFE_DELETE(viewer);
}

//=============================================================================
// �X�V����
//=============================================================================
void BomberStock::Update(void)
{
	for (int i = 0; i < stockedBomNum; i++)
	{
		bom[i]->rotation.z += SPEED_ROTATION;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void BomberStock::Draw(void)
{
	viewer->Begin2D();

	//�w�i���ɕ`��
	bg->Draw();
	bg->SetVertex();

	for (int i = 0; i < stockedBomNum; i++)
	{
		bom[i]->Draw();
		bom[i]->SetVertex();
	}

	viewer->End2D();
	viewer->Draw3D();
}