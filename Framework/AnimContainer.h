//=====================================
//
//�A�j���R���e�i�w�b�_[AnimContainer.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _TEMPLATE_H_
#define _TEMPLATE_H_

#include "../main.h"
#include "MyAllocateHierarchy.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
typedef struct
{
	LPCSTR setname;					//�A�j���[�V�����Z�b�g�̖��O
	ID3DXAnimationSet *animSet;		//�A�j���[�V�����Z�b�g
	float shiftTime;				//�V�t�g����̂ɂ����鎞��
	float currentWeightTime;		//���݂̃E�F�C�g����
}AnimStatus;

typedef struct _AnimContainer
{
	LPD3DXANIMATIONCONTROLLER animController;	//�A�j���[�V�����R���g���[��
	UINT currentAnimID;							//���݂̃A�j���[�V�����ԍ�
	UINT prevAnimID;							//�O�̃A�j���[�V�����ԍ�
	AnimStatus *status;							//�A�j���[�V�����Z�b�g�̃f�[�^
	MyAllocateHierarchy *allocater;				//X�t�@�C���̏����m�ۂ���
	LPD3DXFRAME rootFrame;						//���[�g�t���[��
	int animSetNum;								//�A�j���[�V�����Z�b�g�̐�
	int keyFrameCount;							//Callback KeyFrames������������
	bool isMotionEnd;							//���Đ����Ă���A�j���[�V�������Ōォ�ǂ���
	bool isStopMove;							//�L�������ړ����~���Ă��邩�ǂ���

	HRESULT(*InitAnimation)(_AnimContainer* animation, LPCSTR setName, int setNo);
	void(*UninitAnimation)(_AnimContainer* animation);
	void(*UpdateAnimation)(_AnimContainer* animation, float time);
	void(*DrawAnimation)(_AnimContainer* animation, LPD3DXMATRIX worldMtx);
	void(*ChangeAnimation)(_AnimContainer* animation, UINT animID, float playSpeed);

	void(*SetShiftTime)(_AnimContainer* animation, UINT animID, float interval);
}AnimContainer;

struct AnimCallBackHandler : public ID3DXAnimationCallbackHandler
{
	AnimContainer *animContainer;
	LPCSTR setName;
	int animStatus;
	HRESULT CALLBACK HandleCallback(THIS_ UINT track, LPVOID pCallbackData);
};

/**************************************
�v���g�^�C�v�錾
***************************************/
AnimContainer* CreateAnimContainer(void);	//�A�j���[�V�����R���e�i���쐬
HRESULT LoadXFile(AnimContainer* animation, LPCSTR fileName, const char* errorSrc);	//X�t�@�C���̃��[�h
HRESULT SetupCallbackKeyFrames(AnimContainer* animation, LPCSTR setName);	//�A�j���[�V�������f�C�x���g��KeyFrame��ݒu����
D3DXMATRIX GetBoneMatrix(AnimContainer* animation, const char* boneName);		//����̃{�[���s��̌�������

#endif