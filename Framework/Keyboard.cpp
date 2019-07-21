//=====================================
//
//キーボード処理[Keyboard.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "Keyboard.h"

/**************************************
マクロ定義
***************************************/
#define	NUM_KEY_MAX		(256)			// キー最大数

/**************************************
クラス定義
***************************************/

/**************************************
グローバル変数
***************************************/
LPDIRECTINPUTDEVICE8 g_pDIDevKeyboard = NULL;			// IDirectInputDevice8インターフェースへのポインタ(キーボード)
BYTE	g_aKeyState[NUM_KEY_MAX];			// キーボードの押下状態を保持するワーク
BYTE	g_aKeyStateTrigger[NUM_KEY_MAX];	// キーボードのトリガー状態を保持するワーク
BYTE	g_aKeyStateRelease[NUM_KEY_MAX];	// キーボードのリリース状態を保持するワーク
BYTE	g_aKeyStateRepeat[NUM_KEY_MAX];		// キーボードのリピート状態を保持するワーク
int		g_aKeyStateRepeatCnt[NUM_KEY_MAX];	// キーボードのリピートカウンタ

//=============================================================================
// キーボードの初期化処理
//=============================================================================
HRESULT InitKeyboard(HINSTANCE hInst, HWND hWnd, LPDIRECTINPUT8 inputInterface)
{
	HRESULT hr;

	// デバイスオブジェクトを作成
	hr = inputInterface->CreateDevice(GUID_SysKeyboard, &g_pDIDevKeyboard, NULL);
	if (FAILED(hr) || g_pDIDevKeyboard == NULL)
	{
		MessageBox(hWnd, "キーボードがねぇ！", "警告！", MB_ICONWARNING);
		return hr;
	}

	// データフォーマットを設定
	hr = g_pDIDevKeyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr))
	{
		MessageBox(hWnd, "キーボードのデータフォーマットを設定できませんでした。", "警告！", MB_ICONWARNING);
		return hr;
	}

	// 協調モードを設定（フォアグラウンド＆非排他モード）
	hr = g_pDIDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if (FAILED(hr))
	{
		MessageBox(hWnd, "キーボードの協調モードを設定できませんでした。", "警告！", MB_ICONWARNING);
		return hr;
	}

	// キーボードへのアクセス権を獲得(入力制御開始)
	g_pDIDevKeyboard->Acquire();

	return S_OK;
}

//=============================================================================
// キーボードの終了処理
//=============================================================================
void UninitKeyboard(void)
{
	if (g_pDIDevKeyboard)
	{// デバイスオブジェクトの開放
		g_pDIDevKeyboard->Release();
		g_pDIDevKeyboard = NULL;
	}
}

//=============================================================================
// キーボードの更新処理
//=============================================================================
HRESULT UpdateKeyboard(void)
{
	HRESULT hr;
	BYTE aKeyState[NUM_KEY_MAX];

	// デバイスからデータを取得
	hr = g_pDIDevKeyboard->GetDeviceState(sizeof(aKeyState), aKeyState);
	if (SUCCEEDED(hr))
	{
		for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			g_aKeyStateTrigger[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];
			g_aKeyStateRelease[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & ~aKeyState[nCntKey];
			g_aKeyStateRepeat[nCntKey] = g_aKeyStateTrigger[nCntKey];

			if (aKeyState[nCntKey])
			{
				g_aKeyStateRepeatCnt[nCntKey]++;
				if (g_aKeyStateRepeatCnt[nCntKey] >= 20 && g_aKeyStateRepeatCnt[nCntKey] % 5 == 0)
				{
					g_aKeyStateRepeat[nCntKey] = aKeyState[nCntKey];
				}
				//else
				//{
				//	g_aKeyStateRepeat[nCntKey] = 0;
				//}
			}
			else
			{
				g_aKeyStateRepeatCnt[nCntKey] = 0;
				g_aKeyStateRepeat[nCntKey] = 0;
			}

			g_aKeyState[nCntKey] = aKeyState[nCntKey];
		}
	}
	else
	{
		// キーボードへのアクセス権を取得
		g_pDIDevKeyboard->Acquire();
	}

	return S_OK;
}

//=============================================================================
// キーボードのプレス状態を取得
//=============================================================================
bool GetKeyboardPress(int nKey)
{
	return (g_aKeyState[nKey] & 0x80) ? true : false;
}

//=============================================================================
// キーボードのトリガー状態を取得
//=============================================================================
bool GetKeyboardTrigger(int nKey)
{
	return (g_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//=============================================================================
// キーボードのリピート状態を取得
//=============================================================================
bool GetKeyboardRepeat(int nKey)
{
	return (g_aKeyStateRepeat[nKey] & 0x80) ? true : false;
}

//=============================================================================
// キーボードのリリ－ス状態を取得
//=============================================================================
bool GetKeyboardRelease(int nKey)
{
	return (g_aKeyStateRelease[nKey] & 0x80) ? true : false;
}