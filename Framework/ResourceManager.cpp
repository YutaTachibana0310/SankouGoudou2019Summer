//=====================================
//
//���\�[�X�}�l�[�W������[ResourceManager.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "ResourceManager.h"
#include "MeshContainer.h"

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
�S���\�[�X�������
***************************************/
void ResourceManager::AllRelease()
{
	for (auto& pair : meshPool)
	{
		SAFE_DELETE(pair.second);
	}
	meshPool.clear();
}