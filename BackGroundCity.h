//=====================================
//
//�o�b�N�O���E���h�V�e�B�w�b�_[BackGroundCity.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _BACKGROUNDCITY_H_
#define _BACKGROUNDCITY_H_

#include "main.h"

/**************************************
�O���錾
***************************************/
class MeshContainer;

/**************************************
�N���X��`
***************************************/
class BackGroundCity
{
public:
	BackGroundCity(const char* meshTag);
	~BackGroundCity();

	void Init();
	void Uninit();
	void Update();
	void Draw();

	Transform transform;

private:
	MeshContainer* mesh;
	int cntFrame;
	float alpha;

	static float moveSpeed;
	static int frameFadein;
};
/**************************************
�v���g�^�C�v�錾
***************************************/
void InitBackGroundCity(int num);
void UninitBackGroundCity(int num);
void UpdateBackGroundCity(void);
void DrawBackGroundCity(void);

#endif