//=====================================
//
//�A�j���R���e�i�w�b�_[AnimContainer.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _ANIMCONTAINER_H_
#define _ANIMCONTAINER_H_

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

class AnimContainer
{
public:
	AnimContainer();
	virtual ~AnimContainer();

	HRESULT LoadAnimation(LPCSTR setName, int setNo);
	void Update(float time);
	void Draw(LPD3DXMATRIX worldMtx);
	void ChangeAnim(UINT animID, float playSpeed, bool forceChange = false);
	void SetShiftTime(UINT animID, float interval);

	HRESULT LoadXFile(LPCSTR fileName, const char* errorSrc);
	HRESULT SetupCallbackKeyFrames(LPCSTR setName);
	D3DXMATRIX GetBoneMatrix(const char* boneName);

	int keyFrameCount;							//Callback KeyFrames������������
	bool isMotionEnd;							//���Đ����Ă���A�j���[�V�������Ōォ�ǂ���
	bool isStopMove;							//�L�������ړ����~���Ă��邩�ǂ���	

private:
	LPD3DXANIMATIONCONTROLLER animController;	//�A�j���[�V�����R���g���[��
	UINT currentAnimID;							//���݂̃A�j���[�V�����ԍ�
	UINT prevAnimID;							//�O�̃A�j���[�V�����ԍ�
	AnimStatus *status;							//�A�j���[�V�����Z�b�g�̃f�[�^
	MyAllocateHierarchy *allocater;				//X�t�@�C���̏����m�ۂ���
	LPD3DXFRAME rootFrame;						//���[�g�t���[��
	int animSetNum;								//�A�j���[�V�����Z�b�g�̐�

	//���b�V���R���e�i�`�揈��
	void DrawMeshContainer(LPD3DXMESHCONTAINER meshContainerBase, LPD3DXFRAME frameBase);
	void DrawFrame(LPD3DXFRAME frame);
	HRESULT SetupBoneMatrixPointers(LPD3DXFRAME frameBase, LPD3DXFRAME frameRoot);
	void UpdateFrameMatrixes(LPD3DXFRAME frameBase, LPD3DXMATRIX parentMatrix);
	D3DXFRAME_DERIVED* SearchBoneFrame(const char* boneName, D3DXFRAME* frame);
};

struct AnimCallBackHandler : public ID3DXAnimationCallbackHandler
{
	AnimContainer *animContainer;
	LPCSTR setName;
	int animStatus;
	HRESULT CALLBACK HandleCallback(THIS_ UINT track, LPVOID pCallbackData);
};

#endif