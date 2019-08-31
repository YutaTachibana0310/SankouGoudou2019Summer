//=====================================
//
//�v���C���[�R���g���[������[PlayerBulletController.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "PlayerBulletController.h"
#include <algorithm>
#include "sound.h"

using namespace std;
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
PlayerBulletController::PlayerBulletController()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	const char* TextureName = "data/TEXTURE/Player/PlayerBullet.png";

	texture = CreateTextureFromFile((LPSTR)TextureName, pDevice);
}

/**************************************
�f�X�g���N�^
***************************************/
PlayerBulletController::~PlayerBulletController()
{
	for (auto &bullet : bulletContainer)
	{
		SAFE_DELETE(bullet);
	}
	bulletContainer.clear();

	SAFE_RELEASE(texture);
}

/**************************************
����������
***************************************/
void PlayerBulletController::Init()
{

}

/**************************************
�I������
***************************************/
void PlayerBulletController::Uninit()
{
	for (auto &bullet : bulletContainer)
	{
		bullet->Uninit();
	}
}

/**************************************
�X�V����
***************************************/
void PlayerBulletController::Update()
{
	//�o���b�g�̔j��m�F
	for (auto &bullet : bulletContainer)
	{
		if (bullet->isDestroyed)
			bullet->Uninit();
	}

	//�X�V
	for (auto &bullet : bulletContainer)
	{
		bullet->Update();
	}
}

/**************************************
�`�揈��
***************************************/
void PlayerBulletController::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetFVF(FVF_VERTEX_3D);

	pDevice->SetTexture(0, texture);

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	pDevice->SetRenderState(D3DRS_LIGHTING, false);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);

	for (auto &bullet : bulletContainer)
	{
		bullet->Draw();
	}

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	pDevice->SetRenderState(D3DRS_LIGHTING, true);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
}

/**************************************
�o���b�g�Z�b�g����
***************************************/
void PlayerBulletController::SetPlayerBullet(LineTrailModel model)
{
	auto itr = find_if(bulletContainer.begin(), bulletContainer.end(),[](PlayerBullet* bullet)
	{
		return !bullet->active;
	});

	if (itr != bulletContainer.end())
	{
		(*itr)->Init(model);
		//�V���b�gSE
		Sound::GetInstance()->SetPlaySE(PLAYERSHOT, true, 0.05f);
	}
	else
	{
		PlayerBullet *bullet = new PlayerBullet();
		bullet->Init(model);
		bulletContainer.push_back(bullet);
		//�V���b�gSE
		Sound::GetInstance()->SetPlaySE(PLAYERSHOT, true, 0.05f);
	}
}