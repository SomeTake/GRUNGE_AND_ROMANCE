/*******************************************************************************
* タイトル:		タイトルプログラム
* プログラム名:	Title.cpp
* 作成者:		GP11B341 01 飯塚春輝
* 作成日:		2018/07/26
*******************************************************************************/
#include "Title.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		pD3DTextureTitle = NULL;				// テクスチャへのポインタ
TITLE					TitleWk[TITLE_MAX];						// タイトル構造体

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	TITLE *title = TitleWk;								// タイトルのポインターを初期化

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
		TEXTURE_TITLE,				// ファイルの名前
		&pD3DTextureTitle);			// 読み込むメモリー

	title->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// 座標データを初期化
	title->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// 座標データを初期化
	title->scl = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// 座標データを初期化
	title->col = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// 座標データを初期化
	title->Alpha = 1.0f;
	title->use = true;
	title->Texture = pD3DTextureTitle;								// テクスチャ情報
	D3DXVECTOR2 temp = D3DXVECTOR2(TITLE_SIZE_X, TITLE_SIZE_Y);
	title->Radius = D3DXVec2Length(&temp);							// タイトルの半径を初期化
	title->BaseAngle = atan2f(TITLE_SIZE_Y, TITLE_SIZE_X);			// タイトルの角度を初期化
	title->PatternAnim = 0;											// アニメパターン番号を初期化
	title->CountAnim = 0;											// アニメカウントを初期化
																	// 頂点情報の作成
	MakeVertexTitle();

	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void UninitTitle(void)
{
	if (pD3DTextureTitle != NULL)
	{// テクスチャの開放
		pD3DTextureTitle->Release();
		pD3DTextureTitle = NULL;
	}

}
//=============================================================================
// 更新処理
//=============================================================================
void UpdateTitle(void)
{

}
//=============================================================================
// 描画処理
//=============================================================================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	TITLE *title = TitleWk;				// タイトルのポインターを初期化

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);


	// テクスチャの設定
	pDevice->SetTexture(0, title->Texture);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_TITLE, title->VertexWkTitle, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexTitle(void)
{
	TITLE *title = TitleWk;				// タイトルのポインターを初期化

										// 頂点座標の設定
	title->VertexWkTitle[0].vtx = D3DXVECTOR3(title->pos.x, title->pos.y, 0.0f);
	title->VertexWkTitle[1].vtx = D3DXVECTOR3(title->pos.x + TITLE_SIZE_X, title->pos.y, 0.0f);
	title->VertexWkTitle[2].vtx = D3DXVECTOR3(title->pos.x, title->pos.y + TITLE_SIZE_Y, 0.0f);
	title->VertexWkTitle[3].vtx = D3DXVECTOR3(title->pos.x + TITLE_SIZE_X, title->pos.y + TITLE_SIZE_Y, 0.0f);

	// テクスチャのパースペクティブコレクト用
	title->VertexWkTitle[0].rhw =
	title->VertexWkTitle[1].rhw =
	title->VertexWkTitle[2].rhw =
	title->VertexWkTitle[3].rhw = 1.0f;

	// 反射光の設定
	title->VertexWkTitle[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	title->VertexWkTitle[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	title->VertexWkTitle[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	title->VertexWkTitle[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	title->VertexWkTitle[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	title->VertexWkTitle[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_TITLE, 0.0f);
	title->VertexWkTitle[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_TITLE);
	title->VertexWkTitle[3].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_TITLE, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_TITLE);

	return S_OK;
}

//=============================================================================
// タイトル取得関数
//=============================================================================
TITLE *GetTitle(int no)
{
	return(&TitleWk[no]);
}
