
//=============================================================================
//
// サウンド処理 [sound.cpp]
// Author : 渡邉良則
//
//=============================================================================

#include "sound.h"
#include "soundUI.h"

Sound *Sound::sound = NULL;

//デフォルトコンストラクタ
Sound::Sound()
{

	for (int i = 0; i < MAXBGM; i++) {
		BGMplayflag[i] = false;
		maxvol_BGM[i] = 0.0f;
		fadevolume[i] = 0.0f;
	}
	for (int i = 0; i < MAXSE; i++) {
		SEplayflag[i] = false;

	}

	pauseflag = false;
	playsound = true;
	pause = false;
	changepitch = 0;
	fadecounta = 0.0f;

}

void Sound::Create() {
	if (!sound) {
		sound = new Sound();
	}
}

//デストラクタ
Sound::~Sound()
{

	//XACTをシャットダウン
	if (xactEngine) {

		//XACTエンジンをシャットダウン、リソース解放
		xactEngine->ShutDown();
		xactEngine->Release();
	}
	if (soundBankData) {
		delete[] soundBankData;
	}
	soundBankData = NULL;

	//xactEngine->ShutDown()から戻った後、メモリマップドファイルを開放
	if (mapWaveBank) {
		UnmapViewOfFile(mapWaveBank);
	}
	mapWaveBank = NULL;

	//CoInitializeExが成功した場合
	if (coInitialized) {
		CoUninitialize();
	}
}

//初期化
//1.xactEngine->Initializeによって呼び出されたXACTを初期化
//2.使用するXACTウェイブバンクを作成
//3.使用するXACTサウンドバンクを作成
//4.ゲームが使用するXACTキューにインデックスを格納

HRESULT Sound::initialize() {

	xactEngine = NULL;
	BGMwaveBank = NULL;
	SEwaveBank = NULL;
	soundBank = NULL;
	mapWaveBank = NULL;
	soundBankData = NULL;
	changevol = MAXVOLUME;
	UIcounta = SOUNDUI_PARTS_MAX;


	HRESULT result = E_FAIL;
	HANDLE hFile;
	DWORD fileSize;
	DWORD bytesRead;
	HANDLE hMapFile;

	HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
	if (SUCCEEDED(hr)) {
		coInitialized = true;
	}
	else {
		coInitialized = false;
	}

	if (coInitialized == false) {
		return E_FAIL;
	}

	result = XACT3CreateEngine(0, &xactEngine);
	if (FAILED(result) || xactEngine == NULL) {
		return E_FAIL;
	}

	//XACTランタイムを初期化し、作成する
	XACT_RUNTIME_PARAMETERS xactParams = { 0 };
	xactParams.lookAheadTime = XACT_ENGINE_LOOKAHEAD_DEFAULT;
	result = xactEngine->Initialize(&xactParams);
	if (FAILED(result)) {
		return result;
	}

	//BGM側のWaveBank作成
	//メモリマップドファイルIOを使用する"インメモリ"のXACTウェイブバンクファイルを作成
	result = E_FAIL; //失敗をデフォルトとして成功時に置き換える
	hFile = CreateFile(BGM, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		fileSize = GetFileSize(hFile, NULL);
		if (fileSize != -1)
		{
			hMapFile = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, fileSize, NULL);
			if (hMapFile)
			{
				mapWaveBank = MapViewOfFile(hMapFile, FILE_MAP_READ, 0, 0, 0);
				if (mapWaveBank)
				{
					result = xactEngine->CreateInMemoryWaveBank(mapWaveBank, fileSize, 0, 0, &BGMwaveBank);
				}
				CloseHandle(hMapFile);	// mapWaveBankがファイルへのハンドルを保持するのでこの不要なハンドルを閉じる
			}
		}
		CloseHandle(hFile);		// mapWaveBankはがファイルへのハンドルを保持するのでこの不要なハンドルを閉じる
	}
	if (FAILED(result))
	{
		return HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND);
	}

	//SE側のWaveBank作成
	//メモリマップドファイルIOを使用する"インメモリ"のXACTウェイブバンクファイルを作成
	result = E_FAIL; //失敗をデフォルトとして成功時に置き換える
	hFile = CreateFile(SE, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		fileSize = GetFileSize(hFile, NULL);
		if (fileSize != -1)
		{
			hMapFile = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, fileSize, NULL);
			if (hMapFile)
			{
				mapWaveBank = MapViewOfFile(hMapFile, FILE_MAP_READ, 0, 0, 0);
				if (mapWaveBank)
				{
					result = xactEngine->CreateInMemoryWaveBank(mapWaveBank, fileSize, 0, 0, &SEwaveBank);
				}
				CloseHandle(hMapFile);	// mapWaveBankがファイルへのハンドルを保持するのでこの不要なハンドルを閉じる
			}
		}
		CloseHandle(hFile);		// mapWaveBankはがファイルへのハンドルを保持するのでこの不要なハンドルを閉じる
	}

	if (FAILED(result))
	{
		return HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND);
	}

	// XACTで作成したサウンドバンクファイルを読み込んで予約
	result = E_FAIL;	// 失敗をデフォルトとして、成功時に置き換える
	hFile = CreateFile(SOUND_BANK, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		fileSize = GetFileSize(hFile, NULL);
		if (fileSize != -1)
		{
			soundBankData = new BYTE[fileSize];		// サウンドバンクのメモリを確保する
			if (soundBankData)
			{
				if (0 != ReadFile(hFile, soundBankData, fileSize, &bytesRead, NULL))
				{
					result = xactEngine->CreateSoundBank(soundBankData, fileSize, 0, 0, &soundBank);
				}
			}
		}
		CloseHandle(hFile);
	}
	if (FAILED(result))
	{
		return HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND);
	}

	return S_OK;
}

//=============================================================================
// 周期的なサウンドエンジンタスクを実行
//=============================================================================
void Sound::run()
{
	if (xactEngine == NULL)
	{
		return;
	}
	xactEngine->DoWork();
}

//=============================================================================
// 指定されたサウンドをウェイブバンクらから再生
// 存在しない場合は、サウンドが再生されないだけで、エラーは発生しない
//=============================================================================
void Sound::SetPlayBGM(int wavenum,bool playflag,float vol) {
	if (BGMwaveBank == NULL) {
		return;
	}
	//再生フラグがfalseの場合に再生
	if (!BGMplayflag[wavenum] && !pauseflag) {
		BGMwaveBank->Play(wavenum, XACT_FLAG_UNITS_MS, 0, 99, &BGMwave[wavenum]);
		Sound::ChangeBGMVolume(wavenum, vol);
	}
	//再生フラグをtreuにし多重再生しないように
	BGMplayflag[wavenum] = playflag;

}

void Sound::SetPlaySE(int wavenum, bool playflag, float vol) {

	if (SEwaveBank == NULL) {
		return;
	}
	//※SEの場合はポーズ中に再生できるかのフラグ管理
	//SE再生は基本的にtrue
	//falseの場合はポーズ中に再生できるSE
	SEplayflag[wavenum] = playflag;

	//再生フラグがtrueかつポーズフラグもfalseの場合に再生
	if (SEplayflag[wavenum] && !pauseflag) {
		SEwaveBank->Play(wavenum, XACT_FLAG_UNITS_MS, 0, 0, &SEwave[wavenum]);
		Sound::ChangeSEVolume(wavenum, vol);

	}
	else if (!SEplayflag[wavenum] && pauseflag)
	{
		//playflagをtrueにした場合はポーズ中に再生できるように
		SEwaveBank->Play(wavenum, XACT_FLAG_UNITS_MS, 0, 0, &SEwave[wavenum]);
		Sound::ChangeSEVolume(wavenum, vol);
	}



}
//=============================================================================
// 指定されたサウンドをウェイブバンクで停止
// サウンドが存在しない場合、エラーは発生しない
//=============================================================================
void Sound::SetStopSoundOll() {

	if (BGMwaveBank == NULL)
	{
		return;
	}
	if (SEwaveBank == NULL)
	{
		return;
	}

	for (int i = 0; i < MAXBGM; i++) {
		BGMwaveBank->Stop(i, XACT_FLAG_STOP_IMMEDIATE);
		BGMplayflag[i] = false;
	}
	for (int i = 0; i < MAXSE; i++) {
		SEwaveBank->Stop(i, XACT_FLAG_STOP_IMMEDIATE);
		SEplayflag[i] = false;
	}
}
//=============================================================================
// 指定されたサウンドをウェイブバンクで停止（個別）
// サウンドが存在しない場合、エラーは発生しない
//=============================================================================
void Sound::SetStopSound(int wavenum) {

	if (BGMwaveBank == NULL)
	{
		return;
	}
	if (SEwaveBank == NULL)
	{
		return;
	}

	BGMwaveBank->Stop(wavenum, XACT_FLAG_STOP_IMMEDIATE);
	BGMplayflag[wavenum] = false;

}

//=============================================================================
// 一時停止（TRUEで停止、FALSEで再生）
//=============================================================================
void Sound::ChangePauseSound(bool b) {

	pauseflag = b;
	for (int i = 0; i < MAXBGM; i++) {
		if (BGMplayflag[i]){
			BGMwave[i]->Pause(b);			
		}

	}
	for (int i = 0; i < MAXSE; i++) {
		if (SEplayflag[i]) {
			SEwave[i]->Pause(b);
		}

	}


}
//=============================================================================
// 音量の調整
//=============================================================================
void Sound::ChangeBGMVolume(int wavenum,float vol) {

	if (BGMwave[wavenum] == NULL)
	{
		return;
	}
	BGMwave[wavenum]->SetVolume(vol);

}
void Sound::ChangeSEVolume(int wavenum, float vol) {

	SEwave[wavenum]->SetVolume(vol);

}

//=============================================================================
// フェードの調整
//=============================================================================
void Sound::FadeIn(int wavenum, float fadesec,float setvol,bool inflag) {
	//60フレーム
	//4秒と仮定 = 60フレーム * 4 = 240
	//最大vol = 1
	//vol1 / 4秒 = 1秒間に0.25
	//0.25 / 60 = 1フレームに上がる音量(4秒の場合0.00416…)
	//0.004 * 240 = 0.96(最大vol1）

	if (BGMwave[wavenum] == NULL)
	{
		return;
	}

	if (maxvol_BGM[wavenum] >= fadevolume[wavenum]) {
		fadecounta++;

		maxvol_BGM[wavenum] = setvol;
		fadevolume[wavenum] += (maxvol_BGM[wavenum] / fadesec) / FLAME;
		Sound::ChangeBGMVolume(wavenum, fadevolume[wavenum]);
	}
	else {
		fadecounta = 0;
	}


}
void Sound::FadeOut(int wavenum, float fadesec, float setvol, bool outflag) {

	if (BGMwave[wavenum] == NULL)
	{
		return;
	}

	if (fadevolume[wavenum] >= 0) {
		fadecounta++;
	}

	if (fadecounta / 60 <= fadesec && fadevolume[wavenum] >= 0) {
		maxvol_BGM[wavenum] = setvol;
		fadevolume[wavenum] -= (maxvol_BGM[wavenum] / fadesec) / FLAME;
		Sound::ChangeBGMVolume(wavenum, fadevolume[wavenum]);
	}
	else {
		fadecounta = 0;
	}
}

void Sound::SetPitchSE(int wavenum, int pitch) {
	//ピッチの値は-1200～1200の間
	if (SEwave[wavenum] != NULL) {
		SEwave[wavenum]->SetPitch(pitch);
	}
}

