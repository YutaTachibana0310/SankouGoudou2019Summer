//=====================================
//
//���[�j���OUI�w�b�_[WarningUI.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _WARNINGUI_H_
#define _WARNINGUI_H_

#include "main.h"
#include <vector>

/**************************************
�O���錾
***************************************/
class WarningBelt;
class WarningText;

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
	std::vector<WarningText*> textContainer;
	std::vector<WarningText*>::iterator itrText;

	bool active;
	int cntFrame;

	void CheckFinish();
	void SetTextIn();

	const int TextSetInterval;
	const int Duration;
};

#endif