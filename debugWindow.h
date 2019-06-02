//=====================================
//
//デバッグウィンドウヘッダ[debugWindow.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _DEBUGWINDOW_H_
#define _DEBUGWINDOW_H_

#include "main.h"

#include <string>

/**************************************
マクロ定義
***************************************/
#define USE_DEBUGWINDOW
#define STR(var) #var		//varを文字列に置換するマクロ
/**************************************
構造体定義
***************************************/

/**************************************
プロトタイプ宣言
***************************************/
void DebugLog(const char *str, ...);	//汎用デバッグログ出力関数

/**************************************/
//ImGUIラッパー関数
/***************************************/
void BeginDebugWindow(const char *label);	//デバッグ出力の最初に呼ぶ関数
void EndDebugWindow(const char* label);		//デバッグ出力の最後に呼ぶ関数

//テキスト出力機能
void DebugText(const char *str, ...);
void DebugText(std::string str);

//ボタン機能
bool DebugButton(const char *label);
bool DebugButton(const std::string *label);
bool DebugRadioButton(const char* label, int* output, int val);
bool DebugChechBox(const char* label, bool* val);

//スライダーでfloat値を入力できる機能
bool DebugSliderFloat(const char *label, float *adr, float min, float max);
bool DebugSliderFloat(const std::string *label, float *adr, float min, float max);

//カラーエディット機能
void DebugColorEditor(const char *label, float array[4]);

//ベクトル入力処理
void DebugSliderVector3(const char* label, D3DXVECTOR3 *vec, float min, float max);
void DebugInputVector3(const char* label, D3DXVECTOR3 *vec);
void DebugInputVector2(const char* label, D3DXVECTOR2 *vec);

//データ入力機能
void DebugInputFloat(const char* label, float *var);
bool DebugInputInt(const char* label, int* val);
bool DebugInputText(const char* label, char *buf, size_t buf_size);
bool DebugInputText(const char* label, std::string* pStr);

//テクスチャ描画機能
void DebugDrawTexture(LPDIRECT3DTEXTURE9 texture, float sizeX, float sizeY);

//プログレスバー表示機能
void DebugProgressBar(float fraction, const char* label, D3DXVECTOR2 size = D3DXVECTOR2(-1.0f, 0.0f));

//表示形式調整機能
void DebugNewLine(void);
void DebugSameLine(void);

//ツリー表示機能
void DebugTreeExpansion(bool isOpen);
bool DebugTreePush(const char *label);
void DebugTreePop(void);

//プロシージャ
LRESULT DebugWindPrcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

//各種処理
void InitDebugWindow(HWND hWnd, LPDIRECT3DDEVICE9 pDevice);
void UninitDebugWindow(int num);
void UpdateDebugWindow(void);
void DrawDebugWindow(void);

void SetActiveDebugWindow(bool state = true);	//表示切替処理

//処理時間計測機能
void BeginTimerCount(void);				//高解像度タイマー計測開始
double GetProgressTimerCount(void);		//タイマー経過時間取得処理
void GetTimerCount(LARGE_INTEGER *ptr);	//タイマーカウント取得(20フレーム間隔)
double CalcProgressTime(LARGE_INTEGER start, LARGE_INTEGER end);	//経過時間取得	

#endif