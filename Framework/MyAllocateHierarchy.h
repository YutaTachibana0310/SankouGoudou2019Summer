//=====================================
//
//���b�V���q�G�����L�[�w�b�_[MyAllocateHierarchy.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _MYALLOCATEHIERARCHY_H_
#define _MYALLOCATEHIERARCHY_H_

#include "../main.h"

/**************************************
�}�N����`
***************************************/

/**************************************
D3DXFRAME�h���\����
***************************************/
struct D3DXFRAME_DERIVED : public D3DXFRAME
{
	D3DXMATRIXA16 combiendTransformMatrix;

	void* operator new(size_t i)
	{
		return _aligned_malloc(i, 16);
	}
};

/**************************************
D3DXMESHCONTAINER�h���\����
***************************************/
struct D3DXMESHCONTAINER_DERIVED : public D3DXMESHCONTAINER
{
	LPDIRECT3DTEXTURE9 *textures;

	//�X�L�����b�V�����
	LPD3DXMESH originMesh;				//�I���W�i�����b�V��
	DWORD boneNum;						//�{�[����
	DWORD boneWeightNum;				//1�̒��_�ɉe�����y�ڂ��d�݂̐�
	LPD3DXBUFFER boneCombinationBuf;	//�{�[�����̃o�b�t�@
	D3DXMATRIX** boneMatrices;			//�S�{�[���̍s��̃|�C���^�z��
	D3DXMATRIX* boneOffsetMatrices;		//�{�[���̃I�t�Z�b�g�s��
	DWORD numPaletteEntries;			//�p���b�g�T�C�Y
};

/**************************************
ID3DXAllocateHierarchy�h���N���X
***************************************/
class MyAllocateHierarchy : public ID3DXAllocateHierarchy
{
public:
	MyAllocateHierarchy(void) {}
	virtual ~MyAllocateHierarchy(void) {}

	/***********************************
	�t���[���I�u�W�F�N�g�쐬����
	************************************/
	STDMETHOD(CreateFrame)(THIS_
		LPCSTR name,
		LPD3DXFRAME *ppNewFrame);

	/***********************************
	���b�V���R���e�i�쐬����
	************************************/
	STDMETHOD(CreateMeshContainer)(THIS_
		LPCSTR name,
		CONST D3DXMESHDATA *pMeshData,
		CONST D3DXMATERIAL *pMaterials,
		CONST D3DXEFFECTINSTANCE *pEffectInstance,
		DWORD numMaterials,
		CONST DWORD *pAdjacency,
		LPD3DXSKININFO pSkinInfo,
		LPD3DXMESHCONTAINER *ppNewMeshContainer);

	/***********************************
	�t���[���I�u�W�F�N�g�������
	************************************/
	STDMETHOD(DestroyFrame)(THIS_
		LPD3DXFRAME pFrameToFree);

	/***********************************
	���b�V���R���e�i�������
	************************************/
	STDMETHOD(DestroyMeshContainer)(THIS_
		LPD3DXMESHCONTAINER pMeshContainerToFree);

protected:
	//������R�s�[
	LPSTR CopyStr(LPCSTR name);

	HRESULT AllocateName(LPCSTR name, LPSTR* newName);
	HRESULT GenerateSkinnedMesh(LPDIRECT3DDEVICE9 pDevice, D3DXMESHCONTAINER_DERIVED *meshContainer);
};

#endif