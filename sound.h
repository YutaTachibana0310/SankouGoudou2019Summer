//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : �n糗Ǒ�
//
//=============================================================================
#ifndef _SOUND_H
#define _SOUND_H

#include<xact3.h>

class Sound{
private:
//�|�C���^�錾
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

	//�R���X�g���N�^
	Sound();

	static void Create();

	//�f�X�g���N�^
	virtual ~Sound();

	static void Destroy();

	//�����o�ϐ�
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
