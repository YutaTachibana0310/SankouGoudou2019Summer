//=============================================================================
//
// Result�V�[��UI�Ǘ����� [ResultSceneUIMaager.h]
// Author : 
//
//=============================================================================
#ifndef _RESULTSCENEUIMANAGER_H_
#define _RESULTSCENEUIMANAGER_H_

#include "UIdrawer.h"

/**************************************
�O���錾
***************************************/
class Object;
class Rank;
class ResultBG;

/**************************************
�\���̒�`
***************************************/
class ResultSceneUIManager
{
public:
	ResultSceneUIManager();
	~ResultSceneUIManager();

	ResultBG *resultBG;
	Rank * rank;
	void Init(void);
	void Uninit(void);
	void Update(HWND hwnd);
	void Draw(void);
};

#endif
