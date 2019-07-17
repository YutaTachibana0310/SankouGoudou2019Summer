//=============================================================================
//
// ���C������ [main.h]
// Author : 
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

#define _CRT_SECURE_NO_WARNINGS

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include <windows.h>
#include "d3dx9.h"

#define DIRECTINPUT_VERSION (0x0800)	// �x���΍�
#include "dinput.h"
#include "MyLibrary.h"
#include <tchar.h>
#include <stdio.h>
#include <assert.h>

//*****************************************************************************
// ���C�u�����̃����N
//*****************************************************************************
#if 1	// [������"0"�ɂ����ꍇ�A"�\���v���p�e�B" -> "�����J" -> "����" -> "�ǉ��̈ˑ��t�@�C��"�ɑΏۃ��C�u������ݒ肷��]
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "dxerr.lib")
#endif

//*****************************************************************************
// �}�N����`
//*****************************************************************************
// �Q�c�|���S�����_�t�H�[�}�b�g( ���_���W[2D] / ���ˌ� / �e�N�X�`�����W )
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
// �R�c�|���S�����_�t�H�[�}�b�g( ���_���W[3D] / �@�� / ���ˌ� / �e�N�X�`�����W )
#define	FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

#define SCREEN_WIDTH	(1800)
#define SCREEN_HEIGHT	(1000)

//WQHD�p
//#define SCREEN_WIDTH	(1500)
//#define SCREEN_HEIGHT	(900)

#define SCREEN_CENTER_X	(SCREEN_WIDTH / 2)
#define SCREEN_CENTER_Y	(SCREEN_HEIGHT / 2)

#define	NUM_VERTEX		(4)		// ���_��
#define	NUM_POLYGON		(2)		// �|���S����

//����A�폜�֘A
#define SAFE_RELEASE(p) {if(p){p->Release(); p = NULL;}}
#define SAFE_DELETE(p)	{if(p){delete(p); p = NULL;}}
#define SAFE_DELETE_ARRAY(p)	{if(p){delete[](p); p = NULL;}}

#define TARGETPLAYER_MAX	(2)	//��x�ɎQ���ł���v���C���[�̍ő吔

// ��L�Q�c�|���S�����_�t�H�[�}�b�g�ɍ��킹���\���̂��`
typedef struct
{
	D3DXVECTOR3 vtx;		// ���_���W
	float rhw;				// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	D3DCOLOR diffuse;		// ���ˌ�
	D3DXVECTOR2 tex;		// �e�N�X�`�����W
} VERTEX_2D;

// ��L�R�c�|���S�����_�t�H�[�}�b�g�ɍ��킹���\���̂��`
typedef struct
{
	D3DXVECTOR3 vtx;		// ���_���W
	D3DXVECTOR3 nor;		// �@���x�N�g��
	D3DCOLOR diffuse;		// ���ˌ�
	D3DXVECTOR2 tex;		// �e�N�X�`�����W
} VERTEX_3D;

//�p�[�e�B�N���̒P�ʒ��_
typedef struct
{
	D3DXVECTOR3 vtx;	//���_���W
	D3DXVECTOR2 tex;	//UV���W
} ParticleUnit;

//SRT���
typedef struct _Transform
{
	D3DXVECTOR3 pos;	//���W
	D3DXVECTOR3 rot;	//��]
	D3DXVECTOR3 scale;	//�X�P�[��

	//�R���X�g���N�^
	_Transform()
	{
		pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	}

	_Transform(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale)
	{
		this->pos = pos;
		this->rot = rot;
		this->scale = scale;
	}

	//��]����
	void Rotate(float degX, float degY, float degZ)
	{
		rot.x = D3DXToRadian(degX);
		rot.y = D3DXToRadian(degY);
		rot.z = D3DXToRadian(degZ);
	}

}Transform;

//�p�[�e�B�N����UV���
typedef struct
{
	float u, v;
}ParticleUV;

typedef struct
{
	D3DXVECTOR3 vtx[4];
	D3DXVECTOR3 nor;
}PLANE;


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
LPDIRECT3DDEVICE9 GetDevice(void);
LPDIRECT3DTEXTURE9 CreateTextureFromFile(LPSTR szName, LPDIRECT3DDEVICE9 lpD3DDevice);
void TranslateViewPort(D3DXVECTOR3 *out, D3DXVECTOR3 *pos);
void SetBackColor(D3DXCOLOR color);
int GetCurrentScene(void);
int GetCurrentFPS(void);
LPDIRECT3DTEXTURE9 GetCurrentDrawData();
#endif