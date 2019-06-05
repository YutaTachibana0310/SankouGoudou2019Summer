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

#define TEXTURE_PATTERN_DIVIDE_X	(5)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y	(2)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM			(TEXTURE_PATTERN_DIVIDE_X*TEXTURE_PATTERN_DIVIDE_Y)	// アニメーションパターン数
#define TIME_ANIMATION				(1000)	// アニメーションの切り替わるカウント

#define TEXTURE_PATTERN_DIVIDE_X	(5)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y	(2)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM			(TEXTURE_PATTERN_DIVIDE_X*TEXTURE_PATTERN_DIVIDE_Y)	// アニメーションパターン数
#define MAX_LENGTH (6)
#define JUDG_LEN (5)


typedef struct
{
	LPDIRECT3DTEXTURE9		g_pD3DTexturePlayer = NULL;		// テクスチャへのポリゴン

	VERTEX_2D				g_vertexWk[NUM_VERTEX];				// 頂点情報格納ワーク

	D3DXVECTOR3				g_posPlayer;						// ポリゴンの移動量
	D3DXVECTOR3				g_rotPlayer;						// ポリゴンの回転量
	int						g_nCountAnim;						// アニメーションカウント
	int						g_nPatternAnim;						// アニメーションパターンナンバー

	D3DXVECTOR3				targetpos[MAX_LENGTH];

	// 移動先確保用のナンバー
	int goal;
	//移動先へ移動するまで入力を受け付けないようにするためのフラグ
	bool move_wait;

}PLAYER;

enum MOVEFLAG {
	S_KEY = 0,
	W_KEY,
	A_KEY,
	D_KEY,
	Z_KEY,
	X_KEY,
	


};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);


HRESULT MakeVertexPlayer(void);
void SetTexturePlayer(int cntPattern);
void SetVertex(void);
void DrawTEXT(void);

PLAYER* GetPlayer();
#endif
