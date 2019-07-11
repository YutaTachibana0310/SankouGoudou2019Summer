//=====================================
//
//リソースマネージャヘッダ[ResourceManager.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _RESOURCEMANAGER_H_
#define _RESOURCEMANAGER_H_

#include "../main.h"
#include "BaseSingleton.h"
#include <map>

/**************************************
前方宣言
***************************************/
class MeshContainer;

/**************************************
クラス定義
***************************************/
class ResourceManager : public BaseSingleton<ResourceManager>
{
	friend class BaseSingleton<ResourceManager>;
public:
	//読み込み、解放処理
	void LoadMesh(const char* tag, const char* path);
	void ReleaseMesh(const char* tag);

	//リソース参照処理
	bool GetMesh(const char* tag, MeshContainer* pOut);

	//全リソース解放処理
	void AllRelease();

private:
	ResourceManager() {}
	~ResourceManager() {}

	std::map<std::string, MeshContainer*> meshPool;
};

#endif