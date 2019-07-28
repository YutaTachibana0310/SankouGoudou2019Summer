//=====================================
//
//���b�V���R���e�i����[MeshContainer.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "MeshContainer.h"
#include <stdio.h>
#include <vector>

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
MeshContainer::MeshContainer()
{

}

/**************************************
�f�X�g���N�^
***************************************/
MeshContainer::~MeshContainer()
{
	SAFE_RELEASE(mesh);

	for (DWORD i = 0; i < materialNum; i++)
	{
		SAFE_RELEASE(textures[i]);
	}
}

/**************************************
�t�@�C���ǂݍ��ݏ���
***************************************/
HRESULT MeshContainer::Load(const char* filePath)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	LPD3DXBUFFER tmpMaterial;

	//X�t�@�C���ǂݍ���
	HRESULT res = D3DXLoadMeshFromX(filePath,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&tmpMaterial,
		NULL,
		&materialNum,
		&mesh);

	if (res != S_OK)
	{
		return res;
	}

	//���b�V���̗אڏ����쐬���čœK��
	std::vector<DWORD> adjList;
	adjList.resize(3 * mesh->GetNumFaces());
	mesh->GenerateAdjacency(1.0f / 512, &adjList[0]);
	mesh->OptimizeInplace(D3DXMESHOPT_ATTRSORT, &adjList[0], 0, 0, 0);

	//�}�e���A����D3DXMATERIAL�Ƃ��ĕ���
	materials = (D3DMATERIAL9*)malloc(sizeof(D3DMATERIAL9) * materialNum);
	D3DXMATERIAL* matBuffer = (D3DXMATERIAL*)tmpMaterial->GetBufferPointer();
	for (DWORD i = 0; i < materialNum; i++)
	{
		materials[i] = matBuffer[i].MatD3D;
	}

	//�e�N�X�`���ǂݍ���
	textures = (LPDIRECT3DTEXTURE9*)malloc(sizeof(LPDIRECT3DTEXTURE9) * materialNum);
	ZeroMemory(textures, sizeof(LPDIRECT3DTEXTURE9) * materialNum);
	char directoryPath[_MAX_DIR];
	size_t length = strlen(filePath);

	for (DWORD i = length - 1; i >= 0; i--)
	{
		if (filePath[i] == '/')
		{
			strncpy(directoryPath, filePath, i + 1);
			directoryPath[i + 1] = '\0';
			break;
		}
	}

	for (DWORD i = 0; i < materialNum; i++)
	{
		if (matBuffer[i].pTextureFilename == NULL)
			continue;

		//�e�N�X�`������wchar�ɕϊ�
		char fileName[1024];
		ZeroMemory(fileName, sizeof(fileName));
		strcpy(fileName, matBuffer[i].pTextureFilename);

		//�e�N�X�`���t�@�C���p�X���쐬
		char textureFile[1024];
		ZeroMemory(textureFile, sizeof(textureFile));
		strcat(textureFile, directoryPath);
		strcat(textureFile, fileName);

		//���[�h
		D3DXCreateTextureFromFile(pDevice, (LPSTR)textureFile, &textures[i]);
	}

	SAFE_RELEASE(tmpMaterial);

	return res;
}

/**************************************
�������
***************************************/
void MeshContainer::Release()
{
	for (unsigned i = 0; i < materialNum; i++)
	{
		SAFE_RELEASE(textures[i]);
	}

	SAFE_RELEASE(mesh);
}

/**************************************
�`�揈��
***************************************/
void MeshContainer::Draw()
{
	D3DMATERIAL9 matDef;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�}�e���A���ޔ�
	pDevice->GetMaterial(&matDef);

	for (DWORD i = 0; i < materialNum; i++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, textures[i]);

		//�}�e���A���ݒ�
		pDevice->SetMaterial(&materials[i]);

		//�`��
		mesh->DrawSubset(i);
	}

	//�}�e���A������
	pDevice->SetMaterial(&matDef);
}

/**************************************
�}�e���A���擾
***************************************/
void MeshContainer::GetMaterial(unsigned id, D3DMATERIAL9 *pOut)
{
	if (id >= materialNum || id < 0)
		return;

	*pOut = materials[id];
}

/**************************************
�e�N�X�`���擾
***************************************/
void MeshContainer::GetTexture(unsigned id, LPDIRECT3DTEXTURE9 *pOut)
{
	if (id >= materialNum || id < 0)
		return;

	*pOut = textures[id];
}

/**************************************
�}�e���A�����擾
***************************************/
DWORD MeshContainer::GetMaterialNum()
{
	return materialNum;
}

/**************************************
�}�e���A���J���[�ݒ菈��
***************************************/
void MeshContainer::SetMaterialColor(D3DXCOLOR& color)
{
	for (UINT i = 0; i < materialNum; i++)
	{
		materials[i].Diffuse = color;
	}
}

/**************************************
�}�e���A���A���t�@�ݒ菈��
***************************************/
void MeshContainer::SetMaterialAlpha(float alpha)
{
	for (UINT i = 0; i < materialNum; i++)
	{
		materials[i].Diffuse.a = alpha;
	}
}