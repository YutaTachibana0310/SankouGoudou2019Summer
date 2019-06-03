//=====================================
//
//�e���v���[�g����[BackGroundCity.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "BackGroundCity.h"
#include "Framework\MeshContainer.h"
#include "SkyBox.h"

/**************************************
�}�N����`
***************************************/
#define BACKGROUNDCITY_MODEL_FILE		"data/MODEL/City/city00.x"
#define BACKGROUNDCITY_NUM_MAX			(1)

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
static D3DXVECTOR3 cityPos[BACKGROUNDCITY_NUM_MAX] = {
	D3DXVECTOR3(0.0f, 0.0f, 100.0f)
};

static D3DXVECTOR3 cityRot[BACKGROUNDCITY_NUM_MAX] = {
	D3DXVECTOR3(0.0f, 0.0f, 0.0f)
};

static D3DXVECTOR3 cityScale[BACKGROUNDCITY_NUM_MAX] = {
	D3DXVECTOR3(1.0f, 1.0f, 1.0f)
};

static MeshContainer* meshContainer;

/**************************************
�v���g�^�C�v�錾
***************************************/

/**************************************
����������
***************************************/
void InitBackGroundCity(int num)
{
	meshContainer = new MeshContainer();
	meshContainer->Load(BACKGROUNDCITY_MODEL_FILE);

}

/**************************************
�I������
***************************************/
void UninitBackGroundCity(int num)
{
	delete meshContainer;
}

/**************************************
�X�V����
***************************************/
void UpdateBackGroundCity(void)
{

}

/**************************************
�`�揈��
***************************************/
void DrawBackGroundCity(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxWorld, mtxTranslate, mtxRot, mtxScale;
	D3DMATERIAL9 matDef;

	pDevice->GetMaterial(&matDef);

	for (int i = 0; i < BACKGROUNDCITY_NUM_MAX; i++)
	{
		D3DXMatrixIdentity(&mtxWorld);

		//Scale
		D3DXMatrixScaling(&mtxScale, cityScale[i].x, cityScale[i].y, cityScale[i].z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScale);

		//Rotate
		D3DXMatrixRotationYawPitchRoll(&mtxRot, cityRot[i].y, cityRot[i].x, cityRot[i].z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

		//Translate
		D3DXMatrixTranslation(&mtxTranslate, cityPos[i].x, cityPos[i].y, cityPos[i].z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

		pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
		meshContainer->Draw();

		pDevice->SetMaterial(&matDef);
	}
}