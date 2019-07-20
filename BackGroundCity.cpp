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
#define BACKGROUNDCITY_INIT_SCALE_Y		(15.0f)
#define BACKGROUNDCITY_INIT_SCALE_XZ	(5.5f)

#define BACKGROUNDCITY_BORDER_Z			(-500.0f)

#define BACKGROUNDCITY_POSY_MIN			(-15)
#define BACKGROUNDCITY_POSY_MAX			(-10)
#define BACKGROUNDCITY_POSY_MAGNI		(200.0f);

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
float BackGroundCity::moveSpeed = 75.0f;
int BackGroundCity::frameFadein = 300;
float BackGroundCity::depthMaxZ = 0.0f;

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

	transform.Rotate(0.0f, 45.0f * RandomRange(0, 8), 0.0f);

	transform.pos.y = RandomRange(BACKGROUNDCITY_POSY_MIN, BACKGROUNDCITY_POSY_MAX) * BACKGROUNDCITY_POSY_MAGNI;
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
		transform.pos.z += depthMaxZ;
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
	//mesh->SetMaterialAlpha(alpha);
	mesh->Draw();
}