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

/**************************************
TrailColliderTag�񋓎q
***************************************/
enum class TrailColliderTag
{
	PlayerBullet,
	Enemy,
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

	void RegisterToCheckList();
	void RemoveFromCheckList();

	static void UpdateCollision();

private:
	TrailCollider() {}

	LineTrailModel model;
	float *posZ;
	TrailColliderTag tag;

	static std::map<TrailColliderTag, std::list<TrailCollider*>> checkDictionary;
};


#endif