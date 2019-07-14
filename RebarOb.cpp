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
//D3DLIGHT9			g_aLight[NUM_LIGHT];	// ライト情報
D3DXMATRIX mtxeScl, mtxeRot, mtxeTranslate;

//*************キャラクターデータ変数の用意*****************************
#define		NUM_REBAROB	(1)
#define     REBAR_POS_X (0.0f)
#define     REBAR_POS_Y (2.0f)
#define     REBAR_POS_Z (100.0f)
#define     REBAR_MOVE (0.1f)
OBJECT3D	RebarOB[NUM_REBAROB];//エネミー構造体
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
		RebarOB[i].m_rotRebarOb = D3DXVECTOR3(0.0f, 1.57f, 0.0f);
		RebarOB[i].m_sclRebarOb = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		RebarOB[i].m_vecRebarOb = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

		RebarOB[i].m_DirSpeed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		RebarOB[i].m_RotSpeed = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		RebarOB[i].m_Kakudo = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		RebarOB[i].m_Radius = D3DXVECTOR3(10.0f, 1.0f, 12.10f);
		RebarOB[i].m_RebarObID = 0;
		RebarOB[i].m_ShadowID = 0;

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
			RebarOB[i].m_posRebarOb -= D3DXVECTOR3(0.0f, 0.0f, 3.0f);
			//RebarOB[i].m_rotRebarOb += D3DXVECTOR3(0.032f, 0.0f, 0.0f);

			if (RebarOB[i].m_posRebarOb.z <= -10)
			{
				ResetRebar(i);
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

void SetRebar(D3DXVECTOR3 pos)
{
	for (int i = 0; i < NUM_REBAROB; i++)
	{
		if (RebarOB[i].m_bUse == false)
		{
			RebarOB[i].m_posRebarOb = D3DXVECTOR3(pos);
			RebarOB[i].m_bUse = true;

			return;
		}
	}
}

void ResetRebar(int no)
{
	RebarOB[no].m_posRebarOb = D3DXVECTOR3(REBAR_POS_X, REBAR_POS_Y, REBAR_POS_Z);
}

OBJECT3D* GetRebarOb(int no)
{
	return &RebarOB[no];
}