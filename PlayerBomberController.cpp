//============================================================
//
//�v���C���[�R���g���[������[PlayerBomberController.cpp]
//Author: ����
//
//============================================================
#include "PlayerBomberController.h"
#include<algorithm>


using namespace std;

/*********************************************************
�}�N����`
**********************************************************/

/********************************************************
�\���̒�`
*********************************************************/

/*********************************************************
�O���[�o���ϐ�
**********************************************************/




/*********************************************************
�R���X�g���N�^
**********************************************************/
PlayerBomberController::PlayerBomberController()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	const char* TextureName = "data/TEXTURE/Player/PlayerBullet.png";

	texture = CreateTextureFromFile((LPSTR)TextureName, pDevice);
}
/*********************************************************
�f�X�g���N�^
**********************************************************/
PlayerBomberController::~PlayerBomberController()
{
	for (auto &bomber : bomberContainer)
	{
		SAFE_DELETE(bomber);
	}
	bomberContainer.clear();

	SAFE_RELEASE(texture);

}

/*********************************************************
����������
**********************************************************/
void PlayerBomberController::Init()
{

}


/*********************************************************
�I������
**********************************************************/
void PlayerBomberController::Uninit()
{
	for (auto& bomber : bomberContainer)
	{
		bomber->Uninit();

	}
}

/*********************************************************
�X�V����
**********************************************************/
void PlayerBomberController::Update()
{
	//�X�V
	for (auto &bomber : bomberContainer)
	{
		bomber->Update();
	}
}

/*********************************************
�`�揈��
**********************************************/
void PlayerBomberController::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetFVF(FVF_VERTEX_3D);

	pDevice->SetTexture(0, texture);

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	pDevice->SetRenderState(D3DRS_LIGHTING, false);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);

	for (auto &bomber : bomberContainer)
	{
		bomber->Draw();
	}

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	pDevice->SetRenderState(D3DRS_LIGHTING, true);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);

}

/***************************************************
�{���Z�b�g����
***************************************************/
void PlayerBomberController::SetPlayerBomber(vector<D3DXVECTOR3*>targetList, D3DXVECTOR3 initpos)
{
	for (auto &target : targetList)
	{
		auto itr = find_if(bomberContainer.begin(), bomberContainer.end(), [](PlayerBomber* bomber)
		{
			return !bomber->active;
		});

		if (itr != bomberContainer.end())
		{
			(*itr)->Init();
			(*itr)->Set(target, initpos);
		}
		else
		{
			PlayerBomber *bomber = new PlayerBomber();
			bomber->Init();
			bomberContainer.push_back(bomber);
		}
	}
}





