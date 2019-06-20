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

float amplifier = 1.0f;			//������

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
	float3 normal : NORMAL,
	float2 uv : TEXCOORD0,
	float3 worldPos : TEXCOORD1,
	float3 worldRot : TEXCOORD2,
	float3 worldScl : TEXCOORD3
) {
	VS_OUT Out;

	Out.pos = float4(pos, 1.0f);
	Out.normal = normal;

	//�X�P�[���ϊ�
	float4x4 mtx = {
		worldScl.x, 0.0f, 0.0f, 0.0f,
		0.0f, worldScl.y, 0.0f, 0.0f,
		0.0f, 0.0f, worldScl.z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f };
	Out.pos = mul(mtx, Out.pos);

	//X����]
	mtx = float4x4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, cos(worldRot.x), -sin(worldRot.x), 0.0f,
		0.0f, sin(worldRot.x), cos(worldRot.x), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f );
	Out.pos = mul(mtx, Out.pos);
	Out.normal = mul(mtx, float4(Out.normal, 1.0f)).xyz;

	//Y����]
	mtx = float4x4(
		cos(worldRot.y), 0.0f, sin(worldRot.y), 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		-sin(worldRot.y), 0.0f, cos(worldRot.y), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f );
	Out.pos = mul(mtx, Out.pos);
	Out.normal = mul(mtx, float4(Out.normal, 1.0f)).xyz;

	//Z����]
	mtx = float4x4(
		cos(worldRot.z), -sin(worldRot.z), 0.0f, 0.0f,
		sin(worldRot.z), cos(worldRot.z), 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f );
	Out.pos = mul(mtx, Out.pos);
	Out.normal = mul(mtx, float4(Out.normal, 1.0f)).xyz;

	//���s�ړ�
	mtx = float4x4(
		1.0f, 0.0f, 0.0f, worldPos.x,
		0.0f, 1.0f, 0.0f, worldPos.y,
		0.0f, 0.0f, 1.0f, worldPos.z,
		0.0f, 0.0f, 0.0f, 1.0f );
	Out.pos = mul(mtx, Out.pos);

	//�r���[�ϊ��A�v���W�F�N�V�����ϊ�
	Out.pos = mul(Out.pos, mtxView);
	Out.pos = mul(Out.pos, mtxProj);

	//UV���W�i�[
	Out.uv = uv;

	return Out;
}

/**************************************
*�s�N�Z���V�F�[�_�i�p�X0�p�j ���e�N�X�`���f�B�t���[�Y���g�p����
***************************************/
float4 psMain0(VS_OUT In) : COLOR0
{
	//�e�����̔��˗����v�Z
	float power0 = dot(In.normal, lightDir[0].xyz) * amplifier;
	float power1 = dot(In.normal, lightDir[1].xyz) * amplifier;
	float power2 = dot(In.normal, lightDir[2].xyz) * amplifier;

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
	float power0 = dot(In.normal, lightDir[0].xyz) * amplifier;
	float power1 = dot(In.normal, lightDir[1].xyz) * amplifier;
	float power2 = dot(In.normal, lightDir[2].xyz) * amplifier;

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