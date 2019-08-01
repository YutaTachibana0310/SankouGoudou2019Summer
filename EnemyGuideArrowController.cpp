//=====================================
//
//�G�l�~�[�K�C�h�A���[�R���g���[������[EnemyGuideArrowController.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "EnemyGuideArrowController.h"

#include "Framework\ResourceManager.h"
#include <algorithm>
#include "debugWindow.h"

using namespace std;

/**************************************
�}�N����`
***************************************/
#define ENEMYGUIDEARROW_SIZE		(D3DXVECTOR2(12.5f, 5.0f))
#define ENEMYGUIDEARROW_TEX_NAME	"data/TEXTURE/Enemy/GuideArrow.png"
#define ENEMYGUIDEARROW_TEX_UV		(D3DXVECTOR2(1.0f, 1.0f))

/**************************************
�R���X�g���N�^
***************************************/
EnemyGuideArrowController::EnemyGuideArrowController()
{
	//���\�[�X�쐬
	ResourceManager::Instance()->MakePolygon("EnemyGuideArrow", ENEMYGUIDEARROW_TEX_NAME, ENEMYGUIDEARROW_SIZE, ENEMYGUIDEARROW_TEX_UV);

	//�R���e�i�쐬
	for (auto& emitter : emitterContainer)
	{
		emitter = new EnemyGuideArrowEmitter();
	}
}

/**************************************
�f�X�g���N�^
***************************************/
EnemyGuideArrowController::~EnemyGuideArrowController()
{
	for (auto& emitter : emitterContainer)
	{
		SAFE_DELETE(emitter);
	}
}

/**************************************
�X�V����
***************************************/
void EnemyGuideArrowController::Update()
{
	//�\��m�F
	for (auto& reserve : reserveList)
	{
		if (reserve.cntFrame == 0)
			SetEmitter(reserve.model);

		reserve.cntFrame--;
	}

	//�G�~�b�^�[�X�V
	for (auto& emitter : emitterContainer)
	{
		emitter->Update();
	}

	//�I�������\����폜
	remove_if(reserveList.begin(), reserveList.end(), [](auto reserve)
	{
		return reserve.cntFrame < 0;
	});
}

/**************************************
�`�揈��
***************************************/
void EnemyGuideArrowController::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_LIGHTING, false);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);

	for (auto& emitter : emitterContainer)
	{
		emitter->Draw();
	}

	pDevice->SetRenderState(D3DRS_LIGHTING, true);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
}

/**************************************
�G�~�b�^�[�Z�b�g����
***************************************/
void EnemyGuideArrowController::SetEmitter(LineTrailModel model)
{
	auto itr = find_if(emitterContainer.begin(), emitterContainer.end(), [](EnemyGuideArrowEmitter* emitter)
	{
		return !emitter->active;
	});

	if (itr == emitterContainer.end())
		return;

	D3DXVECTOR3 start, end;
	model.GetEdgePos(&start, &end);
	(*itr)->Init(start, end);
}

/**************************************
�G�~�b�^�[�\�񏈗�
***************************************/
void EnemyGuideArrowController::Reserve(int delay, LineTrailModel model)
{
	reserveList.push_back(EnemyGuideReserve(delay, model));
}