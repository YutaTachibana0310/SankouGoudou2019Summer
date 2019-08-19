//=====================================
//
//�{�X�R���C�_�[�K�C�h�w�b�_[BossColliderGuide.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _BOSSCOLLIDERGUIDE_H_
#define _BOSSCOLLIDERGUIDE_H_

#include "main.h"
#include "Framework\BoardPolygon.h"
#include "LineTrailModel.h"

/**************************************
�O���錾
***************************************/
class BossColliderLine;
class BossColliderEdge;

/**************************************
�}�N���E�񋓎q��`
***************************************/

/**************************************
�N���X��`
***************************************/
class BossColliderGuide
{
public:
	BossColliderGuide(LineTrailModel& model);
	~BossColliderGuide();

	void Update();
	void Draw();

private:
	BossColliderEdge *edgeR, *edgeL;
	BossColliderLine *line;
};

class BossColliderLine
{
public:
	BossColliderLine(const D3DXVECTOR3& edgeR, const D3DXVECTOR3& edgeL);
	~BossColliderLine();

	void Draw();

private:
	Transform* transform;
	BoardPolygon *polygon;
};

class BossColliderEdge
{
public:
	BossColliderEdge(const D3DXVECTOR3& pos);
	BossColliderEdge();

	void Update();
	void Draw();

private:
	Transform* transform;
	BoardPolygon *polygon;
};

#endif