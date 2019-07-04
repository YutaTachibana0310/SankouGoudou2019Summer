//=====================================
//
//�{�b�N�X�R���C�_�[3D����[BoxCollider3D.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "BoxCollider3D.h"

#include <list>

using namespace std;

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/

/**************************************
static�ϐ�
***************************************/
UINT BoxCollider3D::instanceCount;
D3DMATERIAL9 BoxCollider3D::material;
LPD3DXMESH BoxCollider3D::mesh;
map<BoxCollider3DTag, list<BoxCollider3D*>> BoxCollider3D::checkDictionary;

/**************************************
�R���X�g���N�^
***************************************/
BoxCollider3D::BoxCollider3D(BoxCollider3DTag tag, D3DXVECTOR3 *pPos)
{
	this->tag = tag;
	this->pPos = pPos;
	RegisterToCheckList();

#ifdef BOXCOLLIDER3D_USE_DEBUG
	instanceCount++;
	if (mesh == NULL)
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		//�L���[�u���b�V���쐬
		D3DXCreateBox(pDevice,
			1.0f,
			1.0f,
			1.0f,
			&mesh,
			0);

		//�}�e���A���쐬
		ZeroMemory(&material, sizeof(material));
		material.Diffuse.r = 1.0f;
		material.Diffuse.a = 1.0f;
		material.Ambient.r = 1.0f;
		material.Ambient.a = 1.0f;
		material.Specular.r = 1.0f;
		material.Specular.a = 1.0f;
		material.Emissive.r = 1.0f;
		material.Emissive.a = 1.0f;
	}
#endif
}

/**************************************
�R���X�g���N�^
***************************************/
BoxCollider3D::BoxCollider3D(BoxCollider3DTag tag, D3DXVECTOR3 *pPos, D3DXVECTOR3 size)
{
	this->tag = tag;
	this->size = size;
	this->pPos = pPos;
	RegisterToCheckList();

#ifdef BOXCOLLIDER3D_USE_DEBUG
	instanceCount++;
	if (mesh == NULL)
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		//�L���[�u���b�V���쐬
		D3DXCreateBox(pDevice,
			1.0f,
			1.0f,
			1.0f,
			&mesh,
			0);

		//�}�e���A���쐬
		ZeroMemory(&material, sizeof(material));
		material.Diffuse.r = 1.0f;
		material.Diffuse.a = 1.0f;
		material.Ambient.r = 1.0f;
		material.Ambient.a = 1.0f;
		material.Specular.r = 1.0f;
		material.Specular.a = 1.0f;
		material.Emissive.r = 1.0f;
		material.Emissive.a = 1.0f;
	}
#endif
}

/**************************************
�f�X�g���N�^
***************************************/
BoxCollider3D::~BoxCollider3D()
{
	RemoveFromCheckList();

#ifdef BOXCOLLIDER3D_USE_DEBUG
	instanceCount--;
	if (instanceCount == 0)
	{
		SAFE_RELEASE(mesh);
	}
#endif
}

/**************************************
�Փ˔���
***************************************/
bool BoxCollider3D::CheckCollision(BoxCollider3D *other)
{
	D3DXVECTOR3 thisPos = *(this->pPos) + this->offset;
	D3DXVECTOR3 otherPos = *(other->pPos) + other->offset;

	//X�����̔���
	if (thisPos.x + this->size.x < otherPos.x - other->size.x || thisPos.x - this->size.x > otherPos.x + other->size.x)
		return false;

	//Y�����̔���
	if (thisPos.y + this->size.y < otherPos.y - other->size.y || thisPos.y - this->size.y > otherPos.y + other->size.y)
		return false;

	//Z�����̔���
	if (thisPos.z + this->size.z < otherPos.z - other->size.z || thisPos.z - this->size.z > otherPos.z + other->size.z)
		return false;

	//�Փ˒ʒm
	this->NotifyObservers();
	other->NotifyObservers();

	return true;
}

/**************************************
�T�C�Y�Z�b�g
***************************************/
void BoxCollider3D::SetSize(D3DXVECTOR3 size)
{
	this->size = size;
}

/**************************************
���W�A�h���X�Z�b�g
***************************************/
void BoxCollider3D::SetPosAddress(D3DXVECTOR3 *pPos)
{
	this->pPos = pPos;
}

/**************************************
�Փ˃��X�g�`�F�b�N
***************************************/
void BoxCollider3D::UpdateCollision()
{
	//PlayerBomber��Enemy�ŏՓ˔���
	for (auto &bomber : checkDictionary[BoxCollider3DTag::PlayerBomber])
	{
		if (!bomber->active)
			continue;

		for (auto &enemy : checkDictionary[BoxCollider3DTag::Enemy])
		{
			if (!enemy->active)
				continue;

			bomber->CheckCollision(enemy);
		}
	}
}

/**************************************
�Փ˃��X�g�o�^����
***************************************/
void BoxCollider3D::RegisterToCheckList()
{
	list<BoxCollider3D*> *checkList = &checkDictionary[tag];

	//���d�o�^����
	auto itr = find(checkList->begin(), checkList->end(), this);
	if (itr != checkList->end())
		return;

	//�o�^
	checkList->push_back(this);
}

/**************************************
�Փ˃��X�g���E����
***************************************/
void BoxCollider3D::RemoveFromCheckList()
{
	list<BoxCollider3D*> *checkList = &checkDictionary[tag];

	//�o�^�m�F
	auto itr = find(checkList->begin(), checkList->end(), this);
	if (itr == checkList->end())
		return;

	//���E
	checkList->erase(itr);
}

/**************************************
�`�揈��
***************************************/
#ifdef BOXCOLLIDER3D_USE_DEBUG
void BoxCollider3D::DrawCollider(BoxCollider3D *collider)
{
	if (!collider->active)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxTranslate, mtxScale, mtxWorld;
	D3DMATERIAL9 matDef;

	//�f�t�H���g�}�e���A���擾
	pDevice->GetMaterial(&matDef);

	//�����_�[�X�e�[�g�ƃ}�e���A����ݒ�
	pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	pDevice->SetMaterial(&material);
	pDevice->SetTexture(0, NULL);

	//�s��v�Z
	D3DXVECTOR3 pos = *(collider->pPos) + collider->offset;
	D3DXMatrixIdentity(&mtxWorld);
	D3DXMatrixScaling(&mtxScale, collider->size.x * 2, collider->size.y * 2, collider->size.z * 2);
	D3DXMatrixTranslation(&mtxTranslate, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScale);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

	//���[���h���Z�b�g
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	//�`��
	mesh->DrawSubset(0);

	//�����_�[�X�e�[�g�ƃ}�e���A������
	pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	pDevice->SetMaterial(&matDef);

}
#endif