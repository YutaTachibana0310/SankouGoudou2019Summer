//=====================================
//
//モデルインスタンシングシェーダ[ModelInstancing.fx]
//Author:GP12B332 21 立花雄太
//
//=====================================

/**************************************
*グローバル変数
***************************************/
float4x4 mtxView;				//ビュー行列
float4x4 mtxProj;				//プロジェクション行列
float4 matDiffuse;				//マテリアルディフューズ
float4 matAmbient;				//マテリアルアンビエント

float4 lightDiffuse[3];			//ライトディフューズ配列
float4 lightAmbient[3];			//ライトアンビエント配列
float4 lightDir[3];				//ライト方向配列

/**************************************
*テクスチャサンプラー
***************************************/
sampler s0 : register(s0);

/**************************************
*頂点シェーダ出力構造体
***************************************/
struct VS_OUT {
	float4 pos	: POSITION;
	float2 uv	: TEXCOORD0;
	float3 normal	: TEXCOORD1;
};

/**************************************
*頂点シェーダ
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

	////スケール計算
	Out.pos.x = Out.pos.x * worldScl.x;
	Out.pos.y = Out.pos.y * worldScl.y;
	Out.pos.z = Out.pos.z * worldScl.z;

	//回転計算
	float4 tmpPos = Out.pos;
	Out.pos.y = tmpPos.y * cos(worldRot.x) - tmpPos.z * sin(worldRot.x);
	Out.pos.z = tmpPos.y * sin(worldRot.x) + tmpPos.z * cos(worldRot.x);

	tmpPos = Out.pos;
	Out.pos.x = tmpPos.x * cos(worldRot.y) + tmpPos.z * sin(worldRot.y);
	Out.pos.z = tmpPos.x * -sin(worldRot.y) + tmpPos.z * cos(worldRot.y);

	tmpPos = Out.pos;
	Out.pos.x = tmpPos.x * cos(worldRot.z) - tmpPos.y * sin(worldRot.z);
	Out.pos.y = tmpPos.x * sin(worldRot.z) + tmpPos.y * cos(worldRot.z);

	////移動計算
	Out.pos = Out.pos + float4(worldPos, 0.0f);

	//ビュー変換、プロジェクション変換
	Out.pos = mul(Out.pos, mtxView);
	Out.pos = mul(Out.pos, mtxProj);

	//UV座標格納
	Out.uv = uv;

	//法線計算
	Out.normal = normal;
	Out.normal = mul(float4(Out.normal, 0.0f), mtxView).xyz;
	Out.normal = mul(float4(Out.normal, 0.0f), mtxProj).xyz;

	return Out;
}

/**************************************
*ピクセルシェーダ（パス0用） ※テクスチャディフューズを使用する
***************************************/
float4 psMain0(VS_OUT In) : COLOR0
{
	//各光源の反射率を計算
	float power0 = dot(In.normal, lightDir[0].xyz);
	float power1 = dot(In.normal, lightDir[1].xyz);
	float power2 = dot(In.normal, lightDir[2].xyz);

	//テクスチャから色を取得
	float4 RC = tex2D(s0, In.uv);

	//並行光源の計算
	float4 color = RC * max(lightDiffuse[0] * power0, 0.0f);
	color += RC * max(lightDiffuse[1] * power1, 0.0f);
	color += RC * max(lightDiffuse[2] * power2, 0.0f);

	//環境光の計算
	color += lightAmbient[0] * matAmbient;
	color += lightAmbient[1] * matAmbient;
	color += lightAmbient[2] * matAmbient;

	//不透明に設定
	color.a = 1.0f;

	return  color;
}

/**************************************
*ピクセルシェーダ（パス1用） ※マテリアルディフューズを使用する
***************************************/
float4 psMain1(VS_OUT In) : COLOR0
{
	//各光源の反射率を計算
	float power0 = dot(In.normal, lightDir[0].xyz);
	float power1 = dot(In.normal, lightDir[1].xyz);
	float power2 = dot(In.normal, lightDir[2].xyz);

	//マテリアルディフューズを取得
	float4 RC = matDiffuse;

	//並行光源の計算
	float4 color = RC * max(lightDiffuse[0] * power0, 0.0f);
	color += RC * max(lightDiffuse[1] * power1, 0.0f);
	color += RC * max(lightDiffuse[2] * power2, 0.0f);

	//環境光の計算
	color += lightAmbient[0] * matAmbient;
	color += lightAmbient[1] * matAmbient;
	color += lightAmbient[2] * matAmbient;

	//不透明に設定
	color.a = 1.0f;

	return  color;
}

/**************************************
*テクニック
***************************************/
technique tech
{
	//テクスチャディフューズ使用版
	pass p0 {
		VertexShader = compile vs_2_0 vsMain();
		PixelShader = compile ps_2_0 psMain0();
	}

	//マテリアルディフューズ使用版
	pass p1 {
		VertexShader = compile vs_2_0 vsMain();
		PixelShader = compile ps_2_0 psMain1();
	}
}