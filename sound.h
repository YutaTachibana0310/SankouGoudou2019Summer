//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : �n糗Ǒ�
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
//�|�C���^�錾
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
	//�Đ��t���O�Atrue�̏ꍇ�Đ�
	bool BGMplayflag[MAXBGM];
	bool SEplayflag[MAXSE];

	//�R���X�g���N�^
	Sound();

	static void Create();

	//�f�X�g���N�^
	virtual ~Sound();

	static void Destroy();

	//�����o�ϐ�
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
