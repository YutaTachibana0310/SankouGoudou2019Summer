//=============================================================================
//
// �Q�[�W��ʏ��� [guage.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _GUAGE_H_
#define _GUAGE_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	ADRESS_TEXTURE_GUAGEBAR		("data/TEXTURE/UI/guage/guageBar_vertical.png")		
#define	ADRESS_TEXTURE_GUAGEFLAME	("data/TEXTURE/UI/guage/guageFrame_vertical.png")		
#define	ADRESS_TEXTURE_GUAGETEXT	("data/TEXTURE/UI/guage/guageText_fever_vertical.png")		

enum GUARGE_PARTS
{
	GUAGEBAR_DAMAGE,  // �_���[�W�\���Q�[�W�o�[
	GUAGEBAR_TRUE,	  // ���ۂ̃Q�[�W�o�[
	GUAGEFLAME,
	GUAGETEXT,
};

#include "GameSceneUIManager.h"
#include "UIdrawer.h"

/**************************************
�O���錾
***************************************/
class DamageGuage;
class HPGuage;
class GuageFlame;
class GuageText;

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
class Guage :public Object
{
public:
	DamageGuage *damageGuage;
	HPGuage		*hPGuage;
	GuageFlame  *guageFlame;
	GuageText	*guageText;

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void ChangeGuage(float value);

private:
	float	damageGuagePercentage;	//�_���[�W�\���Q�[�W�p�[�Z���e�[�W
	float	trueGuagePercentage;	//���ۂ̃Q�[�W�p�[�Z���e�[�W
};

class DamageGuage :public Guage
{

};

class HPGuage :public Guage
{

};

class GuageFlame :public Guage
{

};

class GuageText :public Guage
{

};

#endif

