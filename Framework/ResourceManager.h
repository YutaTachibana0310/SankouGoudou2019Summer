//=====================================
//
//���\�[�X�}�l�[�W���w�b�_[ResourceManager.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _RESOURCEMANAGER_H_
#define _RESOURCEMANAGER_H_

#include "..\main.h"
#include "BaseSingleton.h"
#include <map>

/**************************************
�O���錾
***************************************/
class MeshContainer;
class BoardPolygon;

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

	void LoadTexture(const char* path);
	void ReleaseTexture(const char* tag);

	void MakePolygon(const char* tag, const char* path, const D3DXVECTOR2& size, const D3DXVECTOR2& uv = D3DXVECTOR2(1.0f, 1.0f));
	void ReleasePolygon(const char* tag);

	//���\�[�X�Q�Ə���
	bool GetMesh(const char* tag, MeshContainer*&  pOut);
	bool GetTexture(const char* path, LPDIRECT3DTEXTURE9& pOut);
	bool GetPolygon(const char* tag, BoardPolygon*& pOut);

	//�S���\�[�X�������
	void AllRelease();

private:
	ResourceManager() {}
	~ResourceManager() {}

	std::map<std::string, MeshContainer*> meshPool;
	std::map<std::string, LPDIRECT3DTEXTURE9> texturePool;
	std::map<std::string, BoardPolygon*> polygonPool;
};

#endif