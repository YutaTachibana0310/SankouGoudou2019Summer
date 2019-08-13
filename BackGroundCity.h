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
	void Update(float speed);
	void Draw(D3DXMATRIX mtxParent);

	Transform transform;

	static float depthMaxZ;

private:
	MeshContainer* mesh;

};

#endif