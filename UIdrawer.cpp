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
void Object::LoadTexture(LPDIRECT3DDEVICE9 device, const char *path)
{
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(device,	// �f�o�C�X�ւ̃|�C���^
		path,							// �t�@�C���̃A�h���X
		&texture);						// �ǂݍ��ރ������[
}

//=============================================================================
// �I�u�W�F�N�g�T�[�N���̍쐬�@�i��]�I�u�W�F�N�g�p�̃T�[�N�������j
//=============================================================================
void Object::CreateObjectCircle()
{
	D3DXVECTOR2 temp = D3DXVECTOR2(size.x, size.y);
	radius = D3DXVec2Length(&temp);
	baseAngle = atan2f(size.y, size.x);
}

//=============================================================================
// �e�N�X�`���̉��
//=============================================================================
void Object::ReleaseTexture()
{
	if (texture != NULL)
	{// �e�N�X�`���̊J��
		texture->Release();
		texture = NULL;
	}
}

//=============================================================================
// �e�N�X�`���̏�����
//=============================================================================
void Object::InitialTexture()
{
	// �e�N�X�`�����
	&texture;
}

//=============================================================================
// �I�u�W�F�N�g�`�揈��
//=============================================================================
void Object::DrawObject(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, texture);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// �e�N�X�`���̒��_�̍쐬
//=============================================================================
void Object::MakeVertexObject()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���W�̐ݒ�
	vertexWk[0].vtx = position + D3DXVECTOR3(-size.x, -size.y, 0.0f);
	vertexWk[1].vtx = position + D3DXVECTOR3(size.x, -size.y, 0.0f);
	vertexWk[2].vtx = position + D3DXVECTOR3(-size.x, size.y, 0.0f);
	vertexWk[3].vtx = position + D3DXVECTOR3(size.x, size.y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	vertexWk[0].rhw =
		vertexWk[1].rhw =
		vertexWk[2].rhw =
		vertexWk[3].rhw = 1.0f;

	// �e�N�X�`�����W�̐ݒ�
	vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexWk[1].tex = D3DXVECTOR2(1.0, 0.0f);
	vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);
}

//=============================================================================
// �e�N�X�`���̒��_�̍쐬 (��]�I�u�W�F�N�g�p)
//=============================================================================
void Object::MakeVertexRotateObject()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���W�̐ݒ�
	vertexWk[0].vtx.x = position.x - cosf(baseAngle + rotation.z) * radius;
	vertexWk[0].vtx.y = position.y - sinf(baseAngle + rotation.z) * radius;
	vertexWk[0].vtx.z = 0.0f;

	vertexWk[1].vtx.x = position.x + cosf(baseAngle - rotation.z) * radius;
	vertexWk[1].vtx.y = position.y - sinf(baseAngle - rotation.z) * radius;
	vertexWk[1].vtx.z = 0.0f;

	vertexWk[2].vtx.x = position.x - cosf(baseAngle - rotation.z) * radius;
	vertexWk[2].vtx.y = position.y + sinf(baseAngle - rotation.z) * radius;
	vertexWk[2].vtx.z = 0.0f;

	vertexWk[3].vtx.x = position.x + cosf(baseAngle + rotation.z) * radius;
	vertexWk[3].vtx.y = position.y + sinf(baseAngle + rotation.z) * radius;
	vertexWk[3].vtx.z = 0.0f;

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	vertexWk[0].rhw =
		vertexWk[1].rhw =
		vertexWk[2].rhw =
		vertexWk[3].rhw = 1.0f;

	// �e�N�X�`�����W�̐ݒ�
	vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexWk[1].tex = D3DXVECTOR2(1.0, 0.0f);
	vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);
}

//=============================================================================
// �e�N�X�`���̒��_�̍쐬�@�i�Q�[�W��p�j
//=============================================================================
void Object::MakeVertexGuageBar(float percentage, float flameWidth)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���W�̐ݒ�
	vertexWk[0].vtx = D3DXVECTOR3(flameWidth + position.x, position.y, position.z)
		+ D3DXVECTOR3(-size.x, -size.y, 0.0f);
	vertexWk[1].vtx = D3DXVECTOR3(-flameWidth + position.x*percentage, position.y, position.z)
		+ D3DXVECTOR3(size.x, -size.y, 0.0f);
	vertexWk[2].vtx = D3DXVECTOR3(flameWidth + position.x, position.y, position.z)
		+ D3DXVECTOR3(-size.x, size.y, 0.0f);
	vertexWk[3].vtx = D3DXVECTOR3(-flameWidth + position.x*percentage, position.y, position.z)
		+ D3DXVECTOR3(size.x, size.y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	vertexWk[0].rhw =
		vertexWk[1].rhw =
		vertexWk[2].rhw =
		vertexWk[3].rhw = 1.0f;

	// �e�N�X�`�����W�̐ݒ�
	vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);
}

//=============================================================================
// �I�u�W�F�N�g�̒��_���W�̐ݒ�
//=============================================================================
void Object::SetVertexObject()
{
	// ���_���W�̐ݒ�
	vertexWk[0].vtx = position + D3DXVECTOR3(-size.x, -size.y, 0.0f);
	vertexWk[1].vtx = position + D3DXVECTOR3(size.x, -size.y, 0.0f);
	vertexWk[2].vtx = position + D3DXVECTOR3(-size.x, size.y, 0.0f);
	vertexWk[3].vtx = position + D3DXVECTOR3(size.x, size.y, 0.0f);
}

//=============================================================================
// �I�u�W�F�N�g�̒��_���W�̐ݒ� (��]�I�u�W�F�N�g�p)
//=============================================================================
void Object::SetVertexRotateObject()
{
	// ���_���W�̐ݒ�
	vertexWk[0].vtx.x = position.x - cosf(baseAngle + rotation.z) * radius;
	vertexWk[0].vtx.y = position.y - sinf(baseAngle + rotation.z) * radius;
	vertexWk[0].vtx.z = 0.0f;

	vertexWk[1].vtx.x = position.x + cosf(baseAngle - rotation.z) * radius;
	vertexWk[1].vtx.y = position.y - sinf(baseAngle - rotation.z) * radius;
	vertexWk[1].vtx.z = 0.0f;

	vertexWk[2].vtx.x = position.x - cosf(baseAngle - rotation.z) * radius;
	vertexWk[2].vtx.y = position.y + sinf(baseAngle - rotation.z) * radius;
	vertexWk[2].vtx.z = 0.0f;

	vertexWk[3].vtx.x = position.x + cosf(baseAngle + rotation.z) * radius;
	vertexWk[3].vtx.y = position.y + sinf(baseAngle + rotation.z) * radius;
	vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �I�u�W�F�N�g�̒��_���W�̐ݒ�@�i�Q�[�W��p�j
//=============================================================================
void Object::SetVertexGuageBar(float percentage, float flameWidth, int guageType)
{
	if (guageType == LEFT_GUAGEBAR)
	{
		// ���_���W�̐ݒ�
		vertexWk[0].vtx =
			D3DXVECTOR3(flameWidth + position.x - size.x, position.y - size.y, position.z);
		vertexWk[1].vtx =
			D3DXVECTOR3(-flameWidth + vertexWk[0].vtx.x + (position.x + size.x - vertexWk[0].vtx.x)*percentage,
				position.y - size.y, position.z);
		vertexWk[2].vtx =
			D3DXVECTOR3(flameWidth + position.x - size.x, position.y + size.y, position.z);
		vertexWk[3].vtx =
			D3DXVECTOR3(-flameWidth + vertexWk[2].vtx.x + (position.x + size.x - vertexWk[2].vtx.x)*percentage,
				position.y + size.y, position.z);
	}
	if (guageType == RIGHT_GUAGEBAR)
	{
		// ���_���W�̐ݒ�
		vertexWk[0].vtx =
			D3DXVECTOR3(flameWidth + vertexWk[1].vtx.x + (position.x - size.x - vertexWk[1].vtx.x)*percentage, position.y - size.y, position.z);
		vertexWk[1].vtx =
			D3DXVECTOR3(-flameWidth + position.x + size.x, position.y - size.y, position.z);
		vertexWk[2].vtx =
			D3DXVECTOR3(flameWidth + vertexWk[3].vtx.x + (position.x - size.x - vertexWk[3].vtx.x)*percentage, position.y + size.y, position.z);
		vertexWk[3].vtx =
			D3DXVECTOR3(-flameWidth + position.x + size.x,
				position.y + size.y, position.z);
	}
	if (guageType == DOWN_GUAGEBAR)
	{
		// ���_���W�̐ݒ�
		vertexWk[0].vtx =
			D3DXVECTOR3(position.x - size.x,
				flameWidth + vertexWk[2].vtx.y + (position.y - size.y - vertexWk[2].vtx.y)*percentage, position.z);
		vertexWk[1].vtx =
			D3DXVECTOR3(position.x + size.x,
				flameWidth + vertexWk[3].vtx.y + (position.y - size.y - vertexWk[3].vtx.y)*percentage, position.z);
		vertexWk[2].vtx =
			D3DXVECTOR3(position.x - size.x, -flameWidth + position.y + size.y, position.z);
		vertexWk[3].vtx =
			D3DXVECTOR3(position.x + size.x, -flameWidth + position.y + size.y, position.z);
	}
	if (guageType == UP_GUAGEBAR)
	{
		// ���_���W�̐ݒ�
		vertexWk[0].vtx =
			D3DXVECTOR3(position.x - size.x, flameWidth + position.y - size.y, position.z);
		vertexWk[1].vtx =
			D3DXVECTOR3(position.x + size.x, flameWidth + position.y - size.y, position.z);
		vertexWk[2].vtx =
			D3DXVECTOR3(position.x - size.x,
				-flameWidth + vertexWk[0].vtx.y + (position.y + size.y - vertexWk[0].vtx.y)*percentage, position.z);
		vertexWk[3].vtx =
			D3DXVECTOR3(position.x + size.x, -flameWidth + vertexWk[1].vtx.y + (position.y + size.y - vertexWk[1].vtx.y)*percentage, position.z);
	}
}

//=============================================================================
// �I�u�W�F�N�g�̒��_���W�̐ݒ�@�i�e���b�v�w�i��p�j
//=============================================================================
void Object::SetVertexTelopBG(float percentage)
{
	// ���_���W�̐ݒ�
	vertexWk[0].vtx = D3DXVECTOR3(0, position.y - size.y*percentage, position.z);
	vertexWk[1].vtx = D3DXVECTOR3(SCREEN_WIDTH, position.y - size.y*percentage, position.z);
	vertexWk[2].vtx = D3DXVECTOR3(0, position.y + size.y*percentage, position.z);
	vertexWk[3].vtx = D3DXVECTOR3(SCREEN_WIDTH, position.y + size.y*percentage, position.z);
}

//=============================================================================
// �I�u�W�F�N�g�̒��_���W�̐ݒ�@�i�J�E���^�[��p�j
//=============================================================================
void Object::SetVertexCounter(int placeCount, float placeInterval)
{
	// ���_���W�̐ݒ�
	vertexWk[0].vtx = D3DXVECTOR3(position.x + placeCount * placeInterval, position.y, position.z)
		+ D3DXVECTOR3(-size.x, -size.y, 0.0f);
	vertexWk[1].vtx = D3DXVECTOR3(position.x + placeCount * placeInterval, position.y, position.z)
		+ D3DXVECTOR3(size.x, -size.y, 0.0f);
	vertexWk[2].vtx = D3DXVECTOR3(position.x + placeCount * placeInterval, position.y, position.z)
		+ D3DXVECTOR3(-size.x, size.y, 0.0f);
	vertexWk[3].vtx = D3DXVECTOR3(position.x + placeCount * placeInterval, position.y, position.z)
		+ D3DXVECTOR3(size.x, size.y, 0.0f);
}

//=============================================================================
//�I�u�W�F�N�g�̃e�N�X�`�����W�ݒ菈��
//=============================================================================
void Object::SetTextureObject(int divX, int divY, int pattern)
{
	float sizeX = 1.0f / divX;
	float sizeY = 1.0f / divY;
	int x = pattern % divX;
	int y = pattern / divX;

	vertexWk[0].tex = D3DXVECTOR2(x * sizeX, y * sizeY);
	vertexWk[1].tex = D3DXVECTOR2((x + 1) * sizeX, y * sizeY);
	vertexWk[2].tex = D3DXVECTOR2(x * sizeX, (y + 1)* sizeY);
	vertexWk[3].tex = D3DXVECTOR2((x + 1) * sizeX, (y + 1) * sizeY);
}

//=============================================================================
//�I�u�W�F�N�g�̃e�N�X�`�����W�ݒ菈���@�i�J�E���^�[��p�j
//=============================================================================
void Object::SetTextureCounter(int number, float placeInterval)
{
	// ���_���W�̐ݒ�
	vertexWk[0].tex = D3DXVECTOR2(number * placeInterval, 0.0f);
	vertexWk[1].tex = D3DXVECTOR2(number * placeInterval + placeInterval, 0.0f);
	vertexWk[2].tex = D3DXVECTOR2(number * placeInterval, 1.0f);
	vertexWk[3].tex = D3DXVECTOR2(number * placeInterval + placeInterval, 1.0f);
}

//=============================================================================
//�I�u�W�F�N�g�̃A���t�@�l�ݒ菈���@�i���߁j
//=============================================================================
void Object::SetAlphaObject(float alpha)
{
	vertexWk[0].diffuse =
		vertexWk[1].diffuse =
		vertexWk[2].diffuse =
		vertexWk[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, alpha);
}

//=============================================================================
//�I�u�W�F�N�g�̔��ˌ��ݒ菈��
//=============================================================================
void Object::SetColorObject(D3DXCOLOR color)
{
	vertexWk[0].diffuse =
		vertexWk[1].diffuse =
		vertexWk[2].diffuse =
		vertexWk[3].diffuse = color;
}

//=============================================================================
// �I�u�W�F�N�g�J�E���g�擾����
//=============================================================================
float Object::GetCountObject(float duration)
{
	countFrame++;
	float t = (float)countFrame / duration;

	return t;
}
