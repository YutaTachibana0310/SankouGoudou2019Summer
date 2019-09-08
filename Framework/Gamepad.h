//=====================================
//
//�Q�[���p�b�h�w�b�_[Gamepad.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _GAMEPAD_H_
#define _GAMEPAD_H_

#include "../main.h"

/**************************************
�}�N����`
***************************************/
#define BUTTON_UP		0x00000001l	// �����L�[��(.IY<0)
#define BUTTON_DOWN		0x00000002l	// �����L�[��(.IY>0)
#define BUTTON_LEFT		0x00000004l	// �����L�[��(.IX<0)
#define BUTTON_RIGHT	0x00000008l	// �����L�[�E(.IX>0)
#define BUTTON_A		0x00000010l	// �`�{�^��(.rgbButtons[0]&0x80)
#define BUTTON_B		0x00000020l	// �a�{�^��(.rgbButtons[1]&0x80)
#define BUTTON_C		0x00000040l	// �b�{�^��(.rgbButtons[2]&0x80)
#define BUTTON_X		0x00000080l	// �w�{�^��(.rgbButtons[3]&0x80)
#define BUTTON_Y		0x00000100l	// �x�{�^��(.rgbButtons[4]&0x80)
#define BUTTON_Z		0x00000200l	// �y�{�^��(.rgbButtons[5]&0x80)
#define BUTTON_L		0x00000400l	// �k�{�^��(.rgbButtons[6]&0x80)
#define BUTTON_R		0x00000800l	// �q�{�^��(.rgbButtons[7]&0x80)
#define BUTTON_START	0x00001000l	// �r�s�`�q�s�{�^��(.rgbButtons[8]&0x80)
#define BUTTON_M		0x00002000l	// �l�{�^��(.rgbButtons[9]&0x80)
#define GAMEPADMAX		4			// �����ɐڑ�����W���C�p�b�h�̍ő吔���Z�b�g
#define PADBUTTON_MAX	14			// ���͂Ɏg����{�^���̍ő吔

/**************************************
�N���X��`
***************************************/

/**************************************
�v���g�^�C�v�錾
***************************************/
HRESULT InitializePad(LPDIRECTINPUT8 inputInterface);			// �p�b�h������
BOOL CALLBACK SearchPadCallback(LPDIDEVICEINSTANCE lpddi, LPVOID);	// �p�b�h�����R�[���o�b�N
void UpdatePad(void);
void UninitPad(void);

BOOL IsButtonPressed(int padNo, DWORD button);
BOOL IsButtonTriggered(int padNo, DWORD button);
BOOL IsButtonReleased(int padNo, DWORD button);

float GetStickAxisX(int padNo);
float GetStickAxisY(int padNo);

int GetPadAxisXTriggered(int padNo);
int GetPadAxisYTriggered(int padNo);

float GetAxisX(int padNo);
float GetAxisY(int padNo);

#endif