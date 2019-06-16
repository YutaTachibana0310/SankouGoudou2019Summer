#include "BackGroundField.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_FIELD	"data/TEXTURE/BG/road.jpg"	// 読み込むテクスチャファイル名
#define BACKGROUNDFIELD_SIZE			(15000.0f)
#define BACKGROUNDFIELD_POS_Y			(-2500.0f)

#define BACKGROUNDFIELD_MOVE_SPEED	    (-25.0f)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureField = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffField = NULL;	// 頂点バッファへのポインタ

D3DXVECTOR3				posField;					// 現在の位置

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitBackGroundField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	HRESULT hr;

	// 位置、向きの初期設定
	posField = D3DXVECTOR3(0.0f, BACKGROUNDFIELD_POS_Y, 0.0f);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
		TEXTURE_FIELD,			// ファイルの名前
		&g_pD3DTextureField);	// 読み込むメモリー

								// 頂点情報の作成
	hr = MakeVertexBackGroundField(pDevice);

	return hr;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBackGroundField(void)
{
	if (g_pD3DTextureField != NULL)
	{// テクスチャの開放
		g_pD3DTextureField->Release();
		g_pD3DTextureField = NULL;
	}

	if (g_pD3DVtxBuffField != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffField->Release();
		g_pD3DVtxBuffField = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBackGroundField(void)
{
	VERTEX_3D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pD3DVtxBuffField->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].tex.y += BACKGROUNDFIELD_MOVE_SPEED;//左奥
	pVtx[1].tex.y += BACKGROUNDFIELD_MOVE_SPEED;//右奥
	pVtx[2].tex.y += BACKGROUNDFIELD_MOVE_SPEED;//左手前
	pVtx[3].tex.y += BACKGROUNDFIELD_MOVE_SPEED;//右手前

	g_pD3DVtxBuffField->Unlock();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBackGroundField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxeTranslate, mtxWorld;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxWorld);

	// 移動を反映
	D3DXMatrixTranslation(&mtxeTranslate, posField.x, posField.y, posField.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxeTranslate);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pD3DVtxBuffField, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureField);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexBackGroundField(LPDIRECT3DDEVICE9 pDevice)
{
	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得

	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
		FVF_VERTEX_3D,				// 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&g_pD3DVtxBuffField,		// 頂点バッファインターフェースへのポインタ
		NULL)))						// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		g_pD3DVtxBuffField->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(-BACKGROUNDFIELD_SIZE, 0.0f, BACKGROUNDFIELD_SIZE);
		pVtx[0].vtx = D3DXVECTOR3( BACKGROUNDFIELD_SIZE, 0.0f, BACKGROUNDFIELD_SIZE);
		pVtx[0].vtx = D3DXVECTOR3(-BACKGROUNDFIELD_SIZE, 0.0f, -BACKGROUNDFIELD_SIZE);
		pVtx[0].vtx = D3DXVECTOR3( BACKGROUNDFIELD_SIZE, 0.0f, -BACKGROUNDFIELD_SIZE);

        // 法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// 反射光の設定
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 50.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 50.0f);

		// 頂点データをアンロックする
		g_pD3DVtxBuffField->Unlock();

	}
	return S_OK;
}