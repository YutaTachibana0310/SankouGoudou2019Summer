//=====================================
//
//プレイヤートレイルヘッダ[PlayerTrail.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _PLAYERTRAIL_H_
#define _PLAYERTRAIL_H_

#include "main.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class PlayerTrail
{
public:
	PlayerTrail();
	~PlayerTrail();

	void Init(D3DXVECTOR3 *pos);
	void Uninit();
	void Update();
	void Draw();

private:
	bool active;
	bool flgFadeout;
	float scale;
	int cntFrame;

	LPDIRECT3DVERTEXBUFFER9 lineBuff;
	LPDIRECT3DVERTEXBUFFER9 edgeBuff;
	LPDIRECT3DTEXTURE9 texture;

	D3DXVECTOR3 rightPos, leftPos;
	D3DXVECTOR3 *playerPos;

	void MakeLineBuffer();
	void MakeEdgeBuffer();

	void SetLine();

};


#endif