//=====================================
//
//�C���X�^���V���O���b�V���R���e�i����[InstancingMeshContainer.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "InstancingMeshContainer.h"

#include <vector>
#include "../light.h"

/**************************************
�}�N����`
***************************************/
#define EFFECTFILE_INSTANCINGMESH	"data/EFFECT/ModelInstancing.fx"

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
InstancingMeshContainer::InstancingMeshContainer()
{

}

/**************************************
�f�X�g���N�^
***************************************/
InstancingMeshContainer::~InstancingMeshContainer()
{
	SAFE_RELEASE(vtxBuff);
	SAFE_RELEASE(indexuff);
	SAFE_RELEASE(declare);
	SAFE_DELETE_ARRAY(attributeTable);

	for (UINT i = 0; i < numMaterial; i++)
	{
		SAFE_RELEASE(textures[i]);
	}

	SAFE_DELETE_ARRAY(textures);
	SAFE_DELETE_ARRAY(materials);

	SAFE_RELEASE(effect);
}

/**************************************
�ǂݍ��ݏ���
***************************************/
void InstancingMeshContainer::Load(const char* filePath)
{
	LPD3DXMESH mesh;
	LPD3DXBUFFER buffer;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���b�V����ǂݍ���
	D3DXLoadMeshFromX(filePath,
		D3DXMESH_MANAGED,
		pDevice,
		NULL,
		&buffer,
		NULL,
		&numMaterial,
		&mesh);

	//���b�V���̗אڏ����쐬
	std::vector<DWORD> adjList;
	adjList.resize(3 * mesh->GetNumFaces());
	mesh->GenerateAdjacency(1.0f / 512, &adjList[0]);

	//���b�V�����œK��
	mesh->OptimizeInplace(D3DXMESHOPT_ATTRSORT, &adjList[0], 0, 0, 0);

	//�e�o�b�t�@���擾
	mesh->GetVertexBuffer(&vtxBuff);
	mesh->GetIndexBuffer(&indexuff);
	fvf = mesh->GetFVF();

	//�����e�[�u�����擾
	attributeTable = new D3DXATTRIBUTERANGE[numMaterial];
	mesh->GetAttributeTable(&attributeTable[0], NULL);

	//���_�錾���擾
	D3DVERTEXELEMENT9 elem[65];
	ZeroMemory(elem, sizeof(D3DVERTEXELEMENT9) * 65);
	mesh->GetDeclaration(&elem[0]);

	//�C���X�^���V���O�p�̒��_�錾��ǉ�
	for (int i = 0; i < 65; i++)
	{
		if (elem[i].Type != D3DDECLTYPE_UNUSED)
			continue;

		elem[i] = D3DVERTEXELEMENT9{ 1, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 1 };
		elem[i + 1] = D3DVERTEXELEMENT9{ 1, sizeof(float) * 3, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 2 };
		elem[i + 2] = D3DVERTEXELEMENT9{ 1, sizeof(float) * 6, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 3 };
		elem[i + 3] = D3DDECL_END();
		break;
	}
	pDevice->CreateVertexDeclaration(elem, &declare);

	//�}�e���A����D3DMATERIAL9�Ƃ��ĕ���
	materials = new D3DMATERIAL9[numMaterial];
	D3DXMATERIAL *matBuffer = (D3DXMATERIAL*)buffer->GetBufferPointer();
	for (DWORD i = 0; i < numMaterial; i++)
	{
		materials[i] = matBuffer[i].MatD3D;
	}

	//�e�N�X�`���ǂݍ���
	textures = new LPDIRECT3DTEXTURE9[numMaterial];
	ZeroMemory(textures, sizeof(LPDIRECT3DTEXTURE9) * numMaterial);
	char directoryPath[_MAX_DIR];
	size_t length = strlen(filePath);

	for (DWORD i = length - 1; i >= 0; i--)
	{
		//X�t�@�C��������f�B���N�g���p�X���Z�o
		if (filePath[i] == '/')
		{
			strncpy(directoryPath, filePath, i + 1);
			directoryPath[i + 1] = '\0';
			break;
		}
	}

	for (DWORD i = 0; i < numMaterial; i++)
	{
		if (matBuffer[i].pTextureFilename == NULL)
			continue;

		//�f�B���N�g���p�X�ƃe�N�X�`��������t�@�C���p�X���쐬
		char texturePath[512];
		ZeroMemory(texturePath, sizeof(texturePath));
		strcat(texturePath, directoryPath);
		strcat(texturePath, matBuffer[i].pTextureFilename);

		//���[�h
		D3DXCreateTextureFromFile(pDevice, (LPSTR)texturePath, &textures[i]);
	}

	//�ǂݍ��݂��I�������̂Ń����[�X
	SAFE_RELEASE(buffer);
	SAFE_RELEASE(mesh);

	//fx�t�@�C���ǂݍ���
	D3DXCreateEffectFromFile(pDevice, EFFECTFILE_INSTANCINGMESH, 0, 0, 0, 0, &effect, 0);
	effect->SetTechnique("tech");
}

/**************************************
�������
***************************************/
void InstancingMeshContainer::Release()
{
	SAFE_RELEASE(vtxBuff);
	SAFE_RELEASE(indexuff);
	SAFE_RELEASE(declare);
	SAFE_DELETE_ARRAY(attributeTable);

	for (UINT i = 0; i < numMaterial; i++)
	{
		SAFE_RELEASE(textures[i]);
	}

	SAFE_DELETE_ARRAY(textures);
	SAFE_DELETE_ARRAY(materials);

	SAFE_RELEASE(effect);
}

/**************************************
�`�揈��
***************************************/
void InstancingMeshContainer::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�}�e���A���ޔ�
	D3DMATERIAL9 matDef;
	pDevice->GetMaterial(&matDef);

	//���C�g�����Z�b�g
	D3DCOLORVALUE diffuse[NUM_LIGHT], ambient[NUM_LIGHT];
	D3DXVECTOR4 dir[NUM_LIGHT];
	GetLightData(diffuse, ambient, dir);

	effect->SetVectorArray("lightDiffuse", (D3DXVECTOR4*)&diffuse, NUM_LIGHT);
	effect->SetVectorArray("lightAmbient", (D3DXVECTOR4*)&ambient, NUM_LIGHT);
	effect->SetVectorArray("lightDir", (D3DXVECTOR4*)&dir, NUM_LIGHT);

	//�r���[�s��A�v���W�F�N�V�����s����Z�b�g
	D3DXMATRIX mtxView, mtxProj;
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);
	pDevice->GetTransform(D3DTS_PROJECTION, &mtxProj);
	effect->SetMatrix("mtxView", &mtxView);
	effect->SetMatrix("mtxProj", &mtxProj);

	//���_�錾�ƃC���f�b�N�X�o�b�t�@��ݒ�
	pDevice->SetVertexDeclaration(declare);
	pDevice->SetIndices(indexuff);

	for (UINT i = 0; i < numMaterial; i++)
	{
		DWORD pass = textures[i] != NULL ? 0 : 1;

		//�}�e���A���ƃe�N�X�`���ݒ�
		pDevice->SetMaterial(&materials[i]);
		pDevice->SetTexture(0, textures[i]);

		effect->SetVector("matDiffuse", (D3DXVECTOR4*)&materials[i].Diffuse);
		effect->SetVector("matAmbient", (D3DXVECTOR4*)&materials[i].Ambient);

		//�`��
		effect->Begin(0, 0);
		effect->BeginPass(pass);

		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
			0,
			attributeTable[i].VertexStart,
			attributeTable[i].VertexCount,
			attributeTable[i].FaceStart * 3,
			attributeTable[i].FaceCount);

		effect->EndPass();
		effect->End();
	}

	pDevice->SetStreamSourceFreq(0, 1);
	pDevice->SetStreamSourceFreq(1, 1);
}

/**************************************
�X�g���[���\�[�X���Z�b�g����
***************************************/
void InstancingMeshContainer::SetStreamSource(LPDIRECT3DVERTEXBUFFER9 transformBuffer, UINT numInstance)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�X�g���[�����g���ݒ�
	pDevice->SetStreamSourceFreq(0, D3DSTREAMSOURCE_INDEXEDDATA | numInstance);
	pDevice->SetStreamSourceFreq(1, D3DSTREAMSOURCE_INSTANCEDATA | 1);

	//�X�g���[���\�[�X�ݒ�
	pDevice->SetStreamSource(0, vtxBuff, 0, D3DXGetFVFVertexSize(fvf));
	pDevice->SetStreamSource(1, transformBuffer, 0, sizeof(Transform));
}

/**************************************
���C�g�������ݒ菈��
***************************************/
void InstancingMeshContainer::SetLightAmplifier(float val)
{
	effect->SetFloat("amplifier", val);
}