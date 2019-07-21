//=============================================================================
//
// UI描画用処理 [UIdrawer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "UIdrawer.h"

//=============================================================================
// テクスチャの読み込み
//=============================================================================
void LoadTexture(LPDIRECT3DDEVICE9 device, const char *adress, OBJECT *object)
{
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(device,	// デバイスへのポインタ
		adress,							// ファイルのアドレス
		&object->texture);				// 読み込むメモリー
}

//=============================================================================
// オブジェクトサークルの作成　（回転オブジェクト用のサークルを作る）
//=============================================================================
void CreateObjectCircle(OBJECT *object, float sizeX, float sizeY)
{
	D3DXVECTOR2 temp = D3DXVECTOR2(sizeX, sizeY);
	object->radius = D3DXVec2Length(&temp);
	object->baseAngle = atan2f(sizeY, sizeX);
}

//=============================================================================
// テクスチャの解放
//=============================================================================
void ReleaseTexture(OBJECT *object)
{
	if (object->texture != NULL)
	{// テクスチャの開放
		object->texture->Release();
		object->texture = NULL;
	}
}

//=============================================================================
// テクスチャの初期化
//=============================================================================
void InitialTexture(OBJECT *object)
{
	// テクスチャ情報
	&object->texture;
}

//=============================================================================
// オブジェクト描画処理
//=============================================================================
void DrawObject(LPDIRECT3DDEVICE9 pDevice, OBJECT object)
{
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, object.texture);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, object.vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// テクスチャの頂点の作成
//=============================================================================
void MakeVertexObject(OBJECT *object)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点座標の設定
	object->vertexWk[0].vtx = object->position + D3DXVECTOR3(-object->size.x, -object->size.y, 0.0f);
	object->vertexWk[1].vtx = object->position + D3DXVECTOR3(object->size.x, -object->size.y, 0.0f);
	object->vertexWk[2].vtx = object->position + D3DXVECTOR3(-object->size.x, object->size.y, 0.0f);
	object->vertexWk[3].vtx = object->position + D3DXVECTOR3(object->size.x, object->size.y, 0.0f);

	// テクスチャのパースペクティブコレクト用
	object->vertexWk[0].rhw =
		object->vertexWk[1].rhw =
		object->vertexWk[2].rhw =
		object->vertexWk[3].rhw = 1.0f;

	// テクスチャ座標の設定
	object->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	object->vertexWk[1].tex = D3DXVECTOR2(1.0, 0.0f);
	object->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	object->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);
}

//=============================================================================
// テクスチャの頂点の作成 (回転オブジェクト用)
//=============================================================================
void MakeVertexRotateObject(OBJECT *object)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点座標の設定
	object->vertexWk[0].vtx.x = object->position.x - cosf(object->baseAngle + object->rotation.z) * object->radius;
	object->vertexWk[0].vtx.y = object->position.y - sinf(object->baseAngle + object->rotation.z) * object->radius;
	object->vertexWk[0].vtx.z = 0.0f;

	object->vertexWk[1].vtx.x = object->position.x + cosf(object->baseAngle - object->rotation.z) * object->radius;
	object->vertexWk[1].vtx.y = object->position.y - sinf(object->baseAngle - object->rotation.z) * object->radius;
	object->vertexWk[1].vtx.z = 0.0f;

	object->vertexWk[2].vtx.x = object->position.x - cosf(object->baseAngle - object->rotation.z) * object->radius;
	object->vertexWk[2].vtx.y = object->position.y + sinf(object->baseAngle - object->rotation.z) * object->radius;
	object->vertexWk[2].vtx.z = 0.0f;

	object->vertexWk[3].vtx.x = object->position.x + cosf(object->baseAngle + object->rotation.z) * object->radius;
	object->vertexWk[3].vtx.y = object->position.y + sinf(object->baseAngle + object->rotation.z) * object->radius;
	object->vertexWk[3].vtx.z = 0.0f;

	// テクスチャのパースペクティブコレクト用
	object->vertexWk[0].rhw =
		object->vertexWk[1].rhw =
		object->vertexWk[2].rhw =
		object->vertexWk[3].rhw = 1.0f;

	// テクスチャ座標の設定
	object->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	object->vertexWk[1].tex = D3DXVECTOR2(1.0, 0.0f);
	object->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	object->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);
}

//=============================================================================
// テクスチャの頂点の作成　（ゲージ専用）
//=============================================================================
void MakeVertexGuageBar(OBJECT *object, float percentage, float flameWidth)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点座標の設定
	object->vertexWk[0].vtx = D3DXVECTOR3(flameWidth + object->position.x, object->position.y, object->position.z) 
		+ D3DXVECTOR3(-object->size.x, -object->size.y, 0.0f);
	object->vertexWk[1].vtx = D3DXVECTOR3(-flameWidth + object->position.x*percentage, object->position.y, object->position.z) 
		+ D3DXVECTOR3(object->size.x, -object->size.y, 0.0f);
	object->vertexWk[2].vtx = D3DXVECTOR3(flameWidth + object->position.x, object->position.y, object->position.z) 
		+ D3DXVECTOR3(-object->size.x, object->size.y, 0.0f);
	object->vertexWk[3].vtx = D3DXVECTOR3(-flameWidth + object->position.x*percentage, object->position.y, object->position.z) 
		+ D3DXVECTOR3(object->size.x, object->size.y, 0.0f);

	// テクスチャのパースペクティブコレクト用
	object->vertexWk[0].rhw =
		object->vertexWk[1].rhw =
		object->vertexWk[2].rhw =
		object->vertexWk[3].rhw = 1.0f;

	// テクスチャ座標の設定
	object->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	object->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	object->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	object->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);
}

//=============================================================================
// オブジェクトの頂点座標の設定
//=============================================================================
void SetVertexObject(OBJECT *object)
{
	// 頂点座標の設定
	object->vertexWk[0].vtx = object->position + D3DXVECTOR3(-object->size.x, -object->size.y, 0.0f);
	object->vertexWk[1].vtx = object->position + D3DXVECTOR3(object->size.x, -object->size.y, 0.0f);
	object->vertexWk[2].vtx = object->position + D3DXVECTOR3(-object->size.x, object->size.y, 0.0f);
	object->vertexWk[3].vtx = object->position + D3DXVECTOR3(object->size.x, object->size.y, 0.0f);
}

//=============================================================================
// オブジェクトの頂点座標の設定 (回転オブジェクト用)
//=============================================================================
void SetVertexRotateObject(OBJECT *object)
{
	// 頂点座標の設定
	object->vertexWk[0].vtx.x = object->position.x - cosf(object->baseAngle + object->rotation.z) * object->radius;
	object->vertexWk[0].vtx.y = object->position.y - sinf(object->baseAngle + object->rotation.z) * object->radius;
	object->vertexWk[0].vtx.z = 0.0f;

	object->vertexWk[1].vtx.x = object->position.x + cosf(object->baseAngle - object->rotation.z) * object->radius;
	object->vertexWk[1].vtx.y = object->position.y - sinf(object->baseAngle - object->rotation.z) * object->radius;
	object->vertexWk[1].vtx.z = 0.0f;

	object->vertexWk[2].vtx.x = object->position.x - cosf(object->baseAngle - object->rotation.z) * object->radius;
	object->vertexWk[2].vtx.y = object->position.y + sinf(object->baseAngle - object->rotation.z) * object->radius;
	object->vertexWk[2].vtx.z = 0.0f;

	object->vertexWk[3].vtx.x = object->position.x + cosf(object->baseAngle + object->rotation.z) * object->radius;
	object->vertexWk[3].vtx.y = object->position.y + sinf(object->baseAngle + object->rotation.z) * object->radius;
	object->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// オブジェクトの頂点座標の設定　（ゲージ専用）
//=============================================================================
void SetVertexGuageBar(OBJECT *object, float percentage, float flameWidth, int guageType)
{
	if (guageType == LEFT_GUAGEBAR)
	{
		// 頂点座標の設定
		object->vertexWk[0].vtx =
			D3DXVECTOR3(flameWidth + object->position.x - object->size.x, object->position.y - object->size.y, object->position.z);
		object->vertexWk[1].vtx =
			D3DXVECTOR3(-flameWidth + object->vertexWk[0].vtx.x + (object->position.x + object->size.x - object->vertexWk[0].vtx.x)*percentage,
				object->position.y - object->size.y, object->position.z);
		object->vertexWk[2].vtx =
			D3DXVECTOR3(flameWidth + object->position.x - object->size.x, object->position.y + object->size.y, object->position.z);
		object->vertexWk[3].vtx =
			D3DXVECTOR3(-flameWidth + object->vertexWk[2].vtx.x + (object->position.x + object->size.x - object->vertexWk[2].vtx.x)*percentage,
				object->position.y + object->size.y, object->position.z);
	}
	if (guageType == RIGHT_GUAGEBAR)
	{
		// 頂点座標の設定
		object->vertexWk[0].vtx =
			D3DXVECTOR3(flameWidth + object->vertexWk[1].vtx.x + (object->position.x - object->size.x - object->vertexWk[1].vtx.x)*percentage, object->position.y - object->size.y, object->position.z);
		object->vertexWk[1].vtx =
			D3DXVECTOR3(-flameWidth + object->position.x + object->size.x,object->position.y - object->size.y, object->position.z);
		object->vertexWk[2].vtx =
			D3DXVECTOR3(flameWidth + object->vertexWk[3].vtx.x + (object->position.x - object->size.x - object->vertexWk[3].vtx.x)*percentage, object->position.y + object->size.y, object->position.z);
		object->vertexWk[3].vtx =
			D3DXVECTOR3(-flameWidth + object->position.x + object->size.x,
				object->position.y + object->size.y, object->position.z);
	}
	if (guageType == DOWN_GUAGEBAR)
	{
		// 頂点座標の設定
		object->vertexWk[0].vtx =
			D3DXVECTOR3(object->position.x - object->size.x, 
				flameWidth + object->vertexWk[2].vtx.y + (object->position.y - object->size.y - object->vertexWk[2].vtx.y)*percentage, object->position.z);
		object->vertexWk[1].vtx =
			D3DXVECTOR3(object->position.x + object->size.x, 
				flameWidth + object->vertexWk[3].vtx.y + (object->position.y - object->size.y - object->vertexWk[3].vtx.y)*percentage, object->position.z);
		object->vertexWk[2].vtx =
			D3DXVECTOR3(object->position.x - object->size.x, -flameWidth + object->position.y + object->size.y, object->position.z);
		object->vertexWk[3].vtx =
			D3DXVECTOR3(object->position.x + object->size.x, -flameWidth + object->position.y + object->size.y, object->position.z);
	}
	if (guageType == UP_GUAGEBAR)
	{
		// 頂点座標の設定
		object->vertexWk[0].vtx =
			D3DXVECTOR3(object->position.x - object->size.x, flameWidth + object->position.y - object->size.y, object->position.z);
		object->vertexWk[1].vtx =
			D3DXVECTOR3(object->position.x + object->size.x, flameWidth + object->position.y - object->size.y, object->position.z);
		object->vertexWk[2].vtx =
			D3DXVECTOR3(object->position.x - object->size.x,
				-flameWidth + object->vertexWk[0].vtx.y + (object->position.y + object->size.y - object->vertexWk[0].vtx.y)*percentage, object->position.z);
		object->vertexWk[3].vtx =
			D3DXVECTOR3(object->position.x + object->size.x, -flameWidth + object->vertexWk[1].vtx.y + (object->position.y + object->size.y - object->vertexWk[1].vtx.y)*percentage, object->position.z);
	}
}

//=============================================================================
// オブジェクトの頂点座標の設定　（テロップ背景専用）
//=============================================================================
void SetVertexTelopBG(OBJECT *object, float percentage)
{
	// 頂点座標の設定
	object->vertexWk[0].vtx = D3DXVECTOR3(0, object->position.y - object->size.y*percentage, object->position.z);
	object->vertexWk[1].vtx = D3DXVECTOR3(SCREEN_WIDTH, object->position.y - object->size.y*percentage, object->position.z);
	object->vertexWk[2].vtx = D3DXVECTOR3(0 , object->position.y + object->size.y*percentage, object->position.z);
	object->vertexWk[3].vtx = D3DXVECTOR3(SCREEN_WIDTH, object->position.y + object->size.y*percentage, object->position.z);
}

//=============================================================================
// オブジェクトの頂点座標の設定　（カウンター専用）
//=============================================================================
void SetVertexCounter(OBJECT *object, int placeCount, float placeInterval)
{
	// 頂点座標の設定
	object->vertexWk[0].vtx = D3DXVECTOR3(object->position.x + placeCount * placeInterval, object->position.y, object->position.z) 
		+ D3DXVECTOR3(-object->size.x, -object->size.y, 0.0f);
	object->vertexWk[1].vtx = D3DXVECTOR3(object->position.x + placeCount * placeInterval, object->position.y, object->position.z) 
		+ D3DXVECTOR3(object->size.x, -object->size.y, 0.0f);
	object->vertexWk[2].vtx = D3DXVECTOR3(object->position.x + placeCount * placeInterval, object->position.y, object->position.z) 
		+ D3DXVECTOR3(-object->size.x, object->size.y, 0.0f);
	object->vertexWk[3].vtx = D3DXVECTOR3(object->position.x + placeCount * placeInterval, object->position.y, object->position.z) 
		+ D3DXVECTOR3(object->size.x, object->size.y, 0.0f);
}

//=============================================================================
//オブジェクトのテクスチャ座標設定処理
//=============================================================================
void SetTextureObject(OBJECT *object, int divX, int divY, int pattern)
{
	float sizeX = 1.0f / divX;
	float sizeY = 1.0f / divY;
	int x = pattern % divX;
	int y = pattern / divX;

	object->vertexWk[0].tex = D3DXVECTOR2(x * sizeX, y * sizeY);
	object->vertexWk[1].tex = D3DXVECTOR2((x + 1) * sizeX, y * sizeY);
	object->vertexWk[2].tex = D3DXVECTOR2(x * sizeX, (y + 1)* sizeY);
	object->vertexWk[3].tex = D3DXVECTOR2((x + 1) * sizeX, (y + 1) * sizeY);
}

//=============================================================================
//オブジェクトのテクスチャ座標設定処理　（カウンター専用）
//=============================================================================
void SetTextureCounter(OBJECT *object, int number, float placeInterval)
{
	// 頂点座標の設定
	object->vertexWk[0].tex = D3DXVECTOR2(number * placeInterval, 0.0f);
	object->vertexWk[1].tex = D3DXVECTOR2(number * placeInterval + placeInterval, 0.0f);
	object->vertexWk[2].tex = D3DXVECTOR2(number * placeInterval, 1.0f);
	object->vertexWk[3].tex = D3DXVECTOR2(number * placeInterval + placeInterval, 1.0f);
}

//=============================================================================
//オブジェクトのアルファ値設定処理　（透過）
//=============================================================================
void SetAlphaObject(OBJECT *object, float alpha)
{
	object->vertexWk[0].diffuse =
		object->vertexWk[1].diffuse =
		object->vertexWk[2].diffuse =
		object->vertexWk[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, alpha);
}

//=============================================================================
//オブジェクトの反射光設定処理
//=============================================================================
void SetColorObject(OBJECT *object, D3DXCOLOR color)
{
	object->vertexWk[0].diffuse =
		object->vertexWk[1].diffuse =
		object->vertexWk[2].diffuse =
		object->vertexWk[3].diffuse = color;
}

//=============================================================================
// オブジェクトカウント取得処理
//=============================================================================
float GetCountObject(OBJECT *object, float duration)
{
	object->countFrame++;
	float t = (float)object->countFrame / duration;

	return t;
}
