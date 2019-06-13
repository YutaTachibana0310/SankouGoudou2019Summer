//=============================================================================
//
// サウンド処理 [sound.h]
// Author : 渡邉良則
//
//=============================================================================
#ifndef _SOUND_H
#define _SOUND_H

#include<xact3.h>

class Sound{
private:
//ポインタ宣言
IXACT3Engine* xactEngine;
IXACT3WaveBank* waveBank;
IXACT3SoundBank* soundBank;
IXACT3Wave* wave[2];

void* mapWaveBank;
void* soundBankData;
bool coInitialized;

public:

	static Sound *GetInstance() {
		return sound;
	}

	//コンストラクタ
	Sound();

	static void Create();

	//デストラクタ
	virtual ~Sound();

	static void Destroy();

	//メンバ変数
	HRESULT initialize();

	void run();

	void SetPlaySound(int n);

	void SetStopSound(int n);

	void CangePauseSound(int n,bool b);

	void CangeSoundVolume(int n,float f);

protected:
	static Sound *sound;


};

#endif
