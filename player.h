//=============================================================================
//
// �v���C���[���� [player.h]
// Author : �n糗Ǒ�
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

// �}�N����`
#define TEXTURE_GAME_SAMPLE00	_T("data/TEXTURE/runningman002.png")	// �T���v���p�摜
#define TEXTURE_SAMPLE00_SIZE_X	(50) // �e�N�X�`���T�C�Y
#define TEXTURE_SAMPLE00_SIZE_Y	(50) // ����

#define MAX_LENGTH (6)
#define JUDG_LEN (5)

typedef struct
{
	LPDIRECT3DTEXTURE9		D3DTexturePlayer = NULL;		// �e�N�X�`���ւ̃|���S��

	VERTEX_2D				vertexWk[NUM_VERTEX];				// ���_���i�[���[�N

	D3DXVECTOR3				posPlayer;						// �|���S���̈ړ���
	D3DXVECTOR3				rotPlayer;						// �|���S���̉�]��
	int						nCountAnim;						// �A�j���[�V�����J�E���g
	int						nPatternAnim;						// �A�j���[�V�����p�^�[���i���o�[

	D3DXVECTOR3				targetpos[MAX_LENGTH];

	// �ړ���m�ۗp�̃i���o�[
	int goal;

}PLAYER;


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);

HRESULT MakeVertexPlayer(void);
void SetVertex(void);


#endif
