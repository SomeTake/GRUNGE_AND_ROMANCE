/*******************************************************************************
* タイトル:		ゲージプログラム
* プログラム名:	Gauge.cpp
* 作成者:		GP11B341 01 飯塚春輝
* 作成日:		2018/07/26
*******************************************************************************/
#include "Main.h"
#include "Input.h"
#include "Gauge.h"
#include "Player.h"
#include "Onna.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureGauge = NULL;		// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureGauge2 = NULL;		// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureGauge3 = NULL;		// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureGauge4 = NULL;		// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureGauge5 = NULL;		// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureGauge6 = NULL;		// テクスチャへのポインタ

GAUGE						gaugeWk[GAUGE_MAX];				// gauge構造体
GAUGE2						gaugeWk2[GAUGE2_MAX];			// gauge2構造体
GAUGE3						gaugeWk3[GAUGE3_MAX];			// gauge3構造体
GAUGE4						gaugeWk4[GAUGE4_MAX];			// gauge4構造体
GAUGE5						gaugeWk5[GAUGE5_MAX];			// gauge5構造体
GAUGE6						gaugeWk6[GAUGE6_MAX];			// gauge6構造体

int						g_nAlpha;							// アルファテストの閾値

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitGauge(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	GAUGE *gauge = gaugeWk;							// gaugeのポインターを初期化
	GAUGE2 *gauge2 = gaugeWk2;						// gauge2のポインターを初期化
	GAUGE3 *gauge3 = gaugeWk3;						// gauge3のポインターを初期化
	GAUGE4 *gauge4 = gaugeWk4;						// gauge4のポインターを初期化
	GAUGE5 *gauge5 = gaugeWk5;						// gauge5のポインターを初期化
	GAUGE6 *gauge6 = gaugeWk6;						// gauge6のポインターを初期化

	// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
			TEXTURE_GAUGE,						// ファイルの名前
			&g_pD3DTextureGauge);				// 読み込むメモリー
	}
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
			TEXTURE_GAUGE2,						// ファイルの名前
			&g_pD3DTextureGauge2);				// 読み込むメモリー
	}
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
			TEXTURE_GAUGE3,						// ファイルの名前
			&g_pD3DTextureGauge3);				// 読み込むメモリー
	}
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
			TEXTURE_GAUGE4,						// ファイルの名前
			&g_pD3DTextureGauge4);				// 読み込むメモリー
	}
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
			TEXTURE_GAUGE5,						// ファイルの名前
			&g_pD3DTextureGauge5);				// 読み込むメモリー
	}
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
			TEXTURE_GAUGE6,						// ファイルの名前
			&g_pD3DTextureGauge6);				// 読み込むメモリー
	}

	// gaugeの初期化処理
	for (int i = 0; i < GAUGE_MAX; i++, gauge++)
	{
		gauge->use = true;												// 使用
		gauge->pos = D3DXVECTOR3(-400.0f, 30.0f, 0.0f);					// 座標データを初期化
		gauge->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// 回転データを初期化

		gauge->g_pD3DTexture = g_pD3DTextureGauge;						// テクスチャ情報
		MakeVertexGauge();												// 頂点情報の作成
	}
	// gauge2の初期化処理
	for (int i = 0; i < GAUGE2_MAX; i++, gauge2++)
	{
		gauge2->use = true;												// 使用
		gauge2->pos = D3DXVECTOR3(-400.0f, 70.0f, 0.0f);				// 座標データを初期化
		gauge2->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// 回転データを初期化
		gauge2->g_pD3DTexture2 = g_pD3DTextureGauge2;					// テクスチャ情報
		MakeVertexGauge();												// 頂点情報の作成
	}
	// gauge3の初期化処理
	for (int i = 0; i < GAUGE3_MAX; i++, gauge3++)
	{
		gauge3->use = true;												// 使用
		gauge3->pos = D3DXVECTOR3(-400.0f, 30.0f, 0.0f);				// 座標データを初期化
		gauge3->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// 回転データを初期化

		gauge3->g_pD3DTexture3 = g_pD3DTextureGauge3;					// テクスチャ情報
		MakeVertexGauge();												// 頂点情報の作成
	}
	// gauge4の初期化処理
	for (int i = 0; i < GAUGE4_MAX; i++, gauge4++)
	{
		gauge4->use = true;												// 使用
		gauge4->pos = D3DXVECTOR3(-400.0f, 70.0f, 0.0f);				// 座標データを初期化
		gauge4->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// 回転データを初期化
		gauge4->g_pD3DTexture4 = g_pD3DTextureGauge4;					// テクスチャ情報
		MakeVertexGauge();												// 頂点情報の作成
	}
	// gauge5の初期化処理
	for (int i = 0; i < GAUGE5_MAX; i++, gauge5++)
	{
		gauge5->use = true;												// 使用
		gauge5->pos = D3DXVECTOR3(-400.0f, 70.0f, 0.0f);				// 座標データを初期化
		gauge5->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// 回転データを初期化
		gauge5->g_pD3DTexture5 = g_pD3DTextureGauge5;					// テクスチャ情報
		MakeVertexGauge();												// 頂点情報の作成
	}
	// gauge6の初期化処理
	for (int i = 0; i < GAUGE6_MAX; i++, gauge6++)
	{
		gauge6->use = true;												// 使用
		gauge6->pos = D3DXVECTOR3(-400.0f, 70.0f, 0.0f);				// 座標データを初期化
		gauge6->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// 回転データを初期化
		gauge6->g_pD3DTexture6 = g_pD3DTextureGauge6;					// テクスチャ情報
		MakeVertexGauge();												// 頂点情報の作成
	}

	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void UninitGauge(void)
{
	if (g_pD3DTextureGauge != NULL)
	{// テクスチャの開放
		g_pD3DTextureGauge->Release();
		g_pD3DTextureGauge = NULL;
	}
	if (g_pD3DTextureGauge2 != NULL)
	{// テクスチャの開放
		g_pD3DTextureGauge2->Release();
		g_pD3DTextureGauge2 = NULL;
	}
	if (g_pD3DTextureGauge3 != NULL)
	{// テクスチャの開放
		g_pD3DTextureGauge3->Release();
		g_pD3DTextureGauge3 = NULL;
	}
	if (g_pD3DTextureGauge4 != NULL)
	{// テクスチャの開放
		g_pD3DTextureGauge4->Release();
		g_pD3DTextureGauge4 = NULL;
	}
	if (g_pD3DTextureGauge5 != NULL)
	{// テクスチャの開放
		g_pD3DTextureGauge5->Release();
		g_pD3DTextureGauge5 = NULL;
	}
	if (g_pD3DTextureGauge6 != NULL)
	{// テクスチャの開放
		g_pD3DTextureGauge6->Release();
		g_pD3DTextureGauge6 = NULL;
	}

}
//=============================================================================
// 更新処理
//=============================================================================
void UpdateGauge(void)
{
	GAUGE *gauge = gaugeWk;							// gaugeのポインターを初期化
	GAUGE2 *gauge2 = gaugeWk2;						// gauge2のポインターを初期化
	GAUGE3 *gauge3 = gaugeWk3;						// gauge3のポインターを初期化
	GAUGE4 *gauge4 = gaugeWk4;						// gauge4のポインターを初期化
	GAUGE5 *gauge5 = gaugeWk5;						// gauge5のポインターを初期化
	GAUGE6 *gauge6 = gaugeWk6;						// gauge6のポインターを初期化

		gauge->pos.x +=4.0f;
		gauge2->pos.x += 4.0f;
		gauge5->pos.x += 4.0f;

		if (gauge->pos.x >= 0.0f)
		{
			gauge->pos.x = 0;
			gauge2->pos.x = 0;
			gauge5->pos.x = 0;
		}

		gauge3->pos.x += 4.0f;
		gauge4->pos.x += 4.0f;
		gauge6->pos.x += 4.0f;

		if (gauge3->pos.x >= 210.0f)
		{
			gauge3->pos.x = 210;
			gauge4->pos.x = 210;
			gauge6->pos.x = 210;
		}

		SetVertexGauge();
		SetTextuerGauge();


}
//=============================================================================
// 描画処理
//=============================================================================
void DrawGauge(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	GAUGE *gauge = gaugeWk;							// gaugeのポインターを初期化
	GAUGE2 *gauge2 = gaugeWk2;						// gauge2のポインターを初期化
	GAUGE3 *gauge3 = gaugeWk3;						// gauge3のポインターを初期化
	GAUGE4 *gauge4 = gaugeWk4;						// gauge4のポインターを初期化
	GAUGE5 *gauge5 = gaugeWk5;						// gauge5のポインターを初期化
	GAUGE6 *gauge6 = gaugeWk6;						// gauge6のポインターを初期化

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, g_nAlpha);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureGauge5);

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_GAUGE5, gauge5->vertexWk5, sizeof(VERTEX_2D));


		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureGauge);

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_GAUGE, gauge->vertexWk, sizeof(VERTEX_2D));


		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureGauge2);

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_GAUGE2, gauge2->vertexWk2, sizeof(VERTEX_2D));


		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureGauge6);

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_GAUGE6, gauge6->vertexWk6, sizeof(VERTEX_2D));


		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureGauge3);

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_GAUGE3, gauge3->vertexWk3, sizeof(VERTEX_2D));


		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureGauge4);

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_GAUGE4, gauge4->vertexWk4, sizeof(VERTEX_2D));


}
//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexGauge(void)
{
	GAUGE *gauge = gaugeWk;					// gaugeのポインターを初期化
	GAUGE2 *gauge2 = gaugeWk2;				// gauge2のポインターを初期化
	GAUGE3 *gauge3 = gaugeWk3;				// gauge3のポインターを初期化
	GAUGE4 *gauge4 = gaugeWk4;				// gauge4のポインターを初期化
	GAUGE5 *gauge5 = gaugeWk5;				// gauge5のポインターを初期化
	GAUGE6 *gauge6 = gaugeWk6;				// gauge6のポインターを初期化


		// 頂点座標の設定
		gauge->vertexWk[0].vtx = D3DXVECTOR3(gauge->pos.x, gauge->pos.y, 0.0f);
		gauge->vertexWk[1].vtx = D3DXVECTOR3(gauge->pos.x + GAUGE_SIZE_X, gauge->pos.y, 0.0f);
		gauge->vertexWk[2].vtx = D3DXVECTOR3(gauge->pos.x, gauge->pos.y + GAUGE_SIZE_Y, 0.0f);
		gauge->vertexWk[3].vtx = D3DXVECTOR3(gauge->pos.x + GAUGE_SIZE_X, gauge->pos.y + GAUGE_SIZE_Y, 0.0f);

		// rhwの設定
		gauge->vertexWk[0].rhw =
			gauge->vertexWk[1].rhw =
			gauge->vertexWk[2].rhw =
			gauge->vertexWk[3].rhw = 1.0f;

		// 反射光の設定
		gauge->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		gauge->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		gauge->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		gauge->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// テクスチャ座標の設定
		gauge->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		gauge->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		gauge->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		gauge->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);


		//頂点座標の設定
		gauge2->vertexWk2[0].vtx = D3DXVECTOR3(gauge2->pos.x, gauge2->pos.y, 0.0f);
		gauge2->vertexWk2[1].vtx = D3DXVECTOR3(gauge2->pos.x + GAUGE2_SIZE_X, gauge2->pos.y, 0.0f);
		gauge2->vertexWk2[2].vtx = D3DXVECTOR3(gauge2->pos.x, gauge2->pos.y + GAUGE2_SIZE_Y, 0.0f);
		gauge2->vertexWk2[3].vtx = D3DXVECTOR3(gauge2->pos.x + GAUGE2_SIZE_X, gauge2->pos.y + GAUGE2_SIZE_Y, 0.0f);

		// rhwの設定
		gauge2->vertexWk2[0].rhw =
			gauge2->vertexWk2[1].rhw =
			gauge2->vertexWk2[2].rhw =
			gauge2->vertexWk2[3].rhw = 1.0f;

		// 反射光の設定
		gauge2->vertexWk2[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		gauge2->vertexWk2[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		gauge2->vertexWk2[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		gauge2->vertexWk2[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// テクスチャ座標の設定
		gauge2->vertexWk2[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		gauge2->vertexWk2[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		gauge2->vertexWk2[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		gauge2->vertexWk2[3].tex = D3DXVECTOR2(1.0f, 1.0f);


		//頂点座標の設定
		gauge5->vertexWk5[0].vtx = D3DXVECTOR3(gauge5->pos.x, gauge5->pos.y, 0.0f);
		gauge5->vertexWk5[1].vtx = D3DXVECTOR3(gauge5->pos.x + GAUGE5_SIZE_X, gauge5->pos.y, 0.0f);
		gauge5->vertexWk5[2].vtx = D3DXVECTOR3(gauge5->pos.x, gauge5->pos.y + GAUGE5_SIZE_Y, 0.0f);
		gauge5->vertexWk5[3].vtx = D3DXVECTOR3(gauge5->pos.x + GAUGE5_SIZE_X, gauge5->pos.y + GAUGE5_SIZE_Y, 0.0f);

		// rhwの設定
		gauge5->vertexWk5[0].rhw =
			gauge5->vertexWk5[1].rhw =
			gauge5->vertexWk5[2].rhw =
			gauge5->vertexWk5[3].rhw = 1.0f;

		// 反射光の設定
		gauge5->vertexWk5[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		gauge5->vertexWk5[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		gauge5->vertexWk5[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		gauge5->vertexWk5[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// テクスチャ座標の設定
		gauge5->vertexWk5[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		gauge5->vertexWk5[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		gauge5->vertexWk5[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		gauge5->vertexWk5[3].tex = D3DXVECTOR2(1.0f, 1.0f);


		// 頂点座標の設定
		gauge3->vertexWk3[0].vtx = D3DXVECTOR3(gauge3->pos.x, gauge3->pos.y, 0.0f);
		gauge3->vertexWk3[1].vtx = D3DXVECTOR3(gauge3->pos.x + GAUGE3_SIZE_X, gauge3->pos.y, 0.0f);
		gauge3->vertexWk3[2].vtx = D3DXVECTOR3(gauge3->pos.x, gauge3->pos.y + GAUGE3_SIZE_Y, 0.0f);
		gauge3->vertexWk3[3].vtx = D3DXVECTOR3(gauge3->pos.x + GAUGE3_SIZE_X, gauge3->pos.y + GAUGE3_SIZE_Y, 0.0f);

		// rhwの設定
		gauge3->vertexWk3[0].rhw =
			gauge3->vertexWk3[1].rhw =
			gauge3->vertexWk3[2].rhw =
			gauge3->vertexWk3[3].rhw = 1.0f;

		// 反射光の設定
		gauge3->vertexWk3[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		gauge3->vertexWk3[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		gauge3->vertexWk3[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		gauge3->vertexWk3[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// テクスチャ座標の設定
		gauge3->vertexWk3[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		gauge3->vertexWk3[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		gauge3->vertexWk3[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		gauge3->vertexWk3[3].tex = D3DXVECTOR2(1.0f, 1.0f);


		//頂点座標の設定
		gauge4->vertexWk4[0].vtx = D3DXVECTOR3(gauge4->pos.x, gauge4->pos.y, 0.0f);
		gauge4->vertexWk4[1].vtx = D3DXVECTOR3(gauge4->pos.x + GAUGE4_SIZE_X, gauge4->pos.y, 0.0f);
		gauge4->vertexWk4[2].vtx = D3DXVECTOR3(gauge4->pos.x, gauge4->pos.y + GAUGE4_SIZE_Y, 0.0f);
		gauge4->vertexWk4[3].vtx = D3DXVECTOR3(gauge4->pos.x + GAUGE4_SIZE_X, gauge4->pos.y + GAUGE4_SIZE_Y, 0.0f);

		// rhwの設定
		gauge4->vertexWk4[0].rhw =
			gauge4->vertexWk4[1].rhw =
			gauge4->vertexWk4[2].rhw =
			gauge4->vertexWk4[3].rhw = 1.0f;

		// 反射光の設定
		gauge4->vertexWk4[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		gauge4->vertexWk4[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		gauge4->vertexWk4[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		gauge4->vertexWk4[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// テクスチャ座標の設定
		gauge4->vertexWk4[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		gauge4->vertexWk4[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		gauge4->vertexWk4[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		gauge4->vertexWk4[3].tex = D3DXVECTOR2(1.0f, 1.0f);


		//頂点座標の設定
		gauge6->vertexWk6[0].vtx = D3DXVECTOR3(gauge6->pos.x, gauge6->pos.y, 0.0f);
		gauge6->vertexWk6[1].vtx = D3DXVECTOR3(gauge6->pos.x + GAUGE6_SIZE_X, gauge6->pos.y, 0.0f);
		gauge6->vertexWk6[2].vtx = D3DXVECTOR3(gauge6->pos.x, gauge6->pos.y + GAUGE6_SIZE_Y, 0.0f);
		gauge6->vertexWk6[3].vtx = D3DXVECTOR3(gauge6->pos.x + GAUGE6_SIZE_X, gauge6->pos.y + GAUGE_SIZE_Y, 0.0f);

		// rhwの設定
		gauge6->vertexWk6[0].rhw =
			gauge6->vertexWk6[1].rhw =
			gauge6->vertexWk6[2].rhw =
			gauge6->vertexWk6[3].rhw = 1.0f;

		// 反射光の設定
		gauge6->vertexWk6[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		gauge6->vertexWk6[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		gauge6->vertexWk6[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		gauge6->vertexWk6[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// テクスチャ座標の設定
		gauge6->vertexWk6[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		gauge6->vertexWk6[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		gauge6->vertexWk6[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		gauge6->vertexWk6[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	return S_OK;
}
//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexGauge(void)
{
	GAUGE *gauge = gaugeWk;					// gaugeのポインターを初期化
	GAUGE2 *gauge2 = gaugeWk2;				// gauge2のポインターを初期化
	GAUGE3 *gauge3 = gaugeWk3;				// gauge3のポインターを初期化
	GAUGE4 *gauge4 = gaugeWk4;				// gauge4のポインターを初期化
	GAUGE5 *gauge5 = gaugeWk5;				// gauge5のポインターを初期化
	GAUGE6 *gauge6 = gaugeWk6;				// gauge6のポインターを初期化

	CHARA *chara = GetPlayer(0);

		// 頂点座標の設定
		gauge2->vertexWk2[0].vtx = D3DXVECTOR3(gauge2->pos.x-0.5f, gauge2->pos.y - 0.5f, 0.0f);
		gauge2->vertexWk2[1].vtx = D3DXVECTOR3(gauge2->pos.x -0.5f, gauge2->pos.y - 0.5f, 0.0f);
		gauge2->vertexWk2[2].vtx = D3DXVECTOR3(gauge2->pos.x - 0.5f, gauge2->pos.y + chara[0].HPzan * 2 - 0.5f, 0.0f);
		gauge2->vertexWk2[3].vtx = D3DXVECTOR3(gauge2->pos.x - 0.5f, gauge2->pos.y + chara[0].HPzan * 2 - 0.5f, 0.0f);

		gauge->vertexWk[0].vtx = D3DXVECTOR3(gauge->pos.x-0.5f, gauge->pos.y-0.5f, 0.0f);
		gauge->vertexWk[1].vtx = D3DXVECTOR3(gauge->pos.x + GAUGE_SIZE_X-0.5f, gauge->pos.y-0.5f, 0.0f);
		gauge->vertexWk[2].vtx = D3DXVECTOR3(gauge->pos.x-0.5f, gauge->pos.y + GAUGE_SIZE_Y-0.5f, 0.0f);
		gauge->vertexWk[3].vtx = D3DXVECTOR3(gauge->pos.x + GAUGE_SIZE_X-0.5f, gauge->pos.y + GAUGE_SIZE_Y-0.5f, 0.0f);

		gauge5->vertexWk5[0].vtx = D3DXVECTOR3(gauge5->pos.x - 0.5f, gauge5->pos.y - 0.5f, 0.0f);
		gauge5->vertexWk5[1].vtx = D3DXVECTOR3(gauge5->pos.x + GAUGE5_SIZE_X - 0.5f, gauge5->pos.y - 0.5f, 0.0f);
		gauge5->vertexWk5[2].vtx = D3DXVECTOR3(gauge5->pos.x - 0.5f, gauge5->pos.y + GAUGE5_SIZE_Y - 0.5f, 0.0f);
		gauge5->vertexWk5[3].vtx = D3DXVECTOR3(gauge5->pos.x + GAUGE5_SIZE_X - 0.5f, gauge5->pos.y + GAUGE5_SIZE_Y - 0.5f, 0.0f);


		// 頂点座標の設定
		gauge4->vertexWk4[0].vtx = D3DXVECTOR3(gauge4->pos.x - 0.5f, gauge4->pos.y - 0.5f, 0.0f);
		gauge4->vertexWk4[1].vtx = D3DXVECTOR3(gauge4->pos.x - 0.5f, gauge4->pos.y - 0.5f, 0.0f);
		gauge4->vertexWk4[2].vtx = D3DXVECTOR3(gauge4->pos.x - 0.5f, gauge4->pos.y + chara[1].HPzan * 2 - 0.5f, 0.0f);
		gauge4->vertexWk4[3].vtx = D3DXVECTOR3(gauge4->pos.x - 0.5f, gauge4->pos.y + chara[1].HPzan * 2 - 0.5f, 0.0f);

		gauge3->vertexWk3[0].vtx = D3DXVECTOR3(gauge3->pos.x - 0.5f, gauge3->pos.y - 0.5f, 0.0f);
		gauge3->vertexWk3[1].vtx = D3DXVECTOR3(gauge3->pos.x + GAUGE3_SIZE_X - 0.5f, gauge3->pos.y - 0.5f, 0.0f);
		gauge3->vertexWk3[2].vtx = D3DXVECTOR3(gauge3->pos.x - 0.5f, gauge3->pos.y + GAUGE3_SIZE_Y - 0.5f, 0.0f);
		gauge3->vertexWk3[3].vtx = D3DXVECTOR3(gauge3->pos.x + GAUGE3_SIZE_X - 0.5f, gauge3->pos.y + GAUGE3_SIZE_Y - 0.5f, 0.0f);

		gauge6->vertexWk6[0].vtx = D3DXVECTOR3(gauge6->pos.x - 0.5f, gauge6->pos.y - 0.5f, 0.0f);
		gauge6->vertexWk6[1].vtx = D3DXVECTOR3(gauge6->pos.x + GAUGE6_SIZE_X - 0.5f, gauge6->pos.y - 0.5f, 0.0f);
		gauge6->vertexWk6[2].vtx = D3DXVECTOR3(gauge6->pos.x - 0.5f, gauge6->pos.y + GAUGE6_SIZE_Y - 0.5f, 0.0f);
		gauge6->vertexWk6[3].vtx = D3DXVECTOR3(gauge6->pos.x + GAUGE6_SIZE_X - 0.5f, gauge6->pos.y + GAUGE6_SIZE_Y - 0.5f, 0.0f);

}
//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetTextuerGauge(void)
{
	GAUGE2 *gauge2 = gaugeWk2;				// gauge2のポインターを初期化
	GAUGE4 *gauge4 = gaugeWk4;				// gauge4のポインターを初期化

	CHARA *chara = GetPlayer(0);

		// テクスチャ座標の設定
		gauge2->vertexWk2[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		gauge2->vertexWk2[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		gauge2->vertexWk2[2].tex = D3DXVECTOR2(0.0f, (float)chara[0].HPzan / chara[0].HP);
		gauge2->vertexWk2[3].tex = D3DXVECTOR2(1.0f, (float)chara[0].HPzan / chara[0].HP);

		// テクスチャ座標の設定
		gauge4->vertexWk4[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		gauge4->vertexWk4[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		gauge4->vertexWk4[2].tex = D3DXVECTOR2(0.0f, (float)chara[1].HPzan / chara[1].HP);
		gauge4->vertexWk4[3].tex = D3DXVECTOR2(1.0f, (float)chara[1].HPzan / chara[1].HP);
}
//=============================================================================
// gauge取得関数
//=============================================================================
GAUGE *GetGauge(int no)
{
	return(&gaugeWk[no]);
}
GAUGE2 *GetGauge2(int no)
{
	return(&gaugeWk2[no]);
}
GAUGE3 *GetGauge3(int no)
{
	return(&gaugeWk3[no]);
}
GAUGE4 *GetGauge4(int no)
{
	return(&gaugeWk4[no]);
}
GAUGE5 *GetGauge5(int no)
{
	return(&gaugeWk5[no]);
}
GAUGE6 *GetGauge6(int no)
{
	return(&gaugeWk6[no]);
}

