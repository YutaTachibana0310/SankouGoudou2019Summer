//=====================================
//
//�{�X�R���C�_�[�R���g���[������[BossColliderController.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "BossColliderController.h"
#include "Framework\ResourceManager.h"
#include "BossColliderGuide.h"
#include "BossEnemyModel.h"

using namespace std;
/**************************************
�}�N����`
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
BossColliderController::BossColliderController(BossEnemyModel& model) : posZ(500.0f), model(model)
{
	//�|���S������
	ResourceManager::Instance()->MakePolygon("BossColliderEdge", "data/TEXTURE/Enemy/BossColliderEdge.png", D3DXVECTOR2(40.0f, 40.0f));
	ResourceManager::Instance()->MakePolygon("BossColliderLine", "data/TEXTURE/Enemy/BossCollider.png", D3DXVECTOR2(0.5f, 20.0f));
}

/**************************************
�f�X�g���N�^
***************************************/
BossColliderController::~BossColliderController()
{
	for (auto&& guide : guideList)
	{
		SAFE_DELETE(guide);
	}
	guideList.clear();

	for (auto&& collider : colliderList)
	{
		SAFE_DELETE(collider);
	}
	colliderList.clear();
}

/**************************************
�X�V����
***************************************/
void BossColliderController::Update()
{
	for (auto&& guide : guideList)
	{
		guide->Update();
	}
}

/**************************************
�`�揈��
***************************************/
void BossColliderController::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
	pDevice->SetRenderState(D3DRS_ZENABLE, false);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	pDevice->SetRenderState(D3DRS_LIGHTING, false);

	for (auto&& guide : guideList)
	{
		guide->Draw();
	}

	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
	pDevice->SetRenderState(D3DRS_ZENABLE, true);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pDevice->SetRenderState(D3DRS_LIGHTING, true);
}

/**************************************
�Z�b�g����
***************************************/
void BossColliderController::SetCollider(const std::vector<int>& edgeList)
{
	const UINT EdgeMax = edgeList.size() - 1;
	for (UINT i = 0; i < EdgeMax; i++)
	{
		LineTrailModel model = LineTrailModel(edgeList[i], edgeList[i + 1]);
		guideList.push_back(new BossColliderGuide(model));
	
		TrailCollider *collider = new TrailCollider(TrailColliderTag::Enemy);
		collider->SetTrailIndex(model);
		collider->SetAddressZ(&posZ);

		//TODO�F�R���C�_�[�̗L�����ƃI�u�U�[�o�[�̒ǉ�
		collider->AddObserver(this);
	}
}

/**************************************
�S��������
***************************************/
void BossColliderController::DeleteAll()
{
	for (auto&& guide : guideList)
	{
		SAFE_DELETE(guide);
	}
	guideList.clear();

	for (auto&& collider : colliderList)
	{
		SAFE_DELETE(collider);
	}
	colliderList.clear();
}

/**************************************
�����蔻��ʒm����
***************************************/
void BossColliderController::OnNotified(ObserveSubject* notifier)
{
	model.OnDamage();
}