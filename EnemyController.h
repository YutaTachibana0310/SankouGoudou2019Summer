//=====================================
//
//エネミー処理ヘッダ[EnemyController.h]
//Author:馬　前程
//
//=====================================
#ifndef _GAMECONTROLLER_H_
#define _GAMECONTROLLER_H_

#include "main.h"


/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
//エネミー抽象クラス
class Enemy
{
public:

	static int objNum;		//オブジェクトをカウントする


	virtual void Init(void) = 0;
	virtual void Uninit(Enemy* enemy) = 0;
	virtual void Update(HWND hWnd) = 0;
	virtual void Draw(void) = 0;

	Enemy();
	virtual ~Enemy();
};

//直進タイプ
class EnemyStraight : public Enemy
{
public:

	void Init(void);
	void Uninit(Enemy* enemy);
	void Update(HWND hWnd);
	void Draw(void);

	EnemyStraight(void);
	~EnemyStraight();

};

//横タイプ
class  EnemyFlat : public Enemy
{
public:

	void Init(void);
	void Uninit(Enemy* enemy);
	void Update(HWND hWnd);
	void Draw(void);

	EnemyFlat();
	~EnemyFlat();
};
#endif
