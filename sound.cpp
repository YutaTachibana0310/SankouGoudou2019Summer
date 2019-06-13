
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

	//�������}�b�v�h�t�@�C��IO���g�p����"�C��������"��XACT�E�F�C�u�o���N�t�@�C�����쐬
	result = E_FAIL; //���s���f�t�H���g�Ƃ��Đ������ɒu��������
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
// �L���[�Ŏw�肳�ꂽ�T�E���h���T�E���h�o���N�炩��Đ�
// �L���[�����݂��Ȃ��ꍇ�́A�T�E���h���Đ�����Ȃ������ŁA�G���[�͔������Ȃ�
//=============================================================================
void Sound::SetPlaySound(int n) {
	if (waveBank == NULL) {
		return;
	}

	switch (n)
	{
	case 0:
		//Play(wave�ɓo�^�������Ԃ̋ȁA�t���O�H�A�I�t�Z�b�g�H�A���[�v�񐔁Awave�|�C���^�j
		waveBank->Play(n, XACT_FLAG_UNITS_MS, 0, 0, &wave[0]);
		break;
	case 1:
		waveBank->Play(n, XACT_FLAG_UNITS_MS, 0, 99, &wave[1]);
		break;
	}
}
//=============================================================================
// �w�肳�ꂽ�T�E���h���E�F�C�u�o���N�Œ�~
// �T�E���h�����݂��Ȃ��ꍇ�A�G���[�͔������Ȃ�
//=============================================================================
void Sound::SetStopSound(int n) {
	if (waveBank == NULL)
	{
		return;
	}
	
	waveBank->Stop(n, XACT_FLAG_STOP_IMMEDIATE);

}
//=============================================================================
// �ꎞ��~�iTRUE�Œ�~�AFALSE�ōĐ��j
//=============================================================================
void Sound::CangePauseSound(int n,bool b) {

	wave[n]->Pause(b);


}
//=============================================================================
// ���ʂ̒���
//=============================================================================
void Sound::CangeSoundVolume(int n,float f) {

	wave[n]->SetVolume(f);

}