//=====================================
//
//�p�[�e�B�N���V�F�[�_[Particle.fx]
//Author:GP12B332 21 ���ԗY��
//
//=====================================

/***************************************
�O���[�o���ϐ�
***************************************/
float4x4 mtxView;		//�r���[�s��
float4x4 mtxProj;		//�v���W�F�N�V�����s��
float4x4 mtxInvView;	//�r���[�t�s��

/**************************************************************
�e�N�X�`���T���v���[�i0�Ԃ�SetTexture�����e�N�X�`�����g�p����
***************************************************************/
sampler s0 : register(s0);

/**************************************************************
���_�V�F�[�_�o�͍\����
***************************************************************/
struct VS_OUTPUT {
	float4 pos : POSITION;
	float2 uv : TEXCOORD0;
	float4 color : COLOR0;
};

/**************************************************************
���_�V�F�[�_
***************************************************************/
VS_OUTPUT vsMain(
	float3 pos : POSITION,
	float2 localUV : TEXCOORD0,
	float3 worldPos : TEXCOORD1,
	float3 worldScl : TEXCOORD2,
	float4 worldRot : TEXCOORD3,
	float2 texUV : TEXCOORD4
) {
	VS_OUTPUT Out;

	Out.pos = float4(pos, 1.0f);

	//scale
	Out.pos.x = Out.pos.x * worldScl.x;
	Out.pos.y = Out.pos.y * worldScl.y;
	Out.pos.z = Out.pos.z * worldScl.z;

	//rotX
	float4 tmp = Out.pos;
	Out.pos.x =
		tmp.x * (1 - 2 * worldRot.y*worldRot.y - 2 * worldRot.z*worldRot.z)
		+ tmp.y * 2 * (worldRot.x*worldRot.y + worldRot.w*worldRot.z)
		+ tmp.z * 2 * (worldRot.x*worldRot.z - worldRot.w*worldRot.x);

	Out.pos.y =
		tmp.x * 2 * (worldRot.x*worldRot.y - worldRot.w*worldRot.z)
		+ tmp.y * (1 - 2 * worldRot.x*worldRot.x - 2 * worldRot.z*worldRot.z)
		+ tmp.z * 2 * (worldRot.y*worldRot.z + worldRot.w*worldRot.x);

	Out.pos.z =
		tmp.x * 2 * (worldRot.x*worldRot.z + worldRot.w*worldRot.y)
		+ tmp.y * 2 * (worldRot.y*worldRot.z - worldRot.w*worldRot.x)
		+ tmp.z * (1 - 2 * worldRot.x*worldRot.x - 2 * worldRot.y*worldRot.y);

	//InvView
	Out.pos = mul(Out.pos, mtxInvView);

	//Translate
	Out.pos.x = Out.pos.x + worldPos.x;
	Out.pos.y = Out.pos.y + worldPos.y;
	Out.pos.z = Out.pos.z + worldPos.z;

	//view & projection
	Out.pos = mul(Out.pos, mtxView);
	Out.pos = mul(Out.pos, mtxProj);

	//texUV
	Out.uv = localUV + texUV;

	//Color
	Out.color = float4(1.0f, 1.0f, 1.0f, 1.0f);

	return Out;
}

/**************************************************************
�s�N�Z���V�F�[�_
***************************************************************/
float4 psMain(VS_OUTPUT In) : COLOR0
{
	//�e�N�X�`������J���[���擾
	return tex2D(s0, In.uv) * In.color;
}

/**************************************************************
�e�N�j�b�N
***************************************************************/
technique tech {
	pass p0 {
		VertexShader = compile vs_2_0 vsMain();
		PixelShader = compile ps_2_0 psMain();
	}
};