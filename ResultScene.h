//=====================================
//
//���U���g�V�[���w�b�_[ResultScene.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _RESULTSCENE_H_
#define _RESULTSCENE_H_

#include "main.h"
#include "IStateScene.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
class ResultScene : public IStateScene
{
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	ResultScene() {}
	~ResultScene() {}
};

#endif