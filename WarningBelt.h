//=====================================
//
//���[�j���O�x���g�w�b�_[WarningBelt.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _WARNINGBELT_H_
#define _WARNINGBELT_H_

#include "main.h"
#include "Framework\Polygon2D.h"

/**************************************
�O���錾
***************************************/

/**************************************
�}�N���E�񋓎q��`
***************************************/

/**************************************
�N���X��`
***************************************/
class WarningBelt : public Polygon2D
{
	using Polygon2D::Polygon2D;
public:
	WarningBelt(float scrollDir);
	
	void Update();
	void SetFade(bool isFadein);

private:
	enum State
	{
		FadeIn,
		FadeOut,
		Idle
	};

	const float scrollDir;
	int cntFrame;
	float startAlpha, endAlpha;
	State currentState;
};

#endif