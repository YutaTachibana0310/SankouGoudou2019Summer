//=====================================
//
//�e���v���[�g����[EnemyBulletController.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "EnemyBulletController.h"
#include "EnemyBulletModel.h"
#include "EnemyBullet.h"
#include "Framework\ResourceManager.h"

#include <algorithm>

using namespace std;

/**************************************
�}�N����`
***************************************/
#define ENEMYBULLET_NUM_MAX				(128)
#define ENEMYBULLET_VTX_SIZE			(D3DXVECTOR2(10.0f, 10.0f))
#define ENEMYBULLET_TEX_NAME			("data/TEXTURE/Enemy/EnemyBullet.png")

/**************************************
�R���X�g���N�^
***************************************/
EnemyBulletController::EnemyBulletController()
{
	//���\�[�X�쐬
	ResourceManager::Instance()->MakePolygon(RESOURCE_ENEMYBULLET_TAG, ENEMYBULLET_TEX_NAME, ENEMYBULLET_VTX_SIZE);
}

/**************************************
�f�X�g���N�^
***************************************/
EnemyBulletController::~EnemyBulletController()
{
	for (auto& bullet : modelContainer)
	{
		SAFE_DELETE(bullet);
	}
	modelContainer.clear();
}

/**************************************
�I������
***************************************/
void EnemyBulletController::Uninit()
{
	for (auto& model : modelContainer)
	{
		model->Uninit();
	}
}

/**************************************
�X�V����
***************************************/
void EnemyBulletController::Update()
{
	for (auto& model : modelContainer)
	{
		model->Update();
	}
}

/**************************************
�`�揈��
***************************************/
void EnemyBulletController::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_LIGHTING, false);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
	for (auto& model : modelContainer)
	{
		model->Draw();
	}

	pDevice->SetRenderState(D3DRS_LIGHTING, true);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
}

/**************************************
�Z�b�g����
***************************************/
void EnemyBulletController::SetEnemyBullet(vector<D3DXVECTOR3> emitters, LineTrailModel target)
{
	auto itr = find_if(modelContainer.begin(), modelContainer.end(),
		[](EnemyBulletModel* model)
	{
		return !model->active;
	});

	if (itr == modelContainer.end())
	{
		modelContainer.push_back(new EnemyBulletModel());
		itr = modelContainer.end() - 1;
	}

	(*itr)->Init(emitters, target);
}

/**************************************
��A�N�e�B�u����
***************************************/
void EnemyBulletController::DisableAll()
{
	for (auto& model : modelContainer)
	{
		if (!model->active)
			continue;

		model->Disable();
	}
}