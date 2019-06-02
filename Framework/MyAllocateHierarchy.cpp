//=====================================
//
//���b�V���q�G�����L�[����[MyAllocateHierarchy.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "MyAllocateHierarchy.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�t���[���I�u�W�F�N�g�쐬����
***************************************/
HRESULT MyAllocateHierarchy::CreateFrame(THIS_
	LPCSTR name,
	LPD3DXFRAME *ppNewFrame)
{
	//�t���[����V������������
	HRESULT hr = S_OK;
	D3DXFRAME_DERIVED *frame;

	*ppNewFrame = NULL;

	frame = new D3DXFRAME_DERIVED;

	if (frame == NULL)
	{
		delete frame;
		return E_OUTOFMEMORY;
	}

	hr = AllocateName(name, &frame->Name);
	if (SUCCEEDED(hr))
	{
		//������
		D3DXMatrixIdentity(&frame->TransformationMatrix);
		D3DXMatrixIdentity(&frame->combiendTransformMatrix);
		frame->pMeshContainer = NULL;
		frame->pFrameSibling = NULL;
		frame->pFrameFirstChild = NULL;

		*ppNewFrame = frame;
		frame = NULL;
	}

	delete frame;
	return hr;
}

/**************************************
���b�V���R���e�i�쐬����
***************************************/
HRESULT MyAllocateHierarchy::CreateMeshContainer(THIS_
	LPCSTR name,
	CONST D3DXMESHDATA *pMeshData,
	CONST D3DXMATERIAL *pMaterials,
	CONST D3DXEFFECTINSTANCE *pEffectInstance,
	DWORD numMaterials,
	CONST DWORD *pAdjacency,
	LPD3DXSKININFO pSkinInfo,
	LPD3DXMESHCONTAINER *ppNewMeshContainer)
{
	HRESULT hr;
	D3DXMESHCONTAINER_DERIVED* meshContainer = NULL;
	UINT numFaces;
	UINT iMaterial;
	UINT iBone, cBones;
	LPDIRECT3DDEVICE9 pDevice = NULL;

	LPD3DXMESH mesh = NULL;

	*ppNewMeshContainer = NULL;

	if (pMeshData->Type != D3DXMESHTYPE_MESH)
	{
		hr = E_FAIL;
		return hr;
	}

	//���b�V���f�[�^���Q��
	mesh = pMeshData->pMesh;

	if (mesh->GetFVF() == 0)
	{
		hr = E_FAIL;
		return hr;
	}

	//���b�V���R���e�i�̃��������m��
	meshContainer = new D3DXMESHCONTAINER_DERIVED;
	if (meshContainer == NULL)
	{
		hr = E_OUTOFMEMORY;
		return hr;
	}
	memset(meshContainer, 0, sizeof(D3DXMESHCONTAINER_DERIVED));

	//���b�V���R���e�i�ɏ����i�[
	hr = AllocateName(name, &meshContainer->Name);
	if (FAILED(hr))
	{
		DestroyMeshContainer(meshContainer);
		return hr;
	}
	mesh->GetDevice(&pDevice);
	numFaces = mesh->GetNumFaces();

	//�@�����Ȃ��ꍇ�͌v�Z���Ēǉ�
	if (!(mesh->GetFVF() & D3DFVF_NORMAL))
	{
		meshContainer->MeshData.Type = D3DXMESHTYPE_MESH;

		hr = mesh->CloneMeshFVF(mesh->GetOptions(),
			mesh->GetFVF() | D3DFVF_NORMAL,
			pDevice, &meshContainer->MeshData.pMesh);

		if (FAILED(hr))
		{
			DestroyMeshContainer(meshContainer);
			SAFE_RELEASE(pDevice);
			return hr;
		}

		mesh = meshContainer->MeshData.pMesh;
		D3DXComputeNormals(mesh, NULL);
	}
	//���̂܂܂��ǉ�
	else
	{
		meshContainer->MeshData.pMesh = mesh;
		meshContainer->MeshData.Type = D3DXMESHTYPE_MESH;
		mesh->AddRef();
	}

	//�}�e���A���A�e�N�X�`���A�אڏ��̃������m��
	meshContainer->NumMaterials = max(1, numMaterials);
	meshContainer->pMaterials = new D3DXMATERIAL[meshContainer->NumMaterials];
	meshContainer->textures = new LPDIRECT3DTEXTURE9[meshContainer->NumMaterials];
	meshContainer->pAdjacency = new DWORD[numFaces * 3];
	if ((meshContainer->pAdjacency == NULL) || (meshContainer->pMaterials == NULL))
	{
		hr = E_OUTOFMEMORY;
		DestroyMeshContainer(meshContainer);
		SAFE_RELEASE(pDevice);
		return hr;
	}

	//�אڏ����i�[�A�e�N�X�`������������
	memcpy(meshContainer->pAdjacency, pAdjacency, sizeof(DWORD) * numFaces * 3);
	memset(meshContainer->textures, 0, sizeof(LPDIRECT3DTEXTURE9) * meshContainer->NumMaterials);

	//�}�e���A�����ƃe�N�X�`�������i�[
	if (numMaterials > 0)
	{
		memcpy(meshContainer->pMaterials, pMaterials, sizeof(D3DXMATERIAL) * numMaterials);

		for (iMaterial = 0; iMaterial < numMaterials; iMaterial++)
		{
			if (meshContainer->pMaterials[iMaterial].pTextureFilename != NULL)
			{
				char textureName[256];
				ZeroMemory(textureName, sizeof(textureName));
				sprintf_s(textureName, "data/MODEL/%s", meshContainer->pMaterials[iMaterial].pTextureFilename);

				if (FAILED(D3DXCreateTextureFromFile(pDevice, textureName, &meshContainer->textures[iMaterial])))
				{
					meshContainer->textures[iMaterial] = NULL;
				}

				meshContainer->pMaterials[iMaterial].pTextureFilename = NULL;
			}
		}
	}
	else
	{
		meshContainer->pMaterials[0].pTextureFilename = NULL;
		memset(&meshContainer->pMaterials[0].MatD3D, 0, sizeof(D3DMATERIAL9));
		meshContainer->pMaterials[0].MatD3D.Diffuse.r = 0.5f;
		meshContainer->pMaterials[0].MatD3D.Diffuse.g = 0.5f;
		meshContainer->pMaterials[0].MatD3D.Diffuse.b = 0.5f;
		meshContainer->pMaterials[0].MatD3D.Specular = meshContainer->pMaterials[0].MatD3D.Diffuse;
	}

	//�X�L�������i�[
	if (pSkinInfo != NULL)
	{
		meshContainer->pSkinInfo = pSkinInfo;
		pSkinInfo->AddRef();

		meshContainer->originMesh = mesh;
		mesh->AddRef();

		cBones = pSkinInfo->GetNumBones();
		meshContainer->boneOffsetMatrices = new D3DXMATRIX[cBones];
		if (meshContainer->boneOffsetMatrices == NULL)
		{
			hr = E_OUTOFMEMORY;
			DestroyMeshContainer(meshContainer);
			SAFE_RELEASE(pDevice);
			return hr;
		}

		for (iBone = 0; iBone < cBones; iBone++)
		{
			meshContainer->boneOffsetMatrices[iBone] = *(meshContainer->pSkinInfo->GetBoneOffsetMatrix(iBone));
		}

		//�X�L�����b�V������
		hr = GenerateSkinnedMesh(pDevice, meshContainer);
		if (FAILED(hr))
		{
			DestroyMeshContainer(meshContainer);
			SAFE_RELEASE(pDevice);
			return hr;
		}
	}

	*ppNewMeshContainer = meshContainer;
	meshContainer = NULL;

	SAFE_RELEASE(pDevice);
	DestroyMeshContainer(meshContainer);
	return hr;
}

/**************************************
�t���[���I�u�W�F�N�g�������
***************************************/
HRESULT MyAllocateHierarchy::DestroyFrame(THIS_
	LPD3DXFRAME pFrameToFree)
{
	SAFE_DELETE_ARRAY(pFrameToFree->Name);

	return D3D_OK;
}

/**************************************
���b�V���R���e�i�������
***************************************/
HRESULT MyAllocateHierarchy::DestroyMeshContainer(THIS_
	LPD3DXMESHCONTAINER pMeshContainerToFree)
{
	if (pMeshContainerToFree == NULL)
		return D3D_OK;

	UINT iMaterial;
	D3DXMESHCONTAINER_DERIVED *meshContainer = (D3DXMESHCONTAINER_DERIVED*)pMeshContainerToFree;

	SAFE_DELETE_ARRAY(meshContainer->Name);
	SAFE_DELETE_ARRAY(meshContainer->pAdjacency);
	SAFE_DELETE_ARRAY(meshContainer->pMaterials);

	if (meshContainer->textures != NULL)
	{
		for (iMaterial = 0; iMaterial < meshContainer->NumMaterials; iMaterial++)
		{
			SAFE_RELEASE(meshContainer->textures[iMaterial]);
		}
	}

	SAFE_DELETE_ARRAY(meshContainer->textures);
	SAFE_RELEASE(meshContainer->pSkinInfo);
	SAFE_RELEASE(meshContainer->boneCombinationBuf);
	SAFE_DELETE_ARRAY(meshContainer->boneMatrices);
	SAFE_DELETE_ARRAY(meshContainer->boneOffsetMatrices);
	SAFE_RELEASE(meshContainer->MeshData.pMesh);
	SAFE_RELEASE(meshContainer->originMesh);
	SAFE_DELETE(meshContainer);

	return D3D_OK;
}

/**************************************
������R�s�[����
***************************************/
LPSTR MyAllocateHierarchy::CopyStr(LPCSTR name)
{
	if (!name) return NULL;

	LPSTR str = new char[strlen(name) + 1];
	strcpy_s(str, strlen(name) + 1, name);
	return str;
}

/**************************************
�l�[���p�������m�ۏ���
***************************************/
HRESULT MyAllocateHierarchy::AllocateName(LPCSTR name, LPSTR* newName)
{
	UINT cbLength;

	if (name != NULL)
	{
		cbLength = (UINT)strlen(name) + 1;
		*newName = new char[cbLength];
		if (*newName == NULL)
		{
			return E_OUTOFMEMORY;
		}
		memcpy(*newName, name, cbLength * sizeof(char));
	}
	else
	{
		*newName = NULL;
	}

	return S_OK;
}

/**************************************
�X�L�����b�V����������
***************************************/
HRESULT MyAllocateHierarchy::GenerateSkinnedMesh(LPDIRECT3DDEVICE9 pDevice, D3DXMESHCONTAINER_DERIVED *meshContainer)
{
	D3DCAPS9 caps;
	pDevice->GetDeviceCaps(&caps);

	if (meshContainer->pSkinInfo == NULL)
	{
		return S_OK;
	}

	SAFE_RELEASE(meshContainer->MeshData.pMesh);
	SAFE_RELEASE(meshContainer->boneCombinationBuf);

	if (FAILED(meshContainer->pSkinInfo->ConvertToBlendedMesh(
		meshContainer->originMesh,
		D3DXMESH_MANAGED | D3DXMESHOPT_VERTEXCACHE,
		meshContainer->pAdjacency,
		NULL,
		NULL,
		NULL,
		&meshContainer->boneWeightNum,
		&meshContainer->boneNum,
		&meshContainer->boneCombinationBuf,
		&meshContainer->MeshData.pMesh)))
	{
		return E_FAIL;
	}

	return S_OK;
}