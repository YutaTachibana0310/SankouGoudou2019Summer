#include "BackGroundRoad.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_FIELD	"data/TEXTURE/BG/road.jpg"	// 読み込むテクスチャファイル名
#define BACKGROUNDROAD_SIZE_X			(600.0f)
#define BACKGROUNDROAD_SIZE_Z			(15000.0f)

#define BACKGROUNDROAD_MOVE_SPEED	    (-0.06f)

#define BACKGROUNDROAD_TEXSIZE_X		(2.0f)
#define BACKGROUNDROAD_TEXSIZE_Y		(50.0f)

#define BACKGROUNDROAD_INIT_POS_Y		(-3500.0f)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureRoad = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffRoad = NULL;	// 頂点バッファへのポインタ

D3DXVECTOR3				posRoad;					// 現在の位置

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitBackGroundRoad(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	HRESULT hr;

	// 位置、向きの初期設定
	posRoad = D3DXVECTOR3(0.0f, BACKGROUNDROAD_INIT_POS_Y, 0.0f);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
		TEXTURE_FIELD,			// ファイルの名前
		&g_pD3DTextureRoad);	// 読み込むメモリー

								// 頂点情報の作成
	hr = MakeVertexBackGroundRoad(pDevice);

	return hr;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBackGroundRoad(void)
{
	if (g_pD3DTextureRoad != NULL)
	{// テクスチャの開放
		g_pD3DTextureRoad->Release();
		g_pD3DTextureRoad = NULL;
	}

	if (g_pD3DVtxBuffRoad != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffRoad->Release();
		g_pD3DVtxBuffRoad = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBackGroundRoad(void)
{
	VERTEX_3D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pD3DVtxBuffRoad->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].tex.y += BACKGROUNDROAD_MOVE_SPEED;//左奥
	pVtx[1].tex.y += BACKGROUNDROAD_MOVE_SPEED;//右奥
	pVtx[2].tex.y += BACKGROUNDROAD_MOVE_SPEED;//左手前
	pVtx[3].tex.y += BACKGROUNDROAD_MOVE_SPEED;//右手前

	g_pD3DVtxBuffRoad->Unlock();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBackGroundRoad(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxeTranslate, mtxWorld;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxWorld);

	// 移動を反映
	D3DXMatrixTranslation(&mtxeTranslate, posRoad.x, posRoad.y, posRoad.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxeTranslate);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pD3DVtxBuffRoad, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureRoad);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexBackGroundRoad(LPDIRECT3DDEVICE9 pDevice)
{
	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得

	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
		FVF_VERTEX_3D,				// 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&g_pD3DVtxBuffRoad,		// 頂点バッファインターフェースへのポインタ
		NULL)))						// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		g_pD3DVtxBuffRoad->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(-BACKGROUNDROAD_SIZE_X, 0.0f, BACKGROUNDROAD_SIZE_Z);
		pVtx[1].vtx = D3DXVECTOR3(BACKGROUNDROAD_SIZE_X, 0.0f, BACKGROUNDROAD_SIZE_Z);
		pVtx[2].vtx = D3DXVECTOR3(-BACKGROUNDROAD_SIZE_X, 0.0f, -BACKGROUNDROAD_SIZE_Z);
		pVtx[3].vtx = D3DXVECTOR3(BACKGROUNDROAD_SIZE_X, 0.0f, -BACKGROUNDROAD_SIZE_Z);


		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// 反射光の設定
		pVtx[0].diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(BACKGROUNDROAD_TEXSIZE_X, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, BACKGROUNDROAD_TEXSIZE_Y);
		pVtx[3].tex = D3DXVECTOR2(BACKGROUNDROAD_TEXSIZE_X, BACKGROUNDROAD_TEXSIZE_Y);

		// 頂点データをアンロックする
		g_pD3DVtxBuffRoad->Unlock();

	}
	return S_OK;
}