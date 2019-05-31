//=====================================
//
//�f�o�b�O�E�B���h�E�w�b�_[debugWindow.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _DEBUGWINDOW_H_
#define _DEBUGWINDOW_H_

#include "main.h"

#include <string>

/**************************************
�}�N����`
***************************************/
#define USE_DEBUGWINDOW
#define STR(var) #var		//var�𕶎���ɒu������}�N��
/**************************************
�\���̒�`
***************************************/

/**************************************
�v���g�^�C�v�錾
***************************************/
void DebugLog(const char *str, ...);	//�ėp�f�o�b�O���O�o�͊֐�

/**************************************/
//ImGUI���b�p�[�֐�
/***************************************/
void BeginDebugWindow(const char *label);	//�f�o�b�O�o�͂̍ŏ��ɌĂԊ֐�
void EndDebugWindow(const char* label);		//�f�o�b�O�o�͂̍Ō�ɌĂԊ֐�

//�e�L�X�g�o�͋@�\
void DebugText(const char *str, ...);
void DebugText(std::string str);

//�{�^���@�\
bool DebugButton(const char *label);
bool DebugButton(const std::string *label);
bool DebugRadioButton(const char* label, int* output, int val);
bool DebugChechBox(const char* label, bool* val);

//�X���C�_�[��float�l����͂ł���@�\
bool DebugSliderFloat(const char *label, float *adr, float min, float max);
bool DebugSliderFloat(const std::string *label, float *adr, float min, float max);

//�J���[�G�f�B�b�g�@�\
void DebugColorEditor(const char *label, float array[4]);

//�x�N�g�����͏���
void DebugSliderVector3(const char* label, D3DXVECTOR3 *vec, float min, float max);
void DebugInputVector3(const char* label, D3DXVECTOR3 *vec);
void DebugInputVector2(const char* label, D3DXVECTOR2 *vec);

//�f�[�^���͋@�\
void DebugInputFloat(const char* label, float *var);
bool DebugInputInt(const char* label, int* val);
bool DebugInputText(const char* label, char *buf, size_t buf_size);
bool DebugInputText(const char* label, std::string* pStr);

//�e�N�X�`���`��@�\
void DebugDrawTexture(LPDIRECT3DTEXTURE9 texture, float sizeX, float sizeY);

//�v���O���X�o�[�\���@�\
void DebugProgressBar(float fraction, const char* label, D3DXVECTOR2 size = D3DXVECTOR2(-1.0f, 0.0f));

//�\���`�������@�\
void DebugNewLine(void);
void DebugSameLine(void);

//�c���[�\���@�\
void DebugTreeExpansion(bool isOpen);
bool DebugTreePush(const char *label);
void DebugTreePop(void);

//�v���V�[�W��
LRESULT DebugWindPrcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

//�e�폈��
void InitDebugWindow(HWND hWnd, LPDIRECT3DDEVICE9 pDevice);
void UninitDebugWindow(int num);
void UpdateDebugWindow(void);
void DrawDebugWindow(void);

void SetActiveDebugWindow(bool state = true);	//�\���ؑ֏���

//�������Ԍv���@�\
void BeginTimerCount(void);				//���𑜓x�^�C�}�[�v���J�n
double GetProgressTimerCount(void);		//�^�C�}�[�o�ߎ��Ԏ擾����
void GetTimerCount(LARGE_INTEGER *ptr);	//�^�C�}�[�J�E���g�擾(20�t���[���Ԋu)
double CalcProgressTime(LARGE_INTEGER start, LARGE_INTEGER end);	//�o�ߎ��Ԏ擾	

#endif