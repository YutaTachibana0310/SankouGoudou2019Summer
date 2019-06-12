//=====================================
//
//バックグラウンドシティ処理[BackGroundCity.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "BackGroundCity.h"
#include "Framework\InstancingMeshContainer.h"
#include "SkyBox.h"

/**************************************
マクロ定義
***************************************/
#define BACKGROUNDCITY_MODEL_FILE		"data/MODEL/City/city01.x"
#define BACKGROUNDCITY_NUM_MAX			(100)
#define BACKGROUNDCITY_KIND_MAX			(2)

#define BACKGROUNDCITY_BASEPOS_X_INNER	(300.0f)
#define BACKGROUNDCITY_BASEPOS_X_OUTER	(500.0f)
#define BACKGROUNDCITY_BASEPOS_Y		(0.0f)
#define BACKGROUNDCITY_BASEPOS_Z		(0.0f)

#define BACKGROUNDCITY_POS_RANGE_X		(200.0f)
#define BACKGROUNDCITY_POS_RANGE_Y		(100.0f)
#define BACKGROUNDCITY_POS_RANGE_Z		(50.0f)

#define BACKGROUNDCITY_OFFSET_Z			(300.0f)

#define BACKGROUNDCITY_MOVE_SPEED		(-25.0f)

#define BACKGROUNDCITY_LIGHT_AMPLIFIER	(2.2f)

/**************************************
構造体定義
***************************************/

/**************************************
グローバル変数
***************************************/
static Transform cityTransform[BACKGROUNDCITY_NUM_MAX];
static InstancingMeshContainer* meshContainer;
static LPDIRECT3DVERTEXBUFFER9 transformBuffer;

/**************************************
プロトタイプ宣言
***************************************/

/**************************************
初期化処理
***************************************/
void InitBackGroundCity(int num)
{
	//インスタンシング用にメッシュをロードして初期化
	meshContainer = new InstancingMeshContainer();
	meshContainer->Load(BACKGROUNDCITY_MODEL_FILE);
	meshContainer->SetLightAmplifier(BACKGROUNDCITY_LIGHT_AMPLIFIER);

	//Y座標、Z座標について初期化
	for (int i = 0; i < BACKGROUNDCITY_NUM_MAX; i += BACKGROUNDCITY_KIND_MAX)
	{
		cityTransform[i].pos.y = BACKGROUNDCITY_BASEPOS_Y + RandomRangef(-BACKGROUNDCITY_POS_RANGE_Y, BACKGROUNDCITY_POS_RANGE_Y);

		for (int j = 0; j < BACKGROUNDCITY_KIND_MAX; j++)
		{
			cityTransform[i+j].pos.z = BACKGROUNDCITY_BASEPOS_Z + BACKGROUNDCITY_OFFSET_Z * (i / 2) + RandomRangef(-BACKGROUNDCITY_POS_RANGE_Z, BACKGROUNDCITY_POS_RANGE_Z);
		}
	}

	//X座標について初期化
	for (int i = 0; i < BACKGROUNDCITY_NUM_MAX; i += BACKGROUNDCITY_KIND_MAX)
	{
		cityTransform[i].pos.x = BACKGROUNDCITY_BASEPOS_X_INNER + RandomRangef(0.0f, BACKGROUNDCITY_POS_RANGE_X);
		cityTransform[i + 1].pos.x = -BACKGROUNDCITY_BASEPOS_X_INNER - RandomRangef(0.0f, BACKGROUNDCITY_POS_RANGE_X);
	}

	//スケール、回転情報を初期化
	Transform *ptr = cityTransform;
	for (int i = 0; i < BACKGROUNDCITY_NUM_MAX; i++, ptr++)
	{
		ptr->scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		ptr->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	//SRT情報バッファを作成
	MakeTransformBuffer(BACKGROUNDCITY_NUM_MAX, &transformBuffer);
}

/**************************************
終了処理
***************************************/
void UninitBackGroundCity(int num)
{
	SAFE_RELEASE(transformBuffer);
	delete meshContainer;
}
/**************************************
更新処理
***************************************/
void UpdateBackGroundCity(void)
{
	for (int i = 0; i < BACKGROUNDCITY_NUM_MAX; i++)
	{
		//移動処理
		cityTransform[i].pos.z += BACKGROUNDCITY_MOVE_SPEED;

		//一定より後ろに下がっていたら最前列へ移動
		if (cityTransform[i].pos.z <= -100.0f)
			cityTransform[i].pos.z += 15000.0f;
	}

	//SRT情報をバッファへセット
	CopyVtxBuff(sizeof(cityTransform), cityTransform, transformBuffer);
}

/**************************************
描画処理
***************************************/
void DrawBackGroundCity(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	
	//ストリームソース設定
	meshContainer->SetStreamSource(transformBuffer, BACKGROUNDCITY_NUM_MAX);

	//描画
	meshContainer->Draw();
}