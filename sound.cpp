
//=============================================================================
//
// �T�E���h���� [sound.cpp]
// Author : �n糗Ǒ�
//
//=============================================================================

#include "sound.h"
#include "soundUI.h"

Sound *Sound::sound = NULL;

//�f�t�H���g�R���X�g���N�^
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

//�f�X�g���N�^
Sound::~Sound()
{

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

//������
//1.xactEngine->Initialize�ɂ���ČĂяo���ꂽXACT��������
//2.�g�p����XACT�E�F�C�u�o���N���쐬
//3.�g�p����XACT�T�E���h�o���N���쐬
//4.�Q�[�����g�p����XACT�L���[�ɃC���f�b�N�X���i�[

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
void Sound::SetPlayBGM(int wavenum,bool playflag,float vol) {
	if (BGMwaveBank == NULL) {
		return;
	}
	//�Đ��t���O��false�̏ꍇ�ɍĐ�
	if (!BGMplayflag[wavenum] && !pauseflag) {
		BGMwaveBank->Play(wavenum, XACT_FLAG_UNITS_MS, 0, 99, &BGMwave[wavenum]);
		Sound::ChangeBGMVolume(wavenum, vol);
	}
	//�Đ��t���O��treu�ɂ����d�Đ����Ȃ��悤��
	BGMplayflag[wavenum] = playflag;

}

void Sound::SetPlaySE(int wavenum, bool playflag, float vol) {

	if (SEwaveBank == NULL) {
		return;
	}
	//��SE�̏ꍇ�̓|�[�Y���ɍĐ��ł��邩�̃t���O�Ǘ�
	//SE�Đ��͊�{�I��true
	//false�̏ꍇ�̓|�[�Y���ɍĐ��ł���SE
	SEplayflag[wavenum] = playflag;

	//�Đ��t���O��true���|�[�Y�t���O��false�̏ꍇ�ɍĐ�
	if (SEplayflag[wavenum] && !pauseflag) {
		SEwaveBank->Play(wavenum, XACT_FLAG_UNITS_MS, 0, 0, &SEwave[wavenum]);
		Sound::ChangeSEVolume(wavenum, vol);

	}
	else if (!SEplayflag[wavenum] && pauseflag)
	{
		//playflag��true�ɂ����ꍇ�̓|�[�Y���ɍĐ��ł���悤��
		SEwaveBank->Play(wavenum, XACT_FLAG_UNITS_MS, 0, 0, &SEwave[wavenum]);
		Sound::ChangeSEVolume(wavenum, vol);
	}



}
//=============================================================================
// �w�肳�ꂽ�T�E���h���E�F�C�u�o���N�Œ�~
// �T�E���h�����݂��Ȃ��ꍇ�A�G���[�͔������Ȃ�
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
// �w�肳�ꂽ�T�E���h���E�F�C�u�o���N�Œ�~�i�ʁj
// �T�E���h�����݂��Ȃ��ꍇ�A�G���[�͔������Ȃ�
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
// �ꎞ��~�iTRUE�Œ�~�AFALSE�ōĐ��j
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
// ���ʂ̒���
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
// �t�F�[�h�̒���
//=============================================================================
void Sound::FadeIn(int wavenum, float fadesec,float setvol,bool inflag) {
	//60�t���[��
	//4�b�Ɖ��� = 60�t���[�� * 4 = 240
	//�ő�vol = 1
	//vol1 / 4�b = 1�b�Ԃ�0.25
	//0.25 / 60 = 1�t���[���ɏオ�鉹��(4�b�̏ꍇ0.00416�c)
	//0.004 * 240 = 0.96(�ő�vol1�j

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
	//�s�b�`�̒l��-1200�`1200�̊�
	if (SEwave[wavenum] != NULL) {
		SEwave[wavenum]->SetPitch(pitch);
	}
}

