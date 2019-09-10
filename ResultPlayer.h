//=====================================
//
// ResultPlayer.h
// 機能:リザルト画面のプレイヤー
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _RESULTPLAYER_H_
#define _RESULTPLAYER_H_

#include "main.h"

/**************************************
前方宣言
***************************************/
class AnimContainer;

/**************************************
クラス定義
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