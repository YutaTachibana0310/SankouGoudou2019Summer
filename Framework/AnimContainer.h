//=====================================
//
//アニメコンテナヘッダ[AnimContainer.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _TEMPLATE_H_
#define _TEMPLATE_H_

#include "../main.h"
#include "MyAllocateHierarchy.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
typedef struct
{
	LPCSTR setname;					//アニメーションセットの名前
	ID3DXAnimationSet *animSet;		//アニメーションセット
	float shiftTime;				//シフトするのにかかる時間
	float currentWeightTime;		//現在のウェイト時間
}AnimStatus;

typedef struct _AnimContainer
{
	LPD3DXANIMATIONCONTROLLER animController;	//アニメーションコントローラ
	UINT currentAnimID;							//現在のアニメーション番号
	UINT prevAnimID;							//前のアニメーション番号
	AnimStatus *status;							//アニメーションセットのデータ
	MyAllocateHierarchy *allocater;				//Xファイルの情報を確保する
	LPD3DXFRAME rootFrame;						//ルートフレーム
	int animSetNum;								//アニメーションセットの数
	int keyFrameCount;							//Callback KeyFramesを処理した数
	bool isMotionEnd;							//今再生しているアニメーションが最後かどうか
	bool isStopMove;							//キャラが移動を停止しているかどうか

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
プロトタイプ宣言
***************************************/
AnimContainer* CreateAnimContainer(void);	//アニメーションコンテナを作成
HRESULT LoadXFile(AnimContainer* animation, LPCSTR fileName, const char* errorSrc);	//Xファイルのロード
HRESULT SetupCallbackKeyFrames(AnimContainer* animation, LPCSTR setName);	//アニメーション中断イベントのKeyFrameを設置する
D3DXMATRIX GetBoneMatrix(AnimContainer* animation, const char* boneName);		//特定のボーン行列の検索処理

#endif