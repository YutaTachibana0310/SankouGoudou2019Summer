//=====================================
//
//ボックスコライダー3D処理[BoxCollider3D.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "BoxCollider3D.h"

#include <list>

using namespace std;

/**************************************
マクロ定義
***************************************/

/**************************************
BoxCollider3DTag列挙子演算子
***************************************/
BoxCollider3DTag begin(BoxCollider3DTag)
{
	return BoxCollider3DTag::PlayerBomber;
}

BoxCollider3DTag end(BoxCollider3DTag)
{
	return BoxCollider3DTag::Max;
}

BoxCollider3DTag operator*(BoxCollider3DTag tag)
{
	return tag;
}

BoxCollider3DTag operator++(BoxCollider3DTag& tag)
{
	return tag = BoxCollider3DTag(std::underlying_type<BoxCollider3DTag>::type(tag) + 1);
}

/**************************************
static変数
***************************************/
UINT BoxCollider3D::instanceCount;
D3DMATERIAL9 BoxCollider3D::material;
LPD3DXMESH BoxCollider3D::mesh;
map<BoxCollider3DTag, list<BoxCollider3D*>> BoxCollider3D::checkDictionary;

/**************************************
コンストラクタ
***************************************/
BoxCollider3D::BoxCollider3D(BoxCollider3DTag tag, D3DXVECTOR3 *pPos)
{
	this->tag = tag;
	this->pPos = pPos;
	RegisterToCheckList(tag);

#ifdef BOXCOLLIDER3D_USE_DEBUG
	instanceCount++;
	if (mesh == NULL)
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		//キューブメッシュ作成
		D3DXCreateBox(pDevice,
			1.0f,
			1.0f,
			1.0f,
			&mesh,
			0);

		//マテリアル作成
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
コンストラクタ
***************************************/
BoxCollider3D::BoxCollider3D(BoxCollider3DTag tag, D3DXVECTOR3 *pPos, D3DXVECTOR3 size)
{
	this->tag = tag;
	this->size = size;
	this->pPos = pPos;
	RegisterToCheckList(tag);

#ifdef BOXCOLLIDER3D_USE_DEBUG
	instanceCount++;
	if (mesh == NULL)
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		//キューブメッシュ作成
		D3DXCreateBox(pDevice,
			1.0f,
			1.0f,
			1.0f,
			&mesh,
			0);

		//マテリアル作成
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
デストラクタ
***************************************/
BoxCollider3D::~BoxCollider3D()
{
	for (const auto& tag : BoxCollider3DTag())
	{
		RemoveFromCheckList(tag);
	}

#ifdef BOXCOLLIDER3D_USE_DEBUG
	instanceCount--;
	if (instanceCount == 0)
	{
		SAFE_RELEASE(mesh);
	}
#endif
}

/**************************************
衝突判定
***************************************/
bool BoxCollider3D::CheckCollision(BoxCollider3D *other)
{
	D3DXVECTOR3 thisPos = *(this->pPos) + this->offset;
	D3DXVECTOR3 otherPos = *(other->pPos) + other->offset;

	//X方向の判定
	if (thisPos.x + this->size.x < otherPos.x - other->size.x || thisPos.x - this->size.x > otherPos.x + other->size.x)
		return false;

	//Y方向の判定
	if (thisPos.y + this->size.y < otherPos.y - other->size.y || thisPos.y - this->size.y > otherPos.y + other->size.y)
		return false;

	//Z方向の判定
	if (thisPos.z + this->size.z < otherPos.z - other->size.z || thisPos.z - this->size.z > otherPos.z + other->size.z)
		return false;

	//衝突通知
	for (auto observer : this->observerList)
	{
		observer->OnNotified(other->tag);
	}
	for (auto observer : other->observerList)
	{
		observer->OnNotified(this->tag);
	}

	return true;
}

/**************************************
観測者追加処理
***************************************/
void BoxCollider3D::AddObserver(ColliderObserver* observer)
{
	observerList.push_back(observer);
}

/**************************************
サイズセット
***************************************/
void BoxCollider3D::SetSize(D3DXVECTOR3 size)
{
	this->size = size;
}

/**************************************
座標アドレスセット
***************************************/
void BoxCollider3D::SetPosAddress(D3DXVECTOR3 *pPos)
{
	this->pPos = pPos;
}

/**************************************
衝突リストチェック
***************************************/
void BoxCollider3D::UpdateCollision()
{
	//PlayerBomberとEnemyで衝突判定
	CheckRoundRobin(BoxCollider3DTag::PlayerBomber, BoxCollider3DTag::Enemy);

	//PlayerBulletとSnakeEnemyで衝突判定
	CheckRoundRobin(BoxCollider3DTag::PlayerBullet, BoxCollider3DTag::SnakeEnemy);
}

/**************************************
総当たり判定
***************************************/
void BoxCollider3D::CheckRoundRobin(BoxCollider3DTag tag1, BoxCollider3DTag tag2)
{
	for (auto& collider1 : checkDictionary[tag1])
	{
		if (!collider1->active)
			continue;

		for (auto& collider2 : checkDictionary[tag2])
		{
			if (!collider2->active)
				continue;

			collider1->CheckCollision(collider2);
		}
	}
}

/**************************************
衝突リスト登録処理
***************************************/
void BoxCollider3D::RegisterToCheckList(BoxCollider3DTag tag)
{
	list<BoxCollider3D*> *checkList = &checkDictionary[tag];

	//多重登録判定
	auto itr = find(checkList->begin(), checkList->end(), this);
	if (itr != checkList->end())
		return;

	//登録
	checkList->push_back(this);
}

/**************************************
衝突リスト離脱処理
***************************************/
void BoxCollider3D::RemoveFromCheckList(BoxCollider3DTag tag)
{
	list<BoxCollider3D*> *checkList = &checkDictionary[tag];

	//登録確認
	auto itr = find(checkList->begin(), checkList->end(), this);
	if (itr == checkList->end())
		return;

	//離脱
	checkList->erase(itr);
}

/**************************************
描画処理
***************************************/
#ifdef BOXCOLLIDER3D_USE_DEBUG
void BoxCollider3D::DrawCollider(BoxCollider3D *collider)
{
	if (!collider->active)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxTranslate, mtxScale, mtxWorld;
	D3DMATERIAL9 matDef;

	//デフォルトマテリアル取得
	pDevice->GetMaterial(&matDef);

	//レンダーステートとマテリアルを設定
	pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	pDevice->SetMaterial(&material);
	pDevice->SetTexture(0, NULL);

	//行列計算
	D3DXVECTOR3 pos = *(collider->pPos) + collider->offset;
	D3DXMatrixIdentity(&mtxWorld);
	D3DXMatrixScaling(&mtxScale, collider->size.x * 2, collider->size.y * 2, collider->size.z * 2);
	D3DXMatrixTranslation(&mtxTranslate, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScale);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

	//ワールド情報セット
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	//描画
	mesh->DrawSubset(0);

	//レンダーステートとマテリアル復元
	pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	pDevice->SetMaterial(&matDef);

}
#endif