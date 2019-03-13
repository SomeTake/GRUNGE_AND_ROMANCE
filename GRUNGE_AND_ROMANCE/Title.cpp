//====================================================================================================================================================================================
// 概要
// ファイル名：Title.cpp
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
#include "Title.h"
//====================================================================================================================================================================================
// グローバル変数
//====================================================================================================================================================================================
TITLE Title_State[TITLE_MAX];
//====================================================================================================================================================================================
// タイトルの初期化
// 関数名：HRESULT Initialize_Title
// 戻り値：HRESULT
//====================================================================================================================================================================================
HRESULT Initialize_Title(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXVECTOR2 Temporary = { NULL,NULL };			//	テンポラリー
	D3DXIMAGE_INFO Texture_Information[TITLE_MAX];	//	テクスチャ情報
	const char *Texture_File[TITLE_MAX] =			//	テクスチャファイル
	{
		TEXTURE_FILE_TITLE_BACK_GROUND,	//	TITLE_TYPE_BACK_GROUND
		TEXTURE_FILE_TITLE_LOGO,		//	TITLE_TYPE_LOGO
	};

	// ゼロクリア
	for (int i = 0; i < TITLE_MAX; i++)
	{
		for (int j = 0; j < NUM_VERTEX; j++)
		{
			ZeroMemory(&Title_State[i].Vertex[j], sizeof(VERTEX_2D));
		}
	}

	for (int i = 0; i < TITLE_MAX; i++)
	{
		// タイトルの頂点を作成
		Create_Vertex_Title(i);

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
			&Title_State[i].Texture
		);

		// タイトルの初期化
		switch (i)
		{
		case TITLE_TYPE_BACK_GROUND:
			Temporary = D3DXVECTOR2(TITLE_TEXTURE_SIZE_X_000 / 2, TITLE_TEXTURE_SIZE_Y_000 / 2);
			Title_State[i].Position = D3DXVECTOR3(SCREEN_WIDTH - (TITLE_TEXTURE_SIZE_X_000 / 2), SCREEN_HEIGHT / 2, 0.0f);
			Title_State[i].Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			Title_State[i].Radius = D3DXVec2Length(&Temporary);
			Title_State[i].Angle = atan2f(TITLE_TEXTURE_SIZE_Y_000, TITLE_TEXTURE_SIZE_X_000);
			continue;
			break;
		case TITLE_TYPE_LOGO:
			Temporary = D3DXVECTOR2(TITLE_TEXTURE_SIZE_X_000 / 2, TITLE_TEXTURE_SIZE_Y_000 / 2);
			Title_State[i].Position = D3DXVECTOR3(SCREEN_WIDTH - (TITLE_TEXTURE_SIZE_X_000 / 2), SCREEN_HEIGHT / 2, 0.0f);
			Title_State[i].Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			Title_State[i].Radius = D3DXVec2Length(&Temporary);
			Title_State[i].Angle = atan2f(TITLE_TEXTURE_SIZE_Y_000, TITLE_TEXTURE_SIZE_X_000);
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
// タイトルの解放
// 関数名：void Release_Title
// 戻り値：void
//====================================================================================================================================================================================
void Release_Title(void)
{
	for (int i = 0; i < TITLE_MAX; i++)
	{
		SAFE_RELEASE(Title_State[i].Texture);
	}

	return;
}

//====================================================================================================================================================================================
// タイトルの更新
// 関数名：void Update_Title
// 戻り値：void
//====================================================================================================================================================================================
void Update_Title(void)
{
	// タイトルの頂点情報を設定
	for (int i = 0; i < TITLE_MAX; i++)
	{
		Set_Vertex_Title(i);
	}

	return;
}

//====================================================================================================================================================================================
// タイトル( 押下待ち )の描画
// 関数名：void Draw_Title
// 戻り値：void
//====================================================================================================================================================================================
void Draw_Title(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < TITLE_MAX; i++)
	{
		// テクスチャの設定
		pDevice->SetTexture(0, Title_State[i].Texture);

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, Title_State[i].Vertex, sizeof(VERTEX_2D));
	}

	return;
}

//====================================================================================================================================================================================
// タイトルの頂点を作成
// 関数名：HRESULT Create_Vertex_Title
// 戻り値：HRESULT
// 引数 1：int
//====================================================================================================================================================================================
HRESULT Create_Vertex_Title(int Title_Index)
{
	// 頂点座標の設定
	Set_Vertex_Title(Title_Index);

	// RHWの設定
	Title_State[Title_Index].Vertex[0].rhw = 1.0f;
	Title_State[Title_Index].Vertex[1].rhw = 1.0f;
	Title_State[Title_Index].Vertex[2].rhw = 1.0f;
	Title_State[Title_Index].Vertex[3].rhw = 1.0f;

	// 反射光の設定( 頂点カラー )
	Title_State[Title_Index].Vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	Title_State[Title_Index].Vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	Title_State[Title_Index].Vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	Title_State[Title_Index].Vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	Set_Texture_Title(Title_Index);

	// 正常終了
	return S_OK;
}

//====================================================================================================================================================================================
// タイトルの頂点座標を設定
// 関数名：void Set_Vertex_Title
// 戻り値：void
// 引数 1：int
//====================================================================================================================================================================================
void Set_Vertex_Title(int Title_Index)
{	
	// --------------------------------------------------	Vertex[0]	--------------------------------------------------
	Title_State[Title_Index].Vertex[0].vtx.x = (Title_State[Title_Index].Position.x - cosf(Title_State[Title_Index].Angle + Title_State[Title_Index].Rotation.z) * Title_State[Title_Index].Radius) - 0.5f;
	Title_State[Title_Index].Vertex[0].vtx.y = (Title_State[Title_Index].Position.y - sinf(Title_State[Title_Index].Angle + Title_State[Title_Index].Rotation.z) * Title_State[Title_Index].Radius) - 0.5f;
	// --------------------------------------------------	Vertex[1]	--------------------------------------------------
	Title_State[Title_Index].Vertex[1].vtx.x = (Title_State[Title_Index].Position.x + cosf(Title_State[Title_Index].Angle - Title_State[Title_Index].Rotation.z) * Title_State[Title_Index].Radius) - 0.5f;
	Title_State[Title_Index].Vertex[1].vtx.y = (Title_State[Title_Index].Position.y - sinf(Title_State[Title_Index].Angle - Title_State[Title_Index].Rotation.z) * Title_State[Title_Index].Radius) - 0.5f;
	// --------------------------------------------------	Vertex[2]	--------------------------------------------------
	Title_State[Title_Index].Vertex[2].vtx.x = (Title_State[Title_Index].Position.x - cosf(Title_State[Title_Index].Angle - Title_State[Title_Index].Rotation.z) * Title_State[Title_Index].Radius) - 0.5f;
	Title_State[Title_Index].Vertex[2].vtx.y = (Title_State[Title_Index].Position.y + sinf(Title_State[Title_Index].Angle - Title_State[Title_Index].Rotation.z) * Title_State[Title_Index].Radius) - 0.5f;
	// --------------------------------------------------	Vertex[3]	--------------------------------------------------
	Title_State[Title_Index].Vertex[3].vtx.x = (Title_State[Title_Index].Position.x + cosf(Title_State[Title_Index].Angle + Title_State[Title_Index].Rotation.z) * Title_State[Title_Index].Radius) - 0.5f;
	Title_State[Title_Index].Vertex[3].vtx.y = (Title_State[Title_Index].Position.y + sinf(Title_State[Title_Index].Angle + Title_State[Title_Index].Rotation.z) * Title_State[Title_Index].Radius) - 0.5f;

	return;
}

//====================================================================================================================================================================================
// タイトルのテクスチャ座標を設定
// 関数名：void Set_Texture_Title
// 戻り値：void
// 引数 1：int
//====================================================================================================================================================================================
void Set_Texture_Title(int Title_Index)
{
	// 変数宣言：初期化
	int Texture_Split_U = 0 % TITLE_TEXTURE_PATTERN_DIVIDE_X;	//	テクスチャ分割数( U )
	int Texture_Split_V = 0 / TITLE_TEXTURE_PATTERN_DIVIDE_X;	//	テクスチャ分割数( V )
	float Size_U = 1.0f / TITLE_TEXTURE_PATTERN_DIVIDE_X;		//	テクスチャの１分割の横幅( X )
	float Size_V = 1.0f / TITLE_TEXTURE_PATTERN_DIVIDE_Y;		//	テクスチャの１分割の縦幅( Y )

	// テクスチャ座標の設定
	Title_State[Title_Index].Vertex[0].tex = D3DXVECTOR2((float)(Texture_Split_U)* Size_U, (float)(Texture_Split_V)* Size_V);					//	テクスチャ座標の左上を設定
	Title_State[Title_Index].Vertex[1].tex = D3DXVECTOR2((float)(Texture_Split_U)* Size_U + Size_U, (float)(Texture_Split_V)* Size_V);			//	テクスチャ座標の右上を設定
	Title_State[Title_Index].Vertex[2].tex = D3DXVECTOR2((float)(Texture_Split_U)* Size_U, (float)(Texture_Split_V)* Size_V + Size_V);			//	テクスチャ座標の左下を設定
	Title_State[Title_Index].Vertex[3].tex = D3DXVECTOR2((float)(Texture_Split_U)* Size_U + Size_U, (float)(Texture_Split_V)* Size_V + Size_V);	//	テクスチャ座標の右下を設定

	return;
}

//====================================================================================================================================================================================
// タイトルの取得
// 関数名：TITLE *Get_Title
// 戻り値：TITLE
// 引数 1：int
//====================================================================================================================================================================================
TITLE *Get_Title(int Title_Index)
{
	return &Title_State[Title_Index];
}