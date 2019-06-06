//=====================================
//
//�G�l�~�[�����w�b�_[EnemyController.h]
//Author:�n�@�O��
//
//=====================================
#ifndef _GAMECONTROLLER_H_
#define _GAMECONTROLLER_H_

#include "main.h"


/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
//�G�l�~�[���ۃN���X
class Enemy
{
public:

	static int objNum;		//�I�u�W�F�N�g���J�E���g����


	virtual void Init(void) = 0;
	virtual void Uninit(Enemy* enemy) = 0;
	virtual void Update(HWND hWnd) = 0;
	virtual void Draw(void) = 0;

	Enemy();
	virtual ~Enemy();
};

//���i�^�C�v
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

//���^�C�v
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
