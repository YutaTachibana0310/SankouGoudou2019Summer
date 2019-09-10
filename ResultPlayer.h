//=====================================
//
// ResultPlayer.h
// �@�\:���U���g��ʂ̃v���C���[
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _RESULTPLAYER_H_
#define _RESULTPLAYER_H_

#include "main.h"

/**************************************
�O���錾
***************************************/
class AnimContainer;

/**************************************
�N���X��`
***************************************/
class ResultPlayer
{
public:
	ResultPlayer(bool isClear);
	~ResultPlayer();

	void Update();
	void Draw();

private:
	Transform* transform;
	AnimContainer *animation;

	enum AnimID
	{
		Clear,
		Failed,
		Max
	};

};

#endif