//=====================================
//
//���[�j���OUI�w�b�_[WarningUI.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _WARNINGUI_H_
#define _WARNINGUI_H_

#include "main.h"

/**************************************
�O���錾
***************************************/
class WarningBelt;

/**************************************
�}�N���E�񋓎q��`
***************************************/

/**************************************
�N���X��`
***************************************/
class WarningUI
{
public:
	WarningUI();
	~WarningUI();

	void Update();
	void Draw();

	void StartFade(bool isFadein);

private:
	WarningBelt *upperBelt, *lowerBelt;
	bool active;
	int cntFrame;
};

#endif