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
void Object::LoadTexture(LPDIRECT3DDEVICE9 device, const char *path)
{
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(device,	// デバイスへのポインタ
		path,							// ファイルのアドレス
		&texture);						// 読み込むメモリー
}

//=============================================================================
// オブジェクトサークルの作成　（回転オブジェクト用のサークルを作る）
//=============================================================================
void Object::CreateObjectCircle()
{
	D3DXVECTOR2 temp = D3DXVECTOR2(size.x, size.y);
	radius = D3DXVec2Length(&temp);
	baseAngle = atan2f(size.y, size.x);
}

//=============================================================================
// テクスチャの解放
//=============================================================================
void Object::ReleaseTexture()
{
	if (texture != NULL)
	{// テクスチャの開放
		texture->Release();
		texture = NULL;
	}
}

//=============================================================================
// テクスチャの初期化
//=============================================================================
void Object::InitialTexture()
{
	// テクスチャ情報
	&texture;
}

//=============================================================================
// オブジェクト描画処理
//=============================================================================
void Object::DrawObject(LPDIRECT3DDEVICE9 pDevice)
{
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, texture);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// テクスチャの頂点の作成
//=============================================================================
void Object::MakeVertexObject()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点座標の設定
	vertexWk[0].vtx = position + D3DXVECTOR3(-size.x, -size.y, 0.0f);
	vertexWk[1].vtx = position + D3DXVECTOR3(size.x, -size.y, 0.0f);
	vertexWk[2].vtx = position + D3DXVECTOR3(-size.x, size.y, 0.0f);
	vertexWk[3].vtx = position + D3DXVECTOR3(size.x, size.y, 0.0f);

	// テクスチャのパースペクティブコレクト用
	vertexWk[0].rhw =
		vertexWk[1].rhw =
		vertexWk[2].rhw =
		vertexWk[3].rhw = 1.0f;

	// テクスチャ座標の設定
	vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexWk[1].tex = D3DXVECTOR2(1.0, 0.0f);
	vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);
}

//=============================================================================
// テクスチャの頂点の作成 (回転オブジェクト用)
//=============================================================================
void Object::MakeVertexRotateObject()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点座標の設定
	vertexWk[0].vtx.x = position.x - cosf(baseAngle + rotation.z) * radius;
	vertexWk[0].vtx.y = position.y - sinf(baseAngle + rotation.z) * radius;
	vertexWk[0].vtx.z = 0.0f;

	vertexWk[1].vtx.x = position.x + cosf(baseAngle - rotation.z) * radius;
	vertexWk[1].vtx.y = position.y - sinf(baseAngle - rotation.z) * radius;
	vertexWk[1].vtx.z = 0.0f;

	vertexWk[2].vtx.x = position.x - cosf(baseAngle - rotation.z) * radius;
	vertexWk[2].vtx.y = position.y + sinf(baseAngle - rotation.z) * radius;
	vertexWk[2].vtx.z = 0.0f;

	vertexWk[3].vtx.x = position.x + cosf(baseAngle + rotation.z) * radius;
	vertexWk[3].vtx.y = position.y + sinf(baseAngle + rotation.z) * radius;
	vertexWk[3].vtx.z = 0.0f;

	// テクスチャのパースペクティブコレクト用
	vertexWk[0].rhw =
		vertexWk[1].rhw =
		vertexWk[2].rhw =
		vertexWk[3].rhw = 1.0f;

	// テクスチャ座標の設定
	vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexWk[1].tex = D3DXVECTOR2(1.0, 0.0f);
	vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);
}

//=============================================================================
// テクスチャの頂点の作成　（ゲージ専用）
//=============================================================================
void Object::MakeVertexGuageBar(float percentage, float flameWidth)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点座標の設定
	vertexWk[0].vtx = D3DXVECTOR3(flameWidth + position.x, position.y, position.z)
		+ D3DXVECTOR3(-size.x, -size.y, 0.0f);
	vertexWk[1].vtx = D3DXVECTOR3(-flameWidth + position.x*percentage, position.y, position.z)
		+ D3DXVECTOR3(size.x, -size.y, 0.0f);
	vertexWk[2].vtx = D3DXVECTOR3(flameWidth + position.x, position.y, position.z)
		+ D3DXVECTOR3(-size.x, size.y, 0.0f);
	vertexWk[3].vtx = D3DXVECTOR3(-flameWidth + position.x*percentage, position.y, position.z)
		+ D3DXVECTOR3(size.x, size.y, 0.0f);

	// テクスチャのパースペクティブコレクト用
	vertexWk[0].rhw =
		vertexWk[1].rhw =
		vertexWk[2].rhw =
		vertexWk[3].rhw = 1.0f;

	// テクスチャ座標の設定
	vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);
}

//=============================================================================
// オブジェクトの頂点座標の設定
//=============================================================================
void Object::SetVertexObject()
{
	// 頂点座標の設定
	vertexWk[0].vtx = position + D3DXVECTOR3(-size.x, -size.y, 0.0f);
	vertexWk[1].vtx = position + D3DXVECTOR3(size.x, -size.y, 0.0f);
	vertexWk[2].vtx = position + D3DXVECTOR3(-size.x, size.y, 0.0f);
	vertexWk[3].vtx = position + D3DXVECTOR3(size.x, size.y, 0.0f);
}

//=============================================================================
// オブジェクトの頂点座標の設定 (回転オブジェクト用)
//=============================================================================
void Object::SetVertexRotateObject()
{
	// 頂点座標の設定
	vertexWk[0].vtx.x = position.x - cosf(baseAngle + rotation.z) * radius;
	vertexWk[0].vtx.y = position.y - sinf(baseAngle + rotation.z) * radius;
	vertexWk[0].vtx.z = 0.0f;

	vertexWk[1].vtx.x = position.x + cosf(baseAngle - rotation.z) * radius;
	vertexWk[1].vtx.y = position.y - sinf(baseAngle - rotation.z) * radius;
	vertexWk[1].vtx.z = 0.0f;

	vertexWk[2].vtx.x = position.x - cosf(baseAngle - rotation.z) * radius;
	vertexWk[2].vtx.y = position.y + sinf(baseAngle - rotation.z) * radius;
	vertexWk[2].vtx.z = 0.0f;

	vertexWk[3].vtx.x = position.x + cosf(baseAngle + rotation.z) * radius;
	vertexWk[3].vtx.y = position.y + sinf(baseAngle + rotation.z) * radius;
	vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// オブジェクトの頂点座標の設定　（ゲージ専用）
//=============================================================================
void Object::SetVertexGuageBar(float percentage, float flameWidth, int guageType)
{
	if (guageType == LEFT_GUAGEBAR)
	{
		// 頂点座標の設定
		vertexWk[0].vtx =
			D3DXVECTOR3(flameWidth + position.x - size.x, position.y - size.y, position.z);
		vertexWk[1].vtx =
			D3DXVECTOR3(-flameWidth + vertexWk[0].vtx.x + (position.x + size.x - vertexWk[0].vtx.x)*percentage,
				position.y - size.y, position.z);
		vertexWk[2].vtx =
			D3DXVECTOR3(flameWidth + position.x - size.x, position.y + size.y, position.z);
		vertexWk[3].vtx =
			D3DXVECTOR3(-flameWidth + vertexWk[2].vtx.x + (position.x + size.x - vertexWk[2].vtx.x)*percentage,
				position.y + size.y, position.z);
	}
	if (guageType == RIGHT_GUAGEBAR)
	{
		// 頂点座標の設定
		vertexWk[0].vtx =
			D3DXVECTOR3(flameWidth + vertexWk[1].vtx.x + (position.x - size.x - vertexWk[1].vtx.x)*percentage, position.y - size.y, position.z);
		vertexWk[1].vtx =
			D3DXVECTOR3(-flameWidth + position.x + size.x, position.y - size.y, position.z);
		vertexWk[2].vtx =
			D3DXVECTOR3(flameWidth + vertexWk[3].vtx.x + (position.x - size.x - vertexWk[3].vtx.x)*percentage, position.y + size.y, position.z);
		vertexWk[3].vtx =
			D3DXVECTOR3(-flameWidth + position.x + size.x,
				position.y + size.y, position.z);
	}
	if (guageType == DOWN_GUAGEBAR)
	{
		// 頂点座標の設定
		vertexWk[0].vtx =
			D3DXVECTOR3(position.x - size.x,
				flameWidth + vertexWk[2].vtx.y + (position.y - size.y - vertexWk[2].vtx.y)*percentage, position.z);
		vertexWk[1].vtx =
			D3DXVECTOR3(position.x + size.x,
				flameWidth + vertexWk[3].vtx.y + (position.y - size.y - vertexWk[3].vtx.y)*percentage, position.z);
		vertexWk[2].vtx =
			D3DXVECTOR3(position.x - size.x, -flameWidth + position.y + size.y, position.z);
		vertexWk[3].vtx =
			D3DXVECTOR3(position.x + size.x, -flameWidth + position.y + size.y, position.z);
	}
	if (guageType == UP_GUAGEBAR)
	{
		// 頂点座標の設定
		vertexWk[0].vtx =
			D3DXVECTOR3(position.x - size.x, flameWidth + position.y - size.y, position.z);
		vertexWk[1].vtx =
			D3DXVECTOR3(position.x + size.x, flameWidth + position.y - size.y, position.z);
		vertexWk[2].vtx =
			D3DXVECTOR3(position.x - size.x,
				-flameWidth + vertexWk[0].vtx.y + (position.y + size.y - vertexWk[0].vtx.y)*percentage, position.z);
		vertexWk[3].vtx =
			D3DXVECTOR3(position.x + size.x, -flameWidth + vertexWk[1].vtx.y + (position.y + size.y - vertexWk[1].vtx.y)*percentage, position.z);
	}
}

//=============================================================================
// オブジェクトの頂点座標の設定　（テロップ背景専用）
//=============================================================================
void Object::SetVertexTelopBG(float percentage)
{
	// 頂点座標の設定
	vertexWk[0].vtx = D3DXVECTOR3(0, position.y - size.y*percentage, position.z);
	vertexWk[1].vtx = D3DXVECTOR3(SCREEN_WIDTH, position.y - size.y*percentage, position.z);
	vertexWk[2].vtx = D3DXVECTOR3(0, position.y + size.y*percentage, position.z);
	vertexWk[3].vtx = D3DXVECTOR3(SCREEN_WIDTH, position.y + size.y*percentage, position.z);
}

//=============================================================================
// オブジェクトの頂点座標の設定　（カウンター専用）
//=============================================================================
void Object::SetVertexCounter(int placeCount, float placeInterval)
{
	// 頂点座標の設定
	vertexWk[0].vtx = D3DXVECTOR3(position.x + placeCount * placeInterval, position.y, position.z)
		+ D3DXVECTOR3(-size.x, -size.y, 0.0f);
	vertexWk[1].vtx = D3DXVECTOR3(position.x + placeCount * placeInterval, position.y, position.z)
		+ D3DXVECTOR3(size.x, -size.y, 0.0f);
	vertexWk[2].vtx = D3DXVECTOR3(position.x + placeCount * placeInterval, position.y, position.z)
		+ D3DXVECTOR3(-size.x, size.y, 0.0f);
	vertexWk[3].vtx = D3DXVECTOR3(position.x + placeCount * placeInterval, position.y, position.z)
		+ D3DXVECTOR3(size.x, size.y, 0.0f);
}

//=============================================================================
//オブジェクトのテクスチャ座標設定処理
//=============================================================================
void Object::SetTextureObject(int divX, int divY, int pattern)
{
	float sizeX = 1.0f / divX;
	float sizeY = 1.0f / divY;
	int x = pattern % divX;
	int y = pattern / divX;

	vertexWk[0].tex = D3DXVECTOR2(x * sizeX, y * sizeY);
	vertexWk[1].tex = D3DXVECTOR2((x + 1) * sizeX, y * sizeY);
	vertexWk[2].tex = D3DXVECTOR2(x * sizeX, (y + 1)* sizeY);
	vertexWk[3].tex = D3DXVECTOR2((x + 1) * sizeX, (y + 1) * sizeY);
}

//=============================================================================
//オブジェクトのテクスチャ座標設定処理　（カウンター専用）
//=============================================================================
void Object::SetTextureCounter(int number, float placeInterval)
{
	// 頂点座標の設定
	vertexWk[0].tex = D3DXVECTOR2(number * placeInterval, 0.0f);
	vertexWk[1].tex = D3DXVECTOR2(number * placeInterval + placeInterval, 0.0f);
	vertexWk[2].tex = D3DXVECTOR2(number * placeInterval, 1.0f);
	vertexWk[3].tex = D3DXVECTOR2(number * placeInterval + placeInterval, 1.0f);
}

//=============================================================================
//オブジェクトのアルファ値設定処理　（透過）
//=============================================================================
void Object::SetAlphaObject(float alpha)
{
	vertexWk[0].diffuse =
		vertexWk[1].diffuse =
		vertexWk[2].diffuse =
		vertexWk[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, alpha);
}

//=============================================================================
//オブジェクトの反射光設定処理
//=============================================================================
void Object::SetColorObject(D3DXCOLOR color)
{
	vertexWk[0].diffuse =
		vertexWk[1].diffuse =
		vertexWk[2].diffuse =
		vertexWk[3].diffuse = color;
}

//=============================================================================
// オブジェクトカウント取得処理
//=============================================================================
float Object::GetCountObject(float duration)
{
	countFrame++;
	float t = (float)countFrame / duration;

	return t;
}
