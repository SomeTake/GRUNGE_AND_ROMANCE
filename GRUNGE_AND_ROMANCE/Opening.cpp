/*******************************************************************************
* タイトル:		オープニングプログラム
* プログラム名:	Opening.cpp
* 作成者:		GP11B341 01 飯塚春輝
* 作成日:		2018/07/26
*******************************************************************************/
#include "Opening.h"
#include "Input.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		pD3DTextureOpening = NULL;				// テクスチャへのポインタ
OPENING					OpeningWk[OPENING_MAX];					// オープニング構造体

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitOpening(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	OPENING *opening = OpeningWk;								// オープニングのポインターを初期化

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,							// デバイスへのポインタ
		TEXTURE_OPENING,				// ファイルの名前
		&pD3DTextureOpening);			// 読み込むメモリー

	opening->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// 座標データを初期化
	opening->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// 座標データを初期化
	opening->scl = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// 座標データを初期化
	opening->col = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// 座標データを初期化
	opening->Alpha = 1.0f;
	opening->use = true;
	opening->Texture = pD3DTextureOpening;								// テクスチャ情報
	D3DXVECTOR2 temp = D3DXVECTOR2(OPENING_SIZE_X, OPENING_SIZE_Y);
	opening->Radius = D3DXVec2Length(&temp);							// オープニングの半径を初期化
	opening->BaseAngle = atan2f(OPENING_SIZE_Y, OPENING_SIZE_X);		// オープニングの角度を初期化
	opening->PatternAnim = 0;											// アニメパターン番号を初期化
	opening->CountAnim = 0;												// アニメカウントを初期化
																		// 頂点情報の作成
	MakeVertexOpening();

	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void UninitOpening(void)
{
	if (pD3DTextureOpening != NULL)
	{// テクスチャの開放
		pD3DTextureOpening->Release();
		pD3DTextureOpening = NULL;
	}

}
//=============================================================================
// 更新処理
//=============================================================================
void UpdateOpening(void)
{
	if (GetKeyboardTrigger(DIK_RETURN))
	{// Enter押したら、ステージを切り替える
		SetStage(STAGE_TITLE);
	}
}
//=============================================================================
// 描画処理
//=============================================================================
void DrawOpening(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	OPENING *opening = OpeningWk;				// オープニングのポインターを初期化

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, opening->Texture);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_OPENING, opening->VertexWkOpening, sizeof(VERTEX_2D));


}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexOpening(void)
{
	OPENING *opening = OpeningWk;				// オープニングのポインターを初期化

	// 頂点座標の設定
	opening->VertexWkOpening[0].vtx = D3DXVECTOR3(opening->pos.x, opening->pos.y, 0.0f);
	opening->VertexWkOpening[1].vtx = D3DXVECTOR3(opening->pos.x + OPENING_SIZE_X, opening->pos.y, 0.0f);
	opening->VertexWkOpening[2].vtx = D3DXVECTOR3(opening->pos.x, opening->pos.y + OPENING_SIZE_Y, 0.0f);
	opening->VertexWkOpening[3].vtx = D3DXVECTOR3(opening->pos.x + OPENING_SIZE_X, opening->pos.y + OPENING_SIZE_Y, 0.0f);

	// テクスチャのパースペクティブコレクト用
	opening->VertexWkOpening[0].rhw =
	opening->VertexWkOpening[1].rhw =
	opening->VertexWkOpening[2].rhw =
	opening->VertexWkOpening[3].rhw = 1.0f;

	// 反射光の設定
	opening->VertexWkOpening[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	opening->VertexWkOpening[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	opening->VertexWkOpening[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	opening->VertexWkOpening[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	opening->VertexWkOpening[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	opening->VertexWkOpening[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_OPENING, 0.0f);
	opening->VertexWkOpening[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_OPENING);
	opening->VertexWkOpening[3].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_OPENING, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_OPENING);

	return S_OK;
}

//=============================================================================
// オープニング取得関数
//=============================================================================
OPENING *GetOpening(int no)
{
	return(&OpeningWk[no]);
}
