/*******************************************************************************
* タイトル:		エンディングプログラム
* プログラム名:	Ending.cpp
* 作成者:		GP11B341 01 飯塚春輝
* 作成日:		2018/07/26
*******************************************************************************/
#include "Ending.h"
#include "Input.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		pD3DTextureEnding = NULL;				// テクスチャへのポインタ
ENDING					EndingWk[ENDING_MAX];					// エンディング構造体

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEnding(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENDING *ending = EndingWk;								// エンディングのポインターを初期化

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
		TEXTURE_ENDING,					// ファイルの名前
		&pD3DTextureEnding);			// 読み込むメモリー

	ending->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// 座標データを初期化
	ending->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// 座標データを初期化
	ending->scl = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// 座標データを初期化
	ending->col = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// 座標データを初期化
	ending->Alpha = 1.0f;
	ending->use = true;
	ending->Texture = pD3DTextureEnding;								// テクスチャ情報
	D3DXVECTOR2 temp = D3DXVECTOR2(ENDING_SIZE_X, ENDING_SIZE_Y);
	ending->Radius = D3DXVec2Length(&temp);							// エンディングの半径を初期化
	ending->BaseAngle = atan2f(ENDING_SIZE_Y, ENDING_SIZE_X);		// エンディングの角度を初期化
	ending->PatternAnim = 0;										// アニメパターン番号を初期化
	ending->CountAnim = 0;											// アニメカウントを初期化
																	// 頂点情報の作成
	MakeVertexEnding();

	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void UninitEnding(void)
{
	if (pD3DTextureEnding != NULL)
	{// テクスチャの開放
		pD3DTextureEnding->Release();
		pD3DTextureEnding = NULL;
	}

}
//=============================================================================
// 更新処理
//=============================================================================
void UpdateEnding(void)
{
	if (GetKeyboardTrigger(DIK_RETURN))
	{// Enter押したら、ステージを切り替える
		SetStage(STAGE_OPENING);
	}

}
//=============================================================================
// 描画処理
//=============================================================================
void DrawEnding(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENDING *ending = EndingWk;				// エンディングのポインターを初期化

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);


	// テクスチャの設定
	pDevice->SetTexture(0, ending->Texture);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_ENDING, ending->VertexWkEnding, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexEnding(void)
{
	ENDING *ending = EndingWk;				// エンディングのポインターを初期化

	// 頂点座標の設定
	ending->VertexWkEnding[0].vtx = D3DXVECTOR3(ending->pos.x, ending->pos.y, 0.0f);
	ending->VertexWkEnding[1].vtx = D3DXVECTOR3(ending->pos.x + ENDING_SIZE_X, ending->pos.y, 0.0f);
	ending->VertexWkEnding[2].vtx = D3DXVECTOR3(ending->pos.x, ending->pos.y + ENDING_SIZE_Y, 0.0f);
	ending->VertexWkEnding[3].vtx = D3DXVECTOR3(ending->pos.x + ENDING_SIZE_X, ending->pos.y + ENDING_SIZE_Y, 0.0f);

	// テクスチャのパースペクティブコレクト用
	ending->VertexWkEnding[0].rhw =
	ending->VertexWkEnding[1].rhw =
	ending->VertexWkEnding[2].rhw =
	ending->VertexWkEnding[3].rhw = 1.0f;

	// 反射光の設定
	ending->VertexWkEnding[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	ending->VertexWkEnding[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	ending->VertexWkEnding[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	ending->VertexWkEnding[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	ending->VertexWkEnding[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	ending->VertexWkEnding[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_ENDING, 0.0f);
	ending->VertexWkEnding[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ENDING);
	ending->VertexWkEnding[3].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_ENDING, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ENDING);

	return S_OK;
}

//=============================================================================
// エンディング取得関数
//=============================================================================
ENDING *GetEnding(int no)
{
	return(&EndingWk[no]);
}
