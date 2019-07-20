//=====================================
//
//�o�b�N�O���E���h�R���g���[���w�b�_[BackGroundController.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _BACKGROUNDCONTROLLER_H_
#define _BACKGROUNDCONTROLLER_H_

#include "main.h"


#include <vector>

/**************************************
�O���錾
***************************************/
class BackGroundCity;

/**************************************
�N���X��`
***************************************/
class BackGroundController
{
public:
	BackGroundController();
	~BackGroundController();

	void Init();
	void Uninit();
	void Update();
	void Draw();

private:
	std::vector<BackGroundCity*> cityContainer;

	void CreateCityContainer();

};

#endif