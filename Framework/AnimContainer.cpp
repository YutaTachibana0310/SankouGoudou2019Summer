//=====================================
//
//アニメコンテナ処理[AnimContainer.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "AnimContainer.h"
#include <stdio.h>

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/

/**************************************
グローバル変数
***************************************/

/**************************************
プロトタイプ宣言
***************************************/
void DrawMeshContainer(AnimContainer *animation, LPD3DXMESHCONTAINER meshContainerBase, LPD3DXFRAME frameBase);
void DrawFrame(AnimContainer *animation, LPD3DXFRAME frame);
HRESULT SetupBoneMatrixPointers(LPD3DXFRAME frameBase, LPD3DXFRAME frameRoot);
void UpdateFrameMatrixes(LPD3DXFRAME frameBase, LPD3DXMATRIX parentMatrix);
D3DXFRAME_DERIVED* SearchBoneFrame(AnimContainer *animation, const char* boneName, D3DXFRAME* frame);

HRESULT InitAnimation(AnimContainer *animation, LPCSTR setName, int setNo);
void UninitAnimation(AnimContainer *animation);
void UpdateAnimation(AnimContainer *animation, float time);
void DrawAnimation(AnimContainer *animation, LPD3DXMATRIX worldMatrix);
void ChangeAnimation(AnimContainer *animation, UINT animID, float playSpeed);

/**************************************
ボーン行列のポインタの準備
***************************************/
HRESULT SetupBoneMatrixPointers(LPD3DXFRAME frameBase, LPD3DXFRAME frameRoot)
{
	if (frameBase->pMeshContainer != NULL)
	{
		D3DXFRAME_DERIVED* frame = NULL;
		D3DXMESHCONTAINER_DERIVED* meshContainer = (D3DXMESHCONTAINER_DERIVED*)frameBase->pMeshContainer;

		//スキンメッシュを持っていたらボーン行列を準備する
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

	//兄弟フレームのボーンをセットアップ
	if (frameBase->pFrameSibling != NULL)
	{
		if (FAILED(SetupBoneMatrixPointers(frameBase->pFrameSibling, frameRoot)))
			return E_FAIL;
	}

	//子フレームのボーンをセットアップ
	if (frameBase->pFrameFirstChild != NULL)
	{
		if (FAILED(SetupBoneMatrixPointers(frameBase->pFrameFirstChild, frameRoot)))
			return E_FAIL;
	}


	return S_OK;
}

/**************************************
フレームの描画処理
***************************************/
void DrawFrame(AnimContainer *animation, LPD3DXFRAME frame)
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
		DrawMeshContainer(animation, meshContainer, frame);
		meshContainer = meshContainer->pNextMeshContainer;
	}

	DrawFrame(animation, frame->pFrameSibling);
	DrawFrame(animation, frame->pFrameFirstChild);
}

/**************************************
メッシュコンテナの描画処理
***************************************/
void DrawMeshContainer(AnimContainer *animatoin, LPD3DXMESHCONTAINER meshContainerBase, LPD3DXFRAME frameBase)
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

	//スキンメッシュの場合の描画
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
	//通常メッシュの描画
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
フレーム行列の更新
***************************************/
void UpdateFrameMatrixes(LPD3DXFRAME frameBase, LPD3DXMATRIX parentMatrix)
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
Xファイルの読み込み
***************************************/
HRESULT LoadXFile(AnimContainer* animation, LPCSTR fileName, const char* errorSrc)
{
	char message[64];
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	animation->allocater = new MyAllocateHierarchy();

	if (FAILED(D3DXLoadMeshHierarchyFromX(fileName,
		D3DXMESH_MANAGED,
		pDevice,
		animation->allocater,
		NULL,
		&animation->rootFrame,
		&animation->animController)))
	{
		sprintf_s(message, "Load %s Model Failed", errorSrc);
		MessageBox(0, message, "Error", 0);
		return E_FAIL;
	}

	if (FAILED(SetupBoneMatrixPointers(animation->rootFrame, animation->rootFrame)))
	{
		return E_FAIL;
	}

	animation->isMotionEnd = false;
	animation->animSetNum = animation->animController->GetNumAnimationSets();
	animation->status = new AnimStatus[animation->animSetNum];

	return S_OK;
}

/**************************************
特定のボーン行列の取得
***************************************/
D3DXMATRIX GetBoneMatrix(AnimContainer* animation, const char* boneName)
{
	char message[64];
	D3DXFRAME_DERIVED* frame = (D3DXFRAME_DERIVED*)SearchBoneFrame(animation, boneName, animation->rootFrame);

	//見つかった場合
	if (frame != NULL && frame->Name != NULL && strcmp(frame->Name, boneName) == 0)
	{
		return frame->combiendTransformMatrix;
	}
	//見つからなかった場合
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
特定のボーンを探す
***************************************/
D3DXFRAME_DERIVED* SearchBoneFrame(AnimContainer *animation, const char* boneName, D3DXFRAME* frame)
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
		p = SearchBoneFrame(animation, boneName, frame->pFrameSibling);
		if (p != NULL && strcmp(p->Name, boneName) == 0)
		{
			return p;
		}
	}

	if (frame->pFrameFirstChild != NULL)
	{
		p = SearchBoneFrame(animation, boneName, frame->pFrameFirstChild);
		if (p != NULL && strcmp(p->Name, boneName) != 0)
		{
			return p;
		}
	}

	return NULL;

}

/**************************************
初期化処理
***************************************/
HRESULT InitAnimation(AnimContainer *animation, LPCSTR setName, int setNo)
{
	char message[64];

	if (FAILED(animation->animController->GetAnimationSetByName(setName, &animation->status[setNo].animSet)))
	{
		sprintf_s(message, "Can't find %s Animationset !", setName);
		MessageBox(0, message, "Error", 0);
		return E_FAIL;
	}

	animation->status[setNo].setname = animation->status[setNo].animSet->GetName();

	return S_OK;
}

/**************************************
終了処理
***************************************/
void UninitAnimation(AnimContainer *animation)
{
	D3DXFrameDestroy(animation->rootFrame, animation->allocater);

	SAFE_DELETE(animation->status);
	SAFE_RELEASE(animation->animController);
	SAFE_DELETE(animation->allocater);
	SAFE_DELETE(animation);
}

/**************************************
更新処理
***************************************/
void UpdateAnimation(AnimContainer* animation, float time)
{
	AnimCallBackHandler callBackHandler;
	callBackHandler.animContainer = animation;
	callBackHandler.setName = animation->status[animation->currentAnimID].setname;

	//合成中か否かを判定
	animation->status[animation->currentAnimID].currentWeightTime += time;

	if (animation->status[animation->currentAnimID].currentWeightTime <= animation->status[animation->currentAnimID].shiftTime)
	{
		//合成中。ウェイトを算出
		float weight = animation->status[animation->currentAnimID].currentWeightTime / animation->status[animation->currentAnimID].shiftTime;

		//ウェイトを登録
		animation->animController->SetTrackWeight(0, weight);		//現在のアニメーション
		animation->animController->SetTrackWeight(1, 1 - weight);	//前のアニメーション
	}
	else
	{
		//合成終了中
		animation->animController->SetTrackWeight(0, 1.0f);			//現在のアニメーション
		animation->animController->SetTrackWeight(1, false);		//前のアニメーションを無効にする
	}

	//時間を更新
	animation->animController->AdvanceTime(time, &callBackHandler);

	return;
}

/**************************************
描画処理
***************************************/
void DrawAnimation(AnimContainer *animation, LPD3DXMATRIX worldMtx)
{
	UpdateFrameMatrixes(animation->rootFrame, worldMtx);
	DrawFrame(animation, animation->rootFrame);
}

/**************************************
アニメーションの切り替え処理
***************************************/
void ChangeAnimation(AnimContainer *animation, UINT animID, float playSpeed)
{
	D3DXTRACK_DESC TD;		//トラックの能力

	animation->isMotionEnd = false;
	animation->isStopMove = false;
	animation->keyFrameCount = 0;

	//指定のアニメーションIDの存在をチェック
	if (animID > (UINT)animation->animSetNum)
	{
		MessageBox(0, "AnimationsSet Don't Exist", "Error", 0);
		return;
	}

	//異なるアニメーションであるかをチェック
	//更新する必要がない
	if (animation->currentAnimID == animID)
	{
		return;
	}

	//現在のアニメーションセットの設定値を取得
	animation->animController->GetTrackDesc(0, &TD);

	//今のアニメーションをトラック１に移行し、トラックの設定も移行
	animation->animController->SetTrackAnimationSet(1, animation->status[animation->currentAnimID].animSet);
	animation->animController->SetTrackDesc(1, &TD);
	animation->animController->SetTrackSpeed(1, 0.0f);

	//新しいアニメーションをトラック０に設定
	animation->animController->SetTrackAnimationSet(0, animation->status[animID].animSet);

	//トラック０のスピード設定
	animation->animController->SetTrackSpeed(0, playSpeed);

	//トラック０の位置は最初からに設定
	animation->animController->SetTrackPosition(0, 0.0f);

	//トラックの合成を許可
	animation->animController->SetTrackEnable(0, true);
	animation->animController->SetTrackEnable(1, true);

	//ウェイト時間を初期化
	animation->status[animID].currentWeightTime = 0.0f;
	animation->animController->ResetTime();

	//現在のアニメーション番号を切り替え
	animation->prevAnimID = animation->currentAnimID;
	animation->currentAnimID = animID;

	return;
}

/**************************************
動作開始にかかる時間を設定
***************************************/
void SetShiftTime(AnimContainer *animation, UINT animID, float interval)
{
	//指定のアニメーションIDの存在をチェック
	if (animID > (UINT)animation->animSetNum)
	{
		MessageBox(0, "AnimationSet Don't Exist", "Error", 0);
		return;
	}

	//シフト時間を登録
	animation->status[animID].shiftTime = interval;

	return;
}

/**************************************
オブジェクトを作るう
***************************************/
AnimContainer* CreateAnimContainer(void)
{
	AnimContainer *obj = new AnimContainer;

	obj->InitAnimation = InitAnimation;
	obj->UninitAnimation = UninitAnimation;
	obj->UpdateAnimation = UpdateAnimation;
	obj->DrawAnimation = DrawAnimation;
	obj->ChangeAnimation = ChangeAnimation;
	obj->SetShiftTime = SetShiftTime;

	return obj;
}

/**************************************
アニメ再生の中断イベント
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
アニメーション中断イベントのKeyFramesを設置する
***************************************/
HRESULT SetupCallbackKeyFrames(AnimContainer *animation, LPCSTR setName)
{
	//KeyFramesを設置する予定のAnimationSet
	ID3DXKeyframedAnimationSet* animSetTemp = 0;

	//KeyFrameを設置した新しいAnimationSet
	ID3DXCompressedAnimationSet *compressedAnimSet = 0;

	//エラーメッセージ
	char message[64];

	//設置するCallback Keysの数
	const UINT callbackNum = 2;
	D3DXKEY_CALLBACK keys[callbackNum];

	if (FAILED(animation->animController->GetAnimationSetByName(setName, (ID3DXAnimationSet**)&animSetTemp)))
	{
		sprintf_s(message, "Setup Callback in %s AnimationSet Failed!", setName);
		MessageBox(0, message, "Error", 0);
		return E_FAIL;
	}

	//圧縮情報を作成
	ID3DXBuffer* compressedInfo = 0;
	animSetTemp->Compress(D3DXCOMPRESS_DEFAULT, 0.5f, 0, &compressedInfo);

	double ticks = animSetTemp->GetSourceTicksPerSecond();

	keys[0].Time = (float)(animSetTemp->GetPeriod() * (90.0f / 125.0f) * ticks);

	keys[1].Time = (float)(animSetTemp->GetPeriod() * 0.9f * ticks);

	D3DXCreateCompressedAnimationSet(animSetTemp->GetName(),
		animSetTemp->GetSourceTicksPerSecond(),
		animSetTemp->GetPlaybackType(), compressedInfo, callbackNum, keys, &compressedAnimSet);

	compressedInfo->Release();

	//圧縮前のデータを削除
	animation->animController->UnregisterAnimationSet(animSetTemp);
	animSetTemp->Release();

	//圧縮したデータを設定
	animation->animController->RegisterAnimationSet(compressedAnimSet);
	compressedAnimSet->Release();

	return S_OK;
}