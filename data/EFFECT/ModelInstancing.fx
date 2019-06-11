//=====================================
//
//���f���C���X�^���V���O�V�F�[�_[ModelInstancing.fx]
//Author:GP12B332 21 ���ԗY��
//
//=====================================

/**************************************
*�O���[�o���ϐ�
***************************************/
float4x4 mtxView;				//�r���[�s��
float4x4 mtxProj;				//�v���W�F�N�V�����s��
float4 matDiffuse;				//�}�e���A���f�B�t���[�Y
float4 matAmbient;				//�}�e���A���A���r�G���g

float4 lightDiffuse[3];			//���C�g�f�B�t���[�Y�z��
float4 lightAmbient[3];			//���C�g�A���r�G���g�z��
float4 lightDir[3];				//���C�g�����z��

/**************************************
*�e�N�X�`���T���v���[
***************************************/
sampler s0 : register(s0);

/**************************************
*���_�V�F�[�_�o�͍\����
***************************************/
struct VS_OUT {
	float4 pos	: POSITION;
	float2 uv	: TEXCOORD0;
	float3 normal	: TEXCOORD1;
};

/**************************************
*���_�V�F�[�_
***************************************/
VS_OUT vsMain(
	float3 pos		: POSITION,
	float3 normal	: NORMAL,
	float2 uv		: TEXCOORD0,
	float3 worldPos : TEXCOORD1,
	float3 worldRot : TEXCOORD2,
	float3 worldScl : TEXCOORD3
) {
	VS_OUT Out;

	Out.pos = float4(pos, 1.0f);

	////�X�P�[���v�Z
	Out.pos.x = Out.pos.x * worldScl.x;
	Out.pos.y = Out.pos.y * worldScl.y;
	Out.pos.z = Out.pos.z * worldScl.z;

	//��]�v�Z
	float4 tmpPos = Out.pos;
	Out.pos.y = tmpPos.y * cos(worldRot.x) - tmpPos.z * sin(worldRot.x);
	Out.pos.z = tmpPos.y * sin(worldRot.x) + tmpPos.z * cos(worldRot.x);

	tmpPos = Out.pos;
	Out.pos.x = tmpPos.x * cos(worldRot.y) + tmpPos.z * sin(worldRot.y);
	Out.pos.z = tmpPos.x * -sin(worldRot.y) + tmpPos.z * cos(worldRot.y);

	tmpPos = Out.pos;
	Out.pos.x = tmpPos.x * cos(worldRot.z) - tmpPos.y * sin(worldRot.z);
	Out.pos.y = tmpPos.x * sin(worldRot.z) + tmpPos.y * cos(worldRot.z);

	////�ړ��v�Z
	Out.pos = Out.pos + float4(worldPos, 0.0f);

	//�r���[�ϊ��A�v���W�F�N�V�����ϊ�
	Out.pos = mul(Out.pos, mtxView);
	Out.pos = mul(Out.pos, mtxProj);

	//UV���W�i�[
	Out.uv = uv;

	//�@���v�Z
	Out.normal = normal;
	Out.normal = mul(float4(Out.normal, 0.0f), mtxView).xyz;
	Out.normal = mul(float4(Out.normal, 0.0f), mtxProj).xyz;

	return Out;
}

/**************************************
*�s�N�Z���V�F�[�_�i�p�X0�p�j ���e�N�X�`���f�B�t���[�Y���g�p����
***************************************/
float4 psMain0(VS_OUT In) : COLOR0
{
	//�e�����̔��˗����v�Z
	float power0 = dot(In.normal, lightDir[0].xyz);
	float power1 = dot(In.normal, lightDir[1].xyz);
	float power2 = dot(In.normal, lightDir[2].xyz);

	//�e�N�X�`������F���擾
	float4 RC = tex2D(s0, In.uv);

	//���s�����̌v�Z
	float4 color = RC * max(lightDiffuse[0] * power0, 0.0f);
	color += RC * max(lightDiffuse[1] * power1, 0.0f);
	color += RC * max(lightDiffuse[2] * power2, 0.0f);

	//�����̌v�Z
	color += lightAmbient[0] * matAmbient;
	color += lightAmbient[1] * matAmbient;
	color += lightAmbient[2] * matAmbient;

	//�s�����ɐݒ�
	color.a = 1.0f;

	return  color;
}

/**************************************
*�s�N�Z���V�F�[�_�i�p�X1�p�j ���}�e���A���f�B�t���[�Y���g�p����
***************************************/
float4 psMain1(VS_OUT In) : COLOR0
{
	//�e�����̔��˗����v�Z
	float power0 = dot(In.normal, lightDir[0].xyz);
	float power1 = dot(In.normal, lightDir[1].xyz);
	float power2 = dot(In.normal, lightDir[2].xyz);

	//�}�e���A���f�B�t���[�Y���擾
	float4 RC = matDiffuse;

	//���s�����̌v�Z
	float4 color = RC * max(lightDiffuse[0] * power0, 0.0f);
	color += RC * max(lightDiffuse[1] * power1, 0.0f);
	color += RC * max(lightDiffuse[2] * power2, 0.0f);

	//�����̌v�Z
	color += lightAmbient[0] * matAmbient;
	color += lightAmbient[1] * matAmbient;
	color += lightAmbient[2] * matAmbient;

	//�s�����ɐݒ�
	color.a = 1.0f;

	return  color;
}

/**************************************
*�e�N�j�b�N
***************************************/
technique tech
{
	//�e�N�X�`���f�B�t���[�Y�g�p��
	pass p0 {
		VertexShader = compile vs_2_0 vsMain();
		PixelShader = compile ps_2_0 psMain0();
	}

	//�}�e���A���f�B�t���[�Y�g�p��
	pass p1 {
		VertexShader = compile vs_2_0 vsMain();
		PixelShader = compile ps_2_0 psMain1();
	}
}