//====================================================================================================================================================================================
// 概要
// ファイル名：Ending.cpp
// コーディングフォント：Ricty Diminished( 16サイズ )
// 作成者：HAL東京 GP-11B-341 07 亀岡竣介
// 作成日：2018/12/10
//====================================================================================================================================================================================

//====================================================================================================================================================================================
// インクルード
//====================================================================================================================================================================================
#include "Main.h"
#include "Input.h"
#include "Sound.h"
#include "Ending.h"
//====================================================================================================================================================================================
// グローバル変数
//====================================================================================================================================================================================
ENDING Ending_State[ENDING_MAX];
//====================================================================================================================================================================================
// エンディングの初期化
// 関数名：HRESULT Initialize_Ending
// 戻り値：HRESULT
//====================================================================================================================================================================================
HRESULT Initialize_Ending(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXVECTOR2 Temporary = { NULL,NULL };			//	テンポラリー
	D3DXIMAGE_INFO Texture_Information[ENDING_MAX];	//	テクスチャ情報
	const char *Texture_File[ENDING_MAX] =			//	テクスチャファイル
	{
		TEXTURE_FILE_ENDING,	//	ENDING_TYPE_000
	};

	// ゼロクリア
	for (int i = 0; i < ENDING_MAX; i++)
	{
		for (int j = 0; j < NUM_VERTEX; j++)
		{
			ZeroMemory(&Ending_State[i].Vertex[j], sizeof(VERTEX_2D));
		}
	}

	for (int i = 0; i < ENDING_MAX; i++)
	{
		// エンディングの頂点を作成
		Create_Vertex_Ending(i);

		// テクスチャ情報の取得
		D3DXGetImageInfoFromFile(Texture_File[i], &Texture_Information[i]);

		// テクスチャの読み込み
		D3DXCreateTextureFromFileEx
		(
			pDevice,
			Texture_File[i],
			Texture_Information[i].Width,
			Texture_Information[i].Height,
			Texture_Information[i].MipLevels,
			0,
			Texture_Information[i].Format,
			D3DPOOL_MANAGED,
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			0,
			&Texture_Information[i],
			NULL,
			&Ending_State[i].Texture
		);

		// エンディングの初期化
		switch (i)
		{
		case ENDING_TYPE_000:
			Temporary = D3DXVECTOR2(ENDING_TEXTURE_SIZE_X_000 / 2, ENDING_TEXTURE_SIZE_Y_000 / 2);
			Ending_State[i].Position = D3DXVECTOR3(SCREEN_WIDTH - (ENDING_TEXTURE_SIZE_X_000 / 2), SCREEN_HEIGHT / 2, 0.0f);
			Ending_State[i].Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			Ending_State[i].Radius = D3DXVec2Length(&Temporary);
			Ending_State[i].Angle = atan2f(ENDING_TEXTURE_SIZE_Y_000, ENDING_TEXTURE_SIZE_X_000);
			continue;
			break;
		default:
			continue;
			break;
		}
	}

	// 正常終了
	return S_OK;
}

//====================================================================================================================================================================================
// エンディングの解放
// 関数名：void Release_Ending
// 戻り値：void
//====================================================================================================================================================================================
void Release_Ending(void)
{
	for (int i = 0; i < ENDING_MAX; i++)
	{
		SAFE_RELEASE(Ending_State[i].Texture);
	}

	return;
}

//====================================================================================================================================================================================
// エンディングの更新
// 関数名：void Update_Ending
// 戻り値：void
//====================================================================================================================================================================================
void Update_Ending(void)
{
	// エンディングの頂点情報を設定
	for (int i = 0; i < ENDING_MAX; i++)
	{
		Set_Vertex_Ending(i);
	}

	return;
}

//====================================================================================================================================================================================
// エンディング( 押下待ち )の描画
// 関数名：void Draw_Ending
// 戻り値：void
//====================================================================================================================================================================================
void Draw_Ending(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < ENDING_MAX; i++)
	{
		// テクスチャの設定
		pDevice->SetTexture(0, Ending_State[i].Texture);

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, Ending_State[i].Vertex, sizeof(VERTEX_2D));
	}

	return;
}

//====================================================================================================================================================================================
// エンディングの頂点を作成
// 関数名：HRESULT Create_Vertex_Ending
// 戻り値：HRESULT
// 引数 1：int
//====================================================================================================================================================================================
HRESULT Create_Vertex_Ending(int Ending_Index)
{
	// 頂点座標の設定
	Set_Vertex_Ending(Ending_Index);

	// RHWの設定
	Ending_State[Ending_Index].Vertex[0].rhw = 1.0f;
	Ending_State[Ending_Index].Vertex[1].rhw = 1.0f;
	Ending_State[Ending_Index].Vertex[2].rhw = 1.0f;
	Ending_State[Ending_Index].Vertex[3].rhw = 1.0f;

	// 反射光の設定( 頂点カラー )
	Ending_State[Ending_Index].Vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	Ending_State[Ending_Index].Vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	Ending_State[Ending_Index].Vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	Ending_State[Ending_Index].Vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	Set_Texture_Ending(Ending_Index);

	// 正常終了
	return S_OK;
}

//====================================================================================================================================================================================
// エンディングの頂点座標を設定
// 関数名：void Set_Vertex_Ending
// 戻り値：void
// 引数 1：int
//====================================================================================================================================================================================
void Set_Vertex_Ending(int Ending_Index)
{	
	// --------------------------------------------------	Vertex[0]	--------------------------------------------------
	Ending_State[Ending_Index].Vertex[0].vtx.x = (Ending_State[Ending_Index].Position.x - cosf(Ending_State[Ending_Index].Angle + Ending_State[Ending_Index].Rotation.z) * Ending_State[Ending_Index].Radius) - 0.5f;
	Ending_State[Ending_Index].Vertex[0].vtx.y = (Ending_State[Ending_Index].Position.y - sinf(Ending_State[Ending_Index].Angle + Ending_State[Ending_Index].Rotation.z) * Ending_State[Ending_Index].Radius) - 0.5f;
	// --------------------------------------------------	Vertex[1]	--------------------------------------------------
	Ending_State[Ending_Index].Vertex[1].vtx.x = (Ending_State[Ending_Index].Position.x + cosf(Ending_State[Ending_Index].Angle - Ending_State[Ending_Index].Rotation.z) * Ending_State[Ending_Index].Radius) - 0.5f;
	Ending_State[Ending_Index].Vertex[1].vtx.y = (Ending_State[Ending_Index].Position.y - sinf(Ending_State[Ending_Index].Angle - Ending_State[Ending_Index].Rotation.z) * Ending_State[Ending_Index].Radius) - 0.5f;
	// --------------------------------------------------	Vertex[2]	--------------------------------------------------
	Ending_State[Ending_Index].Vertex[2].vtx.x = (Ending_State[Ending_Index].Position.x - cosf(Ending_State[Ending_Index].Angle - Ending_State[Ending_Index].Rotation.z) * Ending_State[Ending_Index].Radius) - 0.5f;
	Ending_State[Ending_Index].Vertex[2].vtx.y = (Ending_State[Ending_Index].Position.y + sinf(Ending_State[Ending_Index].Angle - Ending_State[Ending_Index].Rotation.z) * Ending_State[Ending_Index].Radius) - 0.5f;
	// --------------------------------------------------	Vertex[3]	--------------------------------------------------
	Ending_State[Ending_Index].Vertex[3].vtx.x = (Ending_State[Ending_Index].Position.x + cosf(Ending_State[Ending_Index].Angle + Ending_State[Ending_Index].Rotation.z) * Ending_State[Ending_Index].Radius) - 0.5f;
	Ending_State[Ending_Index].Vertex[3].vtx.y = (Ending_State[Ending_Index].Position.y + sinf(Ending_State[Ending_Index].Angle + Ending_State[Ending_Index].Rotation.z) * Ending_State[Ending_Index].Radius) - 0.5f;

	return;
}

//====================================================================================================================================================================================
// エンディングのテクスチャ座標を設定
// 関数名：void Set_Texture_Ending
// 戻り値：void
// 引数 1：int
//====================================================================================================================================================================================
void Set_Texture_Ending(int Ending_Index)
{
	// 変数宣言：初期化
	int Texture_Split_U = 0 % ENDING_TEXTURE_PATTERN_DIVIDE_X;	//	テクスチャ分割数( U )
	int Texture_Split_V = 0 / ENDING_TEXTURE_PATTERN_DIVIDE_X;	//	テクスチャ分割数( V )
	float Size_U = 1.0f / ENDING_TEXTURE_PATTERN_DIVIDE_X;		//	テクスチャの１分割の横幅( X )
	float Size_V = 1.0f / ENDING_TEXTURE_PATTERN_DIVIDE_Y;		//	テクスチャの１分割の縦幅( Y )

	// テクスチャ座標の設定
	Ending_State[Ending_Index].Vertex[0].tex = D3DXVECTOR2((float)(Texture_Split_U)* Size_U, (float)(Texture_Split_V)* Size_V);					//	テクスチャ座標の左上を設定
	Ending_State[Ending_Index].Vertex[1].tex = D3DXVECTOR2((float)(Texture_Split_U)* Size_U + Size_U, (float)(Texture_Split_V)* Size_V);			//	テクスチャ座標の右上を設定
	Ending_State[Ending_Index].Vertex[2].tex = D3DXVECTOR2((float)(Texture_Split_U)* Size_U, (float)(Texture_Split_V)* Size_V + Size_V);			//	テクスチャ座標の左下を設定
	Ending_State[Ending_Index].Vertex[3].tex = D3DXVECTOR2((float)(Texture_Split_U)* Size_U + Size_U, (float)(Texture_Split_V)* Size_V + Size_V);	//	テクスチャ座標の右下を設定

	return;
}

//====================================================================================================================================================================================
// エンディングの取得
// 関数名：ENDING *Get_Ending
// 戻り値：ENDING
// 引数 1：int
//====================================================================================================================================================================================
ENDING *Get_Ending(int Ending_Index)
{
	return &Ending_State[Ending_Index];
}