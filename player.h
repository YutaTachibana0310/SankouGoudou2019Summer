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

#define TEXTURE_PATTERN_DIVIDE_X	(5)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y	(2)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM			(TEXTURE_PATTERN_DIVIDE_X*TEXTURE_PATTERN_DIVIDE_Y)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION				(1000)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define TEXTURE_PATTERN_DIVIDE_X	(5)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y	(2)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM			(TEXTURE_PATTERN_DIVIDE_X*TEXTURE_PATTERN_DIVIDE_Y)	// �A�j���[�V�����p�^�[����
#define MAX_LENGTH (6)
#define JUDG_LEN (5)


typedef struct
{
	LPDIRECT3DTEXTURE9		g_pD3DTexturePlayer = NULL;		// �e�N�X�`���ւ̃|���S��

	VERTEX_2D				g_vertexWk[NUM_VERTEX];				// ���_���i�[���[�N

	D3DXVECTOR3				g_posPlayer;						// �|���S���̈ړ���
	D3DXVECTOR3				g_rotPlayer;						// �|���S���̉�]��
	int						g_nCountAnim;						// �A�j���[�V�����J�E���g
	int						g_nPatternAnim;						// �A�j���[�V�����p�^�[���i���o�[

	D3DXVECTOR3				targetpos[MAX_LENGTH];

	// �ړ���m�ۗp�̃i���o�[
	int goal;
	//�ړ���ֈړ�����܂œ��͂��󂯕t���Ȃ��悤�ɂ��邽�߂̃t���O
	bool move_wait;

}PLAYER;

enum MOVEFLAG {
	S_KEY = 0,
	W_KEY,
	A_KEY,
	D_KEY,
	Z_KEY,
	X_KEY,
	


};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);


HRESULT MakeVertexPlayer(void);
void SetTexturePlayer(int cntPattern);
void SetVertex(void);
void DrawTEXT(void);

PLAYER* GetPlayer();
#endif
