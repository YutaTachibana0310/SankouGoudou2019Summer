//=============================================================================
//
// モデル処理 [player.cpp]
// Author : 自分の氏名
//
//	複数キャラクタ対応版
//
//=============================================================================
#include "RebarOb.h"
//

////*****************************************************************************
//// マクロ定義
////*****************************************************************************
OBJECT3D* rebarob = GetRebarOb(0);

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
D3DXVECTOR3 axis;//回転軸
D3DXMATRIX mtxeScl, mtxeRot, mtxeTranslate;

//*************キャラクターデータ変数の用意*****************************
#define		NUM_REBAROB	(1)//モデルの数

#define     REBAR_POS_X (0.0f)
#define     REBAR_POS_Y (2.0f)
#define     REBAR_POS_Z (500.0f)

#define     REBAR_ROT_X (0.0f)
#define     REBAR_ROT_Y (0.0f)
#define     REBAR_ROT_Z (0.0f)

#define     REBAR_SCL_X (1.0f)
#define     REBAR_SCL_Y (1.0f)
#define     REBAR_SCL_Z (1.0f)

#define     REBAR_VEC_X (0.0f)
#define     REBAR_VEC_Y (0.0f)
#define     REBAR_VEC_Z (1.0f)

#define     MOVE_SPEED (-1.0)

#define     REBAR_MOVE (0.1f)
OBJECT3D	RebarOB[NUM_REBAROB];//エネミー構造体

float rotValue = 0.0f;//モデルの回転用
float Valuerotation = 0.05f;//モデルの回転速度
float lostpos = -50.0f;//モデルがこれより進んだら消える

//*************モデルーデータ変数の用意*****************************

REBAROB3D		RebarOb[NUM_REBAROB];		//モデル構造体

//*********************モデルデータファイル名配列********************
const char* RebarobData[] =
{
	"data/MODEL/redar.x",

};






//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitRebarOb(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ライトの初期化
	//InitLight();
	// キャラクタの位置・回転・スケールなどの初期設定
	for (int i = 0; i < NUM_REBAROB; i++)
	{
		RebarOB[i].m_posRebarOb = D3DXVECTOR3(REBAR_POS_X, REBAR_POS_Y, REBAR_POS_Z);
		RebarOB[i].m_rotRebarOb = D3DXVECTOR3(REBAR_ROT_X, REBAR_ROT_Y, REBAR_ROT_Z);
		RebarOB[i].m_sclRebarOb = D3DXVECTOR3(REBAR_SCL_X, REBAR_SCL_Y, REBAR_SCL_Z);
		RebarOB[i].m_vecRebarOb = D3DXVECTOR3(REBAR_VEC_X, REBAR_VEC_Y, REBAR_VEC_Z);

		RebarOB[i].m_RebarObID = 0;

	}
	for (int i = 0; i < NUM_REBAROB; i++)
	{
		RebarOB[i].m_RebarObID = i;	//キャラクタ[0]が使用するモデルデータの番号
		D3DXVECTOR3 temp = RebarOB[i].m_posRebarOb;//キャラクタ[0]の影オブジェクト作成
	}


	//モデルデータの初期設定
	for (int i = 0; i < NUM_REBAROB; i++)
	{

		RebarOb[i].m_pD3DTextureRebarob = NULL;
		RebarOb[i].m_pD3DXMeshRebarob = NULL;
		RebarOb[i].m_pD3DXBuffMatRebarob = NULL;
		RebarOb[i].m_nNumMatRebarob = 0;

		RebarOB[i].m_bUse = FALSE;


		if (D3D_OK != D3DXLoadMeshFromX(RebarobData[0],			// 読み込むモデルファイル名(Xファイル)
			D3DXMESH_SYSTEMMEM,		// メッシュの作成オプションを指定
			pDevice,				// IDirect3DDevice9インターフェイスへのポインタ
			NULL,					// 隣接性データを含むバッファへのポインタ
			&RebarOb[i].m_pD3DXBuffMatRebarob,	// マテリアルデータを含むバッファへのポインタ
			NULL,					// エフェクトインスタンスの配列を含むバッファへのポインタ
			&RebarOb[i].m_nNumMatRebarob,		// D3DXMATERIAL構造体の数
			&RebarOb[i].m_pD3DXMeshRebarob))	// ID3DXMeshインターフェイスへのポインタのアドレス
		{
			return E_FAIL;
		}
	}




#if 0
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
		TEXTURE_FILENAME,		// ファイルの名前
		&g_pD3DTextureEnemy);	// 読み込むメモリー
#endif
	SetRebar(0,3);
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitRebarOb(void)
{


	for (int i = 0; i < NUM_REBAROB; i++)
	{
		if (RebarOB[i].m_bUse)
		{
			if (NULL != RebarOb[i].m_pD3DTextureRebarob)
			{
				RebarOb[i].m_pD3DTextureRebarob->Release();
				RebarOb[i].m_pD3DTextureRebarob = NULL;
			}

			if (NULL != RebarOb[i].m_pD3DXMeshRebarob)
			{
				RebarOb[i].m_pD3DXMeshRebarob->Release();
				RebarOb[i].m_pD3DXMeshRebarob = NULL;
			}

			if (NULL != RebarOb[i].m_pD3DXBuffMatRebarob)
			{
				RebarOb[i].m_pD3DXBuffMatRebarob->Release();
				RebarOb[i].m_pD3DXBuffMatRebarob = NULL;
			}
		}
	}


}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateRebarOb(void)
{

	for (int i = 0; i < NUM_REBAROB; i++)
	{
		if (RebarOB[i].m_bUse)
		{
			RebarOB[i].m_posRebarOb.z += MOVE_SPEED;
			rotValue += Valuerotation;

			if (RebarOB[i].m_posRebarOb.z <= lostpos)
			{
				RebarOB[i].m_bUse = false;
			}
		}
	}

}


//=============================================================================
// 描画処理
//=============================================================================
void DrawRebarOb(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;

	//ライトON
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);


	// 現在設定されているマテリアルを取得して保存
	pDevice->GetMaterial(&matDef);


	//*************************全てのキャラクターを表示************************
	for (int i = 0; i < NUM_REBAROB; i++)
	{
		if (RebarOB[i].m_bUse)
		{
			D3DXVECTOR3	temp;

			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&RebarOB[i].m_mtxWorld);

			// スケールを行列にしてワールド行列（始めは単位行列）と乗算
			temp = RebarOB[i].m_sclRebarOb;
			D3DXMatrixScaling(&mtxeScl, temp.x, temp.y, temp.z);
			D3DXMatrixMultiply(&RebarOB[i].m_mtxWorld, &RebarOB[i].m_mtxWorld, &mtxeScl);

			// 回転を行列にしてワールド行列と乗算
			temp = RebarOB[i].m_rotRebarOb;
			D3DXMatrixRotationYawPitchRoll(&mtxeRot, temp.y, temp.x, temp.z);
			D3DXMatrixMultiply(&RebarOB[i].m_mtxWorld, &RebarOB[i].m_mtxWorld, &mtxeRot);

			//クォータニオンでの回転
			D3DXQUATERNION rotQ;//回転用のクォータニオン
			D3DXQuaternionRotationAxis(&rotQ,
										&axis,
										rotValue);
			D3DXMatrixRotationQuaternion(&mtxeRot,
				&rotQ);
			D3DXMatrixMultiply(&RebarOB[i].m_mtxWorld, &RebarOB[i].m_mtxWorld, &mtxeRot);

			// 移動を行列にしてワールド行列と乗算
			temp = RebarOB[i].m_posRebarOb;
			D3DXMatrixTranslation(&mtxeTranslate, temp.x, temp.y, temp.z);
			//行列の掛け算
			D3DXMatrixMultiply(&RebarOB[i].m_mtxWorld, &RebarOB[i].m_mtxWorld, &mtxeTranslate);

			// 完成したワールドマトリックスをDirectXへセット
			pDevice->SetTransform(D3DTS_WORLD, &RebarOB[i].m_mtxWorld);


			//このキャラクターが使うモデルのID
			int rebarno = RebarOB[i].m_RebarObID;


			// モデルのマテリアル情報に対するポインタを取得
			pD3DXMat = (D3DXMATERIAL*)RebarOb[rebarno].m_pD3DXBuffMatRebarob->GetBufferPointer();

			//モデルの情報に従ってモデルを構成するオブジェクトの数だけ繰り返す
			for (int nCntMat = 0; nCntMat < (int)RebarOb[rebarno].m_nNumMatRebarob; nCntMat++)
			{
				// オブジェクトのマテリアルの設定
				pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

				// オブジェクトのテクスチャの設定
				pDevice->SetTexture(0, RebarOb[rebarno].m_pD3DTextureRebarob);

				// オブジェクトの描画
				RebarOb[rebarno].m_pD3DXMeshRebarob->DrawSubset(nCntMat);
			}
		}
	}

	// マテリアルをデフォルトに戻す
	pDevice->SetMaterial(&matDef);

}

void SetRebar(int a,int b)
{
	LineTrailModel model;
	D3DXVECTOR3 right, left;

	right = model.GetEdgePos(a);
	left = model.GetEdgePos(b);

	for (int i = 0; i < NUM_REBAROB; i++)
	{
		if (RebarOB[i].m_bUse == false)
		{
			RebarOB[i].m_posRebarOb = (right - left) / 2.0f + left;
			RebarOB[i].m_posRebarOb.z = REBAR_POS_Z;

			RebarOB[i].m_rotRebarOb.z = atan2f(RebarOB[i].m_posRebarOb.y - left.y, RebarOB[i].m_posRebarOb.x - left.x);

			D3DXVec3Cross(&axis,
				&D3DXVECTOR3(0, 0, 1),
				&(right - left));

			RebarOB[i].m_bUse = true;

			return;
		}
	}
}

OBJECT3D* GetRebarOb(int no)
{
	return &RebarOB[no];
}