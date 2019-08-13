//=====================================
//
//���\�[�X�}�l�[�W������[ResourceManager.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "ResourceManager.h"
#include "MeshContainer.h"
#include "BoardPolygon.h"

using namespace std;

/**************************************
�}�N����`
***************************************/

/**************************************
���b�V���ǂݍ��ݏ���
***************************************/
void ResourceManager::LoadMesh(const char* tag, const char* path)
{
	string tagStr = string(tag);

	//�^�O�̏d���m�F
	if (meshPool.count(tagStr) != 0)
		SAFE_DELETE(meshPool[tagStr]);

	//���b�V���R���e�i�𐶐����ă��[�h
	meshPool[tagStr] = new MeshContainer();
	meshPool[tagStr]->Load(path);
}

/**************************************
���b�V���������
***************************************/
void ResourceManager::ReleaseMesh(const char* tag)
{
	string tagStr = string(tag);

	//�^�O�̓o�^�m�F
	if (meshPool.count(tagStr) == 0)
		return;

	//���b�V���R���e�i���폜
	SAFE_DELETE(meshPool[tagStr]);
	meshPool.erase(tagStr);
}

/**************************************
���b�V���擾����
***************************************/
bool ResourceManager::GetMesh(const char* tag, MeshContainer** pOut)
{
	string tagStr = string(tag);

	//�o�^�m�F
	if (meshPool.count(tagStr) == 0)
		return false;

	//���b�V���ւ̎Q�Ƃ��i�[
	*pOut = meshPool[tagStr];
	return true;
}

/**************************************
�e�N�X�`���ǂݍ��ݏ���
***************************************/
void ResourceManager::LoadTexture(const char* tag, const char* path)
{
	string tagStr = string(tag);

	//�d���m�F
	if (texturePool.count(tagStr) != 0)
		SAFE_RELEASE(texturePool[tagStr]);

	//�ǂݍ���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXCreateTextureFromFile(pDevice, path, &texturePool[tagStr]);
}

/**************************************
�e�N�X�`���������
***************************************/
void ResourceManager::ReleaseTexture(const char* tag)
{
	string tagStr = string(tag);

	//�o�^�m�F
	if (texturePool.count(tagStr) == 0)
		return;

	SAFE_RELEASE(texturePool[tagStr]);
}

/**************************************
�e�N�X�`���Q�Ə���
***************************************/
bool ResourceManager::GetTexture(const char* tag, LPDIRECT3DTEXTURE9* pOut)
{
	string tagStr = string(tag);

	//�o�^�m�F
	if (texturePool.count(tagStr) == 0)
		return false;

	*pOut = texturePool[tagStr];
	return true;
}

/**************************************
�|���S���쐬����
***************************************/
void ResourceManager::MakePolygon(const char* tag, const char* path, D3DXVECTOR2 size, D3DXVECTOR2 uv)
{
	string tagStr = string(tag);

	//�o�^�m�F
	if (polygonPool.count(tagStr) == 0)
		SAFE_DELETE(polygonPool[tagStr]);

	//BoardPolygon�N���X�𐶐����ēo�^
	polygonPool[tagStr] = new BoardPolygon();;
	polygonPool[tagStr]->SetSize(size);
	polygonPool[tagStr]->SetTexDiv(uv);
	polygonPool[tagStr]->LoadTexture(path);
}

/**************************************
�|���S���������
***************************************/
void ResourceManager::ReleasePolygon(const char* tag)
{
	string tagStr = string(tag);

	//�o�^�m�F
	if (polygonPool.count(tagStr) == 0)
		return;

	SAFE_DELETE(polygonPool[tagStr]);
}

/**************************************
�|���S���Q�Ə���
***************************************/
bool ResourceManager::GetPolygon(const char* tag, BoardPolygon** pOut)
{
	string tagStr = string(tag);

	//�o�^�m�F
	if (polygonPool.count(tagStr) == 0)
		return false;

	*pOut = polygonPool[tagStr];
	return true;
}

/**************************************
�S���\�[�X�������
***************************************/
void ResourceManager::AllRelease()
{
	for (auto& pair : meshPool)
	{
		SAFE_DELETE(pair.second);
	}
	meshPool.clear();

	for (auto& pair : texturePool)
	{
		SAFE_RELEASE(pair.second);
	}
	texturePool.clear();

	for (auto& pair : polygonPool)
	{
		SAFE_DELETE(pair.second);
	}
	polygonPool.clear();
}