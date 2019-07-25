//=============================================================================
//
// �J�������� [camera.h]
// Author : 
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 target;
	D3DXVECTOR3 up;
	D3DXVECTOR3 destPos;
	D3DXVECTOR3 destTarget;
	D3DXVECTOR3 rot;
	float dist;

	D3DXMATRIX view, projection, invView;
	D3DXVECTOR3 posOffset;
}Camera;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);

void SetCamera(void);

D3DXVECTOR3 GetRotCamera(void);
D3DXMATRIX GetMtxView(void);
D3DXMATRIX GetMtxProjection(void);
void GetInvCameraRotMtx(D3DXMATRIX *mtx, const D3DXVECTOR3* objPos = NULL);
D3DXVECTOR3 GetCameraPos(void);
Camera *GetCameraAdr(void);

D3DXMATRIX GetPlayerMtxView(int targetPlayerID);

D3DXMATRIX GetInvView();

#endif
