//=====================================
//
//���\�[�X�}�l�[�W���w�b�_[ResourceManager.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _RESOURCEMANAGER_H_
#define _RESOURCEMANAGER_H_

#include "../main.h"
#include "BaseSingleton.h"
#include <map>

/**************************************
�O���錾
***************************************/
class MeshContainer;

/**************************************
�N���X��`
***************************************/
class ResourceManager : public BaseSingleton<ResourceManager>
{
	friend class BaseSingleton<ResourceManager>;
public:
	//�ǂݍ��݁A�������
	void LoadMesh(const char* tag, const char* path);
	void ReleaseMesh(const char* tag);

	//���\�[�X�Q�Ə���
	bool GetMesh(const char* tag, MeshContainer* pOut);

	//�S���\�[�X�������
	void AllRelease();

private:
	ResourceManager() {}
	~ResourceManager() {}

	std::map<std::string, MeshContainer*> meshPool;
};

#endif