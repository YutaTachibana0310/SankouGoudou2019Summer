//=============================================================================
//
// UI�`��p���� [UIdrawer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "UIdrawer.h"

//=============================================================================
// �e�N�X�`���̓ǂݍ���
//=============================================================================
void LoadTexture(LPDIRECT3DDEVICE9 device, const char *adress, OBJECT *object)
{
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(device,	// �f�o�C�X�ւ̃|�C���^
		adress,							// �t�@�C���̃A�h���X
		&object->texture);				// �ǂݍ��ރ������[
}

//=============================================================================
// �I�u�W�F�N�g�T�[�N���̍쐬�@�i��]�I�u�W�F�N�g�p�̃T�[�N�������j
//=============================================================================
void CreateObjectCircle(OBJECT *object, float sizeX, float sizeY)
{
	D3DXVECTOR2 temp = D3DXVECTOR2(sizeX, sizeY);
	object->radius = D3DXVec2Length(&temp);
	object->baseAngle = atan2f(sizeY, sizeX);
}

//=============================================================================
// �e�N�X�`���̉��
//=============================================================================
void ReleaseTexture(OBJECT *object)
{
	if (object->texture != NULL)
	{// �e�N�X�`���̊J��
		object->texture->Release();
		object->texture = NULL;
	}
}

//=============================================================================
// �e�N�X�`���̏�����
//=============================================================================
void InitialTexture(OBJECT *object)
{
	// �e�N�X�`�����
	&object->texture;
}

//=============================================================================
// �I�u�W�F�N�g�`�揈��
//=============================================================================
void DrawObject(LPDIRECT3DDEVICE9 pDevice, OBJECT object)
{
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, object.texture);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, object.vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// �e�N�X�`���̒��_�̍쐬
//=============================================================================
void MakeVertexObject(OBJECT *object)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���W�̐ݒ�
	object->vertexWk[0].vtx = object->position + D3DXVECTOR3(-object->size.x, -object->size.y, 0.0f);
	object->vertexWk[1].vtx = object->position + D3DXVECTOR3(object->size.x, -object->size.y, 0.0f);
	object->vertexWk[2].vtx = object->position + D3DXVECTOR3(-object->size.x, object->size.y, 0.0f);
	object->vertexWk[3].vtx = object->position + D3DXVECTOR3(object->size.x, object->size.y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	object->vertexWk[0].rhw =
		object->vertexWk[1].rhw =
		object->vertexWk[2].rhw =
		object->vertexWk[3].rhw = 1.0f;

	// �e�N�X�`�����W�̐ݒ�
	object->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	object->vertexWk[1].tex = D3DXVECTOR2(1.0, 0.0f);
	object->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	object->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);
}

//=============================================================================
// �e�N�X�`���̒��_�̍쐬 (��]�I�u�W�F�N�g�p)
//=============================================================================
void MakeVertexRotateObject(OBJECT *object)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���W�̐ݒ�
	object->vertexWk[0].vtx.x = object->position.x - cosf(object->baseAngle + object->rotation.z) * object->radius;
	object->vertexWk[0].vtx.y = object->position.y - sinf(object->baseAngle + object->rotation.z) * object->radius;
	object->vertexWk[0].vtx.z = 0.0f;

	object->vertexWk[1].vtx.x = object->position.x + cosf(object->baseAngle - object->rotation.z) * object->radius;
	object->vertexWk[1].vtx.y = object->position.y - sinf(object->baseAngle - object->rotation.z) * object->radius;
	object->vertexWk[1].vtx.z = 0.0f;

	object->vertexWk[2].vtx.x = object->position.x - cosf(object->baseAngle - object->rotation.z) * object->radius;
	object->vertexWk[2].vtx.y = object->position.y + sinf(object->baseAngle - object->rotation.z) * object->radius;
	object->vertexWk[2].vtx.z = 0.0f;

	object->vertexWk[3].vtx.x = object->position.x + cosf(object->baseAngle + object->rotation.z) * object->radius;
	object->vertexWk[3].vtx.y = object->position.y + sinf(object->baseAngle + object->rotation.z) * object->radius;
	object->vertexWk[3].vtx.z = 0.0f;

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	object->vertexWk[0].rhw =
		object->vertexWk[1].rhw =
		object->vertexWk[2].rhw =
		object->vertexWk[3].rhw = 1.0f;

	// �e�N�X�`�����W�̐ݒ�
	object->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	object->vertexWk[1].tex = D3DXVECTOR2(1.0, 0.0f);
	object->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	object->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);
}

//=============================================================================
// �e�N�X�`���̒��_�̍쐬�@�i�Q�[�W��p�j
//=============================================================================
void MakeVertexGuageBar(OBJECT *object, float percentage, float flameWidth)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���W�̐ݒ�
	object->vertexWk[0].vtx = D3DXVECTOR3(flameWidth + object->position.x, object->position.y, object->position.z) 
		+ D3DXVECTOR3(-object->size.x, -object->size.y, 0.0f);
	object->vertexWk[1].vtx = D3DXVECTOR3(-flameWidth + object->position.x*percentage, object->position.y, object->position.z) 
		+ D3DXVECTOR3(object->size.x, -object->size.y, 0.0f);
	object->vertexWk[2].vtx = D3DXVECTOR3(flameWidth + object->position.x, object->position.y, object->position.z) 
		+ D3DXVECTOR3(-object->size.x, object->size.y, 0.0f);
	object->vertexWk[3].vtx = D3DXVECTOR3(-flameWidth + object->position.x*percentage, object->position.y, object->position.z) 
		+ D3DXVECTOR3(object->size.x, object->size.y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	object->vertexWk[0].rhw =
		object->vertexWk[1].rhw =
		object->vertexWk[2].rhw =
		object->vertexWk[3].rhw = 1.0f;

	// �e�N�X�`�����W�̐ݒ�
	object->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	object->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	object->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	object->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);
}

//=============================================================================
// �I�u�W�F�N�g�̒��_���W�̐ݒ�
//=============================================================================
void SetVertexObject(OBJECT *object)
{
	// ���_���W�̐ݒ�
	object->vertexWk[0].vtx = object->position + D3DXVECTOR3(-object->size.x, -object->size.y, 0.0f);
	object->vertexWk[1].vtx = object->position + D3DXVECTOR3(object->size.x, -object->size.y, 0.0f);
	object->vertexWk[2].vtx = object->position + D3DXVECTOR3(-object->size.x, object->size.y, 0.0f);
	object->vertexWk[3].vtx = object->position + D3DXVECTOR3(object->size.x, object->size.y, 0.0f);
}

//=============================================================================
// �I�u�W�F�N�g�̒��_���W�̐ݒ� (��]�I�u�W�F�N�g�p)
//=============================================================================
void SetVertexRotateObject(OBJECT *object)
{
	// ���_���W�̐ݒ�
	object->vertexWk[0].vtx.x = object->position.x - cosf(object->baseAngle + object->rotation.z) * object->radius;
	object->vertexWk[0].vtx.y = object->position.y - sinf(object->baseAngle + object->rotation.z) * object->radius;
	object->vertexWk[0].vtx.z = 0.0f;

	object->vertexWk[1].vtx.x = object->position.x + cosf(object->baseAngle - object->rotation.z) * object->radius;
	object->vertexWk[1].vtx.y = object->position.y - sinf(object->baseAngle - object->rotation.z) * object->radius;
	object->vertexWk[1].vtx.z = 0.0f;

	object->vertexWk[2].vtx.x = object->position.x - cosf(object->baseAngle - object->rotation.z) * object->radius;
	object->vertexWk[2].vtx.y = object->position.y + sinf(object->baseAngle - object->rotation.z) * object->radius;
	object->vertexWk[2].vtx.z = 0.0f;

	object->vertexWk[3].vtx.x = object->position.x + cosf(object->baseAngle + object->rotation.z) * object->radius;
	object->vertexWk[3].vtx.y = object->position.y + sinf(object->baseAngle + object->rotation.z) * object->radius;
	object->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �I�u�W�F�N�g�̒��_���W�̐ݒ�@�i�Q�[�W��p�j
//=============================================================================
void SetVertexGuageBar(OBJECT *object, float percentage, float flameWidth, int guageType)
{
	if (guageType == LEFT_GUAGEBAR)
	{
		// ���_���W�̐ݒ�
		object->vertexWk[0].vtx =
			D3DXVECTOR3(flameWidth + object->position.x - object->size.x, object->position.y - object->size.y, object->position.z);
		object->vertexWk[1].vtx =
			D3DXVECTOR3(-flameWidth + object->vertexWk[0].vtx.x + (object->position.x + object->size.x - object->vertexWk[0].vtx.x)*percentage,
				object->position.y - object->size.y, object->position.z);
		object->vertexWk[2].vtx =
			D3DXVECTOR3(flameWidth + object->position.x - object->size.x, object->position.y + object->size.y, object->position.z);
		object->vertexWk[3].vtx =
			D3DXVECTOR3(-flameWidth + object->vertexWk[2].vtx.x + (object->position.x + object->size.x - object->vertexWk[2].vtx.x)*percentage,
				object->position.y + object->size.y, object->position.z);
	}
	if (guageType == RIGHT_GUAGEBAR)
	{
		// ���_���W�̐ݒ�
		object->vertexWk[0].vtx =
			D3DXVECTOR3(flameWidth + object->vertexWk[1].vtx.x + (object->position.x - object->size.x - object->vertexWk[1].vtx.x)*percentage, object->position.y - object->size.y, object->position.z);
		object->vertexWk[1].vtx =
			D3DXVECTOR3(-flameWidth + object->position.x + object->size.x,object->position.y - object->size.y, object->position.z);
		object->vertexWk[2].vtx =
			D3DXVECTOR3(flameWidth + object->vertexWk[3].vtx.x + (object->position.x - object->size.x - object->vertexWk[3].vtx.x)*percentage, object->position.y + object->size.y, object->position.z);
		object->vertexWk[3].vtx =
			D3DXVECTOR3(-flameWidth + object->position.x + object->size.x,
				object->position.y + object->size.y, object->position.z);
	}
	if (guageType == DOWN_GUAGEBAR)
	{
		// ���_���W�̐ݒ�
		object->vertexWk[0].vtx =
			D3DXVECTOR3(object->position.x - object->size.x, 
				flameWidth + object->vertexWk[2].vtx.y + (object->position.y - object->size.y - object->vertexWk[2].vtx.y)*percentage, object->position.z);
		object->vertexWk[1].vtx =
			D3DXVECTOR3(object->position.x + object->size.x, 
				flameWidth + object->vertexWk[3].vtx.y + (object->position.y - object->size.y - object->vertexWk[3].vtx.y)*percentage, object->position.z);
		object->vertexWk[2].vtx =
			D3DXVECTOR3(object->position.x - object->size.x, -flameWidth + object->position.y + object->size.y, object->position.z);
		object->vertexWk[3].vtx =
			D3DXVECTOR3(object->position.x + object->size.x, -flameWidth + object->position.y + object->size.y, object->position.z);
	}
	if (guageType == UP_GUAGEBAR)
	{
		// ���_���W�̐ݒ�
		object->vertexWk[0].vtx =
			D3DXVECTOR3(object->position.x - object->size.x, flameWidth + object->position.y - object->size.y, object->position.z);
		object->vertexWk[1].vtx =
			D3DXVECTOR3(object->position.x + object->size.x, flameWidth + object->position.y - object->size.y, object->position.z);
		object->vertexWk[2].vtx =
			D3DXVECTOR3(object->position.x - object->size.x,
				-flameWidth + object->vertexWk[0].vtx.y + (object->position.y + object->size.y - object->vertexWk[0].vtx.y)*percentage, object->position.z);
		object->vertexWk[3].vtx =
			D3DXVECTOR3(object->position.x + object->size.x, -flameWidth + object->vertexWk[1].vtx.y + (object->position.y + object->size.y - object->vertexWk[1].vtx.y)*percentage, object->position.z);
	}
}

//=============================================================================
// �I�u�W�F�N�g�̒��_���W�̐ݒ�@�i�e���b�v�w�i��p�j
//=============================================================================
void SetVertexTelopBG(OBJECT *object, float percentage)
{
	// ���_���W�̐ݒ�
	object->vertexWk[0].vtx = D3DXVECTOR3(0, object->position.y - object->size.y*percentage, object->position.z);
	object->vertexWk[1].vtx = D3DXVECTOR3(SCREEN_WIDTH, object->position.y - object->size.y*percentage, object->position.z);
	object->vertexWk[2].vtx = D3DXVECTOR3(0 , object->position.y + object->size.y*percentage, object->position.z);
	object->vertexWk[3].vtx = D3DXVECTOR3(SCREEN_WIDTH, object->position.y + object->size.y*percentage, object->position.z);
}

//=============================================================================
// �I�u�W�F�N�g�̒��_���W�̐ݒ�@�i�J�E���^�[��p�j
//=============================================================================
void SetVertexCounter(OBJECT *object, int placeCount, float placeInterval)
{
	// ���_���W�̐ݒ�
	object->vertexWk[0].vtx = D3DXVECTOR3(object->position.x + placeCount * placeInterval, object->position.y, object->position.z) 
		+ D3DXVECTOR3(-object->size.x, -object->size.y, 0.0f);
	object->vertexWk[1].vtx = D3DXVECTOR3(object->position.x + placeCount * placeInterval, object->position.y, object->position.z) 
		+ D3DXVECTOR3(object->size.x, -object->size.y, 0.0f);
	object->vertexWk[2].vtx = D3DXVECTOR3(object->position.x + placeCount * placeInterval, object->position.y, object->position.z) 
		+ D3DXVECTOR3(-object->size.x, object->size.y, 0.0f);
	object->vertexWk[3].vtx = D3DXVECTOR3(object->position.x + placeCount * placeInterval, object->position.y, object->position.z) 
		+ D3DXVECTOR3(object->size.x, object->size.y, 0.0f);
}

//=============================================================================
//�I�u�W�F�N�g�̃e�N�X�`�����W�ݒ菈��
//=============================================================================
void SetTextureObject(OBJECT *object, int divX, int divY, int pattern)
{
	float sizeX = 1.0f / divX;
	float sizeY = 1.0f / divY;
	int x = pattern % divX;
	int y = pattern / divX;

	object->vertexWk[0].tex = D3DXVECTOR2(x * sizeX, y * sizeY);
	object->vertexWk[1].tex = D3DXVECTOR2((x + 1) * sizeX, y * sizeY);
	object->vertexWk[2].tex = D3DXVECTOR2(x * sizeX, (y + 1)* sizeY);
	object->vertexWk[3].tex = D3DXVECTOR2((x + 1) * sizeX, (y + 1) * sizeY);
}

//=============================================================================
//�I�u�W�F�N�g�̃e�N�X�`�����W�ݒ菈���@�i�J�E���^�[��p�j
//=============================================================================
void SetTextureCounter(OBJECT *object, int number, float placeInterval)
{
	// ���_���W�̐ݒ�
	object->vertexWk[0].tex = D3DXVECTOR2(number * placeInterval, 0.0f);
	object->vertexWk[1].tex = D3DXVECTOR2(number * placeInterval + placeInterval, 0.0f);
	object->vertexWk[2].tex = D3DXVECTOR2(number * placeInterval, 1.0f);
	object->vertexWk[3].tex = D3DXVECTOR2(number * placeInterval + placeInterval, 1.0f);
}

//=============================================================================
//�I�u�W�F�N�g�̃A���t�@�l�ݒ菈���@�i���߁j
//=============================================================================
void SetAlphaObject(OBJECT *object, float alpha)
{
	object->vertexWk[0].diffuse =
		object->vertexWk[1].diffuse =
		object->vertexWk[2].diffuse =
		object->vertexWk[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, alpha);
}

//=============================================================================
//�I�u�W�F�N�g�̔��ˌ��ݒ菈��
//=============================================================================
void SetColorObject(OBJECT *object, D3DXCOLOR color)
{
	object->vertexWk[0].diffuse =
		object->vertexWk[1].diffuse =
		object->vertexWk[2].diffuse =
		object->vertexWk[3].diffuse = color;
}

//=============================================================================
// �I�u�W�F�N�g�J�E���g�擾����
//=============================================================================
float GetCountObject(OBJECT *object, float duration)
{
	object->countFrame++;
	float t = (float)object->countFrame / duration;

	return t;
}
