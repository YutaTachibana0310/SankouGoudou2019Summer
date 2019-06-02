//=====================================
//
//���b�V���R���e�i�w�b�_[MeshContainer.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _MESHCONTAINER_H_
#define _MESHCONTAINER_H_

#include "../main.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
class MeshContainer
{
public:
	MeshContainer();					//�R���X�g���N�^
	~MeshContainer();					//�f�X�g���N�^

	HRESULT Load(const char* filePath);	//X�t�@�C���̓ǂݍ���
	void Release();						//���f���f�[�^�����
	void Draw();						//���f����`��

private:								
	LPD3DXMESH mesh;					//���b�V���f�[�^
	D3DMATERIAL9* materials;			//�}�e���A�����
	LPDIRECT3DTEXTURE9 *textures;		//�e�N�X�`��
	DWORD materialNum;					//�}�e���A����
};

#endif