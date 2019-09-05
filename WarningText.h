//=====================================
//
//���[�j���O�e�L�X�g�w�b�_[WarningText.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _WARNINGTEXT_H_
#define _WARNINGTEXT_H_

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
class WarningText : public Polygon2D
{
public:
	enum Index
	{
		W,
		A,
		R,
		N,
		I,
		G,
		EXCLAMATION,		
	};

	WarningText(Index index);

	void Update();
	void StartAnimation(bool isIn);

private:
	enum State
	{
		In,
		Out,
		Idle
	};

	State currentState;
	int cntFrame;
	float startScale, endScale;

	static const float Size;

	void SetUV(int index);
};
#endif