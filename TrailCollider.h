//=====================================
//
//�g���C���R���C�_�[�w�b�_[TrailCollider.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _TRAILCOLLIDER_H_
#define _TRAILCOLLIDER_H_

#include "main.h"
#include "Framework\ObserveSubject.h"
#include "LineTrailModel.h"
#include <list>
#include <map>
#include <string>

#define TRAILCOLLIDER_USE_DEBUG

#ifdef TRAILCOLLIDER_USE_DEBUG
#include "LineRenderer.h"
#endif

/**************************************
TrailColliderTag�񋓎q
***************************************/
enum class TrailColliderTag
{
	PlayerBullet,
	Enemy,
	EnemyBullet,
	Player,
	Max
};

/**************************************
�n�_�E�I�_��`
***************************************/

/**************************************
�g���C���R���C�_�[�N���X
***************************************/
class TrailCollider : public ObserveSubject
{
public:
	friend class TrailCollider;

	TrailCollider(TrailColliderTag tag);
	~TrailCollider();

	bool CheckCollision(TrailCollider *other);
	void SetTrailIndex(LineTrailModel model);
	void SetAddressZ(float* adrPosZ);

	bool active;
	UINT uniquID;

	static void UpdateCollision();

	static void DrawCollider(TrailCollider *collider);

private:
	TrailCollider() {}

	LineTrailModel model;
	float *posZ;
	TrailColliderTag tag;

	static std::map<TrailColliderTag, std::list<TrailCollider*>> checkDictionary;

	void RegisterToCheckList();
	void RemoveFromCheckList();
	
	static UINT instanceCount;
#ifdef TRAILCOLLIDER_USE_DEBUG
	static LineRenderer *renderer;
#endif
};


#endif