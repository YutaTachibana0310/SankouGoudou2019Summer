//============================================================
//
//�v���C���[�R���g���[������[PlayerBomberController.cpp]
//Author: ����
//
//============================================================
#include "PlayerBomberController.h"
#include <algorithm>
#include "Framework\ResourceManager.h"
#include "enemy.h"
#include "GameParticleManager.h"
#include "debugWindow.h"
#include "sound.h"

#include "PlayerBomberEnemy.h"
#include "PlayerBomberBoss.h"
#include "PlayerBomberRebar.h"

using namespace std;

/*********************************************************
�}�N����`
**********************************************************/
#define BOMBER_SIZE					(20.0f)
#define BOMBER_STOCK_INTERVAL		(600)
#define BOMBER_STOCK_MAX			(3)

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

	const char* TextureName = "data/TEXTURE/Effect/PlayerBulletParticle.png";

	texture = CreateTextureFromFile((LPSTR)TextureName, pDevice);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D)* NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &vtxBuff, 0);

	VERTEX_3D *pVtx;
	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].vtx = D3DXVECTOR3(-BOMBER_SIZE / 2.0f, BOMBER_SIZE / 2.0f, 0.0f);
	pVtx[1].vtx = D3DXVECTOR3(BOMBER_SIZE / 2.0f, BOMBER_SIZE / 2.0f, 0.0f);
	pVtx[2].vtx = D3DXVECTOR3(-BOMBER_SIZE / 2.0f, -BOMBER_SIZE / 2.0f, 0.0f);
	pVtx[3].vtx = D3DXVECTOR3(BOMBER_SIZE / 2.0f, -BOMBER_SIZE / 2.0f, 0.0f);

	//���ˌ��̐ݒ�
	pVtx[0].diffuse =
		pVtx[1].diffuse =
		pVtx[2].diffuse =
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//
	pVtx[0].nor =
		pVtx[1].nor =
		pVtx[2].nor =
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//�e�N�X�`�����W�̐ݒ�

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	vtxBuff->Unlock();

	//�X�g�b�N�C���^�[�o��������
	stockInterval = BOMBER_STOCK_INTERVAL;
	stock = 1;
}

/*********************************************************
�f�X�g���N�^
**********************************************************/
PlayerBomberController::~PlayerBomberController()
{
	bomberContainer.clear();

	SAFE_RELEASE(texture);
	SAFE_RELEASE(vtxBuff);
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

	//�I�������{���o�[���R���e�i����폜
	bomberContainer.remove_if([](auto&& bomber)
	{
		return !bomber->active;
	});

	//�X�g�b�N�C���^�[�o�����X�V
	stockInterval = Min(BOMBER_STOCK_INTERVAL, stockInterval + 1);

	DebugLog("BombStock : %d", stock);
	DebugLog("BomInterval : %d", stockInterval);
}

/*********************************************
�`�揈��
**********************************************/
void PlayerBomberController::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//vtxbuff���Z�b�g

	pDevice->SetStreamSource(0, vtxBuff, 0, sizeof(VERTEX_3D));

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
�{���Z�b�g�����i�G�l�~�[�Ώہj
***************************************************/
void PlayerBomberController::SetPlayerBomber(list<std::shared_ptr<Enemy>>& targetList, D3DXVECTOR3 initpos)
{
	D3DXVECTOR3 setPos = initpos + D3DXVECTOR3(0.0f, 10.0f, 50.0f);
	float rotAngle = D3DXToRadian(360.0f / targetList.size());
	float radian = 0.0f;

	for (auto &target : targetList)
	{
		D3DXVECTOR3 dir;
		ZeroMemory(&dir, sizeof(dir));
		dir.x = sinf(radian);
		dir.y = cosf(radian);

		PlayerBomberEnemy *ptr = new PlayerBomberEnemy();
		ptr->Init(dir);
		ptr->Set(target, setPos);
		bomberContainer.push_back(std::unique_ptr<PlayerBomber>(ptr));

		radian += rotAngle;
	}

	//�X�g�b�N������
	stock--;
	stockInterval = 0;

	//���˃G�t�F�N�g�Z�b�g
	GameParticleManager::Instance()->SetBomberFire(&setPos);
}

/***************************************************
�{���Z�b�g�����i�{�X�Ώہj
***************************************************/
void PlayerBomberController::SetPlayerBomber(std::shared_ptr<BossEnemyModel> target, D3DXVECTOR3 initPos)
{
	const int EmitNum = 5;

	D3DXVECTOR3 setPos = initPos + D3DXVECTOR3(0.0f, 10.0f, 50.0f);
	float rotAngle = D3DXToRadian(360.0f / EmitNum);
	float radian = 0.0f;

	for(int i = 0; i < EmitNum; i++)
	{
		D3DXVECTOR3 dir;
		ZeroMemory(&dir, sizeof(dir));
		dir.x = sinf(radian);
		dir.y = cosf(radian);

		PlayerBomberBoss *ptr = new PlayerBomberBoss();
		ptr->Init(dir);
		ptr->Set(target, setPos);
		bomberContainer.push_back(std::unique_ptr<PlayerBomber>(ptr));

		radian += rotAngle;
	}

	//�X�g�b�N������
	stock--;
	stockInterval = 0;

	//���˃G�t�F�N�g�Z�b�g
	GameParticleManager::Instance()->SetBomberFire(&setPos);
}

/***************************************************
�{�����ˁi�S���Ώہj
***************************************************/
void PlayerBomberController::SetPlayerBomber(std::list<std::shared_ptr<RebarObstacle>>& targetList, D3DXVECTOR3 initPos)
{
	D3DXVECTOR3 setPos = initPos + D3DXVECTOR3(0.0f, 10.0f, 50.0f);
	float rotAngle = D3DXToRadian(360.0f / targetList.size());
	float radian = 0.0f;

	for (auto &target : targetList)
	{
		D3DXVECTOR3 dir;
		ZeroMemory(&dir, sizeof(dir));
		dir.x = sinf(radian);
		dir.y = cosf(radian);

		PlayerBomberRebar *ptr = new PlayerBomberRebar();
		ptr->Init(dir);
		ptr->Set(target, setPos);
		bomberContainer.push_back(std::unique_ptr<PlayerBomber>(ptr));

		radian += rotAngle;
	}

	//NOTE : �{�X�펞�A�S���ƃ{�X�ɓ����Ƀ{���o�[�𔭎˂���̂�
	//�����ł̓X�g�b�N��������A�{�X�ւ̔��˂ŏ����

	//���˃G�t�F�N�g�Z�b�g
	GameParticleManager::Instance()->SetBomberFire(&setPos);
}

/***************************************************
�X�g�b�N�̉۔���
***************************************************/
bool PlayerBomberController::CanStock()
{
	//return stockInterval >= BOMBER_STOCK_INTERVAL;
	return true;
}

/***************************************************
�{�����˂̉۔���
***************************************************/
bool PlayerBomberController::CanSet()
{
	if (stock <= 0)
		return false;

	if (stockInterval < BOMBER_STOCK_INTERVAL)
		return false;

	return true;
}

/***************************************************
�X�g�b�N�ǉ�����
***************************************************/
void PlayerBomberController::AddStock()
{
	if (stock < BOMBER_STOCK_MAX) {
		stock = Min(stock + 1, BOMBER_STOCK_MAX);
		//�X�g�b�N�ǉ�����SE
		Sound::GetInstance()->SetPlaySE(BOMBSTOCK, true, (Sound::GetInstance()->changevol / 5.0f));
	}
	//stockInterval = 0;
}

/***************************************************
�X�g�b�N���擾����
***************************************************/
int PlayerBomberController::GetStockNum()
{
	return stock;
}

/***************************************************
�`���[�W���O����
***************************************************/
bool PlayerBomberController::IsCharging()
{
	return stockInterval < BOMBER_STOCK_INTERVAL;
}
