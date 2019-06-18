//=====================================
//
//�N���X�u���[�V�F�[�_[CrossBlur.fx]
//Author:GP12B332 21 ���ԗY��
//
//=====================================

/***************************************
�O���[�o���ϐ�
***************************************/
float texelU[2];			//X�����ׂ̗̃e�N�Z���̈ʒu
float texelV[2];			//Y�����ׂ̗̃e�N�Z���̈ʒu

sampler s0 : register(s0);	//�e�N�X�`���T���v��

/*********************************************
���_�V�F�[�_�o�͍\����
*********************************************/
struct VS_OUTPUT
{
	float4 pos : POSITION;
	float2 tex : TEXCOORD0;
};

/*********************************************
���_�V�F�[�_
*********************************************/
VS_OUTPUT VS(
	float4 pos : POSITION,
	float2 tex : TEXCOORD0
) {
	VS_OUTPUT Out;

	Out.pos = pos;
	Out.tex = tex;

	return Out;
}

/*********************************************
�s�N�Z���J���[�擾����
*********************************************/
float4 GetPixelColor(float2 texel[3])
{
	float4 p0 = tex2D(s0, texel[0]) * 0.5f;
	float4 p1 = tex2D(s0, texel[1]) * 0.3f;
	float4 p2 = tex2D(s0, texel[2]) * 0.2f;

	return p0 + p1 + p2;
}

/********************************************
�s�N�Z���V�F�[�_�i�E��j
*********************************************/
float4 PS1(VS_OUTPUT In) : COLOR0
{
	float2 texel[3];

	texel[0] = In.tex;
	texel[1] = In.tex + float2(texelU[0], -texelV[0]);
	texel[2] = In.tex + float2(texelU[1], -texelV[1]);

	return GetPixelColor(texel);
}

/********************************************
�s�N�Z���V�F�[�_�i�E���j
*********************************************/
float4 PS2(VS_OUTPUT In) : COLOR0
{
	float2 texel[3];

	texel[0] = In.tex;
	texel[1] = In.tex + float2(texelU[0], texelV[0]);
	texel[2] = In.tex + float2(texelU[1], texelV[1]);
	
	return GetPixelColor(texel);
}

/********************************************
�s�N�Z���V�F�[�_�i����j
*********************************************/
float4 PS3(VS_OUTPUT In) : COLOR0
{
	float2 texel[3];

	texel[0] = In.tex;
	texel[1] = In.tex + float2(-texelU[0], -texelV[0]);
	texel[2] = In.tex + float2(-texelU[1], -texelV[1]);

	return GetPixelColor(texel);
}

/********************************************
�s�N�Z���V�F�[�_�i�����j
*********************************************/
float4 PS4(VS_OUTPUT In) : COLOR0
{
	float2 texel[3];

	texel[0] = In.tex;
	texel[1] = In.tex + float2(-texelU[0], texelV[0]);
	texel[2] = In.tex + float2(-texelU[1], texelV[1]);

	return GetPixelColor(texel);
}

/********************************************
�s�N�Z���V�F�[�_�o�͍\���́i1�p�X�p�j
*********************************************/
struct PS_OUTPUT {
	float4 color0 : COLOR0;
	float4 color1 : COLOR1;
	float4 color2 : COLOR2;
	float4 color3 : COLOR3;
};

/********************************************
�s�N�Z���V�F�[�_�i�P�p�X��4�����Ƀu���[�j
*********************************************/
float4 PS5(VS_OUTPUT In) : COLOR0
{
	float2 texel[3];
	float4 color;
	const float magni = 0.6f;	//�������i4�����̌��ʂ����̂܂܍�������ƖO�a����̂Łj

	texel[0] = In.tex;
	texel[1] = In.tex + float2(texelU[0], -texelV[0]);
	texel[2] = In.tex + float2(texelU[1], -texelV[1]);

	color = GetPixelColor(texel) * magni;

	texel[1] = In.tex + float2(texelU[0], texelV[0]);
	texel[2] = In.tex + float2(texelU[1], texelV[1]);

	color += GetPixelColor(texel) * magni;

	texel[1] = In.tex + float2(-texelU[0], -texelV[0]);
	texel[2] = In.tex + float2(-texelU[1], -texelV[1]);

	color += GetPixelColor(texel) * magni;

	texel[1] = In.tex + float2(-texelU[0], texelV[0]);
	texel[2] = In.tex + float2(-texelU[1], texelV[1]);

	color += GetPixelColor(texel) * magni;

	return color;
}

/********************************************
�e�N�j�b�N
*********************************************/
technique tech
{
	pass P0
	{
		VertexShader = compile vs_2_0 VS();
		PixelShader = compile ps_2_0 PS1();
	}

	pass P1
	{
		VertexShader = compile vs_2_0 VS();
		PixelShader = compile ps_2_0 PS2();
	}

	pass P2
	{
		VertexShader = compile vs_2_0 VS();
		PixelShader = compile ps_2_0 PS3();
	}

	pass P3
	{
		VertexShader = compile vs_2_0 VS();
		PixelShader = compile ps_2_0 PS4();
	}

	pass P4
	{
		VertexShader = compile vs_2_0 VS();
		PixelShader = compile ps_2_0 PS5();
	}
};