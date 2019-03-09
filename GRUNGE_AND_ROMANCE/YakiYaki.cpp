//=============================================================================
//
// やきやき処理 [YakiYaki.cpp]
// Author : HAL東京 GP11B341-01 80163 飯塚春輝
//
//=============================================================================
#include "Struct.h"
#include "YakiYaki.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
ITEM yakiyakiWk[YAKIYAKI_NUM];	// アイテム構造体

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitYakiYaki(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int in = 0; in < YAKIYAKI_NUM; in++)
	{
		// 位置・回転・スケールの初期設定
		yakiyakiWk[in].pos = D3DXVECTOR3(CreateRandomFloat(-100.0f, 100.0f), 0.0f, CreateRandomFloat(-10.0f, 10.0f));
		yakiyakiWk[in].rot = D3DXVECTOR3(0.0f, YAKIYAKI_DIRECTION, 0.0f);
		yakiyakiWk[in].scl = D3DXVECTOR3(YAKIYAKI_SCALE, YAKIYAKI_SCALE, YAKIYAKI_SCALE);

		yakiyakiWk[in].D3DTexture = NULL;
		yakiyakiWk[in].D3DXMesh = NULL;
		yakiyakiWk[in].D3DXBuffMat = NULL;
		yakiyakiWk[in].NumMat = 0;

		if (type == 0)
		{
			// Xファイルの読み込み
			if (FAILED(D3DXLoadMeshFromX(YAKIYAKI_XFILE,		// 読み込むモデルファイル名(Xファイル)
				D3DXMESH_SYSTEMMEM,							// メッシュの作成オプションを指定
				pDevice,									// IDirect3DDevice9インターフェイスへのポインタ
				NULL,										// 隣接性データを含むバッファへのポインタ
				&yakiyakiWk[in].D3DXBuffMat,					// マテリアルデータを含むバッファへのポインタ
				NULL,										// エフェクトインスタンスの配列を含むバッファへのポインタ
				&yakiyakiWk[in].NumMat,						// D3DXMATERIAL構造体の数
				&yakiyakiWk[in].D3DXMesh)))					// ID3DXMeshインターフェイスへのポインタのアドレス
			{
				return E_FAIL;
			}

#if 0
			// テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
				TEXTURE_FILENAME,		// ファイルの名前
				&yakiyakiWk[en].D3DTexture);	// 読み込むメモリー
#endif
		}
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitYakiYaki(void)
{
	for (int in = 0; in < YAKIYAKI_NUM; in++)
	{
		if (yakiyakiWk[in].D3DTexture != NULL)
		{	// テクスチャの開放
			yakiyakiWk[in].D3DTexture->Release();
			yakiyakiWk[in].D3DTexture = NULL;
		}

		if (yakiyakiWk[in].D3DXMesh != NULL)
		{	// メッシュの開放
			yakiyakiWk[in].D3DXMesh->Release();
			yakiyakiWk[in].D3DXMesh = NULL;
		}

		if (yakiyakiWk[in].D3DXBuffMat != NULL)
		{	// マテリアルの開放
			yakiyakiWk[in].D3DXBuffMat->Release();
			yakiyakiWk[in].D3DXBuffMat = NULL;
		}
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateYakiYaki(void)
{


}

//=============================================================================
// 描画処理
//=============================================================================
void DrawYakiYaki(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate, g_mtxWorld;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;


	for (int in = 0; in < YAKIYAKI_NUM; in++)
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_mtxWorld);

		// スケールを反映
		D3DXMatrixScaling(&mtxScl, yakiyakiWk[in].scl.x, yakiyakiWk[in].scl.y, yakiyakiWk[in].scl.z);
		D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxScl);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, yakiyakiWk[in].rot.y, yakiyakiWk[in].rot.x, yakiyakiWk[in].rot.z);
		D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxRot);

		// 移動を反映
		D3DXMatrixTranslation(&mtxTranslate, yakiyakiWk[in].pos.x, yakiyakiWk[in].pos.y, yakiyakiWk[in].pos.z);
		D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxTranslate);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld);

		// 現在のマテリアルを取得
		pDevice->GetMaterial(&matDef);

		// マテリアル情報に対するポインタを取得
		pD3DXMat = (D3DXMATERIAL*)yakiyakiWk[in].D3DXBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)yakiyakiWk[in].NumMat; nCntMat++)
		{
			// マテリアルの設定
			pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

			// テクスチャの設定
			pDevice->SetTexture(0, yakiyakiWk[in].D3DTexture);

			// 描画
			yakiyakiWk[in].D3DXMesh->DrawSubset(nCntMat);
		}

		// マテリアルをデフォルトに戻す
		pDevice->SetMaterial(&matDef);

	}
}

//=============================================================================
// アイテムの情報を取得する
// 引数：in やきやき番号
//=============================================================================
ITEM *GetYakiYaki(int in)
{
	return &yakiyakiWk[in];
}