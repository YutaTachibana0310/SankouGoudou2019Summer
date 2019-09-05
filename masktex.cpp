//=============================================================================
//
// �}�X�N���� [masktex.cpp]
// Author : �n糗Ǒ�
//
//=============================================================================
#include "main.h"
#include "masktex.h"
#include "UIdrawerC.h"
#include "Stencil.h"
#include "Game.h"
#include "Framework/EasingVector.h"

Clip::Stencil clip;
OBJECT	masktex;
OBJECT	maskBG;

//�g��k�����n�܂�t���O
bool sizechange;
//�t�F�[�h�C���A�A�E�g�̂ǂ��炩�𔻒肷��t���O
bool isFadeIn;
//�t�F�[�h���s��������
bool active;
//�V�[���؂�ւ��ׂ̈̃E�F�C�g�^�C��
int wait;

Scene nextscene;

//�e�N�X�`��������
HRESULT InitMask(float size_x, float size_y, float size_z)
{

	masktex.size = D3DXVECTOR3(size_x, size_y, size_z);
	masktex.position = POSITION_MASKTEX;
	masktex.rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	SetColorObject(&masktex, SET_COLOR_NOT_COLORED);

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	LoadTexture(pDevice, MASK_TEXTURE, &masktex);
	CreateObjectCircle(&masktex, masktex.size.x, masktex.size.y);
	InitialTexture(&masktex);
	MakeVertexRotateObject(&masktex);


	active = false;
	sizechange = false;
	isFadeIn = false;
	wait = 0;

	//�X�e���V���l��0�̎��ɕ\������摜
	LoadTexture(pDevice, MASK_TEXTUREBG, &maskBG);
	InitialTexture(&maskBG);
	MakeVertexObject(&maskBG);
	maskBG.size = SIZE_MASKBG;
	maskBG.position = POSITION_MASKBG;
	maskBG.rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	SetColorObject(&maskBG, SET_COLOR_NOT_COLORED);

	return S_OK;
}

//�e�N�X�`���I������
void UninitMask(void)
{
	ReleaseTexture(&masktex);
	ReleaseTexture(&maskBG);

}

void UpdateMask(void) {

	if (active) {
		//isFadeIn��true�̏ꍇ�Ƀt�F�[�h�C��
		if (isFadeIn) {
			MaskFadeIn();
		}
		else {
			MaskFadeOut();
		}
	}

}

//�}�X�N�p�e�N�X�`���X�V����
void MaskFadeOut(void) {


	if (sizechange) {

		masktex.countFrame++;
		float t = masktex.countFrame / float(60);

		masktex.size = EaseInCubicVector(t, MAXSIZE_MASKBG, DISAPPER_MASKBG);
		masktex.rotation = EaseInCubicVector(t, DISAPPER_MASKBG, ROTATION);

		CreateObjectCircle(&masktex, masktex.size.x, masktex.size.y);
	}

	//�T�C�Y�������Ȃ�ɂ��ʂ������Ȃ�
	if (masktex.size == DISAPPER_MASKBG) {

		masktex.size = DISAPPER_MASKBG;
		masktex.rotation = DISAPPER_MASKBG;

		SceneChangeFlag(true, nextscene);

		//�T�C�Y0�ȉ��ŃV�[���؂�ւ�
		wait++;

		if (wait > 60) {

			ChangeScene(nextscene);
			isFadeIn = true;
			wait = 0;
			masktex.countFrame = 0;

		}

	}

}

void MaskFadeIn(void) {

	if (sizechange) {

		masktex.countFrame++;
		float t = masktex.countFrame / float(60);

		masktex.size = EaseInCubicVector(t, DISAPPER_MASKBG, MAXSIZE_MASKBG);
		masktex.rotation = EaseInCubicVector(t, ROTATION, DISAPPER_MASKBG);

		CreateObjectCircle(&masktex, masktex.size.x, masktex.size.y);

	}

	//�T�C�Y���傫���Ȃ�ɂ�Q�[����ʕ\��
	if (masktex.size.x >= MASK_SIZE) {

		masktex.size = MAXSIZE_MASKBG;
		masktex.rotation = DISAPPER_MASKBG;

		SceneChangeFlag(false, nextscene);
		active = false;
		masktex.countFrame = 0;
	}




}

//�}�X�N�p�e�N�X�`���`��
void DrawMaskTexSet(void) {

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//�}�X�N����
	clip.setWriteMaskColor(Clip::Stencil::MaskColor_Trans);

	clip.regionBegin(Clip::Stencil::MaskColor_Fill);

	DrawObject(pDevice, masktex);
	SetVertexRotateObject(&masktex);

	clip.regionEnd();

	DrawTransition();

	//
	clip.setRefMaskColor(Clip::Stencil::MaskColor_Fill);

	clip.drawBegin();



}

void DrawMaskTexEnd(void) {

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	clip.drawEnd();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);


}

void SceneChangeFlag(bool fadeflag, Scene next) {

	if (fadeflag) {
		sizechange = true;
		nextscene = next;
		active = true;
		isFadeIn = false;
	}
	else {
		sizechange = false;
		active = false;
	}

}

void DrawTransition(void) {

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	DrawObject(pDevice, maskBG);
	SetVertexObject(&maskBG);
}
