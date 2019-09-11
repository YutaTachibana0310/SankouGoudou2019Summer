//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : �n糗Ǒ�
//
//=============================================================================
#ifndef _SOUND_H
#define _SOUND_H

#include<xact3.h>
#include <windows.h>
#include "IStateScene.h"

#define WIN32_LEAN_AND_MEAN
#define FLAME (float(60))
#define MAXVOLUME (float(1))
#define ALLSOUND (MAXBGM+MAXSE)

//����BGM�̃t�@�C���ꏊ�y�ѕ\��擾

const char BGM[] = "data/SOUND/Win/BGM.xwb";
const char SE[] = "data/SOUND/Win/SE.xwb";
const char SOUND_BANK[] = "data/SOUND/Win/Sound Bank.xsb";

const char TITLE_BGM[] = "Jackhammer";
const char GAME_BGM[] = "Blue_LIGHT_Techno";
const char BOSS_BGM[] = "�_�[�e�B�[�t�@�C�g";

const char ENTER_SE_NOTUSE[] = "����SE";
const char TEST_SE[] = "���C��";
const char COMBO_SE[] = "combo";
const char ENEMYDOWN1_SE[] = "���G�l�~�[����";
const char ENEMYDOWN2_SE[] = "���G�l�~�[���� 2";
const char PLAYERDAMAGE_SE[] = "E�V���b�g���e";
const char PLAYERSHOT_SE[] = "P�V���b�g���ˉ�";
const char ENEMYNOTICE_SE[] = "�G�l�~�[�o���\��";
const char BOMB_SE[] = "bomb";
const char BOMBSTOCK_SE[] = "bombstock";
const char ENTER_SE[] = "ENTERSE";
const char ALARM_SE[] = "�x��";
const char BOSSSHOT_SE[] = "bossshot";
const char BOSSEXPLODE_SE[] = "BossExplode";
const char GAMEOVER_SE[] = "gameover";
const char MIDENEMYDAMAGE_SE[] = "���G�l�~�[�_���[�W";


//�i���o�[��Wave�ɓo�^�������ԂɂȂ邱��
//���O�͐����Ȗ��ł͂Ȃ��A�킩��₷���������邱�Ɓi��F�X�e�[�W1BGM�j
enum BGMNAME
{
	GAMEBGM = 0,
	TITLEBGM,
	BOSSBGM,
	MAXBGM
};

enum SENAME
{
	ENTERSE_NOTUSE = 0,
	TESTSE,
	COMBOSE,
	ENEMYDOWN1,
	ENEMYDOWN2,
	PLAYERDAMAGE,
	PLAYERSHOT,
	ENEMYNOTICE,
	BOMB,
	BOMBSTOCK,
	ENTERSE,
	REBAR,
	ALARM,
	BOSSSHOT,
	BOSSEXPLODE,
	GAMEOVER,
	MIDENEMYDAMAGE,
	MAXSE
};
class Sound {
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

bool pauseflag;


//�t�F�[�h�p�Ɍ��ݍĐ����̍ő剹�ʂ��Z�b�g
float maxvol_BGM[MAXBGM];

//���ۂɕύX����t�F�[�h����
float fadevolume[MAXBGM];

public:

	//�T�E���h�e�X�g�p
	bool playsound;
	bool pause;
	int changepitch;
	float changevol;
	int UIcounta;
	float fadecounta;
	bool enterSE;

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

	//�����o�ϐ�
	HRESULT initialize();

	void run();

	void SetPlayBGM(int wavenum,bool playflag, float vol);

	void SetPlaySE(int wavenum, bool playflag, float vol);

	void SetStopSoundOll();

	void SetStopSound(int wavenum);

	void ChangePauseSound(bool b);

	void ChangeBGMVolume(int wavenum,float vol);

	void ChangeSEVolume(int wavenum, float vol);

	void FadeIn(int wavenum, float fadesec,float setvol, bool inflag);

	void FadeOut(int wavenum, float fadesec, float setvol, bool outflag);

	void SetPitchSE(int wavenum, int pitch);


protected:
	static Sound *sound;


};

#endif
