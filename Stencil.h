//=====================================
//
//�X�e���V������[Stencil.h]
//Author:GP12B332 45�@�n糗Ǒ�
//
//=====================================
#ifndef _STENCIL_H_
#define _STENCIL_H_

#include <d3d9.h>
/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
namespace Clip {
	class Stencil
	{
	public:

		//�}�X�N�F
		enum MaskColor {
			MaskColor_Trans = 0x00, //�����F
			MaskColor_Fill = 0x01, //�h��Ԃ�
			MaskColor_None = 0xff //�����J���[
		};

		//���[�h
		enum StencilMode {
			Mode_Masking, //�}�X�N�������݃��[�h��
			Mode_Draw //�`�惂�[�h��
		};

		Stencil(void);
		virtual ~Stencil();


		//�N���b�s���O�̈�쐬�J�n
		virtual bool regionBegin(MaskColor clearColor = MaskColor_Trans);

		//�N���b�s���O�̈�쐬�I��
		virtual bool regionEnd();

		//�N���b�s���O�`��J�n
		virtual bool drawBegin();

		//�N���b�s���O�`��I��
		virtual bool drawEnd(MaskColor clearColor = MaskColor_Trans);

		//�������ݎ��̃}�X�N�J���[�̐ݒ�
		void setWriteMaskColor(MaskColor color);

		//�`�掞�̃}�X�N�J���[�̎w��
		void setRefMaskColor(MaskColor color);

	protected:
		StencilMode			mode_;			//���[�h
		MaskColor			writeColor_;	//�}�X�N�������ݎ��̐F
		MaskColor			refColor_;		//�`�掞�̃}�X�L���O�F
		IDirect3DDevice9*	device_;		//�`�掞�̃}�X�L���O�F
		DWORD				curZTest_;		//������Z�e�X�g�̗L��
		DWORD				curZFunc_;		//������Z�e�X�g��r�֐�

	};
}

#endif