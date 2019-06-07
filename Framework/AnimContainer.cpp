//=====================================
//
//�A�j���R���e�i����[AnimContainer.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "AnimContainer.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�v���g�^�C�v�錾
***************************************/

/**************************************
�{�[���s��̃|�C���^�̏���
***************************************/
HRESULT AnimContainer::SetupBoneMatrixPointers(LPD3DXFRAME frameBase, LPD3DXFRAME frameRoot)
{
	if (frameBase->pMeshContainer != NULL)
	{
		D3DXFRAME_DERIVED* frame = NULL;
		D3DXMESHCONTAINER_DERIVED* meshContainer = (D3DXMESHCONTAINER_DERIVED*)frameBase->pMeshContainer;

		//�X�L�����b�V���������Ă�����{�[���s�����������
		if (meshContainer->pSkinInfo != NULL)
		{
			UINT cBones = meshContainer->pSkinInfo->GetNumBones();
			meshContainer->boneMatrices = new D3DXMATRIX*[cBones];
			for (UINT iBone = 0; iBone < cBones; iBone++)
			{
				frame = (D3DXFRAME_DERIVED*)D3DXFrameFind(frameRoot, meshContainer->pSkinInfo->GetBoneName(iBone));
				if (frame == NULL)
					return E_FAIL;

				meshContainer->boneMatrices[iBone] = &frame->combiendTransformMatrix;
			}
		}
	}

	//�Z��t���[���̃{�[�����Z�b�g�A�b�v
	if (frameBase->pFrameSibling != NULL)
	{
		if (FAILED(SetupBoneMatrixPointers(frameBase->pFrameSibling, frameRoot)))
			return E_FAIL;
	}

	//�q�t���[���̃{�[�����Z�b�g�A�b�v
	if (frameBase->pFrameFirstChild != NULL)
	{
		if (FAILED(SetupBoneMatrixPointers(frameBase->pFrameFirstChild, frameRoot)))
			return E_FAIL;
	}


	return S_OK;
}

/**************************************
�t���[���̕`�揈��
***************************************/
void AnimContainer::DrawFrame(LPD3DXFRAME frame)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	LPD3DXMESHCONTAINER meshContainer;

	if (frame == NULL)
	{
		return;
	}

	meshContainer = frame->pMeshContainer;
	while (meshContainer != NULL)
	{
		DrawMeshContainer(meshContainer, frame);
		meshContainer = meshContainer->pNextMeshContainer;
	}

	DrawFrame(frame->pFrameSibling);
	DrawFrame(frame->pFrameFirstChild);
}

/**************************************
���b�V���R���e�i�̕`�揈��
***************************************/
void AnimContainer::DrawMeshContainer(LPD3DXMESHCONTAINER meshContainerBase, LPD3DXFRAME frameBase)
{
	D3DXMESHCONTAINER_DERIVED* meshContainer = (D3DXMESHCONTAINER_DERIVED*)meshContainerBase;
	D3DXFRAME_DERIVED* frame = (D3DXFRAME_DERIVED*)frameBase;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	UINT iMaterial;
	UINT numBlend;
	UINT iAttrb;
	DWORD attrbIdPrev;
	LPD3DXBONECOMBINATION boneComb;

	UINT iMatrixIndex;
	D3DXMATRIXA16 mtxTemp;
	D3DCAPS9 caps;
	pDevice->GetDeviceCaps(&caps);

	//�X�L�����b�V���̏ꍇ�̕`��
	if (meshContainer->pSkinInfo != NULL)
	{
		attrbIdPrev = UNUSED32;
		boneComb = reinterpret_cast<LPD3DXBONECOMBINATION>(meshContainer->boneCombinationBuf->GetBufferPointer());

		for (iAttrb = 0; iAttrb < meshContainer->boneNum; iAttrb++)
		{
			numBlend = 0;
			for (DWORD i = 0; i < meshContainer->boneWeightNum; i++)
			{
				if (boneComb[iAttrb].BoneId[i] != UINT_MAX)
				{
					numBlend = i;
				}
			}

			if (caps.MaxVertexBlendMatrices >= numBlend + 1)
			{
				for (DWORD i = 0; i < meshContainer->boneWeightNum; i++)
				{
					iMatrixIndex = boneComb[iAttrb].BoneId[i];
					if (iMatrixIndex != UINT_MAX)
					{
						D3DXMatrixMultiply(&mtxTemp, &meshContainer->boneOffsetMatrices[iMatrixIndex],
							meshContainer->boneMatrices[iMatrixIndex]);
						pDevice->SetTransform(D3DTS_WORLDMATRIX(i), &mtxTemp);
					}
				}

				pDevice->SetRenderState(D3DRS_VERTEXBLEND, numBlend);

				if ((attrbIdPrev != boneComb[iAttrb].AttribId) || (attrbIdPrev == UNUSED32))
				{
					pDevice->SetMaterial(&meshContainer->pMaterials[boneComb[iAttrb].AttribId].MatD3D);
					pDevice->SetTexture(0, meshContainer->textures[boneComb[iAttrb].AttribId]);
					attrbIdPrev = boneComb[iAttrb].AttribId;
				}

				meshContainer->MeshData.pMesh->DrawSubset(iAttrb);
			}
		}
		pDevice->SetRenderState(D3DRS_VERTEXBLEND, 0);
	}
	//�ʏ탁�b�V���̕`��
	else
	{
		pDevice->SetTransform(D3DTS_WORLD, &frame->combiendTransformMatrix);
		for (iMaterial = 0; iMaterial < meshContainer->NumMaterials; iMaterial++)
		{
			pDevice->SetMaterial(&meshContainer->pMaterials[iMaterial].MatD3D);
			pDevice->SetTexture(0, meshContainer->textures[iMaterial]);
			meshContainer->MeshData.pMesh->DrawSubset(iMaterial);
		}
	}
}

/**************************************
�t���[���s��̍X�V
***************************************/
void AnimContainer::UpdateFrameMatrixes(LPD3DXFRAME frameBase, LPD3DXMATRIX parentMatrix)
{
	D3DXFRAME_DERIVED* frame = (D3DXFRAME_DERIVED*)frameBase;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (frameBase == NULL || parentMatrix == NULL)
	{
		return;
	}

	D3DXMatrixMultiply(&frame->combiendTransformMatrix, &frame->TransformationMatrix, parentMatrix);

	UpdateFrameMatrixes(frame->pFrameSibling, parentMatrix);
	UpdateFrameMatrixes(frame->pFrameFirstChild, &frame->combiendTransformMatrix);
}

/**************************************
X�t�@�C���̓ǂݍ���
***************************************/
HRESULT AnimContainer::LoadXFile(LPCSTR fileName, const char* errorSrc)
{
	char message[64];
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	allocater = new MyAllocateHierarchy();

	if (FAILED(D3DXLoadMeshHierarchyFromX(fileName,
		D3DXMESH_MANAGED,
		pDevice,
		allocater,
		NULL,
		&rootFrame,
		&animController)))
	{
		sprintf_s(message, "Load %s Model Failed", errorSrc);
		MessageBox(0, message, "Error", 0);
		return E_FAIL;
	}

	if (FAILED(SetupBoneMatrixPointers(rootFrame, rootFrame)))
	{
		return E_FAIL;
	}

	isMotionEnd = false;
	animSetNum = animController->GetNumAnimationSets();
	status = new AnimStatus[animSetNum];

	return S_OK;
}

/**************************************
����̃{�[���s��̎擾
***************************************/
D3DXMATRIX AnimContainer::GetBoneMatrix(const char* boneName)
{
	char message[64];
	D3DXFRAME_DERIVED* frame = (D3DXFRAME_DERIVED*)SearchBoneFrame(boneName, rootFrame);

	//���������ꍇ
	if (frame != NULL && frame->Name != NULL && strcmp(frame->Name, boneName) == 0)
	{
		return frame->combiendTransformMatrix;
	}
	//������Ȃ������ꍇ
	else
	{
		sprintf_s(message, "Find %s Bone Failed!", boneName);
		MessageBox(0, message, "Error", 0);
		D3DXMATRIX tmpMatrix;
		D3DXMatrixIdentity(&tmpMatrix);
		return tmpMatrix;
	}
}

/**************************************
����̃{�[����T��
***************************************/
D3DXFRAME_DERIVED* AnimContainer::SearchBoneFrame(const char* boneName, D3DXFRAME* frame)
{
	D3DXFRAME_DERIVED* p = NULL;

	if (frame == NULL)
	{
		return NULL;
	}

	if (frame->Name != NULL && strcmp(frame->Name, boneName) == 0)
	{
		p = (D3DXFRAME_DERIVED*)frame;
		return p;
	}

	if (frame->pFrameSibling != NULL)
	{
		p = SearchBoneFrame(boneName, frame->pFrameSibling);
		if (p != NULL && strcmp(p->Name, boneName) == 0)
		{
			return p;
		}
	}

	if (frame->pFrameFirstChild != NULL)
	{
		p = SearchBoneFrame(boneName, frame->pFrameFirstChild);
		if (p != NULL && strcmp(p->Name, boneName) != 0)
		{
			return p;
		}
	}

	return NULL;

}

/**************************************
�A�j���[�V�����ǂݍ��ݏ���
***************************************/
HRESULT AnimContainer::LoadAnimation(LPCSTR setName, int setNo)
{
	char message[64];

	if (FAILED(animController->GetAnimationSetByName(setName, &status[setNo].animSet)))
	{
		sprintf_s(message, "Can't find %s Animationset !", setName);
		MessageBox(0, message, "Error", 0);
		return E_FAIL;
	}

	status[setNo].setname = status[setNo].animSet->GetName();

	return S_OK;
}

/**************************************
�I������
***************************************/
AnimContainer::~AnimContainer()
{
	D3DXFrameDestroy(rootFrame, allocater);

	SAFE_DELETE(status);
	SAFE_RELEASE(animController);
	SAFE_DELETE(allocater);
}

/**************************************
�X�V����
***************************************/
void AnimContainer::Update(float time)
{
	AnimCallBackHandler callBackHandler;
	callBackHandler.animContainer = this;
	callBackHandler.setName = status[currentAnimID].setname;

	//���������ۂ��𔻒�
	status[currentAnimID].currentWeightTime += time;

	if (status[currentAnimID].currentWeightTime <= status[currentAnimID].shiftTime)
	{
		//�������B�E�F�C�g���Z�o
		float weight = status[currentAnimID].currentWeightTime / status[currentAnimID].shiftTime;

		//�E�F�C�g��o�^
		animController->SetTrackWeight(0, weight);		//���݂̃A�j���[�V����
		animController->SetTrackWeight(1, 1 - weight);	//�O�̃A�j���[�V����
	}
	else
	{
		//�����I����
		animController->SetTrackWeight(0, 1.0f);			//���݂̃A�j���[�V����
		animController->SetTrackWeight(1, false);		//�O�̃A�j���[�V�����𖳌��ɂ���
	}

	//���Ԃ��X�V
	animController->AdvanceTime(time, &callBackHandler);

	return;
}

/**************************************
�`�揈��
***************************************/
void AnimContainer::Draw(LPD3DXMATRIX worldMtx)
{
	UpdateFrameMatrixes(rootFrame, worldMtx);
	DrawFrame(rootFrame);
}

/**************************************
�A�j���[�V�����̐؂�ւ�����
***************************************/
void AnimContainer::ChangeAnim(UINT animID, float playSpeed, bool forceChange)
{
	D3DXTRACK_DESC TD;		//�g���b�N�̔\��

	isMotionEnd = false;
	isStopMove = false;
	keyFrameCount = 0;

	//�w��̃A�j���[�V����ID�̑��݂��`�F�b�N
	if (animID > (UINT)animSetNum)
	{
		MessageBox(0, "AnimationsSet Don't Exist", "Error", 0);
		return;
	}

	//�قȂ�A�j���[�V�����ł��邩���`�F�b�N
	//�X�V����K�v���Ȃ�
	if (currentAnimID == animID && !forceChange)
	{
		return;
	}

	//���݂̃A�j���[�V�����Z�b�g�̐ݒ�l���擾
	animController->GetTrackDesc(0, &TD);

	//���̃A�j���[�V�������g���b�N�P�Ɉڍs���A�g���b�N�̐ݒ���ڍs
	animController->SetTrackAnimationSet(1, status[currentAnimID].animSet);
	animController->SetTrackDesc(1, &TD);
	animController->SetTrackSpeed(1, 0.0f);

	//�V�����A�j���[�V�������g���b�N�O�ɐݒ�
	animController->SetTrackAnimationSet(0, status[animID].animSet);

	//�g���b�N�O�̃X�s�[�h�ݒ�
	animController->SetTrackSpeed(0, playSpeed);

	//�g���b�N�O�̈ʒu�͍ŏ�����ɐݒ�
	animController->SetTrackPosition(0, 0.0f);

	//�g���b�N�̍���������
	animController->SetTrackEnable(0, true);
	animController->SetTrackEnable(1, true);

	//�E�F�C�g���Ԃ�������
	status[animID].currentWeightTime = 0.0f;
	animController->ResetTime();

	//���݂̃A�j���[�V�����ԍ���؂�ւ�
	prevAnimID = currentAnimID;
	currentAnimID = animID;

	return;
}

/**************************************
����J�n�ɂ����鎞�Ԃ�ݒ�
***************************************/
void AnimContainer::SetShiftTime(UINT animID, float interval)
{
	//�w��̃A�j���[�V����ID�̑��݂��`�F�b�N
	if (animID > (UINT)animSetNum)
	{
		MessageBox(0, "AnimationSet Don't Exist", "Error", 0);
		return;
	}

	//�V�t�g���Ԃ�o�^
	status[animID].shiftTime = interval;

	return;
}

/**************************************
�I�u�W�F�N�g����邤
***************************************/
AnimContainer::AnimContainer(void)
{

}

/**************************************
�A�j���Đ��̒��f�C�x���g
***************************************/
HRESULT AnimCallBackHandler::HandleCallback(UINT track, LPVOID callBackData)
{
	if (animContainer->keyFrameCount == 0)
	{
		animContainer->isStopMove = true;
	}
	else if (animContainer->keyFrameCount == 1)
	{
		animContainer->isMotionEnd = true;
		return D3D_OK;
	}

	animContainer->keyFrameCount++;

	return D3D_OK;
}

/**************************************
�A�j���[�V�������f�C�x���g��KeyFrames��ݒu����
***************************************/
HRESULT AnimContainer::SetupCallbackKeyFrames(LPCSTR setName)
{
	//KeyFrames��ݒu����\���AnimationSet
	ID3DXKeyframedAnimationSet* animSetTemp = 0;

	//KeyFrame��ݒu�����V����AnimationSet
	ID3DXCompressedAnimationSet *compressedAnimSet = 0;

	//�G���[���b�Z�[�W
	char message[64];

	//�ݒu����Callback Keys�̐�
	const UINT callbackNum = 2;
	D3DXKEY_CALLBACK keys[callbackNum];

	if (FAILED(animController->GetAnimationSetByName(setName, (ID3DXAnimationSet**)&animSetTemp)))
	{
		sprintf_s(message, "Setup Callback in %s AnimationSet Failed!", setName);
		MessageBox(0, message, "Error", 0);
		return E_FAIL;
	}

	//���k�����쐬
	ID3DXBuffer* compressedInfo = 0;
	animSetTemp->Compress(D3DXCOMPRESS_DEFAULT, 0.5f, 0, &compressedInfo);

	double ticks = animSetTemp->GetSourceTicksPerSecond();

	keys[0].Time = (float)(animSetTemp->GetPeriod() * (90.0f / 125.0f) * ticks);

	keys[1].Time = (float)(animSetTemp->GetPeriod() * 0.9f * ticks);

	D3DXCreateCompressedAnimationSet(animSetTemp->GetName(),
		animSetTemp->GetSourceTicksPerSecond(),
		animSetTemp->GetPlaybackType(), compressedInfo, callbackNum, keys, &compressedAnimSet);

	compressedInfo->Release();

	//���k�O�̃f�[�^���폜
	animController->UnregisterAnimationSet(animSetTemp);
	animSetTemp->Release();

	//���k�����f�[�^��ݒ�
	animController->RegisterAnimationSet(compressedAnimSet);
	compressedAnimSet->Release();

	return S_OK;
}