//=============================================================================
//
// プレイヤー処理 [player.h]
// Author : 渡邉良則
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

// マクロ定義
#define TEXTURE_GAME_SAMPLE00	_T("data/TEXTURE/runningman002.png")	// サンプル用画像
#define TEXTURE_SAMPLE00_SIZE_X	(50) // テクスチャサイズ
#define TEXTURE_SAMPLE00_SIZE_Y	(50) // 同上

#define MAX_LENGTH (6)
#define JUDG_LEN (5)

typedef struct
{
	LPDIRECT3DTEXTURE9		D3DTexturePlayer = NULL;		// テクスチャへのポリゴン

	VERTEX_2D				vertexWk[NUM_VERTEX];				// 頂点情報格納ワーク

	D3DXVECTOR3				posPlayer;						// ポリゴンの移動量
	D3DXVECTOR3				rotPlayer;						// ポリゴンの回転量
	int						nCountAnim;						// アニメーションカウント
	int						nPatternAnim;						// アニメーションパターンナンバー

	D3DXVECTOR3				targetpos[MAX_LENGTH];

	// 移動先確保用のナンバー
	int goal;

}PLAYER;


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);

HRESULT MakeVertexPlayer(void);
void SetVertex(void);


#endif
