//=====================================
//
//�o�b�N�O���E���h�V�e�B����[BackGroundCity.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "BackGroundCity.h"
#include "Framework\MeshContainer.h"
#include "Framework\Easing.h"
#include "Framework\ResourceManager.h"

/**************************************
�}�N����`
***************************************/
#define BACKGROUNDCITY_INIT_SCALE_Y		(6.0f)
#define BACKGROUNDCITY_INIT_SCALE_XZ	(3.0f)

#define BACKGROUNDCITY_BORDER_Z			(-500.0f)

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
float BackGroundCity::moveSpeed = 55.0f;
int BackGroundCity::frameFadein = 30;

/**************************************
�R���X�g���N�^
***************************************/
BackGroundCity::BackGroundCity(const char* meshTag)
{
	//���b�V���̓ǂݍ���
	ResourceManager::Instance()->GetMesh(meshTag, &mesh);

	//�X�P�[��������
	transform.scale.x = BACKGROUNDCITY_INIT_SCALE_XZ;
	transform.scale.y = BACKGROUNDCITY_INIT_SCALE_Y;
	transform.scale.z = BACKGROUNDCITY_INIT_SCALE_XZ;
}

/**************************************
�f�X�g���N�^
***************************************/
BackGroundCity::~BackGroundCity()
{
	mesh = NULL;
}

/**************************************
����������
***************************************/
void BackGroundCity::Init()
{
	cntFrame = 0;
}

/**************************************
�I������
***************************************/
void BackGroundCity::Uninit()
{

}

/**************************************
�X�V����
***************************************/
void BackGroundCity::Update()
{
	transform.pos.z -= moveSpeed;

	//�t�F�[�h�C��
	if (cntFrame < frameFadein)
	{
		cntFrame++;
		alpha = (float)cntFrame / (float)frameFadein;
	}

	//�ړ�
	if (transform.pos.z < BACKGROUNDCITY_BORDER_Z)
	{
		//TODO:�}�W�b�N�i���o�[����
		transform.pos.z += 28800.0f;
		Init();
	}


}

/**************************************
�`�揈��
***************************************/
void BackGroundCity::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxWorld;

	//���[���h�s��ݒ�
	transform.CalcWorldMtx(&mtxWorld);
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	//�`��
	mesh->SetMaterialAlpha(alpha);
	mesh->Draw();
}