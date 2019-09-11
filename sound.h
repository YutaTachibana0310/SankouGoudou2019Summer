//=============================================================================
//
// サウンド処理 [sound.h]
// Author : 渡邉良則
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

//流すBGMのファイル場所及び表題取得

const char BGM[] = "data/SOUND/Win/BGM.xwb";
const char SE[] = "data/SOUND/Win/SE.xwb";
const char SOUND_BANK[] = "data/SOUND/Win/Sound Bank.xsb";

const char TITLE_BGM[] = "Jackhammer";
const char GAME_BGM[] = "Blue_LIGHT_Techno";
const char BOSS_BGM[] = "ダーティーファイト";

const char ENTER_SE_NOTUSE[] = "決定SE";
const char TEST_SE[] = "発砲音";
const char COMBO_SE[] = "combo";
const char ENEMYDOWN1_SE[] = "小エネミー爆発";
const char ENEMYDOWN2_SE[] = "中エネミー爆発 2";
const char PLAYERDAMAGE_SE[] = "Eショット着弾";
const char PLAYERSHOT_SE[] = "Pショット発射音";
const char ENEMYNOTICE_SE[] = "エネミー出現予告";
const char BOMB_SE[] = "bomb";
const char BOMBSTOCK_SE[] = "bombstock";
const char ENTER_SE[] = "ENTERSE";
const char ALARM_SE[] = "警報";
const char BOSSSHOT_SE[] = "bossshot";
const char BOSSEXPLODE_SE[] = "BossExplode";
const char GAMEOVER_SE[] = "gameover";
const char MIDENEMYDAMAGE_SE[] = "中エネミーダメージ";


//ナンバーはWaveに登録した順番になること
//名前は正式曲名ではなく、わかりやすく明示すること（例：ステージ1BGM）
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

bool pauseflag;


//フェード用に現在再生中の最大音量をセット
float maxvol_BGM[MAXBGM];

//実際に変更するフェード音量
float fadevolume[MAXBGM];

public:

	//サウンドテスト用
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
	//再生フラグ、trueの場合再生
	bool BGMplayflag[MAXBGM];
	bool SEplayflag[MAXSE];

	//コンストラクタ
	Sound();

	static void Create();

	//デストラクタ
	virtual ~Sound();

	//メンバ変数
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
