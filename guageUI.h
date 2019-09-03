//=============================================================================
//
// �Q�[�W��ʏ��� [guage.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _GUAGE_H_
#define _GUAGE_H_

/**************************************
�O���錾
***************************************/
class Object;
class GuageObject;

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
class Guage
{
public:
	Guage();
	~Guage();

	void Update(void);
	void Draw(void);

	const static int maxHp = 100;

	float trueGuagePercentage;	//���ۂ̃Q�[�W�p�[�Z���e�[�W

private:
	GuageObject *damageGuage;
	GuageObject *hPGuage;
	Object *flame;
	Object *text;

	float	damageGuagePercentage;	//�_���[�W�\���Q�[�W�p�[�Z���e�[�W
};

#endif

