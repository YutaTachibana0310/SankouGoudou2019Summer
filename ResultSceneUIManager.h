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
class ResultBG;

/**************************************
�\���̒�`
***************************************/
class ResultSceneUI:public Object
{
public:
	ResultBG *resultBG;
	virtual void Init(void);
	virtual void Uninit(void);
	virtual void Update(HWND hwnd);
	virtual void Draw(void);
};

#endif
