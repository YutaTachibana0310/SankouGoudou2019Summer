
//=============================================================================
//
// サウンド処理 [sound.cpp]
// Author : 渡邉良則
//
//=============================================================================

#include "sound.h"
#include "constants.h"

Sound *Sound::sound = NULL;

//デフォルトコンストラクタ
Sound::Sound()
{
	//Create();
	xactEngine = NULL;
	waveBank = NULL;
	soundBank = NULL;
	mapWaveBank = NULL;
	soundBankData = NULL;
	wave[0] = NULL;
	wave[1] = NULL;

	HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
	if (SUCCEEDED(hr)) {
		coInitialized = true;
	}
	else {
		coInitialized = false;
	}

}

void Sound::Create() {
	if (!sound) {
		sound = new Sound();
	}
}

//デストラクタ
Sound::~Sound()
{
	//Destroy();
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

void Sound::Destroy() {
	delete sound;
	sound = NULL;
}


//初期化
//1.xactEngine->Initializeによって呼び出されたXACTを初期化
//2.使用するXACTウェイブバンクを作成
//3.使用するXACTサウンドバンクを作成
//4.ゲームが使用するXACTキューにインデックスを格納

HRESULT Sound::initialize() {

	HRESULT result = E_FAIL;
	HANDLE hFile;
	DWORD fileSize;
	DWORD bytesRead;
	HANDLE hMapFile;

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

	//メモリマップドファイルIOを使用する"インメモリ"のXACTウェイブバンクファイルを作成
	result = E_FAIL; //失敗をデフォルトとして成功時に置き換える
	hFile = CreateFile(WAVE_BANK, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
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
					result = xactEngine->CreateInMemoryWaveBank(mapWaveBank, fileSize, 0, 0, &waveBank);
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
// キューで指定されたサウンドをサウンドバンクらから再生
// キューが存在しない場合は、サウンドが再生されないだけで、エラーは発生しない
//=============================================================================
void Sound::SetPlaySound(int n) {
	if (waveBank == NULL) {
		return;
	}

	switch (n)
	{
	case 0:
		//Play(waveに登録した順番の曲、フラグ？、オフセット？、ループ回数、waveポインタ）
		waveBank->Play(n, XACT_FLAG_UNITS_MS, 0, 0, &wave[0]);
		break;
	case 1:
		waveBank->Play(n, XACT_FLAG_UNITS_MS, 0, 99, &wave[1]);
		break;
	}
}
//=============================================================================
// 指定されたサウンドをウェイブバンクで停止
// サウンドが存在しない場合、エラーは発生しない
//=============================================================================
void Sound::SetStopSound(int n) {
	if (waveBank == NULL)
	{
		return;
	}
	
	waveBank->Stop(n, XACT_FLAG_STOP_IMMEDIATE);

}
//=============================================================================
// 一時停止（TRUEで停止、FALSEで再生）
//=============================================================================
void Sound::CangePauseSound(int n,bool b) {

	wave[n]->Pause(b);


}
//=============================================================================
// 音量の調整
//=============================================================================
void Sound::CangeSoundVolume(int n,float f) {

	wave[n]->SetVolume(f);

}