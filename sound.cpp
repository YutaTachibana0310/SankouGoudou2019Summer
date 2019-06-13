
//=============================================================================
//
// �T�E���h���� [sound.cpp]
// Author : �n糗Ǒ�
//
//=============================================================================

#include "sound.h"
#include "constants.h"

Sound *Sound::sound = NULL;

//�f�t�H���g�R���X�g���N�^
Sound::Sound()
{
	//Create();
	xactEngine = NULL;
	BGMwaveBank = NULL;
	SEwaveBank = NULL;
	soundBank = NULL;
	mapWaveBank = NULL;
	soundBankData = NULL;
	for (int i = 0; i < MAXBGM; i++) {
		BGMplayflag[i] = false;
	}
	for (int i = 0; i < MAXSE; i++) {
		SEplayflag[i] = false;
	}

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

//�f�X�g���N�^
Sound::~Sound()
{
	//Destroy();
	//XACT���V���b�g�_�E��
	if (xactEngine) {

		//XACT�G���W�����V���b�g�_�E���A���\�[�X���
		xactEngine->ShutDown();
		xactEngine->Release();
	}
	if (soundBankData) {
		delete[] soundBankData;
	}
	soundBankData = NULL;

	//xactEngine->ShutDown()����߂�����A�������}�b�v�h�t�@�C�����J��
	if (mapWaveBank) {
		UnmapViewOfFile(mapWaveBank);
	}
	mapWaveBank = NULL;

	//CoInitializeEx�����������ꍇ
	if (coInitialized) {
		CoUninitialize();
	}
}

void Sound::Destroy() {
	delete sound;
	sound = NULL;
}


//������
//1.xactEngine->Initialize�ɂ���ČĂяo���ꂽXACT��������
//2.�g�p����XACT�E�F�C�u�o���N���쐬
//3.�g�p����XACT�T�E���h�o���N���쐬
//4.�Q�[�����g�p����XACT�L���[�ɃC���f�b�N�X���i�[

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

	//XACT�����^�C�������������A�쐬����
	XACT_RUNTIME_PARAMETERS xactParams = { 0 };
	xactParams.lookAheadTime = XACT_ENGINE_LOOKAHEAD_DEFAULT;
	result = xactEngine->Initialize(&xactParams);
	if (FAILED(result)) {
		return result;
	}

	//BGM����WaveBank�쐬
	//�������}�b�v�h�t�@�C��IO���g�p����"�C��������"��XACT�E�F�C�u�o���N�t�@�C�����쐬
	result = E_FAIL; //���s���f�t�H���g�Ƃ��Đ������ɒu��������
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
				CloseHandle(hMapFile);	// mapWaveBank���t�@�C���ւ̃n���h����ێ�����̂ł��̕s�v�ȃn���h�������
			}
		}
		CloseHandle(hFile);		// mapWaveBank�͂��t�@�C���ւ̃n���h����ێ�����̂ł��̕s�v�ȃn���h�������
	}
	if (FAILED(result))
	{
		return HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND);
	}

	//SE����WaveBank�쐬
	//�������}�b�v�h�t�@�C��IO���g�p����"�C��������"��XACT�E�F�C�u�o���N�t�@�C�����쐬
	result = E_FAIL; //���s���f�t�H���g�Ƃ��Đ������ɒu��������
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
				CloseHandle(hMapFile);	// mapWaveBank���t�@�C���ւ̃n���h����ێ�����̂ł��̕s�v�ȃn���h�������
			}
		}
		CloseHandle(hFile);		// mapWaveBank�͂��t�@�C���ւ̃n���h����ێ�����̂ł��̕s�v�ȃn���h�������
	}

	if (FAILED(result))
	{
		return HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND);
	}

	// XACT�ō쐬�����T�E���h�o���N�t�@�C����ǂݍ���ŗ\��
	result = E_FAIL;	// ���s���f�t�H���g�Ƃ��āA�������ɒu��������
	hFile = CreateFile(SOUND_BANK, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		fileSize = GetFileSize(hFile, NULL);
		if (fileSize != -1)
		{
			soundBankData = new BYTE[fileSize];		// �T�E���h�o���N�̃��������m�ۂ���
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
// �����I�ȃT�E���h�G���W���^�X�N�����s
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
// �w�肳�ꂽ�T�E���h���E�F�C�u�o���N�炩��Đ�
// ���݂��Ȃ��ꍇ�́A�T�E���h���Đ�����Ȃ������ŁA�G���[�͔������Ȃ�
//=============================================================================
void Sound::SetPlayBGM(int n,bool b) {
	if (BGMwaveBank == NULL) {
		return;
	}
	//�Đ��t���O��folse�̏ꍇ�ɍĐ�
	if (!BGMplayflag[n]) {
		BGMwaveBank->Play(n, XACT_FLAG_UNITS_MS, 0, 0, &BGMwave[n]);
	}
	//�Đ��t���O��treu�ɂ����d�Đ����Ȃ��悤��
	BGMplayflag[n] = b;
}

void Sound::SetPlaySE(int n,bool b) {
	if (SEwaveBank == NULL) {
		return;
	}
	//�Đ��t���O��folse�̏ꍇ�ɍĐ�
	if (!SEplayflag[n]) {
		SEwaveBank->Play(n, XACT_FLAG_UNITS_MS, 0, 0, &SEwave[n]);
	}
	//�Đ��t���O��treu�ɂ����d�Đ����Ȃ��悤��
	SEplayflag[n] = b;
}
//=============================================================================
// �w�肳�ꂽ�T�E���h���E�F�C�u�o���N�Œ�~
// �T�E���h�����݂��Ȃ��ꍇ�A�G���[�͔������Ȃ�
//=============================================================================
void Sound::SetStopSound() {
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
// �ꎞ��~�iTRUE�Œ�~�AFALSE�ōĐ��j
//=============================================================================
void Sound::CangePauseSound(bool b) {

	for (int i = 0; i < MAXBGM; i++) {
		BGMwave[i]->Pause(b);
	}
	for (int i = 0; i < MAXSE; i++) {
		SEwave[i]->Pause(b);
	}


}
//=============================================================================
// ���ʂ̒���
//=============================================================================
void Sound::CangeBGMVolume(int n,float f) {

	BGMwave[n]->SetVolume(f);

}
void Sound::CangeSEVolume(int n, float f) {

	SEwave[n]->SetVolume(f);

}