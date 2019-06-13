//=============================================================================
//
// サウンド処理 [sound.h]
// Author : 渡邉良則
//
//=============================================================================
#ifndef _SOUND_H
#define _SOUND_H

#include<xact3.h>

#define MAXBGM (2)
#define MAXSE (2)
#define ALLSOUND (MAXBGM+MAXSE)

class Sound{
private:
//ポインタ宣言
IXACT3Engine* xactEngine;
IXACT3WaveBank* BGMwaveBank;
IXACT3WaveBank* SEwaveBank;
IXACT3SoundBank* soundBank;
IXACT3Wave* BGMwave[MAXBGM];
IXACT3Wave* SEwave[MAXSE];

void* mapWaveBank;
void* soundBankData;
bool coInitialized;

public:

	static Sound *GetInstance() {
		return sound;
	}
	//再生フラグ、trueの場合再生
	bool BGMplayflag[MAXBGM];
	bool SEplayflag[MAXSE];

	//コンストラクタ
	Sound();

	static void Create();

	//デストラクタ
	virtual ~Sound();

	static void Destroy();

	//メンバ変数
	HRESULT initialize();

	void run();

	void SetPlayBGM(int n,bool b);

	void SetPlaySE(int n,bool b);

	void SetStopSound();

	void CangePauseSound(bool b);

	void CangeBGMVolume(int n,float f);

	void CangeSEVolume(int n, float f);
protected:
	static Sound *sound;


};

#endif
