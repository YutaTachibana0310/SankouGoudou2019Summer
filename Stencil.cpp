//=============================================================================
//
// �X�e���V������ [Stencil.cpp]
// Author : �n糗Ǒ�
//
//=============================================================================

#include "Stencil.h"
#include "main.h"

namespace Clip {
	Stencil::Stencil(void):
		device_		(0),
		mode_		(Mode_Masking),
		writeColor_	(MaskColor_Fill),
		refColor_	(MaskColor_Fill),
		curZTest_	(0),
		curZFunc_	(0)
	{

	}

	Stencil::~Stencil() {

	}



	//�N���b�s���O�̈�쐬�J�n
	bool Stencil::regionBegin(MaskColor initColor) {

		LPDIRECT3DDEVICE9 pDevice = GetDevice();
		device_ = pDevice;

		if (device_ == 0) {
			return false;
		}

		//�X�e���V���o�b�t�@�̂ݏ����l�N���A
		pDevice->Clear(0, NULL, D3DCLEAR_STENCIL, 0, 1.0f, static_cast<DWORD>(initColor));

		//������Z�e�X�g�p�����[�^�̕ۑ�
		pDevice->GetRenderState(D3DRS_ZENABLE, &curZTest_);
		pDevice->GetRenderState(D3DRS_ZFUNC, &curZFunc_);

		//�X�e���V���o�b�t�@�̗L����
		pDevice->SetRenderState(D3DRS_ZENABLE, true);
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_NEVER);

		pDevice->SetRenderState(D3DRS_STENCILENABLE, true);
		pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
		pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);
		pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_REPLACE);
		pDevice->SetRenderState(D3DRS_STENCILREF, writeColor_);
		pDevice->SetRenderState(D3DRS_STENCILMASK,0xff);

		mode_ = Mode_Masking;

		return true;
	}

	//�N���b�s���O�̈�쐬�I��
	bool Stencil::regionEnd() {
		if (device_ == 0) {
			return false;
		}

		//�X�e���V���𖳌���
		//Z�e�X�g��߂�
		device_->SetRenderState(D3DRS_STENCILENABLE, false);
		device_->SetRenderState(D3DRS_ZENABLE,curZTest_);
		device_->SetRenderState(D3DRS_ZFUNC,curZFunc_);

		return true;
	}

	//�N���b�s���O�`��J�n
	bool Stencil::drawBegin() {
		if (device_ == 0) {
			return false;
		}

		//���ɏ������܂�Ă���X�e���V���l�ɑ΂�
		//�}�X�N�F�łȂ����������e�X�g���i����
		device_->SetRenderState(D3DRS_STENCILENABLE,true);
		device_->SetRenderState(D3DRS_STENCILFUNC,D3DCMP_NOTEQUAL);
		device_->SetRenderState(D3DRS_STENCILPASS,D3DSTENCILOP_KEEP);
		device_->SetRenderState(D3DRS_STENCILZFAIL,D3DSTENCILOP_KEEP);
		device_->SetRenderState(D3DRS_STENCILREF,refColor_);
		device_->SetRenderState(D3DRS_STENCILMASK,0xff);

		mode_ = Mode_Draw;

		return true;

	}

	//�N���b�s���O�`��I��
	bool Stencil::drawEnd(MaskColor clearColor) {
		if (device_ == 0) {
			return false;
		}

		//�X�e���V���𖳌������o�b�t�@���N���A
		device_->SetRenderState(D3DRS_STENCILENABLE, false);
		device_->Clear(0, NULL, D3DCLEAR_STENCIL, 0, 1.0f, static_cast<DWORD>(clearColor));

		return true;
	}

	//�������ݎ��}�X�N�J���[�̐ݒ�
	void Stencil::setWriteMaskColor(MaskColor color) {
		writeColor_ = color;
		if (device_ && mode_ == Mode_Masking) {
			device_->SetRenderState(D3DRS_STENCILREF, writeColor_);
		}
	}


	//�`�掞�̃}�X�N�J���[�̎w��
	void Stencil::setRefMaskColor(MaskColor color) {
		refColor_ = color;
		if (device_ && mode_ == Mode_Draw) {
			device_->SetRenderState(D3DRS_STENCILREF, refColor_);
		}
	}

}

